#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <string>


unsigned int djbhash(std::string ulaz, unsigned int max) {
    unsigned int suma=5381;
// 5381 je pocetna vrijednost
// koja poboljsava distribuciju
    for (int i(0); i<ulaz.length(); i++)
        suma = suma*33 + ulaz[i];
    return suma % max;
}


const int defaultkapacitet = 10;
const int defaultK = 10;

using namespace std;
template<typename TipKljuca,typename TipVrijednosti>
class Mapa{
public:
    Mapa(){}
    virtual ~Mapa(){}

    virtual TipVrijednosti &operator[](const TipKljuca &kljuc) = 0;
    virtual const TipVrijednosti &operator[](const TipKljuca & kljuc) const = 0;
    virtual int brojElemenata()const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipKljuca & kljuc) = 0;

};

template<typename TipKljuca,typename TipVrijednosti>
class HashMapa : public Mapa<TipKljuca,TipVrijednosti>{

    TipKljuca * nizk;
    TipVrijednosti *nizv;
    int max;
    int brojEl;
    TipKljuca praznoMjesto;
    TipVrijednosti defaultVrijednost;

//    unsigned int definisiHashFunkciju ( unsigned int  *funkcija(const TipKljuca &k, unsigned int max) ){

//    }

    int h(const TipKljuca &k,int i) const{
        return (k % max + i) % max;
    }

    bool UmetniHash(const TipKljuca &k){
        int j, i = 0;
        do{
            j = h(k,i);
            if(nizk[j] == praznoMjesto || nizk[j] == -2){
                nizk[j] = k;
                nizv[j] = TipVrijednosti();
                brojEl++;
                return  true;
            }
            else
                i = i + 1;
        }while(i < max);
        return false;
    }

    int TraziHash(const TipKljuca &k)const {
        int indeks,i(0);
        do{
            indeks = h(k,i);
            if(nizk[indeks] == k){
                return  indeks;
            }else
                i = i + 1;
        }while(nizk[indeks] != praznoMjesto && i != max);
        return praznoMjesto;
    }

public:
    HashMapa(): nizk(new TipKljuca[defaultK]),nizv(new TipVrijednosti[defaultK]),max(defaultK),brojEl(0),praznoMjesto(-1),defaultVrijednost(TipVrijednosti()) {
        for(int i = 0; i < max;i++){
            nizk[i] = praznoMjesto;
        }

        for(int i = 0; i < max;i++){
            nizv[i] = praznoMjesto;
        }
    }

    void Prikazi()const{
        for(int i = 0; i < max;i++){
            std::cout<< nizk[i]<<" ";
        }
        std::cout<<std::endl;
        for(int i = 0; i < max;i++){
            std::cout<< nizv[i]<<" ";
        }
    }

    TipVrijednosti &operator[](const TipKljuca &kljuc) override;
    const TipVrijednosti &operator[](const TipKljuca & kljuc) const override;
    int brojElemenata()const override { return brojEl; }
    void obrisi() override;
    void obrisi(const TipKljuca & kljuc) override;

    HashMapa(const HashMapa &m);
    HashMapa(HashMapa &&m);
    HashMapa &operator=(const HashMapa &m);
    HashMapa &operator=(HashMapa &&m);
};

template<typename TipKljuca,typename TipVrijednosti>
TipVrijednosti &HashMapa<TipKljuca,TipVrijednosti>::operator[](const TipKljuca & kljuc){
    if(TraziHash(kljuc) != praznoMjesto){
        return nizv[TraziHash(kljuc)];
    }

    UmetniHash(kljuc);
    return nizv[TraziHash(kljuc)];
}

template<typename TipKljuca,typename TipVrijednosti>
const TipVrijednosti &HashMapa<TipKljuca,TipVrijednosti>::operator[](const TipKljuca & kljuc) const {
    if(TraziHash(kljuc) != praznoMjesto){
        return nizv[TraziHash(kljuc)];
    }

    return defaultVrijednost;
}
template<typename TipKljuca,typename TipVrijednosti>
void HashMapa<TipKljuca,TipVrijednosti>::obrisi(){
    brojEl= 0;
}
template<typename TipKljuca,typename TipVrijednosti>
void HashMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca & kljuc){
    if(TraziHash(kljuc) == praznoMjesto) throw std::domain_error("Nista za obrisati");

    int indeks = TraziHash(kljuc);
    nizk[indeks] = -2;
    nizv[indeks] = -2;
    brojEl--;
}
// .............................................................................................

template<typename TipKljuca,typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>::HashMapa(const HashMapa &m) : nizk(new TipKljuca[m.max]),nizv(new TipVrijednosti[m.max]),max (m.max),brojEl(m.brojEl){
    std::copy(m.nizk, m.nizk + m.max , nizk);
    std::copy(m.nizv, m.nizv + m.max , nizv);
}

template<typename TipKljuca,typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti>::HashMapa(HashMapa &&m) : max(m.max),brojEl(m.brojEl){

    nizk = m.nizk;
    m.nizk = nullptr;

    nizv = m.nizv;
    m.nizv = nullptr;

    m.brojEl = 0;
}

template<typename TipKljuca,typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti> &HashMapa<TipKljuca,TipVrijednosti>::operator=(const HashMapa &m){
    if(this == &m) return *this;

    TipKljuca * novi_prostor = new TipKljuca[m.max];
    delete[] nizk;
    nizk = novi_prostor;

    TipVrijednosti * np = new TipVrijednosti[m.max];
    delete[] nizv;
    nizv = np;

    max = m.max;
    brojEl = m.brojEl;

    std::copy(m.nizk, m.nizk + m.max,nizk);
    std::copy(m.nizv, m.nizv + m.max,nizv);

    return *this;
}
template<typename TipKljuca,typename TipVrijednosti>
HashMapa<TipKljuca,TipVrijednosti> &HashMapa<TipKljuca,TipVrijednosti>::operator =(HashMapa &&m){
    if(this == &m) return *this;
    std::swap(nizk,m.nizk);
    std::swap(nizv,m.nizv);
    std::swap(max,m.max);
    std::swap(brojEl,m.brojEl);
    return *this;
}

int main(){
    HashMapa<int,int> hash;
    /*  hash.UmetniHash(12);
      hash.Prikazi();
      int n = hash.TraziHash(12);
      std::cout<< n;
      */
    hash[12] = 10;
    hash[13] = 23;
    hash[10] = 54;
    hash[15] = 87;
    hash[18] = 91;
    // hash[12] = 34; - KOLIZIJA (RIJESITI)

    hash.Prikazi();
    // std::cout<<hash.brojElemenata();
    std::cout<<std::endl;
    HashMapa<int,int> h = (hash);
    h.Prikazi();

    return 0;
}
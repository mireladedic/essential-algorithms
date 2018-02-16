#include <iostream>
template<typename Tip>
class OtvorenoAdr{
private:
    void operator=(const OtvorenoAdr &);
    OtvorenoAdr(const OtvorenoAdr &);

protected:
    Tip * Elementi;
    Tip PraznoMjesto;
    int velicina;

    virtual int h(const Tip & k, int i ) const = 0;
public:
    OtvorenoAdr(Tip PraznoMjesto,int velicina = 100);
    ~OtvorenoAdr();
    bool UmetniHash(const Tip &kljuc);
    int TraziHash(const Tip& kljuc) const;
    void Prikazi() const ;
};

template<typename Tip>
OtvorenoAdr<Tip>::OtvorenoAdr(Tip PraznoMjesto, int velicina) : Elementi(new Tip[velicina]),PraznoMjesto(PraznoMjesto),velicina(velicina){
    for(int i = 0; i < velicina; i++){
        Elementi[i] = PraznoMjesto;
    }
}

template<typename Tip>
OtvorenoAdr<Tip>::~OtvorenoAdr(){
    delete[]Elementi;
}

template<typename Tip>
bool OtvorenoAdr<Tip>::UmetniHash(const Tip &kljuc) {
    int i,j = 0;
    do{
        j = h(kljuc,i);
        if(Elementi[j] == PraznoMjesto){
            Elementi[j] = kljuc;
            return true;
        }else{
            i = i+1;
        }
    }while(i < velicina);

    return false;
}
template<typename Tip>
int OtvorenoAdr<Tip>::TraziHash(const Tip &kljuc) const {
    int indeks,i(0);
    do{
        indeks = h(kljuc,i);
        if(Elementi[indeks] == kljuc)
            return indeks;
        else
            i = i + 1;
    }while(Elementi[indeks] != PraznoMjesto && i != velicina);

    return PraznoMjesto;
}

template<typename Tip>
void OtvorenoAdr<Tip>::Prikazi()const{
    for(int i = 0; i < velicina; i++)
        std::cout<<Elementi[i]<< " ";
}

class LinearniHash : public OtvorenoAdr<int>{
private:
    int h(const int &k,int i)const{
        return(k % velicina + i) % velicina;
    }

public:
    LinearniHash(int PraznoMjesto = -1,int velicina = 10) : OtvorenoAdr<int>(PraznoMjesto,velicina){}
};

class DvostrukiHash : public OtvorenoAdr<int>{
private:
    int h(const int &k,int i)const{
        return (k % 13 + i * (1 + k % 11)) % 13;
    }
public:
    DvostrukiHash(int PraznoMjesto = -1,int velicina = 10) : OtvorenoAdr<int>(PraznoMjesto,velicina){}
};
int main() {
    LinearniHash linhash(-1,20);
    linhash.UmetniHash(12);
    linhash.UmetniHash(34);
    linhash.UmetniHash(58);
    linhash.Prikazi();
    std::cout<< linhash.TraziHash(34);
    return 0;
}
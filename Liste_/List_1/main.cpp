#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename Tip>
class Lista{
private:
    void operator = (const Lista &);
    Lista(const Lista &);

public:
    Lista(){}
    virtual ~Lista(){}
    virtual void Brisi() = 0; // BRISE CITAVU LISTU
    virtual bool Umetni(const Tip&) = 0;
    virtual bool Dodaj(const Tip&) = 0;
    virtual Tip Izbaci() = 0;// IZBACUJE TEKUCI ELEMENT

    virtual void Idi_na_pocetak() = 0;
    virtual void Idi_na_kraj() = 0;
    virtual void Idi_na_prethodni() = 0;
    virtual void Idi_na_sljedeci() = 0;
    virtual void Idi_na_poziciju(int indeks) = 0;
    virtual int LDuzina() const = 0;
    virtual int DDuzina() const = 0;
    virtual const Tip& DajTekuciElement() const = 0;
    virtual int Trenutni() const = 0;
    virtual void ObrniPoredak() = 0;
    virtual int NadjiMin()const = 0;
    virtual int NadjiMax()const = 0;
    virtual Tip IzbaciMin() = 0;
    virtual Tip IzbaciMax() = 0;
    virtual void IzbaciMdoN(int m,int n) = 0;
};
//.................................................................
template<typename Tip>
class NizLista : public Lista<Tip> {
    int kapacitet,velicina,tekuci;
    Tip * niz;
//........................................................................................
    void povecaj_kapacitet(){
        if(velicina == kapacitet){
            kapacitet *= 2;
            Tip* novi = new Tip[kapacitet];
            //std::copy(niz,niz + velicina,novi);
            for(int i = 0; i < velicina;i++)
            novi[i] = niz[i];
            delete[] niz;
            niz = novi;
            }
    }
public:
    NizLista(int kapacitet) :kapacitet(kapacitet),velicina(0), tekuci(0),niz(new Tip[kapacitet]){}
    ~NizLista(){ delete[]niz; }
   //................................................
    void Idi_na_pocetak() override{ tekuci = 0; }
    //...............................................
    void Idi_na_kraj() override { tekuci = velicina - 1;}
    //..................................................
    void Idi_na_prethodni() override {
        if(tekuci != 0){
            tekuci = tekuci - 1;
        }
    }
    //.................................................
    void Idi_na_sljedeci() override{
        if(tekuci != velicina){
            tekuci = tekuci + 1;
        }
    }
    //.....................................................
    void Idi_na_poziciju(int indeks) override{
        if(indeks < 0 || indeks > velicina) throw std::range_error("Index izvan opsega!");
        tekuci = indeks;
    }
    //.......................................................
     int LDuzina() const override{
        return tekuci;
     }
     //..............................
     int DDuzina() const override{
        return velicina - tekuci;
     }
     //...............................
      const Tip& DajTekuciElement() const override{
            return niz[tekuci];
      }

    void Brisi() override; // BRISE CITAVU LISTU
    bool Umetni(const Tip&) override;
    bool Dodaj(const Tip&)  override;
    Tip Izbaci() override;// IZBACUJE

    void Ispisi()const{
        for(int i = 0; i < velicina; i++) std::cout<<niz[i]<< "|";
        std::cout<<"\n";
    }

    int Trenutni() const override{
        return tekuci;
    }

    void ObrniPoredak()override;
    int NadjiMin()const override;
    int NadjiMax()const override;
    Tip IzbaciMin() override;
    Tip IzbaciMax()override;
    void IzbaciMdoN(int m,int n)override;
};
//................................................
template<typename Tip>
void NizLista<Tip>::Brisi() {
    delete[]niz;
    velicina = tekuci = 0;
    niz = new Tip[kapacitet];
}
//...............................................
template<typename Tip>
bool NizLista<Tip>::Umetni(const Tip& x) {
    povecaj_kapacitet();
    if(velicina < kapacitet){
        for(int i = velicina; i > tekuci ; i--){
            niz[i] = niz[i - 1];
        }
        niz[tekuci] = x;
        velicina++;
        return true;
    }
    return false;
}
//.................................................
template<typename Tip>
bool NizLista<Tip>::Dodaj(const Tip& x){
    povecaj_kapacitet();
    if(velicina < kapacitet){
        niz[velicina] = x;
        velicina++;
        return true;
    }
    return false;
}
//....................................................
template<typename Tip>
Tip NizLista<Tip>::Izbaci() {
    if(tekuci == velicina) throw std::range_error("Nista za izbaciti!");

   Tip x = niz[tekuci];
    for(int i = tekuci; i <velicina - 1; i++){
        niz[i] = niz[i + 1];
    }
    velicina--;
    return x;
}
//.....................................................................
template<typename Tip>
void NizLista<Tip>::ObrniPoredak(){
    for(int i = 0; i < velicina/2; i++){
        // niz[i]  = niz[(velicina - 1) - i]; std::cout<<i<<" "<< velicina - 1 - i<<std::endl;
        Tip temp = niz[i];
        niz[i] = niz[velicina - 1 - i];
        niz[velicina - 1 - i] = temp;
       // std::swap(niz[i],niz[velicina - 1 - i]);
    }
    int tren_tek = velicina;
    for(int i = 0; i < tekuci; i++){ tren_tek--;}
    tekuci = tren_tek;
    // std::cout<<LDuzina()<<"| " <<DDuzina()<<std::endl;
}
//..................................................................
template<typename Tip>
int NizLista<Tip>::NadjiMin()const{
    Tip min_ = niz[0]; int mini,indeks;
    for(int i = 0; i < velicina;i++){
            if(niz[i] <= min_){
                if(min_ == niz[i] && mini < i){indeks = mini; return indeks;}
                 min_= niz[i];
                 mini = i;
            }
    }
    return mini;
 }

//....................................................
template<typename Tip>
int NizLista<Tip>::NadjiMax()const{
    Tip maks = 0; int maksi;
    for(int i = 0; i < velicina; i++){
            if(niz[i] >= maks){
                if(niz[i] == maks && maksi < i){ return maksi;}
                maks = niz[i];
                maksi = i;
            }
    }
   return maksi;
}
//...............................
template<typename Tip>
Tip NizLista<Tip>::IzbaciMin(){
    int indeks = NadjiMin();
    if(indeks== velicina) throw std::range_error("Min izvan opsega!");
    Tip izbaceni = niz[indeks];
    for(int i = indeks;i < velicina - 1; i++){
        niz[i] = niz[i + 1];
    }
    velicina--;
    return izbaceni;
}
//......................................
template<typename Tip>
Tip NizLista<Tip>::IzbaciMax(){
    int indeks = NadjiMax();
    if(indeks== velicina) throw std::range_error("Min izvan opsega!");
    Tip izbaceni = niz[indeks];
    for(int i = indeks;i < velicina - 1; i++){
        niz[i] = niz[i + 1];
    }
    velicina--;
    return izbaceni;
}
//..............................................
template<typename Tip>
void NizLista<Tip>::IzbaciMdoN(int m,int n){
    for(int i = m; i <= n; i++){
        if(m == velicina) throw std::range_error("M_N izvan opsega!");
        for(int i = m; i < velicina - 1; i++)
            niz[i] = niz[i + 1];
            velicina--;
    }
}
//.............................................................

int main(){
    try{
    NizLista<int> lista(5);
    lista.Dodaj(3);
    lista.Dodaj(2);
    lista.Dodaj(4);
    lista.Dodaj(5);
    lista.Dodaj(9);
    lista.Ispisi();
    lista.ObrniPoredak();
    lista.Ispisi();
   /* std::cout<<lista.LDuzina()<<"|"<<lista.DDuzina()<<std::endl;
    lista.Idi_na_poziciju(2);
    std::cout<<lista.DajTekuciElement()<<std::endl;

    lista.IzbaciMdoN(0,2);
    lista.Ispisi();
    */
    }catch(std::range_error izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
   /*
    lista.ObrniPoredak();
    lista.Ispisi();
    std::cout<<lista.NadjiMin()<<std::endl;
    std::cout<<lista.NadjiMax()<<std::endl;
    lista.Izbaci();
    lista.Ispisi();
    lista.Dodaj(6);
    lista.Dodaj(7);
    lista.Ispisi();
    lista.Umetni(18);
    lista.Ispisi();
    lista.Idi_na_kraj();
    lista.Umetni(19);
    lista.Ispisi();
    lista.Idi_na_poziciju(2);
    lista.Umetni(16);
    lista.Ispisi();
    std::cout<<lista.DajTekuciElement()<<"|"<<std::endl;
    std::cout<<lista.LDuzina()<<"|"<<lista.DDuzina()<<std::endl;
        lista.Idi_na_prethodni();
    std::cout<<lista.DajTekuciElement()<<"|"<<std::endl;
        lista.Idi_na_sljedeci();
        lista.Idi_na_sljedeci();
    std::cout<<lista.DajTekuciElement()<<"|"<<std::endl;
    lista.Izbaci();
    lista.Ispisi();
    lista.Umetni(10);
    lista.Ispisi();
    lista.Idi_na_kraj();
    std::cout<<lista.DajTekuciElement()<<"|"<<std::endl;
    lista.Izbaci();
    lista.Ispisi();
    lista.Idi_na_pocetak();
    std::cout<<lista.DajTekuciElement()<<"|"<<std::endl;
    lista.Izbaci();
    lista.Ispisi();
    lista.Brisi();
    lista.Dodaj(1);
    lista.Ispisi();
    */
    return 0;
}

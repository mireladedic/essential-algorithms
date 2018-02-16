/* Created on 05.12.2017,Wednesday,00:49
 * By Mirela Dedic */

#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename Tip>
class Lista{
private :
    void operator = (const Lista &l); // ... ZASTITA ZA DODJELU
    Lista(const Lista &l); // ZASTITS ZA KONSTRUKTOR KOPIJE

public :
    Lista(){} // ...PODRAZUMIJEVANI KONSTRUKTOR
    virtual ~Lista(){} //...BAZNI DESTRUKTOR
    virtual void Brisi() = 0;
    virtual bool Umetni(const Tip &) = 0;
    virtual bool Dodaj(const Tip &) = 0;
    virtual Tip Izbaci()= 0;
    virtual void IdiNaPocetak() = 0;
    virtual void IdiNaKraj() = 0;
    virtual void IdiNaSljedeci() = 0;
    virtual void IdiNaPrethodni() = 0;
    virtual void IdiNaPoziciju(int i) = 0;
    virtual int LDuzina() const = 0;
    virtual int DDuzina() const = 0;
    virtual const Tip &DajTekuciElement() const = 0;
};

template<typename Tip>
class NizLista: public Lista<Tip>{
private:
    int kapacitet,duzina,trenutni;
    Tip * niz;
public:
    NizLista(int kapacitet,int duzina = 0,int trenutni = 0) : kapacitet(kapacitet),duzina(0),trenutni(0), niz(new Tip[kapacitet]){}
    ~NizLista(){ delete []niz; }
    NizLista(const NizLista &l);
    NizLista(NizLista &&l);
    NizLista &operator = (const NizLista &l);
    NizLista &operator = (NizLista &&l);

    void IdiNaPocetak() override;
    void IdiNaKraj() override;
    void IdiNaSljedeci() override;
    void IdiNaPrethodni() override;
    void IdiNaPoziciju(int i) override;
    bool Umetni(const Tip &) override;
    bool Dodaj(const Tip &) override;
    Tip Izbaci() override;
    void Brisi() override;
    int  Duzina()const  { return duzina; }
    int LDuzina() const override{ return trenutni; }
    int  DDuzina() const override{ return duzina - trenutni;}
    const Tip &DajTekuciElement() const override{
        if(DDuzina() <= 0) throw std::domain_error("Nista za vratiti");
        return niz[trenutni];
    }

    void Prikazi()const{
        for(int i =0; i < duzina; i++)
            std::cout<<niz[i]<<"|";

        std::cout<<"\n";
    }
};
//...........................................
template<typename Tip>
NizLista<Tip>::NizLista(const NizLista &l): kapacitet(l.kapacitet),duzina(l.duzina),trenutni(l.trenutni),niz(new Tip[l.kapacitet]){
    std::copy(l.niz,l.niz + l.duzina,niz);
}
template<typename Tip>
NizLista<Tip>::NizLista(NizLista &&l) : kapacitet(l.kapacitet),duzina(l.duzina),trenutni(l.trenutni),niz(l.niz){
    l.niz = nullptr;
    l.duzina = 0;
}
template<typename Tip>
NizLista<Tip> &NizLista<Tip>::operator = (const NizLista &l){
    Tip *novi_prostor(new Tip[l.kapacitet]);
    delete[] niz;
    kapacitet = l.kapacitet;
    duzina = l.duzina;
    trenutni = l.trenutni;
    niz = novi_prostor;
    std::copy(l.niz,l.niz + l.duzina,niz);
    return *this;

}
/*
template<typename Tip>
 ... AKO IMAMO KOPIRAJ I RAZMIJENI ONDA NE SMIJEMO PRAVITI POMJERAJUCI OPERATOR DODJELE
NizLista &NizLista<Tip>::operator = (NizLista l){
    std::swap(kapacitet,l.kapacitet);
    std::swap(duzina,l.duzina);
    std::swap(trenutni,l.trenutni);
    std::swap(niz,l.niz);
    return *this;
}
*/
template<typename Tip>
NizLista<Tip> &NizLista<Tip>::operator = (NizLista &&l){
    //... POMJERAJUCI OPERATOR= SE MOZE IZVESTI TEHNIKOM KOPIRAJ I RAZMIJENI
    std::swap(kapacitet,l.kapacitet);
    std::swap(duzina,l.duzina);
    std::swap(trenutni,l.trenutni);
    std::swap(niz,l.niz);
    return *this;

    /* if(&l != this){
         delete[] niz;
         kapacitet = l.kapacitet;
         duzina = l.duzina;
         trenutni = l.trenutni;
         niz = l.niz;
         l.niz = nullptr;
     }
     return *this; */
}
template<typename Tip>
void NizLista<Tip>::IdiNaPocetak(){
    trenutni = 0;
}
template<typename Tip>
void NizLista<Tip>::IdiNaKraj(){
    trenutni = duzina - 1;
}
template<typename Tip>
void NizLista<Tip>::IdiNaSljedeci(){
    if(trenutni < duzina)
        trenutni ++;
}
template<typename Tip>
void NizLista<Tip>::IdiNaPrethodni(){
    if(trenutni != 0)
        trenutni --;
}
template<typename Tip>
void NizLista<Tip>::IdiNaPoziciju(int i){
    if(i < 0 || i > duzina) throw std::domain_error("Invalid Index");
    trenutni = i;
}
template<typename Tip>
bool NizLista<Tip>::Umetni(const Tip &element){
    if(duzina < kapacitet){
        for(int i = duzina;i > trenutni; i--)
            niz[i] = niz[i - 1];
        niz[trenutni] = element;
        duzina++;
        return true;
    }
    return false;
}
template<typename Tip>
bool NizLista<Tip>::Dodaj(const Tip &element){
    if(duzina < kapacitet){
        niz[duzina] = element;
        duzina++;
        return true;
    }
    return false;
}
template<typename Tip>
Tip NizLista<Tip>::Izbaci(){
    if(DDuzina() <= 0) throw std::domain_error("Nista za izbaciti!");
    Tip x = niz[trenutni];
    for(int i = trenutni; i < duzina - 1; i++)
        niz[i] = niz[i + 1];
    duzina--;
    return x;
}
template<typename Tip>
void NizLista<Tip>::Brisi(){
    delete[] niz;
    duzina = trenutni = 0;
    niz = new Tip [kapacitet];
}

class IntLista : public NizLista<int>{
private:
    void Zamijeniti(int i,int j);
    void Ispisi() const;
    int L[10] ;

public:
    IntLista(int velicina = 5): NizLista<int>(velicina){}
    ~IntLista(){}

    int SumaElemenata(int prvi,int zadnji) const;
    int SumaElemenata2(int prvi,int zadnji) const;
    void IspisiPermutacije(int i);
    void IspisiPermutacijeKdoM(int k,int m);
    int Prvi()const{return L[0]; }
    int Zadnji()const{ return L[this->Duzina()];}//-1
};

void IntLista::Ispisi()const{
    for(int i = 0; i < NizLista<int>::Duzina();i++)
        std::cout<<L[i]<<'|';
    std::cout<<"\n";
}
//... IZMJENA POZICIJE ELEMENATA
void IntLista::Zamijeniti(int i, int j) {
  /*  int priv;
    priv = L[i];
    L[i] = L[j];
    L[j] = priv; */

    std::swap(L[i],L[j]);
}

int IntLista::SumaElemenata(int prvi, int zadnji) const {

    if(prvi == zadnji) return L[zadnji];
    else
        return L[prvi] + SumaElemenata(prvi+1,zadnji);

}
int IntLista::SumaElemenata2(int prvi, int zadnji) const {
    //... STRATEGIJA PODIJELI PA VLADAJ
    int m,s1,s2;
    if(prvi == zadnji) return L[prvi];
    else{
        m = (prvi + zadnji)/2;
        s1 = SumaElemenata2(prvi,m);
        s2 = SumaElemenata2(m+1,zadnji);
        return  s1 + s2;
    }
}
void IntLista::IspisiPermutacije(int k) {
    if(k = NizLista<int>::Duzina() - 1)
        Ispisi();
    else{
        for(int i = k; i < NizLista<int>::Duzina(); i++) {
            Zamijeniti(k, i);
            IspisiPermutacije(k + 1);
            Zamijeniti(k, i);
        }
    }

}

void IntLista::IspisiPermutacijeKdoM(int k, int m) {
    if(k == m) Ispisi();
    else
        for(int i = k; i < NizLista<int>::Duzina();i++){
        Zamijeniti(k,i);
        IspisiPermutacijeKdoM(k+1,m);
        Zamijeniti(k,i);
    }
}

int main()
{
    IntLista lista;
    lista.Dodaj(2);
    lista.Dodaj(5);
    lista.Dodaj(7);
    lista.Dodaj(9);
    lista.Prikazi();
    std::cout<<"suma elemenata\n";
    //lista.SumaElemenata(*(lista.Prvi()),*(lista.Zadnji()));
   //lista.SumaElemenata(lista.Prvi(),lista.Zadnji());
    std::cout<<"permutacije\n";
    lista.IspisiPermutacije(0);
    std::cout<<"permutacijeKdoN\n";
    lista.IspisiPermutacijeKdoM(0,3);
    return 0;
}

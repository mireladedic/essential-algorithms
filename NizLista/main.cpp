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

    Tip  Niz(int i) const { return *niz(i); }
    void IdiNaPocetak() override;
    void IdiNaKraj() override;
    void IdiNaSljedeci() override;
    void IdiNaPrethodni() override;
    void IdiNaPoziciju(int i) override;
    bool Umetni(const Tip &) override;
    bool Dodaj(const Tip &) override;
    Tip Izbaci() override;
    void Brisi() override;
    int Duzina() const { return  duzina; }
    int LDuzina() const override{ return trenutni; }
    int DDuzina() const override{ return duzina - trenutni;}
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
//........................................................................................
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
int main(){
    NizLista<int> niz;
    niz.Dodaj(3);
    niz.Dodaj(4);
    niz.Dodaj(8);
    niz.Prikazi();
    std::cout<<"BinarnoPretrazivanje\n";
    std::cout<< niz.BinPretrazi(22);
    return 0;
}
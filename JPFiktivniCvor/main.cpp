/*  Created on : 02.12.2017,Friday
    By Mirela Dedic */

#include <iostream>
#include <stdexcept>
template<typename Tip>
class Lista{
private:
    Lista(const Lista &);
    Lista &operator=(const Lista &);
public:
    Lista(){}
    virtual ~Lista(){}
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
class ListaFiktivni : public Lista<Tip>{
    struct Cvor{
        Tip info;
        Cvor *sljedeci;

        Cvor(Tip info,Cvor *sljedeci) : info(info),sljedeci(sljedeci){}
        Cvor(Cvor * sljedeci = 0): sljedeci(sljedeci){}
    };

    Cvor *pocetak,*kraj,*tekuci;
    int lduzina;
    int dduzina;

    void Iniciraj();
    void Unisti();
public:
    ListaFiktivni() { Iniciraj(); }
    ~ListaFiktivni();
    void Brisi() override;
    bool Umetni(const Tip &) override;
    bool Dodaj(const Tip &) override;
    Tip Izbaci() override;

    void IdiNaPocetak() override{
        tekuci = pocetak;
        dduzina += lduzina;
        lduzina = 0;
    }
    void IdiNaKraj() override{
        tekuci = kraj;
        lduzina += dduzina;
        dduzina = 0;
    }

    void IdiNaSljedeci() override;
    void IdiNaPrethodni() override;
    void IdiNaPoziciju(int i) override;
    int LDuzina() const override{ return lduzina;}
    int DDuzina() const override{return dduzina; }
    const Tip &DajTekuciElement() const override;
    void Prikazi()const;
};
template<typename Tip>
void ListaFiktivni<Tip>::Iniciraj(){
        tekuci = pocetak = kraj = new Cvor;
        lduzina = dduzina = 0;
}
template<typename Tip>
void ListaFiktivni<Tip>::Unisti(){
        //.. BRISI SVE
      while(pocetak != 0){
        tekuci = pocetak;
        pocetak = pocetak->sljedeci;
        delete tekuci;
      }
      pocetak = kraj = tekuci = 0;
}
template<typename Tip>
void ListaFiktivni<Tip>::Brisi(){
    Unisti();
    Iniciraj();
}
template<typename Tip>
ListaFiktivni<Tip>::~ListaFiktivni(){ Unisti(); }
template<typename Tip>
bool ListaFiktivni<Tip>::Umetni(const Tip &x){
    //..DODAJE NEGDJE NA SREDINU,NEMA POSEBNIH SLUCAJEVA I POMJERA KRAJ
    tekuci->sljedeci = new Cvor(x,tekuci->sljedeci);
    if(kraj == tekuci)
        kraj = tekuci->sljedeci;
    dduzina++;
    return true;
}

template<typename Tip>
bool ListaFiktivni<Tip>::Dodaj(const Tip &x){
    kraj = kraj->sljedeci = new Cvor(x,0);
    dduzina++;
    return true;
}
template<typename Tip>
Tip ListaFiktivni<Tip>::Izbaci(){
    if(dduzina == 0)
        throw std::domain_error("Nista za izbaciti");
    Tip x = tekuci->sljedeci->info;

    Cvor *temp = tekuci->sljedeci;
    tekuci->sljedeci = temp->sljedeci;
    if(kraj == temp) kraj = tekuci;

    delete temp;
    dduzina--;
    return x;
}
template<typename Tip>
void ListaFiktivni<Tip>::IdiNaPrethodni(){
    if(lduzina != 0){
        Cvor *temp = pocetak;
        while(temp->sljedeci != tekuci){
            temp = temp->sljedeci;
        }
        tekuci = temp;
        lduzina--;
        dduzina++;
    }
}
template<typename Tip>
void ListaFiktivni<Tip>::IdiNaSljedeci(){
    if(dduzina != 0){
        tekuci = tekuci->sljedeci;
        dduzina--;
        lduzina++;
    }
}
template<typename Tip>
void ListaFiktivni<Tip>::IdiNaPoziciju(int i){
    if(i < 0 || i > dduzina + lduzina) throw std::domain_error("Invalid Index");
    int prethodni(0);
    int ld(lduzina);
    dduzina = dduzina + lduzina - i;
    lduzina = i;

    if(i >= ld)
        prethodni = ld;
    else
        tekuci = pocetak;

    for(int j = prethodni;  j < i - 1; j++)
        tekuci = tekuci->sljedeci;
}

template<typename Tip>
const Tip &ListaFiktivni<Tip>::DajTekuciElement()const{
    if(dduzina == 0) throw std::domain_error("Nista za vratiti");
    return tekuci->sljedeci->info;
}
template<typename Tip>
void ListaFiktivni<Tip>::Prikazi()const{
    if(dduzina == 0) throw("Nista za prikazati");
    Cvor * p = pocetak->sljedeci;
    while(p != 0){
        std::cout<<p->info<<"|";
        p = p->sljedeci;
    }
    std::cout<<"\n";
}
int main()
{
    ListaFiktivni<int> lf;
    lf.Dodaj(4);
    lf.Dodaj(8);
    lf.Dodaj(16);
    lf.Umetni(1);
    lf.Umetni(3);
    lf.Umetni(5);
    lf.Prikazi();
    return 0;
}

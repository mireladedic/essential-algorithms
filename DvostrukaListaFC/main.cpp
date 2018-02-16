/*  Created on : 02.12.2017,Friday
    By Mirela Dedic */

#include <iostream>
#include <stdexcept>
#include<algorithm>
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
class DvostrukaListaFK : public Lista<Tip>{
    struct Cvor{
        Tip info;
        Cvor* prethodni;
        Cvor* sljedeci;

        Cvor(Tip info,Cvor* prethodni,Cvor* sljedeci) : info(info),prethodni(prethodni),sljedeci(sljedeci){
            if(prethodni != 0) prethodni->sljedeci = this;
            if(sljedeci != 0) sljedeci->prethodni = this;
        }

        Cvor(Cvor* prethodni,Cvor *sljedeci) : prethodni(prethodni),sljedeci(sljedeci){
            if(prethodni != 0) prethodni->sljedeci = this;
            if(sljedeci != 0) sljedeci ->prethodni = this;
        }

    };

    Cvor *pocetak, *kraj,*tekuci;
    int lduzina,dduzina;

    void Iniciraj();
    void Unisti();
public:

    DvostrukaListaFK();
    ~DvostrukaListaFK();
    void Brisi() override {Unisti(); Iniciraj();}
    bool Umetni(const Tip &)override;
    bool Dodaj(const Tip &) override;
    Tip Izbaci()override;
    void IdiNaPocetak()override;
    void IdiNaKraj()override;
    void IdiNaSljedeci()override ;
    void IdiNaPrethodni() override;
    void IdiNaPoziciju(int i) override;
    int LDuzina() const override;
    int DDuzina() const override;
    const Tip &DajTekuciElement() const override;
    void Prikazi()const;
};

template<typename Tip>
void DvostrukaListaFK<Tip>::Iniciraj(){
    tekuci = pocetak = new Cvor(0,0);
    pocetak->sljedeci = kraj = new Cvor(pocetak,0);
    lduzina = dduzina = 0;
}
template<typename Tip>
void DvostrukaListaFK<Tip>::Unisti(){
    while(pocetak != 0){
        tekuci = pocetak;
        pocetak = pocetak->sljedeci;
        delete tekuci;
    }
    kraj = 0; tekuci = 0;
}
template<typename Tip>
DvostrukaListaFK<Tip>::DvostrukaListaFK(){Iniciraj();}
template<typename Tip>
DvostrukaListaFK<Tip>::~DvostrukaListaFK(){ Unisti(); }
template<typename Tip>
    bool DvostrukaListaFK<Tip>::Umetni(const Tip &info){
        new Cvor(info,tekuci,tekuci->sljedeci);
        dduzina++;
        return true;
    }
template<typename Tip>
    bool DvostrukaListaFK<Tip>::Dodaj(const Tip &info){
        new Cvor(info,kraj->prethodni,kraj);
        dduzina++;
        return true;
    }
template<typename Tip>
    Tip DvostrukaListaFK<Tip>::Izbaci(){
        if(dduzina == 0) throw("Nema nista za izbaciti");
        Tip el = tekuci->sljedeci->info;
        Cvor *temp = tekuci->sljedeci;
        temp->sljedeci->prethodni = tekuci;
        tekuci->sljedeci =temp->sljedeci;
        delete temp;
        dduzina--;
        return el;
    }
template<typename Tip>
    void DvostrukaListaFK<Tip>::IdiNaPocetak(){
        tekuci = pocetak;
        dduzina += lduzina;
        lduzina = 0;
    }
template<typename Tip>
    void DvostrukaListaFK<Tip>::IdiNaKraj(){
        tekuci = kraj;
        lduzina += dduzina;
        dduzina = 0;
    }
template<typename Tip>
    void DvostrukaListaFK<Tip>::IdiNaSljedeci(){
        if(tekuci != kraj){
            tekuci = tekuci->sljedeci;
            lduzina++;
            dduzina--;
        }
    }
template<typename Tip>
    void DvostrukaListaFK<Tip>::IdiNaPrethodni(){
        if(tekuci != pocetak)
            tekuci = tekuci->prethodni;
        lduzina--;
        dduzina++;
    }
template<typename Tip>
    void DvostrukaListaFK<Tip>::IdiNaPoziciju(int i){
        if(i < 0 || i > dduzina + lduzina) throw ("Invalid Index");
        int p(0);
        int k(0);
        int ld(lduzina);
        int dd (dduzina);
        dduzina = dduzina + lduzina - i;
        lduzina = i;

        if(i < std::abs(i - ld) && i < (ld + dd) / 2){
            k = i;
            tekuci = pocetak;
        }else if(std::abs(i - ld) < ld + dd - i){
            k = i - ld;
        }else{
            k = i - ld - dd - 1;
            tekuci = kraj;
        }

        if(k < 0){
            for(int i = 0; i < std::abs(k);i++)
                tekuci = tekuci->prethodni;
        }else{
            for(int i = 0; i < k; i++)
                tekuci = tekuci->sljedeci;
        }
    }
template<typename Tip>
    int DvostrukaListaFK<Tip>::LDuzina() const { return lduzina; }
template<typename Tip>
    int DvostrukaListaFK<Tip>::DDuzina() const { return dduzina; }
template<typename Tip>
    const Tip &DvostrukaListaFK<Tip>::DajTekuciElement() const {
        if(dduzina + lduzina == 0) throw("Nista za vratiti");
        return tekuci->sljedeci->info;
    }
template<typename Tip>
void DvostrukaListaFK<Tip>::Prikazi()const{
    Cvor *p = pocetak->sljedeci;
    while(p != kraj){
        std::cout<<p->info <<"|";
        p= p->sljedeci;
    }
    std::cout<<"\n";
}
int main(){
    DvostrukaListaFK<int> dl;
    dl.Dodaj(3);
    dl.Dodaj(4);
    dl.Prikazi();
return 0;
}

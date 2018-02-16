/*  Created on : 02.12.2017,Friday
    By Mirela Dedic */

#include <iostream>
#include <stdexcept>
template<typename Tip>
class Lista{
private:
    void operator = (const Lista&);
    Lista(const Lista &);
public:
    Lista(){}
    ~Lista(){}
    virtual void Brisi() = 0;
    virtual bool Umetni(const Tip &) = 0;
    virtual bool Dodaj(const Tip &) = 0;
    virtual Tip Izbaci() = 0;
    virtual void IdiNaPocetak() = 0;
    virtual void IdiNaKraj() = 0;
    virtual void IdiNaSljedeci() = 0;
    virtual void IdiNaPrethodni() = 0;
    virtual void IdiNaPoziciju(int) = 0;
    virtual int LDuzina() const = 0;
    virtual int DDuzina() const = 0;
    virtual const Tip &DajTrenutniElement() const = 0;
};
template<typename Tip>
class JednostrukaLista : public Lista<Tip>{
private:
    struct Cvor{
        Tip info;
        Cvor *sljedeci;

    //...KONSTRUKTOR STRUKTURE
    Cvor(const Tip &info,Cvor *sljedeci): info(info), sljedeci(sljedeci){}
};

    int lduzina,dduzina;
    Cvor *pocetak,*kraj,*tekuci;


public:
    JednostrukaLista() :lduzina(0),dduzina(0), pocetak(0),kraj(0),tekuci(0){}
    ~JednostrukaLista();
    JednostrukaLista(const JednostrukaLista &lista);
    JednostrukaLista &operator=(const JednostrukaLista &lista);

    void Iniciraj();
    void Unisti();
    void Brisi() override;
    bool Umetni(const Tip &) override;
    bool Dodaj(const Tip &) override;
    Tip Izbaci() override;
    void IdiNaPocetak() override;
    void IdiNaKraj() override;
    void IdiNaSljedeci() override;
    void IdiNaPrethodni() override;
    void IdiNaPoziciju(int) override;
    bool JeLiPrazna() const;
    bool Trazi(const Tip &) const;

    Tip &operator[](int);
    Tip operator[](int)const;
    JednostrukaLista &operator += (const JednostrukaLista &);
    JednostrukaLista operator +(const JednostrukaLista &)const;

    int LDuzina() const  override { return lduzina;}
    int DDuzina() const override { return dduzina;}
    const Tip &DajTrenutniElement() const  override ;//{ return tekuci->info; }

    void Prikazi()const{
        Cvor * p = pocetak;
        while(p != 0){
            std::cout<<p->info<<"|";
            p = p->sljedeci;
        }
        std::cout<<"\n";
    }

};
template<typename Tip>
JednostrukaLista<Tip>  &JednostrukaLista<Tip>::operator += (const JednostrukaLista & lista){
    JednostrukaLista l = lista;
    if(pocetak == 0) pocetak = l.pocetak;
        else
    kraj->sljedeci = l.pocetak;
    kraj = l.kraj;
    dduzina += l.dduzina;
    lduzina += l.lduzina;
    l.pocetak = l.kraj = l.tekuci = 0;
    l.dduzina = l.lduzina = 0;

    return *this;
}

template<typename Tip>
JednostrukaLista<Tip> JednostrukaLista<Tip>::operator + (const JednostrukaLista &lista) const{
    JednostrukaLista l (*this);
    l += lista;
    return l;
}
template<typename Tip>
Tip &JednostrukaLista<Tip>::operator[](int i){
    IdiNaPoziciju(i);
    if(i == 0 || tekuci == 0) return pocetak->info;
    else return tekuci->sljedeci->info;
}

template<typename Tip>
Tip JednostrukaLista<Tip>::operator [](int i) const{
    IdiNaPoziciju(i);
    if(i == 0 || tekuci == 0) return pocetak->info;
    else return tekuci->sljedeci->info;
}
template<typename Tip>
bool JednostrukaLista<Tip>::Trazi(const Tip &element)const{
    if(lduzina + dduzina == 0) throw std::domain_error("Lista prazna");
        bool nadjen = false;
    Cvor *p = pocetak;
    while(p != 0 && p->info != element){
        p = p->sljedeci;
    }

    if(p != 0)
        nadjen = true;
    return nadjen;
}
template<typename Tip>
const Tip &JednostrukaLista<Tip>::DajTrenutniElement() const {
    if(dduzina == 0) throw "Nista za vratiti";
    if(tekuci == 0) return pocetak->info;
    else
        return tekuci->sljedeci->info;
}
template<typename Tip>
void JednostrukaLista<Tip>::Iniciraj(){
    tekuci = kraj = pocetak = 0;
    lduzina = dduzina = 0;
}
template<typename Tip>
void JednostrukaLista<Tip>::Unisti(){
    while(pocetak != 0){
        tekuci = pocetak;
        pocetak = pocetak->sljedeci;
        delete tekuci;
    }
    pocetak = tekuci = kraj = 0;
}


template<typename Tip>
void JednostrukaLista<Tip>::Brisi(){
        Unisti();
        Iniciraj();
}


template<typename Tip>
bool JednostrukaLista<Tip>::Dodaj(const Tip &info){
    Cvor *p = new Cvor(info,0);
    if(lduzina + dduzina == 0) pocetak = kraj = p;
    else
        kraj = kraj->sljedeci = p;
    dduzina++;
    return true;
}
template<typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista &lista) : pocetak(0),kraj(0),dduzina(0),lduzina(0){
        Cvor *p = lista.pocetak;
        while(p != 0){
            Dodaj(p->info);
            p= p->sljedeci;
        }
}
template<typename Tip>
bool JednostrukaLista<Tip>::JeLiPrazna() const{
    return dduzina + lduzina == 0;
}
template<typename Tip>
Tip JednostrukaLista<Tip>::Izbaci(){
    if(dduzina <= 0) throw std::domain_error("Nista za izbaciti");
    Tip x;
    Cvor *p;

    if(lduzina == 0){
        x = pocetak->info;
        p = pocetak;
        pocetak = p->sljedeci;
    }else{
        p = tekuci->sljedeci;
        x = tekuci->sljedeci->info;
        tekuci->sljedeci = p->sljedeci;
    }

    if(dduzina == 1)
        kraj = tekuci;


        delete p;
        dduzina--;
        return x;

}
template<typename Tip>
JednostrukaLista<Tip>::~JednostrukaLista(){
    IdiNaPoziciju(0);
    while(!JeLiPrazna())
        Izbaci();
    pocetak = kraj = tekuci = 0;
}
template<typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator=(const JednostrukaLista &lista){
    if(&lista == this) return *this;
    IdiNaPoziciju(0);
    while(!JeLiPrazna())
        Izbaci();

    Cvor *p = lista.pocetak;
    while(p != 0){
        Dodaj(p->info);
    p = p->sljedeci;
    }
    return *this;
}
template<typename Tip>
    bool JednostrukaLista<Tip>::Umetni(const Tip &info){
        Cvor *p = new Cvor(info,0);
        if(lduzina == 0){
            p->sljedeci  = pocetak;
            pocetak = p;
            if(dduzina + lduzina == 0)
                kraj = p;
        }else{
            p->sljedeci = tekuci->sljedeci;
            tekuci->sljedeci = p;
            if(dduzina == 0)
                kraj = tekuci->sljedeci;
        }
        dduzina++;
        return true;
    }
template<typename Tip>
    void JednostrukaLista<Tip>::IdiNaPocetak(){
        tekuci = 0;
        dduzina += lduzina;
        lduzina = 0;
    }
template<typename Tip>
    void JednostrukaLista<Tip>::IdiNaKraj(){
        tekuci = kraj;
        lduzina += dduzina;
        dduzina = 0;
    }
template<typename Tip>
    void JednostrukaLista<Tip>::IdiNaSljedeci(){
        if(dduzina != 0){
            if(lduzina == 0) tekuci = pocetak;
            else tekuci = tekuci->sljedeci;
            lduzina++;
            dduzina--;
        }
    }
template<typename Tip>
    void JednostrukaLista<Tip>::IdiNaPrethodni(){
        if(lduzina != 0){
            if(lduzina == 1) tekuci = 0;
            else{
                Cvor *p = pocetak;
                while(p->sljedeci != tekuci) p = p->sljedeci;
                tekuci = p;
            }
            lduzina--;
            dduzina++;
        }
    }
template<typename Tip>
    void JednostrukaLista<Tip>::IdiNaPoziciju(int i ){
        if(i < 0 || i > dduzina + lduzina) throw std::domain_error("Invalid Index");
        int p(0);
        int ld(lduzina);
        dduzina = dduzina + lduzina - i;
        lduzina = i;

        if(i == 0){
            tekuci = 0;
            return;
        }

        if(i >= ld){
            if(ld == 0) tekuci = pocetak;
            else p = ld -1;
        }
        else {
            tekuci = pocetak;
            for(int j = p; j < i - 1;j++) tekuci = tekuci->sljedeci;
        }
    }

int main()
{
    JednostrukaLista<int>l;
    l.Dodaj(2);
    l.Dodaj(3);
    l.Dodaj(5);
    l.Izbaci();
    l[2] = l.Dodaj(8);
    l.Prikazi();
    JednostrukaLista<int>lista;
    lista.Umetni(2);
    lista.Umetni(3);
    lista.Umetni(5);
    lista.Prikazi();
    lista+=l;
    lista.Prikazi();
    (l + lista).Prikazi();

    return 0;
}

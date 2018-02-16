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

    virtual void Idi_na_prethodni() =0;
    virtual void Idi_na_sljedeci() =0;
    virtual void Idi_na_pocetak() = 0;
    virtual void Idi_na_kraj()= 0;
    virtual void Idi_na_poziciju(int indeks) = 0;
    virtual void Brisi() = 0;
    virtual bool Umetni(const Tip &el) = 0;
    virtual bool Dodaj(const Tip &el) = 0;
    virtual Tip Izbaci() = 0;

    virtual int LDuzina() const = 0;
    virtual int DDuzina() const = 0;

    virtual const Tip& DajTekuciElement() const = 0;
};
template<typename Tip>
class JednostrukaLista : public Lista<Tip>{
    struct Cvor{
        Tip info;
        Cvor *sljedeci;
        //......... new Cvor(el,0) ->
        Cvor(const Tip el, Cvor * sljedeci){
            info = (el);
            sljedeci = (sljedeci);
        }
    };
    int dduzina,lduzina;
    Cvor *pocetak;
    Cvor *t;
    Cvor *kraj;


    void GETNODE(){
        pocetak = kraj = t = 0;
        lduzina=dduzina = 0;
    }
    void FREENODE(){
        while(pocetak != 0){
            t = pocetak;
            pocetak = pocetak->sljedeci;
            delete t;
        }
        pocetak = kraj = t = 0;
    }
public:
    //.........................
    JednostrukaLista() : dduzina(0),lduzina(0),pocetak(0),t(0),kraj(0){}
    JednostrukaLista(const JednostrukaLista &jlista);
    JednostrukaLista &operator=(const JednostrukaLista &jlista);
    ~JednostrukaLista();

    //.........................

    void Idi_na_pocetak() override;
    void Idi_na_kraj() override;
    void Idi_na_prethodni() override;
    void Idi_na_sljedeci() override;
    void Idi_na_poziciju(int indeks)override;
    const Tip &DajTekuciElement()const override;

    void Brisi() override{ FREENODE(); GETNODE();}

    bool Umetni(const Tip &el) override;
    bool Dodaj(const Tip &el) override;
    Tip Izbaci() override;
    bool Trazi(const Tip &x) const;

    int DDuzina() const override {  return dduzina; }
    int LDuzina() const override {  return lduzina; }

    //..............................

    bool JeLIPrazna()const {    return dduzina + lduzina == 0; }
    int Duzina()const {    return dduzina + lduzina; }

    Tip &operator[](int indeks);
    Tip operator[](int indeks) const;
    JednostrukaLista &operator += (const JednostrukaLista &jlista);
    JednostrukaLista operator +(const JednostrukaLista &jlista) const;

    void Ispisi()const;
    //.................................


};
//....KONSTRUKTOR KOPIJE
template<typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista &jlista) : pocetak(0),kraj(0),t(0),dduzina(0),lduzina(0){
    Cvor * p = (jlista.pocetak);
    while(p != 0){
        Dodaj(p ->info); // DODAJ ELEMENT
        p = p->sljedeci; // POMJERAJ p
    }
}
//...................
template<typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator=(const JednostrukaLista &jlista){
    if(&jlista == this) return *this;
    //....BRISEM LISTU
    Idi_na_poziciju(0);
    while(!JeLIPrazna()){
        Izbaci();
    }
    //....ALOCIRAM NOVU
    Cvor *p(jlista.pocetak);
    while(p != 0){
        Dodaj(p->info);
        p = p->sljedeci;
    }

    return *this;
}
template<typename Tip>
JednostrukaLista<Tip>::~JednostrukaLista(){
    Idi_na_poziciju(0);
    while(!JeLIPrazna()){
        Izbaci();
    }
    pocetak = kraj = t = 0;
}
//....................
template<typename Tip>
bool JednostrukaLista<Tip>::Umetni(const Tip &el) {
 /* Cvor *p = new Cvor;
  p->info = el;
  p->sljedeci = nullptr; */
  Cvor *p = new Cvor(el,0);
    if(lduzina == 0){
        p->sljedeci = pocetak;
        pocetak = p;
        if(dduzina + lduzina == 0)
            kraj = p;
    }else{
       p->sljedeci= t->sljedeci;
       t->sljedeci = p;
       if(dduzina == 0)
        kraj = t->sljedeci;
    }
    dduzina++;
    return true;
}

template<typename Tip>
bool JednostrukaLista<Tip>::Dodaj( const Tip &el){
    /*Cvor *p = new Cvor;
    p->info = (el);
    p->sljedeci = nullptr; */
    Cvor *p = new Cvor(el,0);

    if(lduzina + dduzina == 0){
        pocetak = kraj = p;
    }else{
        kraj = kraj->sljedeci = p;
        dduzina++;
        return true;
    }
}

template<typename Tip>
Tip JednostrukaLista<Tip>::Izbaci(){
    if(dduzina <= 0) throw "Nista za izbaciti";
    Tip x;
    Cvor *p;
    if(lduzina == 0){
        x = pocetak->info;
        p = pocetak;
        pocetak = p->sljedeci;
    }else{
        p = t->sljedeci;
        x = t->sljedeci->info;
        t->sljedeci = p->sljedeci;
    }

    if(dduzina == 1) kraj = t;
    delete p;
    dduzina--;
    return x;
}

template<typename Tip>
void JednostrukaLista<Tip>::Idi_na_prethodni(){
    if(lduzina != 0){
        if(lduzina == 1){
            t = nullptr;
        }else{
            Cvor *p(pocetak);
            while(p->sljedeci != t) p= p->sljedeci;
            t = p;
        }
        lduzina--;
        dduzina++;
    }
}
template<typename Tip>
void JednostrukaLista<Tip>::Idi_na_sljedeci(){
    if(dduzina != 0){
        if(lduzina == 0){
            t = pocetak;
        }else{
           t = t->sljedeci;
        }

        lduzina++;
        dduzina--;
    }
}
template<typename Tip>
void JednostrukaLista<Tip>::Idi_na_pocetak(){
    t = 0;
    dduzina += lduzina;
    lduzina = 0;
}
template<typename Tip>
void JednostrukaLista<Tip>::Idi_na_kraj(){
    t = kraj;
    lduzina += dduzina;
    dduzina = 0;
}
template<typename Tip>
void JednostrukaLista<Tip>::Idi_na_poziciju(int indeks){
    if(indeks < 0 || indeks > dduzina + lduzina)throw "Invalid index";
    int p(0);
    int ld(lduzina);
    dduzina = dduzina + lduzina - indeks;
    lduzina = indeks;

    if(indeks == 0){
        t = nullptr;
        return;
    }

    if(indeks >= ld){
        if(ld == 0)
            t = pocetak;
        else
            p = ld - 1;
    }else{
        t  = pocetak;
    }
        for(int i = p; i < indeks - 1;i++)
            t = t->sljedeci;

}
template<typename Tip>
bool JednostrukaLista<Tip>::Trazi(const Tip &x) const{
    if(dduzina + lduzina == 0) throw "error: lista prazna";
    bool nadjen = false;
    Cvor *p = pocetak;
    while(p != 0 && (p->info != x) )
        p = p->sljedeci;
    if(p != 0) nadjen = x;
    return nadjen;
}

template<typename Tip>
const Tip &JednostrukaLista<Tip>::DajTekuciElement()const{
    if(dduzina == 0) throw "Nista za vratiti";
    if(t == 0) return pocetak->info;
    else
        return t->sljedeci->info;
}

template<typename Tip>
Tip JednostrukaLista<Tip>::operator[](int indeks)const{
    Idi_na_poziciju(indeks);
    if(indeks == 0 || t = 0) return pocetak->info;
    else return t->sljedeci->info;
}

template<typename Tip>
Tip &JednostrukaLista<Tip>::operator[](int indeks){
    Idi_na_poziciju(indeks);
    if(indeks == 0 || t = 0) return pocetak->info;
    else return t->sljedeci->info;
}

template<typename Tip>
//..........DODAJE LISTU NATRENUTNU
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator +=(const JednostrukaLista & jlista){
    JednostrukaLista l(jlista);
    if(pocetak == 0) pocetak = l.pocetak;
    else
        kraj->sljedeci = l.pocetak;

    kraj = l.kraj;
    dduzina += l.dduzina;
    lduzina += l.lduzina;

    l.pocetak = l.kraj = l.t = 0;
    l.dduzina = l.lduzina = 0;

    return *this;
}

template<typename Tip>
JednostrukaLista<Tip> JednostrukaLista<Tip>::operator +(const JednostrukaLista &jlista) const{
    JednostrukaLista l(*this);
    l +=jlista;
    return l;
}

template<typename Tip>
void JednostrukaLista<Tip>::Ispisi()const{
    for(Cvor *p = pocetak; p != nullptr;p = p->sljedeci)
        std::cout<<p->info<<"|";

    std::cout<<"\nlduzina: "<<lduzina<<std::endl;
    std::cout<<"dduzina: "<<dduzina<<std::endl;
}


int main(){
    JednostrukaLista<int>lista;
    lista.Umetni(5);
    lista.Umetni(8);
    lista.Umetni(7);
    lista.Ispisi();
        return 0;
}

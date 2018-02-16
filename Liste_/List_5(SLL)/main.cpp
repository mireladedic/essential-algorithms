#include <iostream>
#include <stdexcept>


template<typename Tip>
class Lista{
private:
    void operator = (const Lista &);
    Lista(const Lista &);
public:
    Lista(){}
    virtual ~Lista(){}
    virtual int brojElemenata()const = 0;
    virtual Tip trenutni()const = 0;
    virtual Tip &trenutni() = 0;
    virtual bool Idi_na_prethodni() =0;
    virtual bool Idi_na_sljedeci() =0;
    virtual void Idi_na_pocetak() = 0;
    virtual void Idi_na_kraj()= 0;
    virtual void Obrisi() = 0;
    virtual void DodajIspred(const Tip &el) = 0;
   // virtual void DodajIza(const Tip &el) = 0;
    virtual Tip operator[](int indeks) const = 0;
    virtual Tip &operator[](int indeks) = 0;
};

template<typename Tip>
class JednostrukaLista : public Lista<Tip>{
    struct Cvor{
        Tip info;
        Cvor *sljedeci;
    };

    Cvor* pocetak;
    Cvor* kraj;
    Cvor* tekuci;

    int lduzina,dduzina;

public:
    JednostrukaLista():pocetak(0),kraj(0),tekuci(0),lduzina(0),dduzina(0){}
    JednostrukaLista(const JednostrukaLista &jlista);
    JednostrukaLista &operator=(const JednostrukaLista &jlista);
    ~JednostrukaLista();
    //......................
    int brojElemenata()const override { return lduzina + dduzina; }
    Tip trenutni()const override ;
    Tip &trenutni() override;
    bool Idi_na_prethodni() override;
    bool Idi_na_sljedeci() override;

    void Idi_na_pocetak() override { tekuci = 0; dduzina += lduzina; lduzina = 0;}
    void Idi_na_kraj() override { tekuci = kraj; lduzina += dduzina; dduzina = 0; }

    void Obrisi() override;
    void DodajIspred(const Tip &el) override;
    //void DodajIza(const Tip &el);

    Tip operator[](int indeks) const override;
    Tip &operator[](int indeks) override;

    void Ispisi()const;
};
template<typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista &jlista){
    Cvor *p = (jlista.pocetak);
    while (p != 0){
        DodajIspred(p->info);
        p = p->sljedeci;
    }
}
template<typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator = (const JednostrukaLista &jlista){
  if(&jlista == this) return *this;

  Idi_na_pocetak();
  while (brojElemenata()> 0){
    Obrisi();
  }

  Cvor *p = jlista->pocetak;
  while(p != 0){
    DodajIspred(p->info);
    p= p->sljedeci;
  }

  return *this;

}
template<typename Tip>
JednostrukaLista<Tip>::~JednostrukaLista(){
    Idi_na_pocetak();
    while(brojElemenata()> 0){
        Obrisi();
    }
    pocetak=kraj=tekuci = 0;
}
template<typename Tip>
bool JednostrukaLista<Tip>::Idi_na_prethodni(){
    bool prethodni = false;
    if(lduzina != 0){
        if(lduzina = 1) tekuci = nullptr;
        else{
            Cvor *p = pocetak;
            while(p -> sljedeci != tekuci)
                p= p->sljedeci;
            tekuci = p;
            prethodni = true;
            }
        lduzina = lduzina - 1;
        dduzina = dduzina + 1;
    }
    return prethodni;
}

template<typename Tip>
bool JednostrukaLista<Tip>::Idi_na_sljedeci(){
    if(dduzina != 0){
        if(lduzina == 0) tekuci = pocetak;
        else tekuci = tekuci->sljedeci;
        dduzina = dduzina + 1;
        lduzina = lduzina - 1;
    }

}
template<typename Tip>
Tip JednostrukaLista<Tip>::trenutni() const{
    return tekuci->info;
}

template<typename Tip>
Tip &JednostrukaLista<Tip>::trenutni(){
    return tekuci->info;
}
template<typename Tip>
Tip &JednostrukaLista<Tip>::operator[](int indeks){
    if(indeks < 0 || indeks > brojElemenata()) throw std::range_error("Invalid index");
    int p (0);
    int ld = lduzina;
    dduzina = dduzina  + lduzina - indeks;
    lduzina = indeks;

    if(indeks = 0){
        tekuci = nullptr;
        return;}
    if(indeks >= ld){
        if(ld = 0) tekuci = pocetak;
        else p = ld - 1;
    }else tekuci= pocetak;

    for(int t = p; t <indeks - 1;t++)
        tekuci = tekuci->sljedeci;
    return(tekuci->info);
}
template<typename Tip>
Tip JednostrukaLista<Tip>::operator[](int indeks) const {
    if(indeks < 0 || indeks > brojElemenata()) throw std::range_error("Invalid index");
    int p (0);
    int ld = lduzina;
    dduzina = dduzina  + lduzina - indeks;
    lduzina = indeks;

    if(indeks = 0){
        tekuci = nullptr;
        return;}
    if(indeks >= ld){
        if(ld = 0) tekuci = pocetak;
        else p = ld - 1;
    }else tekuci= pocetak;
    for(int t = p; t <indeks - 1;t++)
        tekuci = tekuci->sljedeci;
    return(tekuci->info);
}
//...................................
template<typename Tip>
void JednostrukaLista<Tip>::Obrisi(){
    if(dduzina == 0) throw std::range_error("Nothing to delete");
    Cvor *p;
    Tip x;
    if(lduzina = 0){
        x = pocetak->info;
        p = pocetak;
        pocetak = p->sljedeci;
    }else{
        x = tekuci->sljedeci->info;
        p = tekuci->sljedeci;
        tekuci->sljedeci = p->sljedeci;
    }

    if(dduzina == 1){
        kraj = tekuci;
    }
    delete p;
    pocetak = kraj= tekuci = 0;
    dduzina = dduzina - 1;
}
template<typename Tip>
void JednostrukaLista<Tip>::DodajIspred(const Tip &el){
   Cvor *p = new Cvor;
   p->info = el;
   p->sljedeci = nullptr;

   if(lduzina = 0){
        p->sljedeci = pocetak;
        pocetak = p;
        if(lduzina + dduzina == 0) kraj = p;
    }else{
       p->sljedeci = tekuci;
       Cvor *t = pocetak;
       for(Cvor *i = t; i != tekuci; i++ )
            t = t->sljedeci;
            t->sljedeci= p;

        if(dduzina == 0) kraj = tekuci->sljedeci;

   }
   dduzina = dduzina + 1;

}
//void JednostrukaLista<Tip>::DodajIza(const Tip &el);
template<typename Tip>
void JednostrukaLista<Tip>::Ispisi()const{
    for( Cvor *p = pocetak; p != nullptr; p= p->sljedeci)
        std::cout<< p->info << "|";
    std::cout<<"\n";

}
int main()
{
    JednostrukaLista<int> lista;
    lista.DodajIspred(2);
    lista.Ispisi();
    return 0;
}

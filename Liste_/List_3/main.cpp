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
    virtual int brojElemenata()const = 0;
    virtual Tip trenutni()const = 0;
    virtual Tip &trenutni() = 0;
    virtual bool Idi_na_prethodni() =0;
    virtual bool Idi_na_sljedeci() =0;
    virtual void Idi_na_pocetak() = 0;
    virtual void Idi_na_kraj()= 0;
    virtual void Obrisi() = 0;
    virtual void DodajIspred(const Tip &el) = 0;
    virtual void DodajIza(const Tip &el) = 0;
    virtual Tip operator[](int indeks) const = 0;
    virtual Tip &operator[](int indeks) = 0;
};

template<typename Tip>
class NizLista: public Lista<Tip>{
    int kapacitet,velicina,tekuci;
    Tip**niz;
public:
    NizLista(int kapacitet) : kapacitet(kapacitet),velicina(0),tekuci(0),niz(new Tip*[kapacitet]){}
    ~NizLista(){ for(int i = 0; i < velicina;i++) delete niz[i]; delete[]niz; }
    //........................................
    NizLista(const NizLista &l);
    NizLista(NizLista &&l);
    NizLista &operator=(const NizLista &l);
    NizLista &operator =(NizLista &&l);

    int brojElemenata() const override;
    Tip trenutni()const override;
    Tip &trenutni() override;
    bool Idi_na_prethodni() override;
    bool Idi_na_sljedeci() override;
    void Idi_na_pocetak() override;
    void Idi_na_kraj() override;
    Tip operator[](int indeks) const override;
    Tip &operator[](int indeks) override;
    void Obrisi() override;
    void DodajIspred(const Tip &el) override;
    void DodajIza(const Tip &el) override;
    //..........................................
    void Ispisi()const {
        for(int i = 0; i < velicina;i++)
            std::cout<< *niz[i] <<"|";
        std::cout<<"\n";
    }
};
template <typename Tip>
NizLista<Tip>::NizLista(const NizLista &l) : kapacitet(l.kapacitet),velicina(l.velicina),tekuci(l.tekuci),niz(new Tip*[l.kapacitet]){
    try{
        for(int i = 0; i < l.velicina;i++)
            niz[i] = new Tip(*l.niz[i]);
    }catch(...){
        for(int i = 0; i < l.velicina;i++) delete niz[i];
        delete[]niz;
        throw;
    }
}

template<typename Tip>
NizLista<Tip>::NizLista(NizLista &&l) :kapacitet(l.kapacitet),velicina(l.velicina),tekuci(l.tekuci),niz(l.niz){
    l.niz = nullptr;
    l.velicina = 0;
}

template<typename Tip>
NizLista<Tip> &NizLista<Tip>::operator = (const NizLista &l){
    Tip**novi_prostor = new Tip*[l.kapacitet];
    try{
        for(int i = 0; i < l.velicina;i++)
            novi_prostor[i] = new Tip(*l.niz[i]);
    }catch(...){
        for(int i = 0; i < l.velicina;i++)
            delete novi_prostor[i];
        delete[] novi_prostor;
        throw;
    }

    //....OBRISEMO ONO NA STO JE RANIJE POKAZIVAO
    for(int i = 0; i < velicina; i++)
        delete niz[i];
    delete[] niz;

    kapacitet = l.kapacitet;
    velicina = l.velicina;
    tekuci = l.tekuci;
    niz = novi_prostor;

    return *this;
}

template<typename Tip>
NizLista<Tip> &NizLista<Tip>::operator = (NizLista &&l){
    std::swap(kapacitet,l.kapacitet);
    std::swap(velicina,l.velicina);
    std::swap(tekuci,l.tekuci);
    std::swap(niz,l.niz);
    return *this;
}
//.............................................................
template<typename Tip>
int NizLista<Tip>::brojElemenata() const{ return velicina; }
//...........................
template<typename Tip>
Tip NizLista<Tip>::trenutni()const{
    if(velicina == 0) throw std::range_error("error");
    return *niz[tekuci];
}
template<typename Tip>
Tip &NizLista<Tip>::trenutni(){
     if(velicina == 0) throw std::range_error("error");
    return *niz[tekuci];
 }
//...............................
template<typename Tip>
bool NizLista<Tip>::Idi_na_prethodni(){
    if(velicina == 0) throw std::range_error("error");
    if(tekuci == 0) return false;
        tekuci--;
        return true;
  }
template <typename Tip>
bool NizLista<Tip>::Idi_na_sljedeci() {
    if(velicina == 0) throw std::range_error("error");
    if(tekuci == velicina - 1) return false;
    tekuci++;
    return true;
}
template<typename Tip>
void NizLista<Tip>::Idi_na_pocetak(){
    tekuci  = 0;
 }
template<typename Tip>
void NizLista<Tip>::Idi_na_kraj(){
    tekuci = velicina - 1;
}
//........................................
template<typename Tip>
Tip NizLista<Tip>::operator[](int indeks) const{
    if(indeks < 0 || indeks >= velicina) throw std::range_error("Invalid indeks");
    return *niz[indeks];
}
template<typename Tip>
Tip &NizLista<Tip>::operator[](int indeks){
    if(indeks < 0 || indeks >= velicina ) throw std::range_error("Invalid indeks");
    return *niz[indeks];
}
//........................................
template<typename Tip>
void NizLista<Tip>::Obrisi(){
    if(tekuci == velicina) throw std::range_error("obrisi_");
    delete niz[tekuci];
    for(int i = tekuci;i < velicina - 1; i++)
        niz[i] = niz[i + 1];
    velicina--;
   if(tekuci == velicina - 1) tekuci--;
}
template<typename Tip>
void NizLista<Tip>::DodajIspred(const Tip &el){
    if(velicina < kapacitet){
    for(int i = velicina; i > tekuci; i--)
        niz[i] = niz[i-1];
        niz[tekuci] = new Tip(el);
        velicina++;

        if(tekuci == velicina) tekuci--;
    }
}
template<typename Tip>
void NizLista<Tip>::DodajIza(const Tip &el){

    if(velicina < kapacitet){
        if(velicina == 0){ niz[tekuci] = new Tip(el); }
        else {
            for(int i = velicina; i > tekuci + 1; i--)
                niz[i] = niz[i - 1];
            tekuci++;
            niz[tekuci] = new Tip(el);
        }
        velicina++;
    }
}

int main(){
    NizLista<int>lista(5);
    lista.DodajIza(3);
    lista.DodajIza(8);
    std::cout<<lista.brojElemenata()<<std::endl;
    std::cout<<lista.trenutni()<<std::endl;
    lista.DodajIza(9);
    std::cout<<lista.trenutni()<<std::endl;
    lista.DodajIspred(4);
    lista.Ispisi();
    NizLista<int>l(5);
    l = lista;
    l.Ispisi();
    NizLista<int>nova(l);
    nova.Ispisi();

    lista.Idi_na_pocetak();
    lista.Idi_na_sljedeci();
    std::cout<<lista.trenutni()<<std::endl;
    lista.Obrisi();
    lista.Ispisi();


    return 0;
}

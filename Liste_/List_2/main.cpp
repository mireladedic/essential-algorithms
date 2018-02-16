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
//........................................
template<typename Tip>
class NizLista : public Lista<Tip>{
    int kapacitet,velicina,tekuci;
    Tip * niz;

    void povecaj_kapacitet(){
        if(velicina == kapacitet){
            kapacitet *= 2;
            Tip* novi = new Tip[kapacitet];
           // for(int i = 0; i < velicina;i++) novi[i] = niz[i];
           std::copy(niz,niz + velicina,novi);
           delete[]niz;
           niz = novi;
        }
    }
public:
    NizLista(int kapacitet) : kapacitet(kapacitet),velicina(0),tekuci(0),niz(new Tip[kapacitet]){}
//.....................................
    ~NizLista(){ delete[] niz; }
//.......................................
    int brojElemenata()const override { return velicina;}
//..............................................................
    Tip trenutni() const override{
        if(velicina == 0) throw std::range_error("Trenutni_niz_lista_prazan!");
         return niz[tekuci]; }
//..................................................................
    Tip &trenutni()override{
        if(velicina == 0) throw std::range_error("Trenutni_niz_lista_prazan!");
        return niz[tekuci]; }
//...........................................................
    bool Idi_na_prethodni()override{
        if(velicina == 0) throw std::range_error("Prethodni_niz_lista_prazan!");
        if(tekuci != 0) { tekuci--; return true;}
        return false;
    }
//........................................................
    virtual bool Idi_na_sljedeci() override{
        if(velicina == 0) throw std::range_error("Sljedeci_niz_lista_prazan!");
        if(tekuci < velicina) {tekuci++; return true;}
        return false;
    }
//....................................................................
    virtual void Idi_na_pocetak() override{
        if(velicina == 0) throw std::range_error("Pocetak_niz_lista_prazan!");
        tekuci = 0;
    }
//.................................................
    virtual void Idi_na_kraj()override{
        if(velicina == 0) throw std::range_error("Kraj_niz_lista_prazan!");
        tekuci = velicina - 1;
    }
//.................................................
    void Obrisi() override;
    Tip operator[](int indeks) const override{
        if(indeks < 0 || indeks >= velicina) throw std::range_error("Indeks izvan opsega!");
        return niz[indeks];
    }
//.....................................................
    Tip &operator[](int indeks) override{
        if(indeks < 0 || indeks >= velicina) throw std::range_error("Indeks izvan opsega!");
        return niz[indeks];
    }
//.....................................................
    void DodajIspred(const Tip &el) override;
    void DodajIza(const Tip &el) override;
//.......................................
    void Ispisi()const{
        for(int i = 0; i < velicina; i++)
        std::cout<<niz[i]<<"|";
        std::cout<<"\n";
    }
};
template<typename Tip>
void NizLista<Tip>::Obrisi(){
    if(velicina == 0) throw std::range_error("Obrisi velicina_nula!");
    if(tekuci == velicina) throw std::range_error("Nema sta obrisati!");
    for(int i = tekuci; i < velicina - 1; i++){
        niz[i] = niz[i + 1];
    }
    velicina--;
    if(tekuci == velicina ) tekuci--;
}
//...........................................
template<typename Tip>
    void NizLista<Tip>::DodajIspred(const Tip &el){
        povecaj_kapacitet();
        if(velicina < kapacitet)
         for(int i = velicina; i > tekuci; i--)
            niz[i] = niz[i - 1];
        //....DODAJE ELEMENT NA  TEKUCU POZICIJU PRI CEMU JE NOVOKREIRANI ELEMENT POSTAO TEKUCI
         niz[tekuci]  = el;
            velicina++;
    }
//..........................................
template<typename Tip>
    void NizLista<Tip>::DodajIza(const Tip &el){
       povecaj_kapacitet();
        if(velicina < kapacitet){
            //...DODAJE NA POCETAK
            if(velicina == 0){niz[tekuci] = el; }
            //..AKO IMA JEDAN ELEMENT
         //   else if(velicina == 1){tekuci++;niz[tekuci] = el; }
            //...DODAJEM NA KRAJ
         //   else if(tekuci == velicina - 1){ tekuci++; niz[velicina] = el;}
            else{
            //...DODAJEM U SREDINU
             for(int i = velicina ; i > tekuci + 1; i--)
                niz[i] = niz[i - 1];

            tekuci++;
            niz[tekuci] = el;

            }

            velicina++;


        }
}

int main()
{
    NizLista<int>lista(5);
    lista.DodajIza(3);
    lista.DodajIza(5);
    lista.DodajIza(9);
    lista.DodajIspred(4);
    lista.Ispisi();
   /* try{
        NizLista<int>lista(5);
        lista.DodajIza(5);
        lista.DodajIza(8);
        lista.Idi_na_kraj();
        lista.DodajIza(3);


        std::cout<<lista.trenutni()<<std::endl;
        lista.DodajIza(8);
        ista.DodajIza(7);
        lista.DodajIza(18);
        lista.Ispisi();
        std::cout<<lista.brojElemenata()<<std::endl;



        lista.DodajIspred(2);
        lista.DodajIspred(3);
        lista.DodajIspred(4);
        std::cout<<lista.trenutni()<<std::endl;

        lista.Idi_na_kraj();


        lista.DodajIza(8);
        lista.DodajIza(3);
        lista.DodajIspred(5);
        lista.Ispisi();

    }catch(std::range_error izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    */
    return 0;
}

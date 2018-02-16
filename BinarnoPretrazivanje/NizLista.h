//
// Created by Mirela on 12/6/2017.
//

#ifndef BINARNOPRETRAZIVANJE_NIZLISTA_H
#define BINARNOPRETRAZIVANJE_NIZLISTA_H
#include "Lista.h"
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

#endif //BINARNOPRETRAZIVANJE_NIZLISTA_H

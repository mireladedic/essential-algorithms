//
// Created by Mirela on 12/6/2017.
//

#ifndef BINARNOPRETRAZIVANJE_NIZLISTAIMPLEMENTACIJA_H
#define BINARNOPRETRAZIVANJE_NIZLISTAIMPLEMENTACIJA_H

#include "NizLista.h"
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
#endif //BINARNOPRETRAZIVANJE_NIZLISTAIMPLEMENTACIJA_H

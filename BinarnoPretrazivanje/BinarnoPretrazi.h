//
// Created by Mirela on 12/6/2017.
//

#ifndef BINARNOPRETRAZIVANJE_BINARNOPRETRAZI_H
#define BINARNOPRETRAZIVANJE_BINARNOPRETRAZI_H

#include "NizListaImplementacija.h"

template<typename Tip>
class BinarnoPretrazi: public NizLista<Tip>{
public:
    Tip Niz(int i) const { return this->Niz(i);}

    bool TestUmetni(int x) { this->Umetni(x); }
    bool TestDodaj(int x) {this->Dodaj(x);}
    void BIspisi()const{ this->Prikazi(); }
    BinarnoPretrazi(int velicinaNiza = 10) : NizLista<Tip>(velicinaNiza){}
    ~BinarnoPretrazi(){}
    int BinPretrazi(const Tip &k) const;
    int InterpolencijskoPretrazi(const Tip &k) const;
};
#endif //BINARNOPRETRAZIVANJE_BINARNOPRETRAZI_H

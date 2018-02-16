//
// Created by Mirela on 12/6/2017.
//

#ifndef BINARNOPRETRAZIVANJE_BINARNOPRETRAZIIMPLEMENTACIJA_H
#define BINARNOPRETRAZIVANJE_BINARNOPRETRAZIIMPLEMENTACIJA_H

#include "BinarnoPretrazi.h"

template<typename  Tip>
int BinarnoPretrazi<Tip>::BinPretrazi(const Tip &k) const {
        int vrh = (this->Duzina() - 1),dno (0),srednji;

    while(vrh >= dno){
        srednji = (vrh + dno)/2;
        if(k == Niz(srednji) )
            return srednji;
        else if( Niz(srednji)< k)
            dno = srednji + 1;
        else
            vrh = srednji - 1;
    }

    return -1;
}

template<typename Tip>
int BinarnoPretrazi<Tip>::InterpolencijskoPretrazi(const Tip &k) const {
    int vrh = (this->Duzina() - 1),dno(0),srednji;

    while(vrh > dno){
        srednji = dno + (vrh - dno) * (k - Niz(dno)) / (Niz(vrh) - Niz(dno));
        if(k == Niz(srednji) )
            return srednji;
        else if( Niz(srednji)< k)
            dno = srednji + 1;
        else
            vrh = srednji - 1;
    }

    return -1;

}
#endif //BINARNOPRETRAZIVANJE_BINARNOPRETRAZIIMPLEMENTACIJA_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "BinarnoPretraziImplementacija.h"

int main()
{
    BinarnoPretrazi<int>lista(8);
    lista.TestDodaj(2);
    lista.TestDodaj(3);
    lista.TestDodaj(6);
    lista.TestDodaj(10);
    lista.TestDodaj(15);
    lista.TestDodaj(22);
    lista.TestDodaj(28);
    lista.TestDodaj(19);
    lista.TestDodaj(36);
    lista.BIspisi();
    std::cout<<"BinarnoPretrazivanje\n";
    std::cout<<lista.BinPretrazi(22);
    return 0;
}

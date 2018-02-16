/* Created On: 06.12.2017,Wednesday,00:53
 * By: Mirela Dedic */
#include <iostream>
#include "RekurzivneFunkcije.h"
int main() {
    std::cout << "Unesite n:\n";
    int n;
    std::cin >> n;

    std::cout << "Faktorijel\n";
    std::cout << Faktorijel(n);

    std::cout << "\nJeLiNeparan\n";
    std::cout << JeLiNeparan(n);

    std::cout << "\nJeLiParan\n";
    std::cout << JeLiParan(n);


    std::cout << "\nHanojskiTornjevi\n";
    HanojskiTornjevi(n, 's', 't', 'd');

    std::cout << "\nKombinacije\n";
    std::cout << Kombinacije(n, 2);

    std::cout << "\nSuma\n";
    std::cout << Suma(n);

    return 0;
}
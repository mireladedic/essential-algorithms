//
// Created by Mirela on 12/6/2017.
//

#ifndef REKURZIJAPRIMJERI_REKURZIVNEFUNKCIJE_H
#define REKURZIJAPRIMJERI_REKURZIVNEFUNKCIJE_H

int Faktorijel(int n){
    if (n == 0) return 1;
    else return n * Faktorijel(n - 1);
}

int Kombinacije(int n,int k){
    if(k == 0 || n == k) return 1;
    else return Kombinacije(n-1,k) + Kombinacije(n - 1,k - 1);
}

int Suma(int n){
    int s{0};
    if(n == 1) return s = 1;
    else return s = 1 + Suma(n -1);
}

void HanojskiTornjevi(int n,char s,char d,char t){
    if(n == 1) {
        std::cout<<"Prenijeti disk br "<< n<<" sa stapa "<< s << " na stap "<< d <<std::endl;
        return;
    }

    HanojskiTornjevi(n-1,s,t,d);
    std::cout<<"Prenijeti disk " << n << "sa stapa " << s << " na stap " << d <<std::endl;
    HanojskiTornjevi(n-1,t,d,s);
    return;
}
bool JeLiNeparan(int n);
bool JeLiParan(int n){
    if (n == 0) return  true;
    return !JeLiNeparan(n - 1);
}

bool JeLiNeparan(int n){
    return !JeLiParan(n);
}
#endif //REKURZIJAPRIMJERI_REKURZIVNEFUNKCIJE_H

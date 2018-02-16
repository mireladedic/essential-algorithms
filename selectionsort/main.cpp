#include <iostream>
template<typename Tip>
void selection_sort(Tip* niz, int vel) {

    for(int i = 1; i <= vel - 1; i++){

        Tip priv = niz[i];

        int j = i - 1;

        while(j >= 0 && niz[j] > priv){
            niz[j + 1] = niz[j];
            j = j - 1;
        }

        niz[j + 1]= priv;
    }
}
int main(){
    int  niz[6] = {4,11,2,9,3,10};

    selection_sort( niz , 6);


    for(int i = 0; i < 6 ; i++)
        std::cout<<niz[i]<<"|";

    return 0;
}

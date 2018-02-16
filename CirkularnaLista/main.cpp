/*  Created on : 02.12.2017,Friday
    By Mirela Dedic */

#include <iostream>
#include <stdexcept>
template<typename Tip>
class Lista{
private:
    void operator = (const Lista&);
    Lista(const Lista &);
public:
    Lista(){}
    ~Lista(){}
    virtual void DodajNaPocetak(const Tip &) = 0;
    virtual void DodajNaKraj(const Tip &) = 0;

};
template<typename Tip>
class CirkularnaLista: public Lista<Tip>{
private:
    struct Cvor{
        Tip info;
        Cvor *sljedeci;
    Cvor(const Tip &info,Cvor *sljedeci): info(info), sljedeci(sljedeci){}
    Cvor(Cvor *sljedeci = 0): sljedeci(sljedeci){}
};
Cvor *pocetak,*kraj;

public:
    CirkularnaLista() : pocetak(0),kraj(0){}
    ~CirkularnaLista();
    void DodajNaPocetak(const Tip &) override;
    void DodajNaKraj(const Tip &) override;


    void Prikazi()const{
        Cvor* tmp= pocetak;
        while(tmp != 0){
            std::cout<<tmp->info<<"|";
            tmp = tmp->sljedeci;
            if(tmp == pocetak) break;
        }
        std::cout<<"\n";
    }

};

template<typename Tip>
CirkularnaLista<Tip>::~CirkularnaLista(){
    Cvor * n = this->pocetak;
    Cvor *temp;
    while(n){
        temp = n;
        n = n->sljedeci;
        delete temp;
    }
    pocetak  = kraj = nullptr;
}
template<typename Tip>
void CirkularnaLista<Tip>::DodajNaKraj(const Tip &info)
{

    Cvor *p = new Cvor(info,0);

    if (pocetak == NULL) {
            pocetak = p;
    } else {
            Cvor *temp = new Cvor;
            temp = pocetak;
            while (temp->sljedeci != NULL) {
                temp = temp->sljedeci;
            }
        temp->sljedeci = p;
    }
}

template<typename Tip>
void CirkularnaLista<Tip>::DodajNaPocetak(const Tip & info){
    Cvor *p = new Cvor(info,0);

    if(pocetak == 0) { pocetak = p; p->sljedeci = pocetak;}
    else{
        Cvor *temp = pocetak;
        while(temp->sljedeci != pocetak)
            temp = temp->sljedeci;
        p->sljedeci = pocetak;
        pocetak = p;
        temp->sljedeci = pocetak;
    }
}

int main(){
    CirkularnaLista<int> cirkularna;
    cirkularna.DodajNaPocetak(5);
    cirkularna.DodajNaPocetak(9);
    cirkularna.DodajNaPocetak(7);
    cirkularna.Prikazi();
    CirkularnaLista<int>lista;
    lista.DodajNaKraj(3);
    lista.DodajNaKraj(11);
    lista.DodajNaKraj(17);
    lista.Prikazi();

return 0;
}

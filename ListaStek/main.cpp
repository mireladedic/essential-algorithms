/*  Created on : 02.12.2017,Friday, 03:31 AM
    By Mirela Dedic */
#include <iostream>
#include <stdexcept>
template<typename Tip>
class Stek{
private:
    Stek(const Stek &);
    Stek &operator=(const Stek &);
public:
    Stek(){}
    ~Stek(){}
    virtual void Brisi() = 0;
    virtual void StaviNaStek(const Tip &) = 0;
    virtual Tip SkiniSaSteka() = 0;
    virtual int Duzina() const = 0;
    virtual const &ElementNaVrhu()const = 0;
};
template<typename Tip>
class ListaStek : public Stek<Tip>{
    struct Cvor{
        Tip info;
        Cvor *sljedeci;
    Cvor(const Tip &info,Cvor *sljedeci): info(info),sljedeci(sljedeci){}
    };
    Cvor * vrh;
    int velicina;
public:
    void Brisi() override{
        if(!JeLiPrazan()) SkiniSaSteka();
    }
    ListaStek() : vrh(0),velicina(0){}
    ~ListaStek(){ Brisi(); }
    bool JeLiPrazan() const{ return vrh == 0; }

    void StaviNaStek(const Tip &) override;
    Tip SkiniSaSteka() override;
    int Duzina() const override {return velicina; }
    const &ElementNaVrhu()const override;
    void Kopiraj(const ListaStek &);
    ListaStek(const ListaStek &);
    ListaStek &operator=(const ListaStek &);

    void Prikazi()const{
        Cvor *p = vrh;
        while(p != 0){
            std::cout<<p->info<<"\n";
            p = p->sljedeci;
        }
    }

};
template<typename Tip>
void ListaStek<Tip>::StaviNaStek(const Tip &info){
    vrh = new Cvor(info,vrh);
    velicina++;
}
template<typename Tip>
 Tip ListaStek<Tip>::SkiniSaSteka(){
    if(JeLiPrazan()) throw std::domain_error("ListaStek prazan");
    Tip x = vrh->info;
    Cvor *p = vrh->sljedeci;
    delete vrh;
    vrh = p;
    velicina--;
    return x;
}
template<typename Tip>
const &ListaStek<Tip>::ElementNaVrhu()const{
     if(JeLiPrazan()) throw std::domain_error("ListaStek prazan");
     return vrh->info;
}
template<typename Tip>
void ListaStek<Tip>::Kopiraj(const ListaStek &s){
    Cvor *q,*p = s.vrh;
    vrh = 0;
    velicina = s.velicina;
    while(p!= 0){
        Cvor *n = new Cvor(p->info,0);
        if(vrh == 0) vrh = n;
        else
            q->sljedeci = n; // >>>>> ????

        p = p->sljedeci;
        q = n;
    }
}
template<typename Tip>
ListaStek<Tip>::ListaStek(const ListaStek &s){  Kopiraj(s); }
template<typename Tip>
ListaStek<Tip> &ListaStek<Tip>::operator=(const ListaStek &s){
    if(&this == s) return *this;
    Brisi();
    Kopiraj(s);
    return *this;
}

int main()
{
    ListaStek<int>s;
    s.StaviNaStek(3);
    s.StaviNaStek(4);
    s.Prikazi();
    ListaStek<int>l = s;
    l.Prikazi();
    return 0;
}

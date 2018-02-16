/*  Created on : 04/12/2017,Monday,02:00 PM
    By Mirela Dedic  */

#include <iostream>
#include <stdexcept>
template<typename Tip>
class Stek{
private :
    void operator=(const Stek &);
    Stek(const Stek &);

public:
    Stek(){}
    virtual ~Stek(){}
    virtual void Brisi() = 0;
    virtual void StaviNaStek(const Tip &info) = 0;
    virtual Tip SkiniSaSteka() = 0;
    virtual const &ElementNaVrhu() const = 0;
    virtual int Duzina() = 0;
};
template<typename Tip>
class ListaStek : public Stek<Tip>{
        struct Cvor{
            Tip info;
            Cvor *sljedeci;

            Cvor(Tip info, Cvor *sljedeci) : info(info),sljedeci(sljedeci) {}
            Cvor(Cvor * sljedeci = 0) : sljedeci(sljedeci){}
        };

        Cvor * vrh;
        int velicina;
public:
    ListaStek() : vrh(0),velicina(0) {}
    ListaStek(const ListaStek &);
    ListaStek &operator=(const ListaStek &);
    ~ListaStek(){ Brisi(); }
    void StaviNaStek(const Tip &) override;
    Tip SkiniSaSteka() override;
    const &ElementNaVrhu() const override;
    int Duzina() override;
    bool JeLiPrazan();
    void Kopiraj(const ListaStek &);
    void Brisi() override;
    void Prikazi()const;
};
template<typename Tip>
ListaStek<Tip>::ListaStek(const ListaStek & stek){
    Kopiraj(stek);
}
template<typename Tip>
bool ListaStek<Tip>::JeLiPrazan(){return vrh==0; }
template<typename Tip>
void ListaStek<Tip>::StaviNaStek(const Tip &info){
    vrh = new  Cvor(info,vrh); velicina++;
}
template<typename Tip>
Tip ListaStek<Tip>::SkiniSaSteka(){
    if(JeLiPrazan()) throw std::domain_error("Stek je prazan");
    Tip info = vrh->info;
    Cvor *p = vrh->sljedeci;
    delete vrh;
    vrh = p;
    velicina--;
    return info;
}
template<typename Tip>
int ListaStek<Tip>::Duzina() { return velicina; }
template<typename Tip>
const &ListaStek<Tip>::ElementNaVrhu() const {
    if(vrh == 0) throw std::domain_error("Nema se sta vratiti");
    return vrh->info;
}
template<typename Tip>
void ListaStek<Tip>::Brisi(){
    if(!JeLiPrazan()) SkiniSaSteka();
}
template<typename Tip>
ListaStek<Tip> &ListaStek<Tip>::operator=(const ListaStek &stek){
    if(this = &stek) return;
    Brisi();
    Kopiraj(stek);
    return *this;

}
template<typename Tip>
void ListaStek<Tip>::Kopiraj(const ListaStek &stek){
    Cvor *p = stek.vrh;
    Cvor* q ;
    vrh = 0;
    this->velicina = stek.velicina;
    while(p != 0){
        Cvor *n = new Cvor(p->info,0);
        if(vrh == 0) vrh = n;
        else q->sljedeci = n;

        p = p->sljedeci;
        q = n;
    }
}
template<typename Tip>
void ListaStek<Tip>::Prikazi()const{
    Cvor *p = vrh;

    while(p != 0){
        std::cout<<p->info<<"|";
        p = p->sljedeci;
    }
    std::cout<<"\n";
}
int main()
{
    ListaStek<int> s;
    s.StaviNaStek(2);
    s.StaviNaStek(3);
    s.StaviNaStek(5);
    s.Prikazi();
    ListaStek<int> ls = s;
    ls.Prikazi();

    return 0;
}

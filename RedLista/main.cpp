/* Created on 04.12.201, Monday,23:30
 * BY Mirela Dedic */

#include <iostream>
#include <stdexcept>
template<typename Tip>
class Red{
private:
    Red &operator=(const Red&);
    Red(const Red &);
public:
    Red(){}
    ~Red(){}
    virtual void Brisi() = 0;
    virtual void StaviURed(const Tip &) = 0;
    virtual Tip IzvadiIzReda() = 0;
    virtual const Tip &ElementNaCelu()const = 0;
    virtual int Duzina() const = 0;
};

template<typename Tip>
class RedLista : public Red<Tip>{
    struct Cvor{
        Tip info;
        Cvor *sljedeci;
        Cvor(Tip info,Cvor *sljedeci): info(info),sljedeci(sljedeci){}
        Cvor(Cvor *sljedeci = nullptr) : sljedeci(sljedeci){}
    };
    Cvor *pocetak;
    Cvor *kraj;
    int duzina;
    void Unisti();
    void Kopiraj(const RedLista &);
public:
    RedLista() : pocetak(0),kraj(0),duzina(0){}
    ~RedLista(){ Unisti(); }
    RedLista &operator=(const RedLista &);
    RedLista(const RedLista &);

    void Brisi() override;
    void StaviURed(const Tip &) override;
    Tip IzvadiIzReda() override;
    const Tip &ElementNaCelu()const override;
    int Duzina() const override;
    bool JeLiPrazan();
    void Prikazi()const;

};
template<typename Tip>
void RedLista<Tip>::Kopiraj(const RedLista & red){
    pocetak = 0;
    duzina = red.duzina;
    Cvor *p = red.pocetak;
    Cvor *q;
    while(p != 0){
        Cvor *n = new Cvor(p->info,0);
        if(pocetak == 0) pocetak = n;
        else q->sljedeci = n;

        p = p->sljedeci;
        q = n;
    }

  /*  Cvor *p = pocetak;
    while(p != 0){
        StaviURed(p->info);
        p = p->sljedeci;
    }
*/

}

template<typename Tip>
RedLista<Tip>::RedLista(const RedLista &red) {
    Kopiraj(red);
}
template<typename Tip>
RedLista<Tip> &RedLista<Tip>::operator=(const RedLista &red) {
    if(this == &red) return *this;
    Unisti();
    Kopiraj(red);
    return *this;
}
template<typename Tip>
void RedLista<Tip>::Unisti(){
    while(!JeLiPrazan()){
        IzvadiIzReda();
    }
}
template<typename Tip>
void RedLista<Tip>::Brisi(){
    Unisti();
}
template<typename Tip>
void RedLista<Tip>::StaviURed(const Tip &info){
    Cvor *n = new Cvor(info,0);
    if(pocetak == 0) pocetak =kraj =  n;
    else{
        kraj->sljedeci = n;
        kraj = kraj->sljedeci;
    }
    duzina++;
}
template<typename Tip>
Tip RedLista<Tip>::IzvadiIzReda(){
    if(pocetak == 0) throw("Red je prazan");
    Tip el = pocetak->info;
    Cvor *p = pocetak;
    if(pocetak == kraj) pocetak = kraj = 0;
    else {
        pocetak = pocetak->sljedeci;
    }
    delete p;
    duzina--;
    return el;
}
template<typename Tip>
const Tip &RedLista<Tip>::ElementNaCelu()const{
    return pocetak->info;
}
template<typename Tip>
int RedLista<Tip>::Duzina() const{
    return duzina;
}
template<typename Tip>
bool RedLista<Tip>::JeLiPrazan(){
    return pocetak == 0;
}
template<typename Tip>
void RedLista<Tip>::Prikazi()const{
    Cvor *p = pocetak;
    while(p != 0){
        std::cout<<p->info<<"|";
        p = p->sljedeci;
    }
    std::cout<<"\n";
}

class
int main() {
    RedLista<int> red;
    red.StaviURed(2);
    red.StaviURed(3);
    red.StaviURed(5);
    red.Prikazi();
    RedLista<int> novi = red;
    novi.Prikazi();
    return 0;
}
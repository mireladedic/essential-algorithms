/*Created On 04.12.2017,Monday,22:07
  By Mirela Dedic */
#include<iostream>
#include<stdexcept>
template<typename Tip>
class Red{
private:
    Red &operator=(const Red &);
    Red(const Red &);
public:
    Red(){}
    ~Red(){}
    virtual void Brisi() = 0;
    virtual void StaviURed(const Tip &) = 0;
    virtual Tip IzvadiIzReda() = 0;
    virtual const Tip &ElementNaCelu()const = 0;
    virtual int Duzina() = 0;
};

template<typename Tip>
class NizRed : public Red<Tip> {
    int kapacitet, velicina;
    Tip *niz;
    int pocetak, kraj;
public:
    NizRed(int kapacitet = 5) : kapacitet(kapacitet),velicina(0),pocetak(-1),kraj(-1), niz(new Tip[kapacitet]){}
    ~NizRed() { delete[] niz; }

    void Brisi()  override;
    void StaviURed(const Tip &) override;
    Tip IzvadiIzReda() override;
    const Tip &ElementNaCelu()const override;
    int Duzina() override;
    void Prikazi();

    bool JeLiPun() {
        return pocetak == (kraj + 1) % kapacitet;
    }

    bool JeLiPrazan() {
        return pocetak == -1;
    }
};
template <typename Tip>
void NizRed<Tip>::Prikazi() {
    if(JeLiPrazan())throw std::domain_error("Red je prazan");
    std::cout<<"Red\n";
    int i = pocetak;

    do{
        std::cout<<niz[i]<<"|";
        i = (i + 1) % kapacitet;
    }while(i != (kraj + 1) % kapacitet);
}
template<typename Tip>
void NizRed<Tip>::Brisi() {
    pocetak = -1; kraj = -1;
}
template<typename Tip>
const Tip &NizRed<Tip>::ElementNaCelu()const {
    if(pocetak != -1)
    return niz[pocetak];
}
template<typename Tip>
int NizRed<Tip>::Duzina() {
    if (pocetak == -1) return 0;
    else
        return ((kraj + kapacitet) - pocetak) % kapacitet + 1;
}

template<typename Tip>
void NizRed<Tip>::StaviURed(const Tip &el) {
    if (JeLiPun()) throw std::domain_error("Red je pun!");
    //...POSTAVI KRAJ,DODA ELEMENT
    kraj = (kraj + 1) % kapacitet;
    niz[kraj] = el;
    if(pocetak == -1) pocetak = 0;
}
template<typename Tip>
Tip NizRed<Tip>::IzvadiIzReda() {
    if (JeLiPrazan()) throw std::domain_error("Red je prazan");
    //..SAMO POMJERI POCETAK ZA JEDAN
    if (pocetak == kraj) pocetak = kraj = -1;
    else
        pocetak = (pocetak + 1) % kapacitet;
}

int main() {
   NizRed<int> red;
    red.StaviURed(2);
    red.StaviURed(3);
    red.StaviURed(5);
    red.IzvadiIzReda();
    red.Prikazi();
    std::cout<<"\n"<<red.ElementNaCelu()<<" " << red.Duzina()<<std::endl;
    return 0;
}
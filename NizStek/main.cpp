/*  Created on : 02.12.2017,Friday
    By Mirela Dedic */
#include <iostream>
#include <stdexcept>
template<typename Tip>
class Stek{
private:
    void operator=(const Stek &);
    Stek(const Stek &);
public:
    Stek(){}
    virtual ~Stek(){}
    virtual void Brisi() = 0;
    virtual void StaviNaStek(const Tip &) = 0;
    virtual Tip SkiniSaSteka() = 0;
    virtual const Tip &ElementNaVrhu()const = 0;
    virtual int Duzina()const =0;
};
template<typename Tip>
class NizStek: public Stek<Tip>{
    int kapacitet;
    int vrh;
    Tip *niz;
public:
    NizStek(int kapacitet = 5): kapacitet(kapacitet),vrh(-1),niz(new Tip[kapacitet]){}
    ~NizStek(){ delete [] niz; }
    void Brisi()override { vrh = -1; }
    int Duzina()const override{ return vrh + 1;}
    bool JeLiPrazan()const { return vrh == -1;}
    bool JeLiPun()const {return vrh == kapacitet - 1; }

    void StaviNaStek(const Tip &) override;
    Tip SkiniSaSteka() override;
    const Tip &ElementNaVrhu()const override;

    void Prikazi()const{
        for(int i = vrh; i >= 0; i--)
            std::cout<< i << " " << niz[i] << "\n" ;

    }
};
template<typename Tip>
void NizStek<Tip>::StaviNaStek(const Tip &el){
    if(JeLiPun()) throw std::domain_error("Stek je pun!");
    vrh++;
    niz[vrh] = el;
}
template<typename Tip>
Tip NizStek<Tip>::SkiniSaSteka(){
    if(JeLiPrazan()) throw std::domain_error("Stek je prazan!");
    Tip el = niz[vrh];
    vrh--;
    return el;
}
template<typename Tip>
const Tip &NizStek<Tip>::ElementNaVrhu()const{
    if(JeLiPrazan()) throw std::domain_error("Stej prazan.");
    return niz[vrh];
}
int main()
{
    NizStek<int>s;
    s.StaviNaStek(23);
    s.StaviNaStek(15);
    s.StaviNaStek(30);
    s.StaviNaStek(12);
    s.SkiniSaSteka();
    s.Prikazi();
    std::cout<<s.ElementNaVrhu()<<" | " <<s.Duzina();
    return 0;
}

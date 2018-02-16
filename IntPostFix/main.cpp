/* Created on 04.12.2017,Monday,14:45
   By Mirela Dedic */
#include <iostream>
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
    virtual const Tip &ElementNaVrhu() const = 0;
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
    ListaStek() : vrh(nullptr),velicina(0) {}
    ListaStek(const ListaStek &);
    ListaStek &operator=(const ListaStek &);
    ~ListaStek(){ Brisi(); }
    void StaviNaStek(const Tip &) override;
    Tip SkiniSaSteka() override;
    const Tip &ElementNaVrhu() const override;
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
bool ListaStek<Tip>::JeLiPrazan(){return vrh== nullptr; }
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
const Tip &ListaStek<Tip>::ElementNaVrhu() const {
    if(vrh == 0) throw std::domain_error("Nema se sta vratiti");
    return vrh->info;
}
template<typename Tip>
void ListaStek<Tip>::Brisi(){
    if(!JeLiPrazan()) SkiniSaSteka();
}
template<typename Tip>
ListaStek<Tip> &ListaStek<Tip>::operator=(const ListaStek &stek){
    if(this == &stek) return *this;
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
class IntPostFix{
private:
    static const int MaxVelicina = 40;
    char Izraz[MaxVelicina + 1];
    ListaStek<int>stek;
    int rezultat;
    bool JeLiOperator(const char znak) const;
    bool PrimijeniOperator(const char Operator,const int operand1,const int operand2);
public:
    IntPostFix(){}
    void Ucitaj();                      //.. CITANJE POSTFIKSINIH IZRAZA
    void Evaluacija();                  //...   EVALUACIJA IZRAZA
    void IspisRezultata()const;
    int Izdvoji(int &b);             //... IZDVAJANJE BROJA IZ IZRAZA

};
void IntPostFix::Ucitaj() {
    //stek.Brisi();
    stek = *(new ListaStek<int>());
    std::cin.clear();
    //std::cin.ignore(100,'\n');
    std::cin.getline(Izraz,MaxVelicina);
}

bool IntPostFix::JeLiOperator(const char znak) const {
    if(znak == '+' || znak == '-' || znak == '*' || znak =='/') return  true;
    return  false;
}

bool IntPostFix::PrimijeniOperator(const char Operator, const int operand1, const int operand2) {
    switch(Operator){
        case '*' :
            stek.StaviNaStek(operand2 * operand1);
            break;
        case '/':
            stek.StaviNaStek(operand2 / operand1);
            break;
        case'-':
            stek.StaviNaStek(operand2 - operand1);
            break;
        case'+':
            stek.StaviNaStek(operand2 + operand1);
            break;
        default:
            return  false;
    }

    return  true;
}

void IntPostFix::Evaluacija() {
    int operand1,operand2;
    int i = 0;
    while(Izraz[i]) {
        if (JeLiOperator(Izraz[i])) {
            operand1 = stek.SkiniSaSteka();
            operand2 = stek.SkiniSaSteka();
            PrimijeniOperator(Izraz[i], operand1, operand2);
        } else if (int(Izraz[i]) >= int('0') && int(Izraz[i]) <= int('9')) {
            stek.StaviNaStek(Izdvoji(i));
        }
        i++;

    }
    rezultat = stek.SkiniSaSteka();
    if(!stek.JeLiPrazan()) throw("Previse operanada");
}

void IntPostFix::IspisRezultata() const {
    std::cout<<"rezultat = "<< rezultat<<std::endl;

}

int IntPostFix::Izdvoji(int &b) {
    int broj(Izraz[b] - '0');
    b++;
    while(Izraz[b] >= '0' && Izraz[b] <= '9'){
        broj = 10 * broj - Izraz[b] - '0';
        b++;
    }

    b--;
    return  broj;
}


int main() {
    IntPostFix izraz;
    std::cout<<"Unesite postfiksni izraz:\n";
    izraz.Ucitaj();

    izraz.Evaluacija();
    izraz.IspisRezultata();

    std::cin.get();
    return 0;
}
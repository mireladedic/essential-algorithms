//
// Created by Mirela on 12/6/2017.
//

#ifndef BINARNOPRETRAZIVANJE_LISTA_H
#define BINARNOPRETRAZIVANJE_LISTA_H
template<typename Tip>
class Lista{
private :
    void operator = (const Lista &l); // ... ZASTITA ZA DODJELU
    Lista(const Lista &l); // ZASTITS ZA KONSTRUKTOR KOPIJE

public :
    Lista(){} // ...PODRAZUMIJEVANI KONSTRUKTOR
    virtual ~Lista(){} //...BAZNI DESTRUKTOR
    virtual void Brisi() = 0;
    virtual bool Umetni(const Tip &) = 0;
    virtual bool Dodaj(const Tip &) = 0;
    virtual Tip Izbaci()= 0;
    virtual void IdiNaPocetak() = 0;
    virtual void IdiNaKraj() = 0;
    virtual void IdiNaSljedeci() = 0;
    virtual void IdiNaPrethodni() = 0;
    virtual void IdiNaPoziciju(int i) = 0;
    virtual int LDuzina() const = 0;
    virtual int DDuzina() const = 0;
    virtual const Tip &DajTekuciElement() const = 0;
};
#endif //BINARNOPRETRAZIVANJE_LISTA_H

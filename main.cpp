#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct berResults
{
    double tot;
    double err;
    float ber;
    clock_t t1;
    clock_t t2;
};
Mechanizm Hamminga(Mechanizm m1, Mechanizm m2);
void StworzPlik(const string nazwa, const int licznik, const char wartosc);
WynikBER ObliczBER(string Splik1, string Splik2);
void WyswietlWynik(WynikBER Wynik);
Mechanizm Hamminga(Mechanizm m1, Mechanizm m2)
void OtoworzLOG(string NazwaPliku)
void ZapiszLOG(string msg)
void Zamknij(void)

Mechanizm Hamminga(Mechanizm m1, Mechanizm m2)
{
    Mechanizm x = m1 ^ m2;
    Mechanizm UstawBit = 0;
    while (x > 0)
    {
        UstawBit += x & 1;
        x >>= 1;
    }
    return UstawBit;
}
void StworzPlik(const string nazwa, const int licznik, const char wartosc)
{
    fstream P;
    P.open(nazwa.c_str(), ios::binary | ios::out);
    for (int i = 0; i < licznik; i++)
    {
        P.write((char*)&wartosc, 1);
    }
    P.close();
}
WynikBER ObliczBER(string Splik1, string Splik2)
{
    fstream P1, P2;
    WynikBER Wynik;
    Wynik.t1 = 0;
    Wynik.t2 = 0;
    Wynik.ber = 0;
    Wynik.err = 0;
    Wynik.tot = 0;
    ZapiszLOG("Obliczanie BER");
    P1.open(Splik1.c_str(), ios::binary | ios::in);
    P2.open(Splik2.c_str(), ios::binary | ios::in);
    char a = 0x00;
    char b = 0x00;
    Wynik.t1 = clock();
    while (!P1.eof())
    {
        P1 >> a;
        P2 >> b;
        if (!P1.eof())
        {
            Wynik.err += Hamminga(a, b);
            Wynik.tot += 8;
        }
    }
    Wynik.ber = (float)Wynik.err / Wynik.tot;
    Wynik.t2 = clock();
    ZapiszLOG("Wykonano obliczenia BER");
    return Wynik;
}
void WyswietlWynik(WynikBER Wynik)
{
    stringstream message;
    message << "Wyniki: " << endl;
    message << "BER: " << Wynik.ber << endl;
    message << "Tot: " << Wynik.tot << endl;
    message << "Bledy: " << Wynik.err << endl;
    message << "Czas obliczen: " << ((float)Wynik.t2 - Wynik.t1) / CLOCKS_PER_SEC << " sec " << endl;
    ZapiszLOG(message.str());
}
fstream PlikLOG;
void OtworzLOG(string NazwaPliku)
{
    PlikLOG.open(NazwaPliku.c_str(), ios_base::app);
    if (!PlikLOG.good() == true)
    {
        cout << "Niemozna otworzyc pliku LOG " << "log.txt" << endl;
    }
    ZapiszLOG("Plik LOG otwarty");
}

void ZamknijLOG(void)
{
    ZapiszLOG("Plik LOG zamkniety");
    PlikLOG.close();
}
void ZapiszLOG(string msg)
{
    string ss;
    time_t currentTime = time(NULL);
    string txttime = (string)asctime(localtime(&currentTime));
    txttime = txttime.substr(0, txttime.length() - 1);
    ss = (string)"T: " + txttime + " M: " + msg + "\n";
    PlikLOG << ss.c_str();
    PlikLOG.flush();
    cout << ss.c_str();
    cout.flush();
}
int main(int argc, char* argv[])
{
    string Splik1;
    string Splik2;
    WynikBER Wynik;
    OtworzLOG("log.log");
    if (argc != 3)
    {
        ZapiszLOG("Tworzenie plikow testowych");
        StworzPlik("Plik1.bin", 100, 0xFF);
        StworzPlik("Plik2.bin", 100, 0xFE);
        //StworzPlik("Plik1.bin", 100, 0xFF); 
        //StworzPlik("Plik2.bin", 100, 0xFD); 
        //StworzPlik("Plik1.bin",400000000,0x55); 
        //StworzPlik("Plik2.bin",400000000,0x50);
        ZapiszLOG("Pliki testowe sa gotowe");
    }
    else
    {
        Splik1 = argv[1];
        Splik2 = argv[2];

        ZapiszLOG("Przetwarzanie pliku testowego");
        Wynik = ObliczBER(Splik1, Splik2);
        WyswietlWynik(Wynik);
    }
    ZamknijLOG();
    return 0;
}

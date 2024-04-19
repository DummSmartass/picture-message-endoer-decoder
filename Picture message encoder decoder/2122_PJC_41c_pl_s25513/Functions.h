//
// Created by User on 18.06.2022.
//

//
// Potrzebne importy
//

#ifndef PROJEKTC___FUNCTIONS_H
#define PROJEKTC___FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;

//! Klasa Functions
/*******************************************************************************
 * klasa Functions zawiera przydatne, ale nie bezpośrednio związane z operacjami na obrazach funkcje
 * są one później używane przez komponenty innych klas
 *******************************************************************************/
class Functions
{
public:

    //! funkcja toUpper
    /*******************************************************************************
     *
     * @param s - zmienna typu string zawierająca
     *
     * funkcja iteruje po charach string s i zapisuje wartości kolejnych char potraktowanych funkcją toUpper tworząc jego kopie z małymi literami zastąpionymi przez duże
     *
     * @return zwracana jest wersja zmiennej s ze wszystkimi małymi literami zamienionymi na duże
    *******************************************************************************/
    static string toUpper(string s);


    //! funkcja toBit
    /*******************************************************************************
     *
     * @tparam T - typ podanej tablicy
     * @param image - tablica do modyfikacji
     * @param text - text którego fragment będzie zawarty w tablicy
     * @param amount  - długość fragment text do zawarcia w tablicy
     *
     * funkcja koduje binarnie fragment tekst długości amount do ostatniego bita pierwszych amount elementów tablicy z użyciem operacji bitowych
     * w ostatnim elemencie tablicy zakodowanym umieszczany jest znak końca wiadomosći
    *******************************************************************************/
    template <typename T>
    static void toBit(T image[],const string text,const int amount)
    {
        for (int i = 0; i < amount; ++i)
        {
            int pom=256;
            for (int j = 0; j < 8; ++j)
            {
                image[i*9+j]=image[i*9+j] & (0xFE) | ((int)(text[i]) & (pom=pom/2))/pom;
            }
            if(i==amount-1)
                image[i*9+8]=image[i*9+8] & (0xFE) | 1;
            else
                image[i*9+8]=image[i*9+8] & (0xFE);
        }
    }


    //! funkcja  FromBit
    /*******************************************************************************
     *
     * @tparam T - typ podanej tablicy
     * @param image - tablica z zakodowaną wiadomością
     *
     * funkcja dekoduje wiadomość binarną zakodowaną na ostatnim bicie części elementów element tablicy
     * wiadomość jest zamieniana na string a odczyt kończy sie po napodkaniu znaku końca
     *
     * @return zwraca odczytaną z tablicy wiadomość
    *******************************************************************************/
    template <typename T>
    static string fromBit(const T image[])
    {
        string s="";
        int i=0;

        do
        {
            s=s+(char)( 128*(image[9*i]&1) + 64*(image[9*i+1]&1) + 32*(image[9*i+2]&1) + 16*(image[9*i+3]&1) + 8*(image[9*i+4]&1) + 4*(image[9*i+5]&1) + 2*(image[9*i+6]&1) + 1*(image[9*i+7]&1)) ;
            i++;
        }
        while(!(image[9*(i-1)+8] & 1));

        return s;
    }

};


#endif //PROJEKTC___FUNCTIONS_H

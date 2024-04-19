//
// Created by User on 18.06.2022.
//

#ifndef PROJEKTC___IMAGEOPERATIONS_H
#define PROJEKTC___IMAGEOPERATIONS_H

//
// Potrzebne importy
//

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <sys/stat.h>
#include <fstream>

using namespace std;

//! klasa ImageOperations
/*******************************************************************************
 * Zapewnia funkcje i przechowuje zmienne bezpośrednio powiązane z operacjami na obrazach
*******************************************************************************/
class ImageOperations

{
public:

    //! konstruktory ImageOperations
    /*******************************************************************************
     *
     * @param path - ścieżkado pliku od użytkownika
     * @param text - text od użytkownika
     *
     * Konstruktory z
     * 1. path and text
     * 2. path
     * 3. no data
     * wypełniają odpowiadające argumentom zmienne wewnątrz instancji klasy
    *******************************************************************************/
    ImageOperations(char *path, const string &text);
    ImageOperations(char *path);
    ImageOperations();

    //! destructor ImageOperations
    /**  nic nie robi  */
    virtual ~ImageOperations();

    //! funkcja i
    /*******************************************************************************
     *
     * sprawdza czy plik może być obsługiwany przez aplikacje
     * jeżeli tak uzyskuje za pomocą innych funkcji dane o pliku
     *
     * wypisuje: format pliku, wymiar obrazka(w pikselach), wielkość pliku, ostatni czas modyfikacji i ile znaków można zakodować w danym pliku
    *******************************************************************************/
    void i() const;

    //! funkcja e
    /*******************************************************************************
     *
     * sprawdza czy plik może być obsługiwany przez aplikacje
     * jeżeli tak to dostosowuje długość textu od użytkownika i zakodowuje go w obraz z uszyciem funkcji write
    *******************************************************************************/
    void e() const;

    //! funkcja d
    /*******************************************************************************
     *
     * sprawdza czy plik może być obsługiwany przez aplikacje
     * jeżeli tak to odszyfrowuje wiadomość zapisaną w obrazie do którego prowadzi ścieżka path
    *******************************************************************************/
    void d() const;

    //! funkcja c
    /**  używa CheckA i zwraca adekwatną wiadomość   */
    void c() const;

    //! funkcja h
    /**   wyświetla stronę help   **/
    void h() const;


private:
    //! char* path variable
    /**   zawiera ścieżkę do pliku   */
    char *path;

    //! string text variable
    /**  zawiera tekst od urzytkownika    */
    string text;

    //! vector<string> typy_wspierane variable
    /**   zawiera wszystkie wspierane przez aplikacje typy graficzne   */
    vector<string> typy_wspierane = {"ppm","bmp"};

    //! funkcja getfSize
    /**   @return zwraca realny rozmiar pliku   */
    int getfSize() const;

    //! funkcja exist
    /**  @return sprawdza i zwraca wynik sprawdzenia czy plik o podanej nazwie istnieje w zasięgu   */
    bool exist() const;

    //! funkcja getTime
    /**  @return zwraca timestamp ostatniej edycji podanego pliku   */
    string getTime() const;

    //! funkcja getFormat
    /**  @return format danego pliku, jeżeli jest to format obsługiwany przez aplikacje  */
    string getFormat() const;


    //! funkcja getElement
    /*******************************************************************************
     *
     * @param elementID - które słowo trzeba uzyskać z pliku
     *
     * funkcja zwraca znajduje w pliku element na odpowiedniej pozycji i go zwraca
     *
     * @return zwraca elementID słowo z pliku
      *******************************************************************************/
    string getElement(const int elementID) const;

    //! funkcja getElement
    /*******************************************************************************
     *
     * @param elementID - od którego bitupodawać informacje
     * @param amount - ile bitów informacji podawać
     *
     * funkcja odczytuje amount bitów z pliku zaczynając od bitu elementID
     *
     * @return zwraca elementID słowo z pliku
      *******************************************************************************/
    int getElement (const int charID,int amount)const;

    //! funkcja getWidth
    /**  @return zwraca szerokość zapisanego obrazu (w pikselach) */
    int getWidth()const;

    //! funkcja getHight
    /**  @return zwraca wysokość zapisanego obrazu (w pikselach)   */
    int getHeight()const;

    //! funkcja getCompacity
    /**  @return zwraca trzykrotną ilość pixeli, jest to wartość niezbędna przy kodowaniu obrazu */
    int getCompacity()const;

    //! funkcja check
    /*******************************************************************************
     *
     * funkcja przeprowadza diagnostykę pliku do którego ścieżkę udostępnia użytkownika
     *
     * funkcja sprawdza czy plik istnieje
     * funkcja sprawdza czy plik nie jest pusty
     * czy jego typ i format są obsługiwane przez aplikacje
     *
     * @return zwraca czy plik jest zdatny do użycia przez aplikacje
    *******************************************************************************/
    bool check ()const;

    //! funkcja checkA
    /*******************************************************************************
     *
     * funkcja przeprowadza diagnostykę pliku do którego ścieżkę udostępnia użytkownika
     *
     * funkcja sprawdza czy plik istnieje
     * funkcja sprawdza czy plik nie jest pusty
     * czy jego typ i format są obsługiwane przez aplikacje
     *
     * po czym funkcja sprawdza czy wiadomość dostarczona przez użytkownika jest możliwa do zapisania wewnątrz pliku
     *
     * @return zwraca czy plik jest zdatny do użycia przez aplikacje i pomieszczenia wiadomości od użytkownika
    *******************************************************************************/
    bool checkA ()const;

    //! funkcja write
    /*******************************************************************************
     *
     * checkA = Advance check
     * @param length - długość wiadomości do zapisania
     *
     * funkcja sprawdza czy może odczytać plik
     * funkcja odczytuje plik i zapisuje jego zwartość
     * funkcja modyfikuje zapisaną zawartość pliku pod kontem zawarcia binarnie textu dostarczone prez użytkownika w ostatnich bitach każdego koloru za pomocą funkcji toBit
     * funkcja nadpisuje plik z zapisaną wiadomością
    *******************************************************************************/
    void write(int length)const;

    //! decryptText
    /*******************************************************************************
     *
     * funkcja sprawdza czy może odczytać plik
     * funkcja odczytuje plik i zapisuje jego zwartość
     * funkcja za pomocą funkcji fromBit odczytuje wiadomość zakodowaną w pliku
     *
     * @return funkcja zwraca odczytaną wiadomość
    *******************************************************************************/
    string decryptText()const;
};


#endif //PROJEKTC___IMAGEOPERATIONS_H

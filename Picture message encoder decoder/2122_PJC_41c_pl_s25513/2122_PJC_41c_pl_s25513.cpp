
//
// Potrzebne importy
//

#include <iostream>
#include <string>

#include "ImageOperations.h"
#include "Functions.h"
#include "ERRORmanager.h"

using  namespace std;

//! funkcja main
/*******************************************************************************
 * przyjmuje od 0 do 3 argument
 * w kolejności flaga, ścieżka do pliku ,wiadomość w cudzysłowach
*******************************************************************************/
int main(int argc, char *argv[])
{

    // sprawdzenie, czy istnieją argumenty
    if(argc==1)
    {
        //przekierowanie do helpa
        ImageOperations im = ImageOperations();
        im.h();
    }
    else
    {
        //przypisanie flagi do zmiennej
        const string flaga= Functions::toUpper(argv[1]);

        // weryfikacja flagi czy i
        if(flaga=="-I" or flaga=="--INFO")
        {
            // weryfikacja ilości argumentów
            if(argc==3)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations(argv[2]);
                im.i();
            }
            // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }

        // weryfikacja flagi czy e
        else if(flaga=="-E" or flaga=="--ENCRYPT")
        {
            // weryfikacja ilości argumentów
            if(argc==4)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations(argv[2],argv[3]);
                im.e();
            }
            // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }

        // weryfikacja flagi czy d
        else if(flaga=="-D" or flaga=="--DECRYPT")
        {
            // weryfikacja ilości argumentów
            if(argc==3)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations(argv[2]);
                im.d();
            }
            // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }

        // weryfikacja flagi czy c
        else if(flaga=="-C" or flaga=="--CHECK")
        {
            // weryfikacja ilości argumentów
            if(argc==4)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations(argv[2],argv[3]);
                im.c();
            }
            // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }

        // weryfikacja flagi czy h
        else if(flaga=="-H" or flaga=="--HELP")
        {
            // weryfikacja ilości argumentów
            if(argc==2)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations();
                im.h();
            }
            // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }

/*            // weryfikacja flagi czy s
        else if(flaga=="-S" or flaga=="--SETTINGS")
        {
            // weryfikacja ilości argumentów
            if(argc==2)
            {
                // utworzenie obiektu i wywołanie funkcji
                ImageOperations im = ImageOperations();
                im.s();
            }
                // odprowadzanie błędów
            else ERRORmanager::wrongAmountOfArguments();
        }*/

        // odprowadzanie błędów
        else ERRORmanager::unknownFlag();
    }
}





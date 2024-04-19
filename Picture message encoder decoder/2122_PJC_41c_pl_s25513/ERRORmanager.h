//
// Created by User on 18.06.2022.
//

#ifndef PROJEKTC___ERRORMANAGER_H
#define PROJEKTC___ERRORMANAGER_H

using namespace std;

class ERRORmanager
{
public:
    //! klasy ERRORÓW
    /*******************************************************************************
     *
     * wypisują wiadomości o błędach korespondujących ich nazwie
    *******************************************************************************/
    static void wrongAmountOfArguments();
    static void unknownFlag();
    static void fileDoesNotExist();
    static void fileIsEmpty();
    static void formatIsNotSupported();
    static void typeIsNotSupported();
    static void providedTextIsTooShort();
    static void providedTextIsTooLong();
};


#endif //PROJEKTC___ERRORMANAGER_H

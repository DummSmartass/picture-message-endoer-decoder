//
// Created by User on 18.06.2022.
//

//
// Potrzebne importy
//

#include <string>

#include "Functions.h"

string Functions::toUpper(string s)
{
    for (int i = 0; i < s.length(); ++i)
    {
        s[i]=toupper(s[i]);
    }
    return s;
}



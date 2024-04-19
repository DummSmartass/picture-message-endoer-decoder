//
// Created by User on 18.06.2022.
//

//
// Potrzebne importy
//
#include <iostream>

#include "ERRORmanager.h"

using namespace std;

void ERRORmanager::wrongAmountOfArguments()
{
    system("Color 04");
    cout <<"ERROR: Invalid amount of aruments for provided flag, to find out more use flag -h (with no further arguments)\n";
}

void ERRORmanager::unknownFlag()
{
    system("Color 04");
    cout<<"ERROR: Unknown flag provided, all flas are descibed under -h flag\n";
}

void ERRORmanager::fileDoesNotExist()
{
    system("Color 04");
    cout << "ERROR: Provided file does not exist)\n";
}

void ERRORmanager::fileIsEmpty()
{
    system("Color 04");
    cout << "ERROR: Provided file is empty\n";
}

void ERRORmanager::formatIsNotSupported()
{
    system("Color 04");
    cout << "ERROR: Provided file belongs to not supported format\n";
};

void ERRORmanager::typeIsNotSupported()
{
    system("Color 04");
    cout << "ERROR: Provided file belongs to not supported type\n";
};

void ERRORmanager::providedTextIsTooShort()
{
    system("Color 04");
    cout << "ERROR: Provided text could not be encrypted, it is too short\n";
};

void ERRORmanager::providedTextIsTooLong()
{
    system("Color 04");
    cout << "ERROR: Provided text is too long to fit without cropping in provided file\n";
};
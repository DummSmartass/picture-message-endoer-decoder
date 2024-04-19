//
// Created by User on 18.06.2022.
//

#ifndef PROJEKTC___IMAGEOPERATIONS_H
#define PROJEKTC___IMAGEOPERATIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <sys/stat.h>
#include <fstream>

using namespace std;

class ImageOperations
{
public:
    ImageOperations(char *path, const string &text);
    ImageOperations(char *path);

    virtual ~ImageOperations();
    int getfSize();
    bool exist();
    string getTime();
    string getFormat();
    string getElement(int elementID);
    int getElement (int charID,int amount);
    int getWidth();
    int getHight();
    int getCompacity();
    bool check ();
    bool checkA ();
    void write(int length);
    string decryptText();



private:
    char *path;
    string text;
    vector<string> typy_wspierane = {"ppm","bmp"};
};


#endif //PROJEKTC___IMAGEOPERATIONS_H

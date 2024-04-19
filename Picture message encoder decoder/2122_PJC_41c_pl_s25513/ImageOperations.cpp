//
// Created by User on 18.06.2022.
//

//
// Potrzebne importy
//
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <sys/stat.h>

#include "ImageOperations.h"
#include "Functions.h"
#include "ERRORmanager.h"


ImageOperations::~ImageOperations() {}


ImageOperations::ImageOperations(char *path, const string &text) : path(path), text(text) {}
ImageOperations::ImageOperations(char *path) : path(path) {}
ImageOperations::ImageOperations(){}


void ImageOperations::i() const
{
    if(check())
    {
        system("Color 0A");

        cout<<"File can be processed:"<<endl
        <<"     format of picture: "<<getFormat()<<endl
        <<"     picture dimensions: "<<getWidth()<<" x "<<getHeight()<<" pixels\n"
        <<"     size of file: "<<getfSize()<<" B\n"
        <<"     last modification time of file: "<<getTime()
        <<"     encrypted file can contain up to: "<<getCompacity()/9<<" characters\n";
    }
    else
    {
        system("Color 04");
        cout << "file can not be processed\n";
    }
}


void ImageOperations::e() const
{
    if(size(text)==0)
    {
        ERRORmanager::providedTextIsTooShort();
        return;
    }

    if(check())
    {
        int amount;
        if (size(text) * 9 < getCompacity())
        {
            amount = size(text);
        } else
            amount = getCompacity() / 9;

        write(amount);

        system("Color 0A");
        cout<<"Encrypting performed successfully";
        if(amount< size(text))
            cout<<"\nThe message has been shortened";
    }
    else
    {
        system("Color 04");
        cout << "Encrypting can not be performed";
    }
}


void ImageOperations::d() const
{
    system("Color 0E");
    cout<<decryptText();
}


void ImageOperations::c() const
{
    if(checkA())
    {
        system("Color 0A");
        cout << "encoding succesful";
    }
    else
    {
        system("Color 04");
        cout << "it is not possible to encode provided text into given file";
    }
}


void ImageOperations::h() const
{
    cout<<endl;
    system("Color 0B");
    cout<<"Welcome to Help page\n\n"
        <<"Primary purpose of this application is to allow to code text messages into pictures and to decode messages encoded into pictures back to text \n"
        <<"Coding and decoding is based on binary representation of message influencing last bits of all colors of each pixel\n\n"
        <<"Formats supported by application are: \n";
    for (string format:typy_wspierane){
        cout<<"  "<<format<<endl;
    }
    cout<<"\nTo navigate and use application's features require usage of flags:\n"
        <<"  -i(--info)\n"
        <<"     Flag -i requires one argument: path to the file"
        <<"     Flag -i allows user to examine whether provided file can be used for coding or decoding messages ,flag check whether file exit and if its format can be operated on in application \n"
        <<"     SYNTAX: -i filepath\n"
        <<"  -e(--encrypt)\n"
        <<"     Flag -e requires two argument: path to the file and text"
        <<"     Flag -e allows user to encrypt provided text into picture to which path leads to, on condition that it is possible to use this picture for such purposes \n"
        <<"     SYNTAX: -e filepath \"text\" \n"
        <<"  -d(--decrypt)\n"
        <<"     Flag -d requires one argument: path to the file"
        <<"     Flag -d allows user to get text encrypted into the file \n"
        <<"     SYNTAX: -d filepath\n"
        <<"  -c(--check)\n"
        <<"     Flag -c requires two argument: path to the file and text"
        <<"     Flag -c allows user to examine whether provided text can be encrypted into given file without need to crop the text \n"
        <<"     SYNTAX: -c filepath \"text\" \n"
        <<"  -h(--help)\n"
        <<"     Flag -h requires no arguments"
        <<"     Flag -h allows user to access help page\n"
        <<"     SYNTAX -h \n"
        <<"\n WARNINGS: "
        <<"     --encrypt will crop text if it is too long for provided picture\n"
        <<"     application will decode message from any not empty and existing provided file of operated format even if the message was never coded into it and it will print nonsense\n"
        <<"     application is prepared to avoid files of not suited type as well as empty and not existing files, but can not handle wrongly coded file\n"
        <<"     application is not prepared for handling any unnecessary content included in files (np commends) it may fail\n"
        <<"     application can't handle polish letters"
        <<"\n ERRORS: Application will display errors if: \n"
        << "    user attempt to use incorrect flag\n"
        << "    user attempt to use incorrect amount of argument on argument on flag\n"
        << "    user attempt to encode or decode from file that, does not exist, is empty or belongs to not supported format or type\n";
}


bool ImageOperations::exist() const
{
    struct stat fileInfo;

    if (stat(path, &fileInfo) != 0)
        return false;
    return true;
}


int ImageOperations::getfSize() const
{
    struct stat fileInfo;

    stat(path, &fileInfo);
    return fileInfo.st_size;
}


string ImageOperations::getTime() const
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    return ctime(&fileInfo.st_mtime);
}


string ImageOperations::getFormat() const
{
    for (string s1: typy_wspierane)
    {
        if (regex_match(path, regex(".*\\." + s1)))
        {
            return s1;
        }
    }
    return "0";
}


string ImageOperations::getElement(const int elementID) const
{
    ifstream image;
    image.open(path);

    if(!image.is_open())
        return "";

    string element;
    for (int i = 0; i < elementID+1; ++i)
    {
        element="";
        image>>element;
    }

    image.close();
    return element;
}


int ImageOperations::getElement (const int charID,const int amount) const
{

    int element=0;
    ifstream image;
    image.open(path, ios::in | ios::binary);
    if (!image.is_open())
    {
        return 0;
    }

    image.ignore(charID);
    unsigned char fileHeader[amount];
    image.read(reinterpret_cast<char *>(fileHeader),amount);

    for (int i = 0; i < amount; ++i)
    {
        element=element+(fileHeader[i]<<8*i);
    }

    image.close();
    return element;
}


int ImageOperations::getWidth() const
{
    if(getFormat()=="ppm")
    {
        return stoi(getElement(1));
    }
    else if(getFormat()=="bmp")
    {
        return getElement(18,4);
    }
}


int ImageOperations::getHeight() const
{
    if(getFormat()=="ppm")
    {
        return stoi(getElement(2));
    }
    else if(getFormat()=="bmp")
    {
        return getElement(22,4);
    }
}


int ImageOperations::getCompacity() const
{
    return getWidth()*getHeight()*3;
}


bool ImageOperations::check () const
{
    if (!exist())
    {
        ERRORmanager::fileDoesNotExist();
        return false;
    }

    if(getfSize()==0)
    {
        ERRORmanager::fileIsEmpty();
        return false;
    }

    if(getFormat()=="0")
    {
        ERRORmanager::formatIsNotSupported();
        return false;
    }

    if(getFormat()=="ppm")
        if(getElement(0)!="P3")
        {
            ERRORmanager::typeIsNotSupported();
            return false;
        }

    return true;
}


bool ImageOperations::checkA () const
{
    if(check())
    {
        if(size(text)==0)
        {
            ERRORmanager::providedTextIsTooShort();
            return false;
        }

        return size(text)*9<=getCompacity();
    }
    ERRORmanager::providedTextIsTooLong();
    false;
}


void ImageOperations::write(const int length) const
{
    if(getFormat()=="ppm")
    {
        ifstream in;
        in.open(path);

        string typ="",width="", hight="",rgb="";

        in>>typ;
        in>>width;
        in>>hight;
        in>>rgb;

        if (regex_match(rgb, regex("#.*")))
            in>>rgb;

        int compacity = stoi(width)*stoi(hight)*3;

        if(typ=="P3")
        {
            short image[compacity];

            for (int j = 0; j < compacity; ++j)
            {
                in>>image[j];
            }
            in.close();

            Functions::toBit(image,text,length);

            ofstream out;
            out.open(path);
            out<<typ<<'\n';
            out<<width<<' ';
            out<<hight<<'\n';
            out<<rgb<<'\n';
            for (int j = 0; j < compacity; ++j)
            {
                out<<image[j]<<' ';
            }

            out.close();
        }
    }

    else if (getFormat()=="bmp")
    {
        int offset=0;
        int hight=0;
        int width=0;
        const unsigned char bmpPad[3] = {0,0,0};
        ifstream in;
        in.open(path,ios::in | ios::binary);

        unsigned char fileHeader[14];
        in.read(reinterpret_cast<char *>(fileHeader),14);
        for (int i = 0; i < 4; ++i)
        {
            offset = offset + (fileHeader[i+10] << 8 * i);
        }

        unsigned char informationHeader[offset-14];
        in.read(reinterpret_cast<char *>(informationHeader),offset-14);
        for (int i = 0; i < 4; ++i)
        {
            width = width + (informationHeader[i+4] << 8 * i);
        }
        for (int i = 0; i < 4; ++i)
        {
            hight = hight + (informationHeader[i+8] << 8 * i);
        }

        unsigned char image[width*hight*3];
        const int paddingAmount = ((4-(width*3)%4)%4);
        unsigned char *p = &image[0];
        for(int y=0; y<hight; y++)
        {
            in.read(reinterpret_cast<char*>(p),width*3);
            p = p + width*3;
            in.ignore(paddingAmount);
        }
        in.close();

        Functions::toBit(image,text,length);

        ofstream out;
        out.open(path,ios::out | ios::binary);
        out.write(reinterpret_cast<char*>(fileHeader),14);
        out.write(reinterpret_cast<char*>(informationHeader),offset-14);

        p = &image[0];
        for(int y=0;y<hight; y++)
        {
            out.write(reinterpret_cast<char *>(p), width*3);
            p = p + width*3;
            out.write(reinterpret_cast<char*>(image),paddingAmount);
        }

        out.close();
    }
}


string ImageOperations::decryptText() const
{
    string message;

    if(getFormat()=="ppm")
    {
        ifstream in;
        in.open(path);
        string typ="",width="", hight="",rgb="";

        in>>typ;
        in>>width;
        in>>hight;
        in>>rgb;
        int compacity = stoi(width)*stoi(hight)*3;

        if(typ=="P3")
        {
            short image[compacity];

            for (int j = 0; j < compacity; ++j)
            {
                in>>image[j];
            }
            in.close();

            message = Functions::fromBit(image);
        }
    }
    else if (getFormat()=="bmp")
    {
        int offset=0;
        int hight=0;
        int width=0;

        ifstream in;
        in.open(path,ios::in | ios::binary);

        unsigned char fileHeader[14];
        in.read(reinterpret_cast<char *>(fileHeader),14);
        for (int i = 0; i < 4; ++i) {
            offset = offset + (fileHeader[i+10] << 8 * i);
        }

        unsigned char informationHeader[offset-14];
        in.read(reinterpret_cast<char *>(informationHeader),offset-14);
        for (int i = 0; i < 4; ++i) {
            width = width + (informationHeader[i+4] << 8 * i);
        }
        for (int i = 0; i < 4; ++i) {
            hight = hight + (informationHeader[i+8] << 8 * i);
        }

        unsigned char image[width*hight*3];
        const int paddingAmount = ((4-(width*3)%4)%4);

        unsigned char *p = &image[0];
        for(int y=0; y<hight; y++)
        {
            in.read(reinterpret_cast<char*>(p),width*3);
            p = p + width*3;
            in.ignore(paddingAmount);
        }
        in.close();

        message = Functions::fromBit(image);
    }
    return message;
}






















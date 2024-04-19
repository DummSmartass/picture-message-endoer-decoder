//
// Created by User on 18.06.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <sys/stat.h>
#include <fstream>

#include "ImageOperations.h"
#include "Functions.h"


ImageOperations::~ImageOperations() {}


ImageOperations::ImageOperations(char *path, const string &text) : path(path), text(text) {}
ImageOperations::ImageOperations(char *path) : path(path) {}


bool ImageOperations::exist()
{
    struct stat fileInfo;

    if (stat(path, &fileInfo) != 0)
        return false;
    return true;
}


int ImageOperations::getfSize()
{
    struct stat fileInfo;

    stat(path, &fileInfo);
    return fileInfo.st_size;
}


string ImageOperations::getTime()
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    return ctime(&fileInfo.st_mtime);
}


string ImageOperations::getFormat()
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    for (string s1: typy_wspierane)
    {
        if (regex_match(path, regex(".*\\." + s1)))
        {
            return s1;
        }
    }
    return "0";
}


string ImageOperations::getElement(int elementID)
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


int ImageOperations::getElement (int charID,int amount)
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


int ImageOperations::getWidth()
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


int ImageOperations::getHight()
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


int ImageOperations::getCompacity()
{
    return getWidth()*getHight()*3;
}


bool ImageOperations::check ()
{
    if (!exist())
        return false;

    if(getfSize()==0)
        return false;

    string format = getFormat();
    if(format=="0")
    {
        return false;
    }
    return true;
}


bool ImageOperations::checkA ()
{
    if(check())
    {
        return size(text)*9<=getCompacity();
    }
    false;
}


void ImageOperations::write(int length)
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

/*        if(typ=="P6"){
            // revisit
            in.close();
            in.open(path,ios::in | ios::binary);
            in.ignore(size(typ)+ size(width)+ size(hight)+ size(rgb)+4);

            unsigned char image[compacity];
            in.read(reinterpret_cast<char*>(image),compacity);



            *//*cout<<(sizeof(unsigned char))<<endl;*//*
            cout<<endl<<">"<<(0x00 + ((int)image[0]))<<"<"<<endl;

            in.close();

            toBit(image,text,length);

            ofstream out;
            out.open("test1.ppm");

            out<<typ<<"\n"<<width<<" "<<hight<<"\n"<<rgb<<"\n";
            out.write(reinterpret_cast<char*>(image),compacity);

            out.close();
        }*/

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


string ImageOperations::decryptText()
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
/*        if(typ=="P6")
        {
            // revisit
            in.close();
            in.open(path,ios::in | ios::binary);
            in.ignore(size(typ)+ size(width)+ size(hight)+ size(rgb)+4);

            unsigned char image[compacity];
            in.read(reinterpret_cast<char*>(image),compacity);
            in.close();

            message = Functions::fromBit(image);

        }*/

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






















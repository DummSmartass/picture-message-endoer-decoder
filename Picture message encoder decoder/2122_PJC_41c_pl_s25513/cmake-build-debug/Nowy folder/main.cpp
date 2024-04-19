#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <ctime>
#include <sys/stat.h>
#include <fstream>

using  namespace std;

vector<string> typy_wspierane = {"ppm","bmp"};

// tworzy kopie i zamienia wszystkie małe litery na wielkie w podanym kopi stringa, po czym ją zwraca
string toUpper(string s)// diała
{
    for (int i = 0; i < s.length(); ++i){
        s[i]=toupper(s[i]);
    }
    return s;
}//relocated


// sprawdzaczy plik coś zawiera
bool exist(const char *path) { //diziała

    struct stat fileInfo;
    if (stat(path, &fileInfo) != 0)
        return false;
    return true;
}//relocated

int getfSize(const char *path) //diała
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    return fileInfo.st_size;
}//relocated

string getTime(const char *path) // działa
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    return ctime(&fileInfo.st_mtime);
}//relocated

string getFormat(const char *path) //działa
{
    struct stat fileInfo;
    stat(path, &fileInfo);

    for (string s1: typy_wspierane) {
        if (regex_match(path, regex(".*\\." + s1))) {
            return s1;
        }
    }
    return "0";
}//relocated

string getElement(const char *path,int elementID) // działa
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
}//relocated

int getElement (const char *path, int charID,int amount) {

    int element=0;

    ifstream image;
    image.open(path, ios::in | ios::binary);
    if (!image.is_open()) {
        return 0;
    }

    image.ignore(charID);
    unsigned char fileHeader[amount];
    image.read(reinterpret_cast<char *>(fileHeader),amount);

    for (int i = 0; i < amount; ++i)
    {
        element=element+(fileHeader[i]<<8*i);
    }

    //element = fileHeader[18] + (fileHeader[19]<<8) + (fileHeader[20]<<16) + (fileHeader[21]<<24);
    image.close();

    return element;
}//relocated

int getWidth(const char *path)
{
    if(getFormat(path)=="ppm")
    {
        // stoi zamienia na int
        return stoi(getElement(path,1));
    }
    else if(getFormat(path)=="bmp")
    {
        // trzeba urzyc binarneo
        return getElement(path,18,4);
    }
}//relocated

int getHight(const char *path)
{
    if(getFormat(path)=="ppm")
    {
        // stoi zamienia na int
        return stoi(getElement(path,2));
    }
    else if(getFormat(path)=="bmp")
    {
        // trzeba urzyc binarnego
        return getElement(path,22,4);
    }
}//relocated

int getCompacity(const char *path)
{
    int compacity=getWidth(path)*getHight(path);
    if(getFormat(path)=="ppm")
    {
        return compacity*3;
    }
    else if(getFormat(path)=="bmp")
    {
        // trzeba urzyc binarnego
        return compacity*3;
    }
}//elocated

bool check (const char *path){

    // wykorzystanie funkcji notempty do weryfikacji czy plik istnieje
    if (!exist(path))
        return false;

    if(getfSize(path)==0)
        return false;

    string format = getFormat(path);
    if(format=="0")
    {
        return false;
    }
    return true;
}// relocated

bool check (const char *path,string text){

   if(check(path))
   {
       return size(text)*9<=getCompacity(path);
   }
   false;
}//relocated


void i(const char *path)
{
    if(check(path))
    {
        cout<<"type of picture: "<<getFormat(path)<<endl;
        cout<<"picture dimensions: "<<getWidth(path)<<"X"<<getHight(path)<<"pixels\n";
        cout<<"size of file: "<<getfSize(path)<<" B\n";
        cout<<"last modification time of file: "<<getTime(path)<<endl;
    }
    else
    //zaimplementować manager błędów
    cout<<"file can not be proccesed\n";
}

template <typename T>
void toBit(T image[],string text,int length)
{
    for (int i = 0; i < length; ++i)
    {
        int pom=256;
        for (int j = 0; j < 8; ++j)
        {
            image[i*9+j]=image[i*9+j] & (0xFE) | ((int)(text[i]) & (pom=pom/2))/pom;
        }
        if(i==length-1)
            image[i*9+8]=image[i*9+8] & (0xFE) | 1;
        else
            image[i*9+8]=image[i*9+8] & (0xFE);
    }
}//relocated


void write(const char *path,string text,int length)
{
    if(getFormat(path)=="ppm")
    {
        ifstream in;
        in.open(path);

        string typ="",width="", hight="",rgb="";

        in>>typ;
        in>>width;
        in>>hight;
        in>>rgb;

        int compacity = stoi(width)*stoi(hight)*3;


        if(typ=="P3"){
            short image[compacity];

            for (int j = 0; j < compacity; ++j)
            {
                in>>image[j];
            }
            in.close();

            toBit(image,text,length);

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
    else if (getFormat(path)=="bmp")
    {

        int offset=0;
        int hight=0;
        int width=0;
        const unsigned char bmpPad[3] = {0,0,0};

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

        toBit(image,text,length);

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
}//relocated

void e(const char *path,string text)
{
    if(check(path))
    {
        int length;
        if (size(text) * 9 < getCompacity(path)) {
            length = size(text);
        } else
            length = getCompacity(path) / 9;

        write(path, text, length);
    }
}


template <typename T>
string fromBit(T image[])
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
}// relocated


string decryptText(const char *path)
{
    string message;

    if(getFormat(path)=="ppm")
    {
        ifstream in;
        in.open(path);

        string typ="",width="", hight="",rgb="";

        in>>typ;
        in>>width;
        in>>hight;
        in>>rgb;

        int compacity = stoi(width)*stoi(hight)*3;


        if(typ=="P3"){
            short image[compacity];

            for (int j = 0; j < compacity; ++j)
            {
                in>>image[j];
            }
            in.close();

            message = fromBit(image);

        }
        if(typ=="P6"){
            // revisit
            in.close();
            in.open(path,ios::in | ios::binary);
            in.ignore(size(typ)+ size(width)+ size(hight)+ size(rgb)+4);

            unsigned char image[compacity];
            in.read(reinterpret_cast<char*>(image),compacity);
            in.close();

            message = fromBit(image);

        }

    }
    else if (getFormat(path)=="bmp")
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

        message = fromBit(image);
    }

    return message;
}//relocated

void d(const char *path)
{
    cout<<decryptText(path);
}

void c(const char *path,string text)
{
    if(check(path,text))
        cout<<"it is possible to encode provided text into given file";
}

void h()
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
        <<"     Flag -i reqires one argument: path to the file"
        <<"     Flag -i allows user to examine wheter provided file can be used for coding or decoding messages ,flag check whether file exit and if its format can be operated on in application \n"
        <<"     SYNTAX: -i filepath\n"
    <<"  -e(--encrypt)\n"
        <<"     Flag -e reqires two argument: path to the file and text"
        <<"     Flag -e allows user to encrypt provided text into picture to which path leads to, on condition that it is possible to use this picture for such purposes \n"
        <<"     SYNTAX: -e filepath \"text\" \n"
    <<"  -d(--decrypt)\n"
        <<"     Flag -d reqires one argument: path to the file"
        <<"     Flag -d allows user to get text encrypted into the file \n"
        <<"     SYNTAX: -d filepath\n"
    <<"  -c(--check)\n"
        <<"     Flag -c reires two argument: path to the file and text"
        <<"     Flag -c allows user to examine wheter provided text can be encrypted into given file withough need to crop the text \n"
        <<"     SYNTAX: -c filepath \"text\" \n"
    <<"  -h(--help)\n"
        <<"     Flag -h reqires no aruments"
        <<"     Flag -h allows user to acces help page\n"
        <<"     SYNTAX -h \n"
    <<"\n WARNINIGS: "
        <<"     --encrypt will crop text if it is too long for provided picture\n"
        <<"     aplication will decode message from any not empty and existing provided file of operated format even if the message was never coded into it and it will print nonsesne\n"
        <<"     application is prepered to avoid files of not suited type as well as empty and not existing files, but can not handle wrongly coded file\n"
        <<"     application not prepered for handling any unnesesary content included in files (np commends) it may fail\n"
    <<"\n ERRORS: Aplication will display errors if: \n"
        << "    user attept to use incorecct flag\n"
        << "    user attept to use incorect amount of arument on argument on flag\n"
        <<      "user attept to encode or decode from file that, does not exist, is empty or belongs to not supported type\n";

}








int main(int argc, char *argv[])
{
    string typ="";

    ifstream image;
    image.open("ppm1.ppm");
    image>>typ;
    image.close();
    cout<<">"<<typ<<"<"<<endl;

    cout<<getfSize("ppm1.ppm")<<endl;
    cout<<getTime("ppm1.ppm");
    cout<<getFormat("ppm1.ppm")<<endl;
    cout<<getElement("ppm1.ppm",1)<<endl;

    string str="44";
    cout<<""<<stoi(str)<<endl;
    cout<<""<<(getElement("image.bmp",18,4))<<endl;
    cout<<""<<(getElement("image.bmp",22,4))<<endl;

    cout<<""<<getWidth("ppm1.ppm")<<endl;
    cout<<""<<getWidth("image.bmp")<<endl;
    cout<<""<<getHight("ppm1.ppm")<<endl;
    cout<<""<<getHight("image.bmp")<<endl;

    string a;
    for (int i = 0; i < 20000; ++i) {
        a=a+"a";
    }

    if(check("ppm1.ppm",a))
        cout<<"tak"<<endl;
    if(check("image.bmp"))
        cout<<"tak"<<endl;

    //e("ppm1.ppm","text");

   // write("ppmP6.ppm","text",10);

//    bool b1[8];
//    boolconwerter('a',b1);

/*    for (int j = 0; j < size(b1); ++j) {
        cout<<b1[j]<<endl;
    }*/
    ifstream f1;
    ofstream f2;
    f1.open("test2.txt");
    f2.open("test2.txt");

    string ak;

    f1>>ak;
    f2<<"aa";

    f1>>ak;
    f2<<"aa";

    f1>>ak;
    f2<<"aa";

    f1>>ak;
    f2<<"aa";

    f2.close();
    f1.close();

    int pl = getElement("image.bmp",10,4);
    cout<<pl;

    write("ppmP6.ppm","Atext",5);

    d("ppmP6.ppm");


    if(argc==0)
        h();
    else{
        string flaga=toUpper(argv[1]);

        // java jest lepsza od C++ argument 12346/88437 switch działą na strinach
        if(flaga=="-I" or flaga=="--INFO"){
            if(argc==3)
            {
                i(argv[2]);
            }
            else goto ERROR1;
        }

        else if(flaga=="-E" or flaga=="--ENCRYPT"){
            if(argc==4)
            {
                e(argv[2],argv[3]);
                //if(advanceCheck(argv[2],argv[3]));
                // dodaj enkrypcje
            }
            else goto ERROR1;
        }

        else if(flaga=="-D" or flaga=="--DECRYPT"){
            if(argc==3){
                d(argv[2]);
            }
            else goto ERROR1;
        }

        else if(flaga=="-C" or flaga=="--CHECK"){
            if(argc==4){
                c(argv[2],argv[3]);
            }
            else goto ERROR1;
        }

        else if(flaga=="-H" or flaga=="--HELP"){
            if(argc==2)
                h();
            else goto ERROR1;
        }
        else goto ERROR2;
    }


    goto END;

/*    HELP:
    system("Color 0B");
    cout<<"";
    goto END;*/
    
    ERROR1:
    system("Color 04");
    cout<<"ERROR: Invalid amuont of aruments for given flag provided, to find out more use flag -h (with no further arguments)";
    goto END;

    ERROR2:
    system("Color 04");
    cout<<"ERROR: unknown flag provided, all flas are descibed under -h flag"<<endl;
    goto END;

    ERROR3:
    system("Color 04");
    cout<<"ERROR: file can not be proccesed"<<endl;
    goto END;



END:;
}





#include <map>
#include <string>
#pragma once
using namespace std;

map<string,string>Operatie;
map<string,int>Temp;
map<string,int>Nums;
string num1,num2;
string semn;
string input_question;

string lang="ro";
string fisier1 = "operatii_"+lang+".txt";
string fisier2 = "modify_"+lang+".txt";
string fisier3 = "logs_"+lang+".txt";
string fisier4 = "template_numere.txt";
string fisier5 = "template_cifre.txt";
string fisier6 = "numere_ro.txt";
string fisier7 = "numere_c_ro.txt";

int pos;
int corect;


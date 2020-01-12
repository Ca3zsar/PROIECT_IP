#include <string>
#include <fstream>
#include <map>
#include "global_variables.h"
#pragma once
using namespace std;

//In cazul in care unele cuvinte contin o litera mare vor fi aduse la lowercase pentru
// a se potrivi cu "dictionarul"
string lower_string(string word)
{
    for_each(word.begin(),word.end(), [](char &c){
        c = tolower(c);
    });
    return word;
}

void log_print(int wrong, string Question,string answer)
{
    ofstream fout(fisier3,ios::app);

    fout<<Question<<'\n';
    if(wrong==1)
    {
        fout<<">>Input invalid\n";
        answer_to_the_question="Input invalid";
    }else{
        fout<<">>"<<answer<<'\n'; 
        answer_to_the_question=answer;
    }
}


// Simulate a dictionary, where each word has a sign attributed
void MapTheFiles()
{
    Operatie.clear();
    Temp.clear();
    Nums.clear();

    ifstream f1(fisier1);
    ifstream f2(fisier2);

    string cuvant,simbol;
    int num;

    while(getline(f1,cuvant) && getline(f2,simbol))
    {
        Operatie[cuvant]=simbol;
    }

    f1.close();
    f2.close();

    f1.open(fisier4);
    f2.open(fisier5);

    while(getline(f1,cuvant) && f2>>num)
    {
        Temp[cuvant]=num;
    }

    f1.close();
    f2.close();

    f1.open(fisier6);
    f2.open(fisier7);

    while(getline(f1,cuvant) && f2>>num)
    {
        Nums[cuvant]=num;
    }

    f1.close();
    f2.close();

}

bool word_in_file(string word,string f)
{
    ifstream reader(f);
    string temp;
    while(getline(reader,temp))
    {
        if(temp==word)return true;
    }
    reader.close();
    return false;
}

bool is_symbol(string word)
{
    string simboluri = "+-*/%^()";
    if(simboluri.find(word)!=string::npos)return true;
    else return false;
}

bool is_word(string word)
{
    int size_of_word = word.size();
    for(int i=0;i<size_of_word;i++)
    {
        if(!(word[i]>='a' && word[i]<='z'))return false;
    }
    return true;
}

bool is_number(string word)
{
    int size_of_word = word.size();
    for(int i=0;i<size_of_word;i++)
    {
        if(!(word[i]>='0' && word[i]<='9'))return false;
    }
    return true;
}

/*Takes the input from the button in the menu and changes the text files
according to the language chosen by the user. From now on the expression must be
written in the chosen language or otwherwise it will be considered invalid*/
void choose_language(string ln)
{
    fisier1 = "operatii_"+ln+".txt";
    fisier2 = "modify_"+ln+".txt";
    fisier3 = "logs_"+ln+".txt";
    MapTheFiles();
}

vector<string> read_questions()
{
    ifstream r(fisier3);
    vector<string>aux;
    string temp;
    aux.clear();
    while(getline(r,temp))
    {
        if(temp[0]=='>')continue;
        else{
            aux.push_back(temp);
        }
    }
    return aux;
}

vector<string> read_answers()
{
    ifstream r(fisier3);
    vector<string>aux;
    string temp;
    aux.clear();
    while(getline(r,temp))
    {
        if(temp[0]!='>')continue;
        else{
            aux.push_back(temp);
        }
    }
    return aux;
}

void clear_the_file()
{
    remove("logs_ro.txt");
    ofstream f("logs_ro.txt");
    point=0;
}
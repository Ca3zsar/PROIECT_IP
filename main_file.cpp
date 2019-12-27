#include <iostream> //Basic input/output operation from the console
#include <fstream> //Input from the files
#include <string> //Used for keeping expression as text and to use the operation included in the string library
#include <vector> //Used for keeping expression after breaking text into words
#include <sstream> //Included for stringstream
#include <map> //Used for creating a "dictionary"
#include <algorithm> //For importing for_each
#include "convertor.h"
#include "convertor2.h"
using namespace std;

// Authors: Dobrovici Cristian && Todirisca Cezar
// Start_Date: 6th of December 2019
// Name of the project: Natural language calculator
// Reads a question, for example : "What is the result of the multiplication of x and y?"
// and gives back the answer written with letters
// Uses three auxiliar files for the template numbers. This way the template would not interfere with the code
// Uses 3 modes: Romanian, English or French. The default mode will be Romanian with the posibilty of chaning it afterwards

long long evaluate(string),term(string),factor(string); //The functions used for the evaluation of the expression
void TakeTheInput();

map<string,string>Operatie;

string lang="ro";
string fisier1 = "operatii_"+lang+".txt";
string fisier2 = "modify_"+lang+".txt";
string fisier3 = "logs_"+lang+".txt";
string fisier4 = "template_numere.txt";
string fisier5 = "numere_ro.txt";

int cont;
int count_si,count_dintre;
int corect=1;
string input_question;

// Simulate a dictionary, where each word has a sign attributed
void MapTheFiles()
{
    ifstream f1(fisier1);
    ifstream f2(fisier2);

    string cuvant,semn;
    int num;

    while(getline(f1,cuvant) && getline(f2,semn))
    {
        Operatie[cuvant]=semn;
    }

    f1.close();
    f2.close();
}

void log_print(int wrong, string Question,string answer)
{
    ofstream fout(fisier3,ios::app);

    fout<<Question<<'\n';
    if(wrong==1)
    {
        fout<<">> Input invalid\n";
    }else{
        fout<<">>"<<answer<<'\n'; 
    }
}

/*Splits the expression into word by considering the separator to be the space
It uses the stringstream to break the string into smaller pieces*/
vector<string> split_expression(string expression) 
{
    vector<string>list_of_words;
    if(expression.back()=='?')
        expression.pop_back();
    stringstream splitter(expression);
    
    string word;

    int size_of_word;

    while(splitter >> word)
    {
        size_of_word = word.size();
        if((word[0]>='a' && word[0]<='z') || (word[0]>='A' && word[0]<='Z'))
            list_of_words.push_back(word);
        else{

            string temp_word;
            temp_word.clear();

            for(int i=0;i<size_of_word;i++)
            {
                if((word[i]>='0' && word[i]<='9'))
                {
                    temp_word=temp_word+word[i];
                }else{
                    if(word[i]=='+' || word[i]=='-' || word[i]=='/' || word[i]=='*')
                    {
                        if(temp_word!=" " && !temp_word.empty())list_of_words.push_back(temp_word);
                        temp_word.clear();
                        temp_word=temp_word+word[i];
                        list_of_words.push_back(temp_word);
                        temp_word.clear();
                    }else{
                        log_print(1,input_question,"");
                        TakeTheInput();
                    }
                }
            }
            if(!temp_word.empty() && temp_word!=" ")
            {
                list_of_words.push_back(temp_word);
            }
        }
    }

    return list_of_words;
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

string form_number(vector<string> list_of_words, int k)
{
    int size_of_list = list_of_words.size();
    int number=0;
    int temp=0;
    while(k<size_of_list)
    {
        if(list_of_words[k] == "si")
        {
            count_si++;
            k++;
            continue;
        }
        if(word_in_file(list_of_words[k],fisier4))
        {
            
        }
    }
}

/*Select the correct words from the previous processed list
by searching in the text files for every possible variation of the words.
It mainly looks for the operations and for the possible numbers using the 
template from the text file*/
vector<string> select_correct_words(vector<string> list_of_words)
{
    vector<string>correct_words;
    int size_of_list = list_of_words.size();
    string word, temp;
    string simboluri = "()+-*/%";

    corect = 1;

    //In cazul in care unele cuvinte contin o litera mare vor fi aduse la lowercase pentru
    // a se potrivi cu "dictionarul"
    for(int i=0; i<size_of_list; i++)
    {
        word = list_of_words[i];
        for_each(word.begin(),word.end(), [](char &c){
            c = tolower(c);
        });
        list_of_words[i]=word;
    }

    if(list_of_words[0]=="cat")
    {
        list_of_words.erase(list_of_words.begin());
    }

    for(int i=0; i<size_of_list && corect; i++)
    {
        word = list_of_words[i];
        if(word.size()==1)
        {
            if(simboluri.find(word) != string::npos)
            {
                correct_words.push_back(word);
            }
            else{
                if(isdigit(word[0]))
                {
                    correct_words.push_back(word);
                }
            }
        }else{
            if(is_word(word))
            {
                if(word_in_file(word,fisier1))
                {
                    correct_words.push_back(Operatie[word]);
                }else{
                    if(word_in_file(word,fisier4))
                    {
                        temp=form_number(list_of_words,i);
                    }
                }
            }else{
                if(is_number(word))
                {
                    correct_words.push_back(word);
                }else{
                    log_print(1,input_question,"");
                    corect=0;
                }
            }
        }
    }

    return correct_words;
}

/*Checks if the final expression is valid before converting it to
the normal form*/
bool check_if_valid(vector<string>expression)
{
    return true;
}

/*Transforms the operations from the list of correct word into the analog 
symbol and the numbers from words to their decimal representations*/
string convert_to_math(vector<string> expression)
{
    string math_expression;
    return math_expression;
}

string convert_to_expression(long long number)
{
    string final_number;

    return final_number;
}


long long evaluate(string exp)
{
    long long res = term(exp);
    while(exp[cont]=='+' || exp[cont]=='-')
    {
        if(exp[cont]=='+')
        {
            cont++;
            res+=term(exp);
        }else{
            cont++;
            res=res-term(exp);         
        }
    }
    return res;
}

long long term(string exp)
{
    long long res = factor(exp);
    while(exp[cont]=='*' || exp[cont]=='/' || exp[cont]=='%')
    {
        if(exp[cont]=='*')
        {
            cont++;
            res=res*factor(exp);
        }else{
            if(exp[cont]=='/')
            {
                cont++;
                res=res/factor(exp);
            }else{
                cont++;
                res=res%factor(exp);
            }
        }
    }
    return res;
}

long long factor(string exp)
{
    long long res=0;
    if(exp[cont]=='(')
    {
        cont++;
        res = evaluate(exp);
        cont++;
    }else{
        while(exp[cont]>='0' && exp[cont]<='9')
        {
            res=res*10+exp[cont]-'0';
            cont++;
        }
    }
    return res;
}

long long unsigned get_result_of_expression(string math_expression)
{
    long long unsigned result;
    cont = 0;
    result = evaluate(math_expression);
    return result;
}

/*Takes the input from the button in the menu and changes the text files
according to the language chosen by the user. From now on the expression must be
written in the chosen language or otwherwise it will be considered invalid*/
void choose_language(int choice)
{
    if(choice==1)lang="ro";
    if(choice==2)lang="en";
    if(choice==3)lang="fr";
    fisier1 = "operatii_"+lang+".txt";
    fisier2 = "modify_"+lang+".txt";
    fisier3 = "logs_"+lang+".txt";
}

void TakeTheInput()
{
    vector<string>list_of_words;
    vector<string>correct_words;
    string math_exp;
    string final_result;
    corect=1;
    count_dintre=count_si=0;
    getline(cin,input_question);
    list_of_words = split_expression(input_question);
    correct_words = select_correct_words(list_of_words);
    if(corect==0)return;
    if(!check_if_valid(correct_words))
    {
        log_print(1,input_question,"");
    }
    
    math_exp = convert_to_math(correct_words);
    
    long long result = get_result_of_expression(math_exp);
    final_result = convert_to_expression(result);
    log_print(0,input_question,final_result);
}

int main()
{
    MapTheFiles();
    while(true)
    {
        TakeTheInput();
    }
    return 0;
}
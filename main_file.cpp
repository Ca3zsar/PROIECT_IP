#include <iostream> //Basic input/output operation from the console
#include <fstream> //Input from the files
#include <string> //Used for keeping expression as text and to use the operation included in the string library
#include <vector> //Used for keeping expression after breaking text into words
#include <sstream> //Included for stringstream
#include <map> //Used for creating a "dictionary"
#include <algorithm> //For importing for_each
using namespace std;

// Authors: Dobrovici Cristian && Todirisca Cezar
// Start_Date: 6th of December 2019
// Name of the project: Natural language calculator
// Reads a question, for example : "What is the result of the multiplication of x and y?"
// and gives back the answer written with letters
// Uses three auxiliar files for the template numbers. This way the template would not interfere with the code
// Uses 3 modes: Romanian, English or French. The default mode will be Romanian with the posibilty of chaning it afterwards

long long evaluate(),term(),factor(); //The functions used for the evaluation of the expression

map<string,string>Operatie;
map<string,int>Numar;
string lang="ro";
string fisier1 = "operatii_"+lang+".txt";
string fisier2 = "modify_"+lang+".txt";
string fisier3 = "logs_"+lang+".txt";
string fisier4 = "template_numere.txt";
string fisier5 = "template_cifre.txt";

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

    ifstream f1(fisier4);
    ifstream f2(fisier5);

    while(getline(f1,cuvant) && f2>>num)
    {
        Numar[cuvant]=num;
    }

    f1.close();
    f2.close();
}

void log_print(int wrong = 0, string Question,string answer)
{
    ofstream fout(fisier3);
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
                    if(temp_word!=" " && !temp_word.empty())list_of_words.push_back(temp_word);
                    temp_word.clear();
                    temp_word=temp_word+word[i];
                    list_of_words.push_back(temp_word);
                    temp_word.clear();
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

bool word_in_file(string word)
{
    ifstream reader(fisier1);
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

/*Select the correct words from the previous processed list
by searching in the text files for every possible variation of the words.
It mainly looks for the operations and for the possible numbers using the 
template from the text file*/
vector<string> select_correct_words(vector<string> list_of_words)
{
    vector<string>correct_words;
    int size_of_list = list_of_words.size();
    string word;
    string simboluri = "()+-*/%";

    bool apare_dintre = (find(list_of_words.begin(),list_of_words.end(),"dintre")!=list_of_words.end());
    //We need this to check for the"si" between the numbers

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

    for(int i=0; i<size_of_list; i++)
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
                if(word_in_file(word))
                {
                    correct_words.push_back(Operatie[word]);
                }else{

                }
            }else{
                if(is_number(word))
                {
                    correct_words.push_back(word);
                }else{
                    log_print(1,input_question,"");
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

}

/*Transforms the operations from the list of correct word into the analog 
symbol and the numbers from words to their decimal representations*/
string convert_to_math(vector<string> expression)
{
    string math_expression;
    return math_expression;
}

long long evaluate()
{

}

long long term()
{

}

long long factor()
{

}

long long unsigned get_result_of_expression(string math_expression)
{
    long long unsigned result;
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

int main()
{
    MapTheFiles();
    return 0;
}

#include <iostream> //Basic input/output operation from the console
#include <fstream> //Input from the files
#include <string> //Used for keeping expression as text and to use the operation included in the string library
#include <vector> //Used for keeping expression after breaking text into words
#include <sstream> //Included for stringstream
#include <map> //Used for creating a "dictionary"
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

void MapTheOperations()
{
    ifstream f1("operatii_ro.txt");
    ifstream f2("modify_ro.txt");

    string cuvant,semn;

    while(getline(f1,cuvant) && getline(f2,semn))
    {
        Operatie[cuvant]=semn;
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
    cout<<list_of_words.size()<<'\n';
    for(auto vec:list_of_words)
    {
        cout<<vec<<'\n';
    }
    return list_of_words;
}

/*Select the correct words from the previous processed list
by searching in the text files for every possible variation of the words.
It mainly looks for the operations and for the possible numbers using the 
template from the text file*/
vector<string> select_correct_words(vector<string> list_of_words)
{
    vector<string>correct_words;
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
void choose_language()
{

}

int main()
{
    MapTheOperations();
    string Expression;
    getline(cin,Expression);
    split_expression(Expression);
    return 0;
}
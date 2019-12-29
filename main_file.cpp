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

int evaluate(string),term(string),factor(string); //The functions used for the evaluation of the expression
void TakeTheInput();

map<string,string>Operatie;
map<string,int>Temp;
map<string,int>Nums;
string num1,num2;

string lang="ro";
string fisier1 = "operatii_"+lang+".txt";
string fisier2 = "modify_"+lang+".txt";
string fisier3 = "logs_"+lang+".txt";
string fisier4 = "template_numere.txt";
string fisier5 = "template_cifre.txt";
string fisier6 = "numere_ro.txt";
string fisier7 = "numere_c_ro.txt";

int cont,pos;
int corect=1;
string input_question;
string semn;
vector<string>nums;

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

/*Splits the expression into words by considering the separator to be the space
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
                    if(word[i]=='+' || word[i]=='-' || word[i]=='/' || word[i]=='*' || word[i]=='%')
                    {
                        if(temp_word!=" " && !temp_word.empty())list_of_words.push_back(temp_word);
                        temp_word.clear();
                        semn=word[i];
                        temp_word=temp_word+word[i];
                        list_of_words.push_back(temp_word);
                        temp_word.clear();
                    }else{
                        log_print(1,input_question,"");
                        corect=0;
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
                semn=word;
            }
            else{
                if(isdigit(word[0]) || word[0]=='o')
                {
                    correct_words.push_back(word);
                }else{
                    if(!isalpha(word[0])){
                        log_print(1,input_question,"");
                        corect=0;
                    }
                }
            }
        }else{
            if(is_word(word))
            {
                if(word_in_file(word,fisier1))
                {
                    correct_words.push_back(Operatie[word]);
                    if(semn != "%")semn=Operatie[word];
                }else{
                    if(word_in_file(word,fisier4) || word_in_file(word,fisier6) || word=="si" || word=="lui" || word=="cu" || word=="la")
                    {
                        correct_words.push_back(word);
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
    string simboluri = "()+-*/%";
    if(semn=="")return false;
    int w_count=0;
    int size_of_list=expression.size();
    for(int i=0;i<size_of_list && w_count<=1;i++)
    {
        if(expression[i]=="si")
        {
            if(i==0 || expression[i-1]=="si")return false;
            if(i>=1 && is_number(expression[i-1]))
            {
                w_count++;
                if(pos==-1)pos=i;
                else return false;
                
            }else{
                if(word_in_file(expression[i-1],fisier6) && Nums[expression[i-1]]<20)
                {
                    w_count++;
                    if(pos==-1)pos=i;
                else return false;
                }else{
                    if(word_in_file(expression[i-1],fisier4))
                    {
                        w_count++;
                        if(pos==-1)pos=i;
                        else return false;
                    }
                }
            }
        }
        if(i>=1 && expression[i-1]==expression[i])return false;
        if(pos!=-1)
        {
            if(expression[i]=="cu" || expression[i]=="la" || expression[i]=="lui")return false;
        }else{
            if(expression[i]=="cu")pos=i;
        }
        if(i>=1)
        {
            if(simboluri.find(expression[i]) != string::npos){
                if(pos==-1)pos=i;
                else {
                    if(semn=="%" && pos==0 && i==1){
                        expression.erase(expression.begin()+i);
                        i--;
                    }else return false;
                }
            }
        }
    }
    if(w_count>1)return false;
    return true;
}

/*Transforms the operations from the list of correct word into the analog 
symbol and the numbers from words to their decimal representations*/
string convert_to_math(vector<string> expression)
{

    string math_expression="";
    string simboluri = "()+-*/%";
    if(simboluri.find(expression[0]) != string::npos && pos!=-1)
    {
        swap(expression[pos],expression[0]);
        expression.erase(expression.begin());
    }
    vector<string>::iterator it;
    vector<string>::iterator it2;
    it=find(expression.begin(),expression.end(),"lui");
    cout<<semn<<'\n';
    if(it!=expression.end())
    {
        if((semn=="/" || semn=="%" ))
        {
            
            it2=find(expression.begin(),expression.end(),"la");
            if(it2!=expression.end())
            {
                if(it<it2)
                {
                    if(is_number(*(it+1)))
                    {
                        math_expression = math_expression + *(it+1);
                    }else{
                        string temp="";
                        ++it;
                        for(;it<it2;it++)
                        {
                            temp=temp+*it;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                    math_expression = math_expression + semn;
                    if(is_number(*(it2+1)))
                    {
                        math_expression = math_expression + *(it2+1);
                    }else{
                        string temp="";
                        ++it2;
                        for(;it2<expression.end();it2++)
                        {
                            temp=temp+*it2;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                }else{
                    
                }
            }
        }else{
            if(semn=="-")
            {
                it2=find(expression.begin(),expression.end(),"din");
            }else{
                
            }
        }
    }
    return math_expression;
}

int evaluate(string exp)
{
    int res = term(exp);
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

int term(string exp)
{
    int res = factor(exp);
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

int factor(string exp)
{
    int res=0;
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

int get_result_of_expression(string math_expression)
{
    int result;
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
    pos=-1;
    semn="";
    getline(cin,input_question);
    list_of_words = split_expression(input_question);
    if(corect==0)return;
    correct_words = select_correct_words(list_of_words);
    if(corect==0)return;

    for(auto vec:correct_words)
    {
        cout<<vec<<' ';
    }
    cout<<'\n';

    if(!check_if_valid(correct_words))
    {
        log_print(1,input_question,"");
        return;
    }
    

    math_exp = convert_to_math(correct_words);
    cout<<math_exp<<'\n';
    int result = get_result_of_expression(math_exp);
    final_result = NumToWord(result);
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
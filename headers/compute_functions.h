#include <string>
#include <vector>
#include <algorithm>
#include "aux_functions.h"
#include "convertor.h"
#include "convertor2.h"
#include "global_variables.h"
using namespace std;

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
                    if(word[i]=='+' || word[i]=='-' || word[i]=='/' || word[i]=='*' || word[i]=='%'|| word[i]=='^')
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

/*
Select the correct words from the previous processed list
by searching in the text files for every possible variation of the words.
It mainly looks for the operations and for the possible numbers using the 
template from the text file
*/
vector<string> select_correct_words(vector<string> list_of_words)
{
    vector<string>correct_words;
    int size_of_list = list_of_words.size();
    string word, temp;
    corect = 1;

    for(int i=0;i<size_of_list;i++)
    {
        list_of_words[i]=lower_string(list_of_words[i]);
    }

    if(list_of_words[0]=="cat")
    {
        list_of_words.erase(list_of_words.begin());
    }
    for(int i=0; i<size_of_list && corect; i++)
    {
        word = list_of_words[i];
        if(word=="de")correct_words.push_back("de");
        if(word=="din" && semn=="-")correct_words.push_back("din");
        if(word.size()==1)
        {
            if(is_symbol(word))
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
                    if(semn != "%"){
                        correct_words.push_back(Operatie[word]);
                        semn=Operatie[word];
                    }
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
    if(semn.empty())return false;
    int w_count=0;
    vector<string>::iterator it = find(expression.begin(),expression.end(),"lui");
    if(it==expression.end())
    {
        vector<string>::iterator it2;
        it2 = find(expression.begin(),expression.end(),"la");
        if(it2!=expression.end())expression.erase(it2);

        it2 = find(expression.begin(),expression.end(),"cu");
        if(it2!=expression.end())expression.erase(it2);
    }
    int size_of_list=expression.size();
    for(int i=0;i<size_of_list && w_count<=1;i++)
    {
        if(expression[i]=="si")
        {
            if(i==0)return false;
            if(i>=1){
                if(is_number(expression[i-1]))
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
                        }else{
                            if(i<size_of_list-1)
                            {
                                if(Nums[expression[i+1]]>=10)
                                {
                                    w_count++;
                                    if(pos==-1)pos=i;
                                    else return false;
                                }else{
                                    if(is_number(expression[i+1]))
                                    {
                                        w_count++;
                                        if(pos==-1)pos=i;
                                        else return false;
                                    }else{
                                        if(size_of_list-i>2)
                                        {
                                            if(word_in_file(expression[i+1],fisier4))
                                            {
                                                if(word_in_file(expression[i+2],fisier4))
                                                {
                                                    w_count++;
                                                    if(pos==-1)pos=i;
                                                    else return false;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(i>=1 && expression[i-1]==expression[i])return false;
        if(pos!=-1)
        {
            if(expression[i]=="cu" || expression[i]=="la" || expression[i]=="lui")return false;
        }else{
            //if(expression[i]=="cu")pos=i;
        }
        if(i>=1)
        {
            if(is_symbol(expression[i])){
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
    if(is_symbol(expression[0]) && pos!=-1)
    {
        swap(expression[pos],expression[0]);
        expression.erase(expression.begin());
        pos--;
    }
    vector<string>::iterator it=expression.begin();
    vector<string>::iterator it2;
    int c=0;
    while(it!=expression.end())
    {
        if(*it=="de")
        {
            it=expression.erase(it);
            if(c<pos)pos--;
        }
        else it++;
        c++;
    }
    int size_of_list = expression.size();
    it=find(expression.begin(),expression.end(),"lui");
    if((semn=="/" || semn=="%" ))
    {
    
        if(it!=expression.end()){
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
                            temp=temp+' '+*it;
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
                            temp=temp+' '+*it2;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                }else{
                    if(is_number(*(it+1))){
                        math_expression=math_expression+*(it+1);
                    }else{
                        string temp="";
                        ++it;
                        for(;it<expression.end();it++)
                        {
                            temp=temp+' '+*it;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }
                    math_expression=math_expression+ semn;
                    if(is_number(*(it2+1)))
                    {
                        math_expression=math_expression+ *(it2+1);
                    }else{
                        string temp="";
                        ++it2;
                        for(;it2<it-1;it2++)
                        {
                            temp=temp+' '+*it2;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }
                }
            }
        }
    }
    if(semn=="+")
    {
        if(it!=expression.end()){
            it2=find(expression.begin(),expression.end(),"cu");
            if(is_number(*(it+1)))
            {
                math_expression = math_expression + *(it+1);
            }else{
                string temp="";
                ++it;
                for(;it<it2;it++)
                {
                    temp=temp+' '+*it;
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
                    temp=temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
        }else{
            vector<string>::iterator it2=expression.begin();
            if(is_number(*it2))
            {
                math_expression = math_expression+*it2;
            }else{
                string temp="";
                for(;*it2!=expression[pos];it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
            math_expression = math_expression + semn;
            it2=find(expression.begin(),expression.end(),semn)+1;
            if(is_number(*it2))
            {
                math_expression= math_expression+*it2;
            }else{
                string temp="";
                for(;it2!=expression.end();it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
        }
    }
    if(semn=="*")
    {
        if(it!=expression.end())
        {
            it2=find(expression.begin(),expression.end(),"cu");
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
                            temp=temp+' '+*it;
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
                            temp=temp+' '+*it2;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                }else{
                    if(is_number(*(it+1))){
                        math_expression=math_expression+*(it+1);
                    }else{
                        string temp="";
                        ++it;
                        for(;it<expression.end();it++)
                        {
                            temp=temp+' '+*it;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }
                    math_expression=math_expression+ semn;
                    if(is_number(*(it2+1)))
                    {
                        math_expression=math_expression+ *(it2+1);
                    }else{
                        string temp="";
                        ++it2;
                        for(;it2<it-1;it2++)
                        {
                            temp=temp+' '+*it2;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }
                }
            }
        }else{
            it2=find(expression.begin(),expression.end(),"cu");
            if(it2!=expression.end())expression.erase(it2);
            it2=expression.begin();
            if(is_number(*it2))
            {
                math_expression = math_expression+*it2;
            }else{
                string temp="";
                for(;*it2!=expression[pos];it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
            math_expression = math_expression + semn;
            it2=find(expression.begin(),expression.end(),semn)+1;
            if(is_number(*it2))
            {
                math_expression= math_expression+*it2;
            }else{
                string temp="";
                for(;it2!=expression.end();it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
        }
    }
    if(semn=="-")
    {
        if(it!=expression.end())
        {
            it2=find(expression.begin(),expression.end(),"din");
            if(it2!=expression.end())
            {
                if(it>it2)
                {
                     if(is_number(*(it2+1)))
                    {
                        math_expression = math_expression + *(it2+1);
                    }else{
                        string temp="";
                        ++it2;
                        for(;it2<it;it2++)
                        {
                            temp=temp+' '+*it2;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                   math_expression = math_expression + semn;

                    if(is_number(*(it+1)))
                    {
                        math_expression = math_expression + *(it+1);
                    }else{
                        string temp="";
                        ++it;
                        for(;it<expression.end();it++)
                        {
                            temp=temp+' '+*it;
                        }
                        math_expression = math_expression + to_string(WordsToNumbers(temp));
                    }
                }else{
                    if(is_number(*(it2+1)))
                    {
                        math_expression=math_expression+ *(it2+1);
                    }else{
                        string temp="";
                        ++it2;
                        for(;it2<expression.end();it2++)
                        {
                            temp=temp+' '+*it2;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }
                    math_expression=math_expression+ semn;
                    if(is_number(*(it+1))){
                        math_expression=math_expression+*(it+1);
                    }else{
                        string temp="";
                        ++it;
                        it2=find(expression.begin(),expression.end(),"din");
                        for(;it<it2;it++)
                        {
                            temp=temp+' '+*it;
                        }
                        math_expression=math_expression+to_string(WordsToNumbers(temp));
                    }                    
                }
            }
        }
        else{
            vector<string>::iterator it2=expression.begin();
            if(is_number(*it2))
            {
                math_expression = math_expression+*it2;
            }else{
                string temp="";
                for(;*it2!=expression[pos];it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
            math_expression = math_expression + semn;
            it2=find(expression.begin(),expression.end(),semn)+1;
            if(is_number(*it2))
            {
                math_expression= math_expression+*it2;
            }else{
                string temp="";
                for(;it2!=expression.end();it2++)
                {
                    temp = temp+' '+*it2;
                }
                math_expression = math_expression + to_string(WordsToNumbers(temp));
            }
        }
    }
    if(semn=="^")
    {
        if(it!=expression.end())
        {
            expression.erase(it);
            it2=find(expression.begin(),expression.end(),"la");
            if(it2!=expression.end())expression.erase(it2);
        }
        it2=expression.begin();
        if(is_number(*it2)){
            math_expression = math_expression + *(it2);
        }else{
            string temp="";
            for(;*it2!=semn;it2++)
            {
                temp = temp+' '+*it2;
            }
            math_expression = math_expression + to_string(WordsToNumbers(temp));
        }
        math_expression = math_expression + semn;
        it2=find(expression.begin(),expression.end(),semn)+1;
        if(is_number(*it2))
        {
            math_expression= math_expression+*it2;
        }else{
            string temp="";
            for(;it2!=expression.end();it2++)
            {
                temp = temp+' '+*it2;
            }
            math_expression = math_expression + to_string(WordsToNumbers(temp));
        }
    }
    return math_expression;
}
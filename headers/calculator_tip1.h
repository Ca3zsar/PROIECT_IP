#include <string>
#include <sstream>
#include "convertor.h"
#include "convertor2.h"
#include "aux_functions.h"
using namespace std;

string get_to_right_form(string expression)
{
    string temp="",w;
    string::iterator it;
    expression = lower_string(expression);
    it = expression.begin();
    for(;it<expression.end()-1;it++)
    {
        if(*it>='a' && *it<='z')
        {
            w=*(it+1);
            if(is_symbol(w))
            {
                temp=temp+*it+' '+w + ' ';
            }else temp=temp+ *it;
        }else{
            if(*it>='0' && *it<='9')
            {
                 w=*(it+1);
                if(is_symbol(w))
                {
                    temp=temp+*it+' ' + w + ' ';
                }else temp=temp+ *it;
            }else{
                w=*it;
                if(is_symbol(w))
                {
                    if( w!="(" && w!=")" ){
                        if(*(it-1)==' ')temp = temp + *it;
                        w=*(it+1);
                        if(w=="(")
                        {
                            if(temp.back()!=' ')temp = temp + ' ';
                            temp = temp + w + ' ';
                        }
                    }else{
                        if(*(it-1)==' ')temp = temp + *it + ' ';
                    }
                }else{
                    if(w==" ")temp = temp + " ";
                }
            }
        }
    }
    w=*it;
    if(!is_symbol(w))temp = temp + *it;
    return temp;
}

string compute(string expression)
{
    expression = get_to_right_form(expression);
    string math_exp="",word,temp;
    vector<string>list_of_words;
    stringstream splitter(expression);
    while(splitter>>word)
    {
        list_of_words.push_back(word);
    }
    for(auto vec:list_of_words)cout<<vec<<' ';
    cout<<'\n';
    vector<string>::iterator it=list_of_words.begin();
    for(;it<list_of_words.end();it++){
        if(!is_symbol(*it)){
            if(it!=list_of_words.begin())
            {
                if(*it=="0" || *it=="zero")
                {
                    if(*(it-1)=="/")
                    {
                        log_print(0,input_question,"Input invalid. Impartire la 0");
                        corect=0;
                    }
                }
            }
            if(is_number(*it))math_exp = math_exp + *it;
            else if(is_word(*it))temp = temp + *it + ' ';
                else {
                    log_print(1,input_question,"");
                    return "";
                }
        }else{
            if(temp!="")math_exp = math_exp + to_string(WordsToNumbers(temp)) + ' ';
            math_exp = math_exp + *it;
            temp = "";
        }
    }
    if(temp!="")math_exp = math_exp + to_string(WordsToNumbers(temp));
    if(corect==1)return math_exp;
}
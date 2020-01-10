#include <vector>
#include <string>
#include <algorithm>
#pragma once
using namespace std;

string NumToWord(int input)
{
    vector<string> singles = {"","unu","doi","trei","patru","cinci","sase","sapte","opt","noua"};
    vector<string> temps = {"", "o", "doua","trei","patru","cinci","sase","sapte","opt","noua"};
    vector<string> teens = {"zece","unsprezece","doisprezece","treisprezece","paisprezece","cincisprezece","saisprezece","saptesprezece","optsprezece","nouasprezece"};
    vector<string> tens = {"","","douazeci","treizeci","patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci"};

    string word = "";
    
    if(input==0){
        return "zero";
    }
    
    string exp = to_string(input);
    reverse(exp.begin(),exp.end());

    bool v,v2,v3; // v is for every third digit of group, v2 for second and v3 for the third, from left to right in the original number
    
    //Form multiple of 3 groups
    if(exp.size()%3==1)exp=exp+"00";
    else{
        if(exp.size()%3==2)exp=exp+"0";
    }
    int grup = (exp.size()-1)/3;
    for(int i=grup;i>=0;i--)
    {
        v=v2=v3=false;

        if(exp[i*3+2]!='0')
        {
            v=true;
            if(exp[i*3+2]=='1')
            {
                word=word+ "o suta ";
            }else{
                word = word+temps[exp[3*i+2]-'0'] + " sute ";
            }
        }

        if(exp[i*3+1]!='0')
        {
            v2=true;
            if(exp[i*3+1]=='1')
            {
                word = word + teens[exp[i*3]-'0'] + ' ';
            }else{
                word = word + tens[exp[i*3+1]-'0'] + ' ';
                if(exp[i*3]!='0')
                {
                    word = word + "si ";
                    if(exp[i*3]=='2' && i>0)word=word + "doua ";
                    else{
                        word = word + singles[exp[i*3]-'0'] + ' ';
                    }
                    
                }
            }
        }

        if(!v2)
        {
            if(exp[i*3]!='0')
            {
                v3=true;
                if(v)
                {
                    if(i>0)
                    {
                        if(exp[i*3]-'0'==2)
                        {
                            word=word+ "doua ";
                        }else word = word + singles[exp[i*3]-'0'] + ' ';
                    }else{
                    word = word +singles[exp[i*3]-'0'] + ' ';
                    }
                }
                else{
                    if(exp[i*3]-'0'==2){
                        if(i==0)word=word+"doi ";
                        else word=word+"doua ";
                    }
                    else{
                        if(exp[i*3]-'0'==1)
                        {
                            if(i==2)word = word + "un ";
                            else if(i==1) word= word + "o ";
                            else if(i==0) word = word+ "unu ";
                        }
                        else word = word + singles[exp[i*3]-'0'] + ' ';
                    }
                }
            }
        }

        if(i>0)
        {
            if(v || v2 || v3){
                if(((exp[i*3+1]-'0')*10+(exp[i*3]-'0')>=20 || (exp[i*3+1]-'0')*10+(exp[i*3]-'0')==0))
                {
                    word = word + "de ";
                }
                if(i==2){
                    if(!v && !v2 && exp[i*3]=='1')word = word + "milion ";
                    else word=word+"milioane ";
                }else{
                    if(!v && !v2 && exp[i*3]=='1')word = word + "mie ";
                    else word = word +"mii ";
                }
            }
        }
    }
    return word;
}

#include <bits/stdc++.h>

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
    bool v,v2;
    string exp = to_string(input);
    int grup = (exp.size()-1)/3;
    string rev = exp;
    reverse(rev.begin(),rev.end());
    if(exp.size()%3==1)rev=rev+"00";
    else{
        if(exp.size()%3==2)rev=rev+"0";
    }
    for(int i=grup;i>=0;i--)
    {
        v=v2=false;
        if(rev[i*3+2]!='0')
        {
            v=true;
            if(rev[i*3+2]=='1')
            {
                word=word+ " o suta";
            }else{
                word = word+ ' ' +temps[rev[3*i+2]-'0'] + " sute";
            }
        }
        if(rev[i*3+1]!='0')
        {
            v2=true;
            if(rev[i*3+1]=='1')
            {
                word = word + ' '+teens[rev[i*3]-'0'];
            }else{
                word = word + ' '+tens[rev[i*3+1]-'0'];
                if(rev[i*3]!='0')
                {
                    word = word + " si";
                    if(rev[i*3]=='2' && i>0)word=word + " doua";
                    else{
                        word = word + ' ' + singles[rev[i*3]-'0'];
                    }
                    
                }
            }
        }
        if(!v2)
        {
            if(rev[i*3]!='0')
            {
                if(v)word = word + ' ' + singles[rev[i*3]-'0'];
                else{
                    if(i==2)word = word + " un";
                    else if(i==1) word= word + " o";
                }
            }
        }
        if(i>0)
        {
            if(v && ((rev[i*3+1]-'0')*10+(rev[i*3]-'0')>=20 || (rev[i*3+1]-'0')*10+(rev[i*3]-'0')==0))
            {
                word = word + " de";
            }
            if(i==2){
                if(!v && !v2 && rev[i*3]=='1')word = word + " milion";
                else word=word+" milioane";
            }else{
                if(!v && !v2 && rev[i*3]=='1')word = word + " mie";
                else word = word +" mii";
            }
        }
    }
    cout<<rev<<'\n';
    return word;
}

int main(){
    string expression;
    int input;
    cin>>input;
    cout<<NumToWord(input);
}

//7.123.412
//214.321.700


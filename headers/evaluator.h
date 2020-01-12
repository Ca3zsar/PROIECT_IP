#include <string>

using namespace std;

int evaluate(string),term(string),factor(string); //The functions used for the evaluation of the expression
int cont;

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
            if(exp[cont]=='-'){
                cont++;
                res=res-term(exp); 
            }else{
            while(exp[cont]==' ')cont++;
            }     
        }
    }
    return res;
}

int term(string exp)
{
    int res = factor(exp);
    while(exp[cont]=='*' || exp[cont]=='/' || exp[cont]=='%' || exp[cont]=='^')
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
                if(exp[cont]=='%'){
                    cont++;
                    res=res%factor(exp);
                }else{
                    if(exp[cont]=='^'){
                        cont++;
                        int x=factor(exp);
                        int temp=1;
                        while(x)
                        {
                            temp=temp*res;
                            x--;
                        }
                        res=temp;
                    }else{
                        while(exp[cont]==' ')cont++;
                    }
                }
            }
        }
    }
    while(exp[cont]==' ')cont++;
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
        while(exp[cont]==' ')cont++;
        
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

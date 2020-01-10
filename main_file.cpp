#include <iostream> //Basic input/output operation from the console
#include <fstream> //Input from the files
#include <string> //Used for keeping expression as text and to use the operation included in the string library
#include <vector> //Used for keeping expression after breaking text into words
#include <sstream> //Included for stringstream
#include <map> //Used for creating a "dictionary"
#include <algorithm> //For importing for_each
#include "headers/convertor.h"
#include "headers/convertor2.h"
#include "headers/aux_functions.h"
#include "headers/calculator_tip1.h"
#include "headers/evaluator.h"
#include "headers/compute_functions.h"
#include "headers/global_variables.h"
#pragma once
using namespace std;

// Authors: Dobrovici Cristian && Todirisca Cezar
// Start_Date: 6th of December 2019
// Name of the project: Natural language calculator
// Reads a question, for example : "What is the result of the multiplication of x and y?"
// and gives back the answer written with letters
// Uses three auxiliar files for the template numbers. This way the template would not interfere with the code
// Uses 3 modes: Romanian, English or French. The default mode will be Romanian with the posibilty of chaning it afterwards

void TakeTheInput();

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
    int tip=0;
    corect=1;
    pos=-1;
    semn="";
    cin>>tip;
    cin.get();
    getline(cin,input_question);   
    if(tip==1){
        string temp = compute(input_question);
        if(temp=="")return;
        int result = get_result_of_expression(temp);
        final_result = NumToWord(result);
        log_print(0,input_question,final_result);
        return;
    } 
    if(input_question=="")return;
    if(input_question=="Pentru nota 10")
    {
        system("firefox https://programarecurabdare.ro/");
        exit(0);
    }
    list_of_words = split_expression(input_question);
    if(corect==0)return;
    correct_words = select_correct_words(list_of_words);
    if(corect==0)return;
    if(!check_if_valid(correct_words))
    {
        log_print(1,input_question,"");
        return;
    }
    try{
        math_exp = convert_to_math(correct_words);
    }
    catch(bad_alloc)
    {
        log_print(1,input_question,"");
        return;
    }
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
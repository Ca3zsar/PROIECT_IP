#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/global_variables.h"
#include "headers/aux_functions.h"
#include "headers/interface_functions.h"
#include "start_functions.h"
#include <unistd.h>
using namespace std;

sf::RenderWindow main_frame(sf::VideoMode(600,600),"Natural language Calculator");
int focus=0;

string answer_to_show;

void go_to_main_screen()
{
    sf::Font menu_font;
    menu_font.loadFromFile("menu_font.ttf");
    sf::Font main_font;
    main_font.loadFromFile("usable_font.ttf");

    sf::Event event;

    sf::Text input_text;
    input_text.setPosition(15,90);
    input_text.setCharacterSize(10);
    input_text.setFillColor(sf::Color(26,26,26));
    input_text.setFont(main_font);

    sf::RectangleShape input_box;
    input_box.setSize(sf::Vector2f(580,50));
    input_box.setPosition(10,70);
    input_box.setFillColor(sf::Color(209, 220, 240));

    sf::Text output_text;
    output_text.setPosition(15,170);
    output_text.setCharacterSize(10);
    output_text.setFillColor(sf::Color(26,26,26));
    output_text.setFont(main_font);

    sf::RectangleShape output_box;
    output_box.setSize(sf::Vector2f(580,50));
    output_box.setPosition(10,150);
    output_box.setFillColor(sf::Color(209, 220, 240));

    sf::Texture back_icon;
    back_icon.loadFromFile("back_icon.png");
    sf::Sprite back_button(back_icon);
    back_button.setPosition(535,15);

    sf::RectangleShape expresie;
    expresie.setSize(sf::Vector2f(110,40));
    expresie.setPosition(150,400);
    expresie.setFillColor(sf::Color(209, 220, 240));

    sf::RectangleShape intrebare;
    intrebare.setSize(sf::Vector2f(110,40));
    intrebare.setPosition(360,400);
    intrebare.setFillColor(sf::Color(209, 220, 240));

    sf::Text ex("EXPRESIE",main_font);
    ex.setCharacterSize(12);
    ex.setPosition(153,415);
    ex.setFillColor(sf::Color(26,26,26));

    sf::Text intreb("INTREBARE",main_font);
    intreb.setCharacterSize(12);
    intreb.setPosition(359,415);
    intreb.setFillColor(sf::Color(26,26,26));

    sf::Text Introducere("Introduceti input-ul in casuta de mai jos",main_font);
    Introducere.setCharacterSize(10);
    Introducere.setPosition(10,35);

    while(main_frame.isOpen())
    {
        string to_show;
        for(int i=0;i<input_question.size();i++)
        {
            if(i>0 && i%45==0)to_show=to_show+'\n';
            to_show=to_show+input_question[i];
        }
        if(answer_to_the_question!="")
        {
            answer_to_show="";
            for(int i=0;i<answer_to_the_question.size();i++)
            {
                if(answer_to_the_question[i]==' ')
                {
                    int p=-1;
                    for(int j=i+1;j<answer_to_the_question.size();j++)
                    {
                        if(answer_to_the_question[j]==' ')
                        {
                            p=j;
                            break;
                        }
                    }
                    if(p!=-1 && i%45>p%45)answer_to_show=answer_to_show+'\n';
                    else answer_to_show = answer_to_show + ' ';
                }else{
                    answer_to_show = answer_to_show + answer_to_the_question[i];
                }
            }
        }
        main_frame.clear(sf::Color(26,26,26));
        main_frame.draw(input_box);
        main_frame.draw(output_box);
        main_frame.draw(back_button);
        main_frame.draw(expresie);
        main_frame.draw(intrebare);
        main_frame.draw(ex);
        main_frame.draw(intreb);
        main_frame.draw(Introducere);
        input_text.setString(to_show);
        main_frame.draw(input_text);
        output_text.setString(answer_to_show);
        main_frame.draw(output_text);
        //cout<<input<<'\n';
        if(main_frame.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                main_frame.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i coord = sf::Mouse::getPosition(main_frame);
                    if((coord.x>=535 && coord.x<=580 && coord.y>=15 && coord.y<=60))return;
                    if((coord.x>=150 && coord.x<=260 && coord.y>=400 && coord.y<=440))
                    {
                        tip=1;
                        expresie.setFillColor(sf::Color(255,0,0));
                        intrebare.setFillColor(sf::Color(209, 220, 240));
                    }
                    if((coord.x>=360 && coord.x<=470 && coord.y>=400 && coord.y<=440))
                    {
                        tip=0;
                        intrebare.setFillColor(sf::Color(255,0,0));
                        expresie.setFillColor(sf::Color(209, 220, 240));
                    }
                    if(coord.x>=10 && coord.x<=590 && coord.y>=70 && coord.y<=120)
                    {
                        focus=1;
                    }else focus=0;
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(focus)
                {
                    if(event.key.code>=sf::Keyboard::A && event.key.code<=sf::Keyboard::Z)
                    {
                        input_question=input_question+char(event.key.code+65);
                    }
                    if(event.key.code>=sf::Keyboard::Numpad0 && event.key.code<=sf::Keyboard::Numpad9)
                    {
                        input_question=input_question+char(event.key.code-27);
                         cout<<input_question<<'\n';
                    }
                    if(event.key.code==sf::Keyboard::Backspace)
                    {
                        if(input_question.size())input_question.pop_back();
                    }
                    if(event.key.code==sf::Keyboard::Divide)
                    {
                        input_question=input_question+'/';
                    }
                    if(event.key.code==sf::Keyboard::Add)
                    {
                        input_question=input_question+'+';
                    }
                    if(event.key.code==sf::Keyboard::Space)
                    {
                        input_question=input_question+' ';
                    }
                    if(event.key.code==sf::Keyboard::Subtract)
                    {
                        input_question=input_question+'-';
                    }
                    if(event.key.code==sf::Keyboard::Multiply)
                    {
                        input_question=input_question+'*';
                    }
                    if(event.key.code==sf::Keyboard::LBracket)
                    {
                        input_question=input_question+'(';
                    }
                    if(event.key.code==sf::Keyboard::RBracket)
                    {
                        input_question=input_question+')';
                    }
                    if(event.key.code==sf::Keyboard::Slash)
                    {
                        input_question=input_question+'?';
                    }
                    if(event.key.code==sf::Keyboard::Enter)
                    {
                        Process(input_question);
                        input_question="";

                    }
                }
            }
            
        }
        main_frame.display();
    }
}

int main()
{
    sf::Texture image;
    sf::Texture ro_flag;
    sf::Texture en_flag;
    sf::Texture arrow;
    arrow.loadFromFile("arrow.png");
    ro_flag.loadFromFile("steag_ro.jpg");
    en_flag.loadFromFile("steag_uk.jpg");
    image.loadFromFile("back_img.jpg");
    sf::Sprite background(image);
    
    sf::Sprite up_arrow(arrow);
    up_arrow.setPosition(375,3);
    up_arrow.setScale(sf::Vector2f(0.09,0.09));
    sf::Sprite down_arrow(arrow);
    down_arrow.setRotation(180);
    down_arrow.setPosition(420,398);
    down_arrow.setScale(sf::Vector2f(0.09,0.09));
    
    sf::Font menu_font;
    menu_font.loadFromFile("menu_font.ttf");
    sf::Font main_font;
    main_font.loadFromFile("usable_font.ttf");

    while(main_frame.isOpen())
    {
        main_frame.draw(background);
        sf::Event event;

        sf::RectangleShape exit_shape;
        exit_shape.setSize(sf::Vector2f(300,50));
        exit_shape.setPosition(150,395);
        exit_shape.setFillColor(sf::Color(209, 220, 240));
        exit_shape.setOutlineColor(sf::Color(193, 203, 222));
        exit_shape.setOutlineThickness(2);
        main_frame.draw(exit_shape);

        sf::RectangleShape history_shape;
        history_shape.setSize(sf::Vector2f(300,50));
        history_shape.setPosition(150,300);
        history_shape.setFillColor(sf::Color(209, 220, 240));
        history_shape.setOutlineColor(sf::Color(193, 203, 222));
        history_shape.setOutlineThickness(2);
        main_frame.draw(history_shape);

        sf::RectangleShape enter_shape;
        enter_shape.setSize(sf::Vector2f(300,50));
        enter_shape.setPosition(150,205);
        enter_shape.setFillColor(sf::Color(209, 220, 240));
        enter_shape.setOutlineColor(sf::Color(193, 203, 222));
        enter_shape.setOutlineThickness(2);
        main_frame.draw(enter_shape);

        sf::RectangleShape ro_shape;
        ro_shape.setSize(sf::Vector2f(140,50));
        ro_shape.setPosition(150,490);
        ro_shape.setTexture(&ro_flag);
        main_frame.draw(ro_shape);

        sf::RectangleShape en_shape;
        en_shape.setSize(sf::Vector2f(140,50));
        en_shape.setPosition(310,490);
        en_shape.setTexture(&en_flag);
        main_frame.draw(en_shape);

        sf::RectangleShape title_shape;
        title_shape.setFillColor(sf::Color(26,26,26));
        title_shape.setPosition(150,60);
        title_shape.setSize(sf::Vector2f(300,90));
        main_frame.draw(title_shape);

        sf::Text title("Calculator",menu_font);
        title.setCharacterSize(40);
        title.setStyle(sf::Text::Bold);
        title.setPosition(157,60);
        title.setFillColor(sf::Color(255,255,255));
        main_frame.draw(title);

        sf::Text title2("Limbaj natural",menu_font);
        title2.setCharacterSize(30);
        title2.setStyle(sf::Text::Bold);
        title2.setPosition(160,110);
        title2.setFillColor(sf::Color(255,255,255));
        main_frame.draw(title2);

        sf::Text exit_b("EXIT",menu_font);
        exit_b.setCharacterSize(35);
        exit_b.setStyle(sf::Text::Bold);
        exit_b.setPosition(264,395);
        exit_b.setFillColor(sf::Color(30, 31, 29));
        main_frame.draw(exit_b);

        sf::Text history_b("HISTORY",menu_font);
        history_b.setCharacterSize(35);
        history_b.setStyle(sf::Text::Bold);
        history_b.setPosition(227,300);
        history_b.setFillColor(sf::Color(30, 31, 29));
        main_frame.draw(history_b);

        sf::Text enter_b("ENTER",menu_font);
        enter_b.setCharacterSize(35);
        enter_b.setStyle(sf::Text::Bold);
        enter_b.setPosition(239,205);
        enter_b.setFillColor(sf::Color(30, 31, 29));
        main_frame.draw(enter_b);

        if(main_frame.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                main_frame.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i position = sf::Mouse::getPosition(main_frame);
                    if((position.x>=150 && position.x<=450 && position.y >=395 && position.y<=445))
                    {
                        main_frame.close();
                    }
                    if((position.x>=150 && position.x<=450 && position.y >=300 && position.y<=355))
                    { 
                        sf::Event evt;
                        sf::RenderWindow hist(sf::VideoMode(800,400),"History");
        
                        vector<string>Questions;
                        vector<string>Answers;
                        
                        sf::Clock clk;
                        while(hist.isOpen())
                        {
                            hist.clear(sf::Color(26,26,26));
                            
                            Questions = read_questions();
                            Answers = read_answers();
                        
                            int size_of_list = Questions.size();
                            if(hist.pollEvent(evt))
                            {
                                if(evt.type == sf::Event::Closed)
                                {
                                    hist.close();
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                {
                                    hist.close();
                                }
                                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                {
                                    
                                    sf::Vector2i hist_p = sf::Mouse::getPosition(hist);
                                    if(point>0 && (hist_p.x>=375 && hist_p.x<=421 && hist_p.y>=3 && hist_p.y<=49))
                                    {
                                        if(clk.getElapsedTime().asSeconds()>0.5)point--;
                                        clk.restart();
                                        
                                    }
                                    if(point<size_of_list-3 && (hist_p.x>=375 && hist_p.x<=421 && hist_p.y>=352 && hist_p.y<=398))
                                    {
                                        if(clk.getElapsedTime().asSeconds()>1)point++;
                                        clk.restart();
                                    }
                                    if(hist_p.x>=670 && hist_p.x<=770 && hist_p.y>=10 && hist_p.y<=40)
                                    {
                                        clear_the_file();
                                    }
                                }
                                if(evt.type==sf::Event::KeyPressed)
                                {
                                    if(point>0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))point--;
                                    if(point<size_of_list-3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))point++;
                                }
                                
                            }
                            sf::Text qs[3];
                            sf::Text as[3];
                            if(!Questions.empty())
                            {
                                for(int i=point;i<min(point+3,(int)Questions.size());i++)
                                {
                                    qs[i-point].setString(Questions[i]);
                                    qs[i-point].setFont(main_font);
                                    qs[i-point].setCharacterSize(9);
                                    qs[i-point].setPosition(10,70+(i-point)*100);
                                    hist.draw(qs[i-point]);

                                    as[i-point].setString(Answers[i]);
                                    as[i-point].setFont(main_font);
                                    as[i-point].setCharacterSize(9);
                                    as[i-point].setPosition(10,120+(i-point)*100);
                                    hist.draw(as[i-point]);
                                }
                            }

                            sf::RectangleShape bottom_line(sf::Vector2f(800,50));
                            bottom_line.setPosition(0,350);
                            bottom_line.setFillColor(sf::Color(209, 220, 240));
                            hist.draw(bottom_line);

                            sf::RectangleShape top_line(sf::Vector2f(800,50));
                            top_line.setPosition(0,0);
                            top_line.setFillColor(sf::Color(209, 220, 240));
                            hist.draw(top_line);

                            sf::RectangleShape delete_button(sf::Vector2f(100,30));
                            delete_button.setPosition(670,10);
                            delete_button.setFillColor(sf::Color(26,26,26));
                            hist.draw(delete_button);

                            sf::Text del_text("DELETE",main_font);
                            del_text.setFont(main_font);
                            del_text.setCharacterSize(15);
                            del_text.setPosition(675,15);
                            hist.draw(del_text);

                            sf::RectangleShape first_line(sf::Vector2f(800,2));
                            first_line.setPosition(0,150);
                            hist.draw(first_line);
                            sf::RectangleShape second_line(sf::Vector2f(800,2));
                            second_line.setPosition(0,250);

                            hist.draw(second_line);
                            if(point>0)hist.draw(up_arrow);
                            if(point<size_of_list-3)hist.draw(down_arrow);
                            hist.display();
                        }
                    }
                    if(position.x>=150 && position.x<=450 && position.y>=205 && position.y<=300)
                    {
                        go_to_main_screen();
                    }
                    if(position.x>=150 && position.x<=290 && position.y>=490 && position.y<=540)choose_language("ro");
                    if(position.x>=310 && position.x<=450 && position.y>=490 && position.y<=540)choose_language("en");
                }
            }
        }
        
        main_frame.display();
    }
}
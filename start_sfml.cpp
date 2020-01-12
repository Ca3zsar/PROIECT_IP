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
#include <unistd.h>
using namespace std;

sf::RenderWindow main_frame(sf::VideoMode(600,600),"Natural language Calculator");

void go_to_main_screen()
{
    sf::Font menu_font;
    menu_font.loadFromFile("menu_font.ttf");
    sf::Font main_font;
    main_font.loadFromFile("usable_font.ttf");

    sf::Event event;

    sf::RectangleShape input_box;
    input_box.setSize(sf::Vector2f(580,50));
    input_box.setPosition(10,70);
    input_box.setFillColor(sf::Color(209, 220, 240));

    sf::Texture back_icon;
    back_icon.loadFromFile("back_icon.png");
    sf::Sprite back_button(back_icon);
    back_button.setPosition(535,15);

    while(main_frame.isOpen())
    {
        main_frame.clear(sf::Color(26,26,26));
        main_frame.draw(input_box);
        main_frame.draw(back_button);
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
                        Questions = read_questions();
                        Answers = read_answers();
                        
                        int size_of_list = Questions.size();
                        sf::Clock clk;
                        while(hist.isOpen())
                        {
                            hist.clear(sf::Color(26,26,26));
                            
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow main_frame(sf::VideoMode(600,600),"Natural language Calculator");
    sf::Texture image;
    image.loadFromFile("back_img.jpg");
    sf::Sprite background(image);

    sf::IntRect  Button1,Button2,Button3;

    while(main_frame.isOpen())
    {
        main_frame.draw(background);
        sf::Event event;
        if(main_frame.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                main_frame.close();
            }
        }

        

        sf::RectangleShape test_rect;
        test_rect.setSize(sf::Vector2f(300,50));
        test_rect.setPosition(150,300);
        test_rect.setFillColor(sf::Color(209, 220, 240));
        test_rect.setOutlineColor(sf::Color(193, 203, 222));
        test_rect.setOutlineThickness(2);
        main_frame.draw(test_rect);

        main_frame.display();
    }
}
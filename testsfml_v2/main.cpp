#include <iostream>
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include <vector>

static const float VIEW_HEIGHT = 540.0f;
static const float VIEW_WIDTH = 960.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDTH);
}

int main()
{
 
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Game's oat", sf::Style::Titlebar | sf::Style::Close);
    //sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1020, 1080));
    sf::Texture playerTexture;
        playerTexture.loadFromFile("pngegg.png");
    sf::Texture box;
        box.loadFromFile("1.png");
    sf::Texture em;
        em.loadFromFile("oj1.png");
   
    Player player(&playerTexture, sf::Vector2u(3, 4), 0.2f, 100.0f,200.0f);
    
    std::vector<Platform> platforms;
    platforms.push_back(Platform(nullptr, sf::Vector2f(960.0f, 200.0f), sf::Vector2f(480.0f, 600.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    Platform box3(nullptr, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(500.0f, 400.0f));
    //Platform platform1(&em, sf::Vector2f(80.0f, 100.0f), sf::Vector2f(500.0f, 100.0f));
    

    //Animation oj1(&em, sf::Vector2u(6, 1), 0.2f);

    float deltaTime = 0.0f;
    sf::Clock clock;
  
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;
        
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
            /*else if (ev.type == sf::Event::Resized)
            {
                ResizeView(window,view);
            }*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

        }
        player.Update(deltaTime);
        //oj1.Update(0,deltaTime);
        //platform1.body.setTextureRect(oj1.uvRect);
        Collider playerCollision = player.GetCollider();
        sf::Vector2f direction;

        //for (int i = 0; i < platforms.size(); i++)
        //{
        //    Platform& platform = platforms[i];
        //}

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollider(playerCollision, direction, 1.0f))
                player.OnCollosion(direction);
        box3.GetCollider().CheckCollider(playerCollision, direction, 0.9f);
        
        //view.setCenter(player.GetPosition());

        window.clear(sf::Color(150,150,150));
        //window.setView(view);
        player.Draw(window);
        for (Platform& platform : platforms)
            platform.Draw(window);
        box3.Draw(window);
        
        window.display();
    }
    return 0;
}



/*
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousepos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousepos.x, (float)mousepos.y);
        }

        */


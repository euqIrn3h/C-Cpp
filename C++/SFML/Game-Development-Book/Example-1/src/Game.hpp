#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Window{

public:
    Window(){ Setup("Window", sf::Vector2u(640,480)); }

    Window(const std::string& l_title, const sf::Vector2u& l_size){
        Setup(l_title, l_size);
    }

    ~Window(){ Destroy(); }

    void Update(){
        sf::Event event;

        while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                m_isDone = true;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){
                ToogleFullscreen();
            }
        }
    }
    
    void ToogleFullscreen(){
        m_isFullscreen = !m_isFullscreen;
        Destroy();
        Create();
    }

    void BeginDraw(){ m_window.clear(sf::Color::Black); }
    void EndDraw(){ m_window.display(); }

    bool IsDone(){ return m_isDone; }
    bool ISFullscreen(){ return m_isFullscreen; }
    sf::Vector2u GetWindowSize(){ return m_windowSize; }

    void Draw(sf::Drawable& l_drawable){
        m_window.draw(l_drawable);
    }

    void Setup(const std::string& l_title, const sf::Vector2u& l_size){
        m_windowTitle = l_title;
        m_windowSize = l_size;
        m_isFullscreen = false;
        m_isDone = false;
        Create();
    }

    void Create(){
        auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        m_window.create(
            { m_windowSize.x, m_windowSize.y, 32},
            m_windowTitle,
            style
        );
    }    

    void Destroy(){
        m_window.close();
    }

private:
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

};

class Game{
public:
    void HandleInput(){}

    Window* GetWindow(){
        return &m_window;
    };

    Game(): m_window("Chapter 2", sf::Vector2u(800,600)){
        m_mushroomTexture.loadFromFile("./src/assets/Maca-do-bicho.jpg");
        m_mushroom.setTexture(m_mushroomTexture);
        m_increment = sf::Vector2i(4,4);
    }

    ~Game(){}

    void Update(){
        m_window.Update();
        MoveMushroom();
    }

    void Render(){
        m_window.BeginDraw();
        m_window.Draw(m_mushroom);
        m_window.EndDraw();
    }

    void MoveMushroom(){
        sf::Vector2u l_windSize = m_window.GetWindowSize();
        sf::Vector2u l_textSize = m_mushroomTexture.getSize();

        if((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) || (m_mushroom.getPosition().x < 0 && m_increment.x < 0)){
            m_increment.x = -m_increment.x;
        }

        if((m_mushroom.getPosition().y > l_windSize.y -l_textSize.y && m_increment.y > 0) || (m_mushroom.getPosition().y < 0 && m_increment.y < 0)){
            m_increment.y = -m_increment.y;
        }

        m_mushroom.setPosition(m_mushroom.getPosition().x + m_increment.x, m_mushroom.getPosition().y + m_increment.y);

    }

private:
    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite m_mushroom;
    sf::Vector2i m_increment;

    
};

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Window{

public:
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window();

    void BeginDraw();
    void EndDraw();

    void Update();

    bool IsDone();
    bool ISFullscreen();

    sf::Vector2u GetWindowSize();

    void ToogleFullscreen();

    void Draw(sf::Drawable& l_drawable);

    Window::Window(){ Setup("Window", sf::Vector2u(640,480)); }

    Window::Window(const std::string& l_title, const sf::Vector2u& l_size){
        Setup(l_title, l_size);
    }

    Window::~Window(){ Destroy(); }

    void Window::Update(){
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
    
    void Window::ToogleFullscreen(){
        m_isFullscreen = !m_isFullscreen;
        Destroy();
        Create();
    }

    void Window::BeginDraw(){ m_window.clear(sf::Color::Black); }
    void Window::EndDraw(){ m_window.display(); }

    bool Window::IsDone(){ return m_isDone; }
    bool Window::ISFullscreen(){ return m_isFullscreen; }
    sf::Vector2u Window::GetWindowSize(){ return m_windowSize; }

    void Window::Draw(sf::Drawable& l_drawable){
        m_window.draw(l_drawable);
    }

    void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size){
        m_windowTitle = l_title;
        m_windowSize = l_size;
        m_isFullscreen = false;
        m_isDone = false;
        Create();
    }

    void Window::Create(){
        auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        m_window.create(
            { m_windowSize.x, m_windowSize.y, 32},
            m_windowTitle,
            style
        );
    }    

    void Window::Destroy(){
        m_window.close();
    }

private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

};

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();

    Game::Game(): m_window("Chapter 2", sf::Vector2u(800,600)){
        m_mushroomTexture.loadFromFile("./assets/Maca-do-bicho.jpg");
        m_mushroom.setTexture(m_mushroomTexture);
        m_increment = sf::Vector2i(4,4);
    }

    void Game::Update(){
        m_window.Update();
        MoveMushroom();
    }

    void Game::Render(){
        m_window.BeginDraw();
        m_window.Draw(m_mushroom);
        m_window.EndDraw();
    }

private:
    void MoveMushroom();
    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite m_mushroom;
    sf::Vector2i m_increment;

    void Game::MoveMushroom(){
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
};

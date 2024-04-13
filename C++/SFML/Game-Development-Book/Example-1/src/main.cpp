#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "SFML works!", sf::Style::Default);


    while (window.isOpen())
    {
        sf::Event event;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}

class Window{

public:
    Window();
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
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            {
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

private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

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

};


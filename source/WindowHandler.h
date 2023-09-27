#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>


class WindowHandler {
public:
    ~WindowHandler();
    static WindowHandler& Instance();
    static sf::RenderWindow& window();

    void close() { m_is_to_close = true; };
    bool is_to_close() { return m_is_to_close; }
private:
    sf::RenderWindow m_window;
    bool m_is_to_close = false;

    WindowHandler();
    WindowHandler(const WindowHandler& other_) = delete;
    WindowHandler& operator=(const WindowHandler&) = delete;
};
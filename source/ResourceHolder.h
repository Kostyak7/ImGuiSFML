#pragma once

#include <SFML/Graphics.hpp>
#include <GL/freeglut.h>
#include <unordered_map>


GLuint log_gl_texture(sf::Image& image_);

class ResourceHolder {
public:
    using key_t = std::string;
    using ckey_t = const std::string;
    using cskey_t = const std::string&;
public:
    ResourceHolder& operator()() { return Instance(); }

    std::shared_ptr<sf::Image> getSfImage(cskey_t path_);
    std::shared_ptr<sf::Texture> getSfTexture(cskey_t path_);
    std::shared_ptr<sf::Font> getFont(cskey_t path_);

    static ResourceHolder& Instance();
private:
    std::unordered_map<key_t, std::shared_ptr<sf::Image>> m_images;
    std::unordered_map<key_t, std::shared_ptr<sf::Texture>> m_textures;
    std::unordered_map<key_t, std::shared_ptr<sf::Font>> m_fonts;

    ResourceHolder() = default;
    ResourceHolder(const ResourceHolder& other_player_) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;

    template <class T_, class lambda_t_> static T_& getItem(std::unordered_map<key_t, T_>& from_map_, cskey_t key_, lambda_t_& if_load_);
    static std::shared_ptr<sf::Image> load_image(cskey_t path_);
    static std::shared_ptr<sf::Texture> load_texture(cskey_t path_);
    static std::shared_ptr<sf::Font> load_font(cskey_t path_);
};
#pragma once

#include "config.h"
#include <gl/freeglut.h>
#include <unordered_map>


class ResourceHolder {
public:
    using key_t = std::string;
    using ckey_t = const key_t;
    using cskey_t = ckey_t&;
public:
    static ResourceHolder& Instance();

    std::shared_ptr<sf::Image> getSfImage(cskey_t path_);
    GLuint getGlTexture(cskey_t path_, const sf::IntRect& int_rect_ = sf::IntRect());
    std::shared_ptr<sf::Texture> getSfTexture(cskey_t path_, const sf::IntRect& int_rect_ = sf::IntRect());
    std::shared_ptr<sf::Font> getSfFont(cskey_t path_);
private:
    std::unordered_map<key_t, std::shared_ptr<sf::Image>> m_sf_images;
    std::unordered_map<key_t, GLuint> m_gl_textures;
    std::unordered_map<key_t, std::shared_ptr<sf::Texture>> m_sf_textures;
    std::unordered_map<key_t, std::shared_ptr<sf::Font>> m_sf_fonts;

    static GLuint log_gl_texture(std::shared_ptr<sf::Image> ptr_image_, const sf::IntRect& int_rect_);

    ResourceHolder() = default;
    ResourceHolder(const ResourceHolder& other_player_) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;
};
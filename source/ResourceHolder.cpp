#include "config.h"
#include "ResourceHolder.h"
#include <functional>
#include <iostream>


GLuint log_gl_texture(sf::Image& image_) {
    image_.flipVertically();

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image_.getSize().x, image_.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image_.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}


std::shared_ptr<sf::Image> ResourceHolder::getSfImage(cskey_t path_) {
    static auto lambda = [this](cskey_t path_) { return load_image(path_); };
    return getItem(m_images, path_, lambda);
}

std::shared_ptr<sf::Texture> ResourceHolder::getSfTexture(cskey_t path_) {
    static auto lambda = [this](cskey_t path_) { return load_texture(path_); };
    return getItem(m_textures, path_, lambda);
    /*auto it = m_textures.find(path_);
    if (it == m_textures.end()) {
        auto texture = std::make_shared<sf::Texture>();
        texture->loadFromFile(path_);
        m_textures[path_] = texture;
        return texture;
    }
    return it->second;*/
}

std::shared_ptr<sf::Font> ResourceHolder::getFont(cskey_t path_) {
    static auto lambda = [this](cskey_t path_) { return load_font(path_); };
    return getItem(m_fonts, path_, lambda);
    /*auto it = m_fonts.find(path_);
    if (it == m_fonts.end()) {
        auto font = std::make_shared<sf::Font>();
        font->loadFromFile(path_);
        m_fonts[path_] = font;
        return font;
    }
    return it->second;*/
}


ResourceHolder& ResourceHolder::Instance() {
    static ResourceHolder me_resource_holder;
    return me_resource_holder;
}


template <class T_, class lambda_t_>
T_& ResourceHolder::getItem(std::unordered_map<key_t, T_>& from_map_, cskey_t key_, lambda_t_& if_load_) {
    auto it = from_map_.find(key_);
    if (it == from_map_.end()) {
        auto item = if_load_(key_);
        from_map_[key_] = item;
        return item;
    }
    return it->second;
}

std::shared_ptr<sf::Image> ResourceHolder::load_image(cskey_t path_) {
    auto image = std::make_shared<sf::Image>();
    if (image->loadFromFile(path_)) return image;
    else return {};
}

std::shared_ptr<sf::Texture> ResourceHolder::load_texture(cskey_t path_) {
    auto texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(path_)) return texture;
    else return {};
}

std::shared_ptr<sf::Font> ResourceHolder::load_font(cskey_t path_) {
    auto font = std::make_shared<sf::Font>();
    if (font->loadFromFile(path_)) return font;
    else return {};
}
#include "ResourceHolder.h"


ResourceHolder& ResourceHolder::Instance() {
    static ResourceHolder me;
    return me;
}

std::shared_ptr<sf::Image> ResourceHolder::getSfImage(cskey_t path_) {
    auto it = m_sf_images.find(path_);
    if (it == m_sf_images.end()) {
        auto image = std::make_shared<sf::Image>();
        image->loadFromFile(path_);
        image->flipVertically();
        m_sf_images[path_] = image;
        return image;
    }
    return it->second;
}

GLuint ResourceHolder::getGlTexture(cskey_t path_, const sf::IntRect& int_rect_) {
    auto it = m_gl_textures.find(path_);
    if (it == m_gl_textures.end()) {
        auto texture = log_gl_texture(getSfImage(path_), int_rect_);
        m_gl_textures[path_] = texture;
        return texture;
    }
    return it->second;
}

std::shared_ptr<sf::Texture> ResourceHolder::getSfTexture(cskey_t path_, const sf::IntRect& int_rect_) {
    auto it = m_sf_textures.find(path_);
    if (it == m_sf_textures.end()) {
        auto texture = std::make_shared<sf::Texture>();
        texture->loadFromImage(*getSfImage(path_), int_rect_);
        m_sf_textures[path_] = texture;
        return texture;
    }
    return it->second;
}

std::shared_ptr<sf::Font> ResourceHolder::getSfFont(cskey_t path_) {
    auto it = m_sf_fonts.find(path_);
    if (it == m_sf_fonts.end()) {
        auto font = std::make_shared<sf::Font>();
        font->loadFromFile(path_);
        m_sf_fonts[path_] = font;
        return font;
    }
    return it->second;
}

GLuint ResourceHolder::log_gl_texture(std::shared_ptr<sf::Image> ptr_image_, const sf::IntRect& int_rect_) {
    if (!ptr_image_) return GLuint();

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // TODO: implement int_rect
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, ptr_image_->getSize().x, ptr_image_->getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, ptr_image_->getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}
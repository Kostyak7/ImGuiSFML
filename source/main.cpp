//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <glad/glad.h>
//#include "imgui.h"
//
////#include "imgui_impl_opengl3.h"
//#include "imgui-sfml.h"
//#include <vector>
//#include <memory>
//
//
//
//class Floor {
//public:
//    Floor() {
//        m_vertexes = { 0.5,0.5,0,  0.5,-0.5,0,  -0.5,-0.5,0,  -0.5,0.5,0 };
//        glGenBuffers(1, &m_vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//        glBufferData(GL_ARRAY_BUFFER, m_vertexes.size() * sizeof(float), m_vertexes.data(), GL_STATIC_DRAW);
//        //glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//    }
//
//    void draw(sf::RenderWindow& window_) {
//        window_.setActive();
//
//        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//        glVertexPointer(3, GL_FLOAT, 0, NULL);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glColor3f(0.1f, 0.5f, 0.0f);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//        glDisableClientState(GL_VERTEX_ARRAY);
//    }
//private:
//    std::vector<GLfloat> m_vertexes;
//    GLuint m_vbo;
//};
//
//
//
//
//int main() {
//	sf::RenderWindow window(sf::VideoMode(800, 800), "Glad-test", sf::Style::Default, sf::ContextSettings(24));
//    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);
//    window.setActive();
//
//    gladLoadGL();
//
//    window.pushGLStates();
//    ImGui::SFML::Init(window);
//
//    window.resetGLStates();
//    window.popGLStates();
//
//    std::shared_ptr<Floor> floor;
//    int i = 0;
//    sf::Clock clock;
//
//    while (window.isOpen()) {
//        ImGui::SFML::SetCurrentWindow(window);
//
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            ImGui::SFML::ProcessEvent(event);
//            if (event.type == sf::Event::Closed) {
//                window.close();
//                return 0;
//            }
//        }
//
//        ImGui::SFML::Update(window, clock.restart());
//
//        if (i < 10000 && i != -1) ++i;
//        else {
//            if (i != -1) floor = std::make_shared<Floor>();
//            i = -1;
//        }
//        ImGui::Begin("Yes");
//        if (ImGui::Button("Open")) {
//            i = 10000;
//        }
//        ImGui::End();
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//        glPushMatrix();
//
//        /*glEnable(GL_DEPTH_TEST);
//        glDepthMask(true);
//        glClearDepth(100.f);
//        glMatrixMode(GL_PROJECTION);*/
//        glLoadIdentity();
//
//        if (floor) floor->draw(window);
//        glPopMatrix();
//
//
//        
//        window.pushGLStates();
//        ImGui::SFML::Render(window);
//        window.popGLStates();
//
//        window.display();
//    }
//
//    ImGui::SFML::Shutdown(window);
//    ImGui::SFML::Shutdown();
//
//	return 0;
//}


#include "Application.h"


int main() {
	return Application::app().run();
}
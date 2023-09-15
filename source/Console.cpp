#include "Console.h"


Console::Console() {
	init();
}

Console:: ~Console() {

}


void Console::init() {
	m_console.System().Log(csys::ItemType::INFO) << "Welcome to the imgui-console example!" << csys::endl;
	m_console.System().Log(csys::ItemType::INFO) << "There you can input your commands" << csys::endl;
	m_console.System().Log(csys::ItemType::INFO) << "Enter 'help' if you don`t know anything" << csys::endl;
}
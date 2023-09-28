//#include "Console.h"
//#include "imgui.h"
//#include "imgui_console.h"
//
//
//Console& Console::console() {
//	static Console me;
//	return me;
//}
//
//Console::Console() {
//	init();
//}
//
//
//void Console::init() {
//
//}
//
//void Console::activate(bool is_activate_) {
//	if (is_activate_) open();
//	else close();
//}
//
//void Console::open() {
//	m_is_open = true;
//}
//
//void Console::close() {
//	m_is_open = false;
//}
//
//bool Console::is_open() {
//	return m_is_open;
//}
//
//void Console::draw() {
//	if (is_open()) m_console.Draw();
//}

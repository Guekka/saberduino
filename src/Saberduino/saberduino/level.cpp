#include "level.hpp"
#include "printer.hpp"

void Level::init() {
    printer.println("init level");
}

void Level::load(const char* filename) {
    printer.println("load level");
}

void Level::start() {
    printer.println("start level");
}

void Level::update(Position pos) {
    printer.println("update level");
}

#include "gdMain.h"

using namespace godot;

void GDMyMain::_register_methods() {
    register_method("_process", &GDMyMain::_process);
}

GDMyMain::GDMyMain() {
}

GDMyMain::~GDMyMain() {
    // add your cleanup here
}

void GDMyMain::_init() {
    // initialize any variables here
    time_passed = 0.0;
}

void GDMyMain::_process(float delta) {


}

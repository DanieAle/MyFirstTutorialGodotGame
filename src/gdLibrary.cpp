#include "gdMain.h"
#include "gdKeys.h"
#include "gdEnemy.h"
#include "gdColision.h"
#include "gdEnemyColision.h"
#include "gdMainNode.h"


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GDMyMain>();
    godot::register_class<godot::GDKeys>();
    godot::register_class<godot::GDEnemy>();
    godot::register_class<godot::GDColision>();
    godot::register_class<godot::GDEnemyColision>();
    godot::register_class<godot::GDMainNode>();
}

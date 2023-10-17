#include "gdCollisionPlayer.h"
#include "GDSprite.h"
#include "gdCollisionEnemy.h"
#include "gdMainNode.h"
#include "gdMenu.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GDCollisionPlayer>();
    godot::register_class<godot::GDSprite>();
    godot::register_class<godot::GDCollisionEnemy>();
    godot::register_class<godot::GDMainNode>();
    godot::register_class<godot::GDMenu>();
}

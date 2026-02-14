#include "gdCollision.h"
#include "gdCollisionPlayer.h"
#include "GDSprite.h"
#include "gdCollisionEnemy.h"
#include "gdMainNode.h"
#include "gdMenu.h"
#include "gdController1.h"
#include "gdControllertouch.h"
#include "MenuTouch.h"
#include "gdControlLayout.h"
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GDCollision>();
    godot::register_class<godot::GDCollisionPlayer>();
    godot::register_class<godot::GDSprite>();
    godot::register_class<godot::GDCollisionEnemy>();
    godot::register_class<godot::GDMainNode>();
    godot::register_class<godot::GDMenu>();
    godot::register_class<godot::GDController>();
    godot::register_class<godot::GDControllerTouch>();
    godot::register_class<godot::GDMenuTouch>();
    godot::register_class<godot::GDControlLayout>();
}

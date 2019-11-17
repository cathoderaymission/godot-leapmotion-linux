#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
//#include <Sprite.hpp>
#include <Spatial.hpp>

namespace godot {

class GDExample : public godot::GodotScript<Spatial> {
    GODOT_CLASS(GDExample)

private:
    float time_passed;

public:
    static void _register_methods();

    GDExample();
    ~GDExample();

    void _process(float delta);
};

}

#endif

#ifndef DEF_GUARD_WINDOW_RESIZER
#define DEF_GUARD_WINDOW_RESIZER

#include <Godot.hpp>
#include <Node.hpp>
#include <String.hpp>
#include <OS.hpp>

namespace godot {

class WindowResizer : public Node 
{
    GODOT_CLASS(WindowResizer, Node)

private:
    Vector2 window_size = Vector2(0,0);
    String title = "";
    OS * os;

    enum Choice{
        KEEP = -1,
        FALSE = 0,
        TRUE = 1
    };

    int window_resizable = Choice::KEEP;
    int window_borderless = Choice::KEEP;
    int window_ontop = Choice::KEEP;
    int window_fullscreen = Choice::KEEP;
    int window_maximized = Choice::KEEP;
    
    bool auto_trigger = false;
    
public:
    static void _register_methods();
    void _init();
    void _ready();
    void Toggle();
};

}

#endif
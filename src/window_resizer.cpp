#include "window_resizer.hpp"

using namespace godot;

void WindowResizer::_register_methods() 
{
    // METHODS
	register_method("_ready", &WindowResizer::_ready);
    register_method("toggle", &WindowResizer::Toggle);

    // PROPERTY
    register_property<WindowResizer, String>(
        "title", 
        &WindowResizer::title, 
        ""
    );

    register_property<WindowResizer, Vector2>(
        "window_size", 
        &WindowResizer::window_size, 
        Vector2(0,0)
    );

    register_property<WindowResizer, int>(
		"window_resizable", 
		&WindowResizer::window_resizable,	
		Choice::KEEP, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("KEEP:-1, FALSE:0, TRUE:1")
	);
    register_property<WindowResizer, int>(
		"window_borderless", 
		&WindowResizer::window_borderless,	
		Choice::KEEP, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("KEEP:-1, FALSE:0, TRUE:1")
	);
    register_property<WindowResizer, int>(
		"window_ontop", 
		&WindowResizer::window_ontop,	
		Choice::KEEP, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("KEEP:-1, FALSE:0, TRUE:1")
	);
    register_property<WindowResizer, int>(
		"window_fullscreen", 
		&WindowResizer::window_fullscreen,	
		Choice::KEEP, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("KEEP:-1, FALSE:0, TRUE:1")
	);
    register_property<WindowResizer, int>(
		"window_maximized", 
		&WindowResizer::window_maximized,	
		Choice::KEEP, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("KEEP:-1, FALSE:0, TRUE:1")
	);

    register_property<WindowResizer, bool>(
        "auto_trigger", 
        &WindowResizer::auto_trigger, 
        false
    );
}

void WindowResizer::_init() 
{
	
}

void WindowResizer::_ready()
{
    os = OS::get_singleton();
    if(auto_trigger)
        Toggle(); 
    Godot::print(String(window_resizable+window_borderless+window_ontop+window_fullscreen+window_maximized));
}

void WindowResizer::Toggle()
{
    if (title != "")
        os->set_window_title(title);
    if (window_size != Vector2(0,0))
    {
        Vector2 win_pos_centered = os->get_window_position() + os->get_window_size()/2;
	    os->set_window_size(window_size);
	    os->set_window_position(win_pos_centered - window_size/2);
    }
    if (window_resizable != KEEP)
        os->set_window_resizable(window_resizable);
    if (window_borderless != KEEP)
        os->set_borderless_window(window_borderless);
    if (window_ontop != KEEP)
        os->set_window_always_on_top(window_ontop);
    if (window_maximized != KEEP)
        os->set_window_maximized(window_maximized);
}
#ifndef DEF_GUARD_QUAKE_SCROLL
#define DEF_GUARD_QUAKE_SCROLL

#include <Godot.hpp>
#include <Panel.hpp>
#include <Tween.hpp>
#include <String.hpp>

namespace godot {

class QuakeScroll : public Panel 
{
	GODOT_CLASS(QuakeScroll, Panel)

private:
	// -------------------------------------------------------
	// Internal
	// -------------------------------------------------------
	Tween * tween;
	bool switcher = true;
	real_t start_position_y;
	real_t start_size_y;
	real_t end_position_y;
	real_t end_size_y;

	// -------------------------------------------------------
	// Export
	// -------------------------------------------------------
	int height_open = 200;
	real_t open_speed = 1.0;
	real_t close_speed = 1.0;
	
	enum Direction {
		TOP=0, 
		DOWN=1
	};

	Direction expand_direction = Direction::DOWN;

	Tween::EaseType open_ease_type = Tween::EASE_OUT;
	Tween::TransitionType open_transition_type = Tween::TRANS_BOUNCE;
	Tween::EaseType close_ease_type = Tween::EASE_OUT;
	Tween::TransitionType close_transition_type = Tween::TRANS_BOUNCE;

	bool  closed_state = true;	

public:
	// Godot
	static void _register_methods();
	void _process(float delta);
	void _init();
	void _ready();

	// User
	void tween_start();
	void toggle();

	// SetGet JUNGLE
	void set_height_open(int value);
	int get_height_open();

	void set_open_speed(real_t value);
	real_t get_open_speed();

	void set_close_speed(real_t value);
	real_t get_close_speed();

	void set_closed(bool value);
	bool is_closed();

	void set_expand_direction(int value);
	int get_expand_direction();

	void set_open_ease_type(int value);
	int get_open_ease_type();

	void set_open_transition_type(int value);
	int get_open_transition_type();

	void set_close_ease_type(int value);
	int get_close_ease_type();
	
	void set_close_transition_type(int value);
	int get_close_transition_type();
};

} // namespace godot
#endif // QUAKE_SCROLL
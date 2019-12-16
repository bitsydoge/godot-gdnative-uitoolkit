#include "quake_scroll.hpp"
#include <Input.hpp>

using namespace godot;

void QuakeScroll::_register_methods() 
{
	// METHODS
	register_method("_ready", &QuakeScroll::_ready);
	register_method("toggle", &QuakeScroll::toggle);
	
	// PROPERTY
	register_property<QuakeScroll, int>("height_open", &QuakeScroll::set_height_open, &QuakeScroll::get_height_open, 200);
	register_property<QuakeScroll, real_t>("open_speed", &QuakeScroll::set_open_speed, &QuakeScroll::get_open_speed, 1.0);
	register_property<QuakeScroll, real_t>("close_speed", &QuakeScroll::set_close_speed, &QuakeScroll::get_close_speed, 1.0);
	register_property<QuakeScroll, bool>("is_closed", &QuakeScroll::set_closed, &QuakeScroll::is_closed, true);
	
	register_property<QuakeScroll, int>(
		"expand_direction", 
		&QuakeScroll::set_expand_direction,	
		&QuakeScroll::get_expand_direction,	
		Direction::DOWN, 
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		String("TOP,DOWN")
	);
	register_property<QuakeScroll, int>(
		"open_ease_type", 
		&QuakeScroll::set_open_ease_type,	
		&QuakeScroll::get_open_ease_type,	
		Tween::EASE_OUT,
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		"EASE_IN,EASE_OUT,EASE_IN_OUT,EASE_OUT_IN"
	);
	register_property<QuakeScroll, int>(
		"open_transition_type", 
		&QuakeScroll::set_open_transition_type,	
		&QuakeScroll::get_open_transition_type,	
		Tween::TRANS_BOUNCE,
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		"TRANS_LINEAR, TRANS_SINE, TRANS_QUINT, TRANS_QUART, TRANS_QUAD, TRANS_EXPO, TRANS_ELASTIC, TRANS_CUBIC, TRANS_CIRC, TRANS_BOUNCE, TRANS_BACK"
	);
	register_property<QuakeScroll, int>(
		"close_ease_type", 
		&QuakeScroll::set_close_ease_type,	
		&QuakeScroll::get_close_ease_type,	
		Tween::EASE_OUT,
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		"EASE_IN,EASE_OUT,EASE_IN_OUT,EASE_OUT_IN"
	);
	register_property<QuakeScroll, int>(
		"close_transition_type", 
		&QuakeScroll::set_close_transition_type,	
		&QuakeScroll::get_close_transition_type,	
		Tween::TRANS_BOUNCE,
		GODOT_METHOD_RPC_MODE_DISABLED, 
		GODOT_PROPERTY_USAGE_DEFAULT, 
		GODOT_PROPERTY_HINT_ENUM, 
		"TRANS_LINEAR, TRANS_SINE, TRANS_QUINT, TRANS_QUART, TRANS_QUAD, TRANS_EXPO, TRANS_ELASTIC, TRANS_CUBIC, TRANS_CIRC, TRANS_BOUNCE, TRANS_BACK"
	);

	// REGISTER
	register_signal<QuakeScroll>("open_start", Dictionary());
	register_signal<QuakeScroll>("close_start", Dictionary());
	register_signal<QuakeScroll>("open_finish", Dictionary());
	register_signal<QuakeScroll>("close_finish", Dictionary());
	register_signal<QuakeScroll>("toggled", Dictionary());
}

void QuakeScroll::_init() 
{
	
}

void QuakeScroll::_ready()
{
	Godot::print("Init_QuakeScroll in " + get_name() + " node");
	tween = godot::Object::cast_to<Tween>(get_node("Tween"));
	start_position_y = get_position().y;
	if(expand_direction == Direction::TOP)
	{
		end_position_y = get_position().y - height_open;
		start_size_y = get_size().y;
		end_size_y = get_size().y + height_open;
	}
	else
	{
		end_position_y = get_position().y;
		start_size_y = get_size().y;
		end_size_y = get_size().y + height_open;
	}

	if(!closed_state)
	{
		tween_start();
		tween->seek(open_speed);
	}
}

void QuakeScroll::tween_start()
{
	if(switcher)
	{
		if (expand_direction == Direction::TOP)
		{
			tween->interpolate_property(
				this, 
				"rect_postion:y", 
				get_position().y, 
				end_position_y, 
				open_speed, 
				open_transition_type, 
				open_ease_type
			);
		}

		tween->interpolate_property(
			this, 
			"rect_size:y",
			get_size().y, 
			end_size_y, 
			open_speed,
			open_transition_type, 
			open_ease_type
		);

		tween->start();
	}
	else
	{
		if(expand_direction == Direction::TOP)
		{
			tween->interpolate_property(
				this, "rect_position:y",
				get_position().y, 
				start_position_y, 
				close_speed,
				close_transition_type, 
				close_ease_type
			);
		}
		tween->interpolate_property(
			this, "rect_size:y",
			get_size().y, 
			start_size_y, 
			close_speed,
			close_transition_type, 
			close_ease_type
		);
		tween->start();
	}
	switcher = !switcher;
}

void QuakeScroll::toggle()
{
	emit_signal("toggled");
	tween->stop_all();
	if(switcher)
	{
		emit_signal("open_start");
		tween_start();
	}
	else
	{
		emit_signal("close_start");
		tween_start();
	}
}

// SetGet jungle

void QuakeScroll::set_height_open(int value)
{
	height_open = value;
}

int QuakeScroll::get_height_open()
{
	return height_open;
}

void QuakeScroll::set_open_speed(real_t value)
{
	open_speed = value;
}
real_t QuakeScroll::get_open_speed()
{
	return open_speed;
}

void QuakeScroll::set_close_speed(real_t value)
{
	close_speed = value;
}
real_t QuakeScroll::get_close_speed()
{
	return close_speed;
}

void QuakeScroll::set_closed(bool value)
{
	closed_state = value;
}
bool QuakeScroll::is_closed()
{
	return closed_state;
}

void QuakeScroll::set_expand_direction(int value)
{
	expand_direction = static_cast<Direction>(value);
}

int QuakeScroll::get_expand_direction()
{
	return expand_direction;
}


// SETGET EASE/TRANSITION

void QuakeScroll::set_open_ease_type(int value)
{
	open_ease_type = static_cast<Tween::EaseType>(value);
}

int QuakeScroll::get_open_ease_type()
{
	return open_ease_type;
}

void QuakeScroll::set_open_transition_type(int value)
{
	open_transition_type = static_cast<Tween::TransitionType>(value);
}

int QuakeScroll::get_open_transition_type()
{
	return open_transition_type;
}

void QuakeScroll::set_close_ease_type(int value)
{
	close_ease_type = static_cast<Tween::EaseType>(value);
}

int QuakeScroll::get_close_ease_type()
{
	return close_ease_type;
}

void QuakeScroll::set_close_transition_type(int value)
{
	close_transition_type = static_cast<Tween::TransitionType>(value);
}

int QuakeScroll::get_close_transition_type()
{
	return close_transition_type;
}
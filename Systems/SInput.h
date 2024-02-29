#pragma once

class SInput
{
	SInput()  = default;
	~SInput() = default;

	sf::Event m_event = {};
	Vec2      m_move  = {};
	bool      m_moved = false;

public:
	static SInput& get()
	{
		static SInput inputSystem;
		return inputSystem;
	}

	SInput(SInput const&)            = delete;
	SInput(SInput&&)                 = delete;
	SInput& operator=(SInput const&) = delete;
	SInput& operator=(SInput&&)      = delete;

	void update();

	void get_window_event();
	void get_mouse_event() const;
	void get_key_event();

	bool enabled = true;
};
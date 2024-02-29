#include "../stdafx.h"
#include "SInput.h"
#include "SPhysics.h"
#include "SRender.h"
#include "../Math.hpp"
#include "../Entities/Behavior.hpp"
#include "../Components/Transform.hpp"
#include "../Engine/GameEngine.h"

void SInput::update()
{
	while (window.pollEvent(m_event))
	{
		ImGui::SFML::ProcessEvent(window, m_event);

		get_window_event();
		get_mouse_event();
		get_key_event();
	}

	if (!enabled) return;
	if (m_moved)
	{
		const auto  player = EntityManager::get().get_player();
		auto        vec    = player->transform->get_velocity();
		const float spdMax = player->info->player_info->player_speed;
		vec += m_move * spdMax;
		vec = Vec2{
			clamp(vec.x, -spdMax, spdMax),
			clamp(vec.y, -spdMax, spdMax)
		};
		EntityManager::get().get_player()->transform->velocity = vec;

		m_move  = vec2_zero;
		m_moved = false;
	}
}

void SInput::get_window_event()
{
	if (m_event.type == sf::Event::Closed) window.close();

	if (m_event.type == sf::Event::LostFocus)
	{
		GameEngine::get().pause();
	}

	if (m_event.type == sf::Event::GainedFocus)
	{
		GameEngine::get().resume();
	}

	if (m_event.type == sf::Event::Resized)
	{
		const sf::Vector2u size{m_event.size.width, m_event.size.height};
		window.setSize(size);
		window_size = size;
	}
}

void SInput::get_mouse_event() const
{
	if (m_event.type == sf::Event::MouseButtonPressed)
	{
		if (GameEngine::game_over_predicate())
		{
			GameEngine::get().reset();
		}
	}

	// if (m_event.type == sf::Event::MouseButtonReleased);
}

void SInput::get_key_event()
{
	using namespace sf;
	const std::shared_ptr<Entity> player = EntityManager::get().get_player();
	if (m_event.type == Event::KeyPressed)
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			GameEngine::get().paused ?
					GameEngine::get().resume() :
					GameEngine::get().pause();
		}
		if (!enabled) return;
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_move -= vec2_unit_x;
			m_moved = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_move += vec2_unit_x;
			m_moved = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
		{
			m_move += vec2_unit_y;
			m_moved = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
		{
			m_move -= vec2_unit_y;
			m_moved = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			fire();
		}
	}

	if (m_event.type == Event::KeyReleased) {}
}
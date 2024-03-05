#include "../stdafx.h"
#include "SInterface.h"

#include "../Entities/Entity.h"
#include "../Components/Transform.hpp"

void SInterface::initialize(const std::string& font_file)
{
	if (!m_font.loadFromFile(font_file))
	{
		error("Error loading main font!", 1);
	}
	create_text("Health Point", Vec2{window_size.x - 100.f, 10.f});
	create_text("Health", Vec2{window_size.x - 400.f, 10.f});

	create_text("Score Count", Vec2{10.f, window_size.y - 40.f});
	create_text("Score", Vec2{10.f, window_size.y - 80.f});

	create_text("Instance Count", Vec2{window_size.x - 150.f, window_size.y - 40.f});
	create_text("Showing Count:", Vec2{window_size.x - 450.f, window_size.y - 40.f});

	create_text("Reserved Instance Count", Vec2{window_size.x - 150.f, window_size.y - 80.f});
	create_text("Pool Count:", Vec2{window_size.x - 450.f, window_size.y - 80.f});

	create_text("Total Count", Vec2{window_size.x - 150.f, window_size.y - 120.f});
	create_text("Total Instances:", Vec2{window_size.x - 450.f, window_size.y - 120.f});

	create_text("Game Over", window_size / 2, 120);
	sf::FloatRect bounds = m_texts["Game Over"].getLocalBounds();
	sf::Vector2f  pos    = m_texts["Game Over"].getPosition();
	m_texts["Game Over"].setPosition(pos.x - bounds.width / 2, pos.y - bounds.height);
	m_texts["Game Over"].setFillColor(sf::Color::Transparent);
	m_texts["Game Over"].setOutlineColor(sf::Color::Transparent);

	create_text("Paused", window_size / 2, 120);
	bounds = m_texts["Paused"].getLocalBounds();
	pos    = m_texts["Paused"].getPosition();
	m_texts["Paused"].setPosition(pos.x - bounds.width / 2, pos.y - bounds.height);
	m_texts["Paused"].setFillColor(sf::Color::Transparent);
	m_texts["Paused"].setOutlineColor(sf::Color::Transparent);

	ImGui::SFML::Init(window);
	const ImGuiIO& io = ImGui::GetIO();
	m_uiFont          = io.Fonts->AddFontFromFileTTF(font_file.c_str(), 20);
	ImGui::SFML::UpdateFontTexture();
}

void SInterface::create_text(
	const string&  key, const Vec2&       pos,
	const unsigned size, const sf::Color& color)
{
	if (m_texts.find(key) != m_texts.end())
	{
		error("Error creating text" + key, 2);
	}

	m_texts[key].setFont(m_font);
	m_texts[key].setPosition(pos.x, pos.y);
	m_texts[key].setCharacterSize(size);
	m_texts[key].setFillColor(color);
	m_texts[key].setOutlineColor(m_outlineColor);
	m_texts[key].setOutlineThickness(1.f);
	m_texts[key].setString(key);
}

void SInterface::delete_text(const string& name)
{
	if (m_texts.find(name) != m_texts.end())
	{
		m_texts.erase(name);
	}
}

const map<string, sf::Text>& SInterface::get_texts()
{
	return m_texts;
}

void SInterface::game_over(const bool flag)
{
	m_texts["Game Over"].setFillColor(flag ? sf::Color::White : sf::Color::Transparent);
	m_texts["Game Over"].setOutlineColor(flag ? m_outlineColor : sf::Color::Transparent);
}

void SInterface::pause(const bool flag)
{
	m_texts["Paused"].setFillColor(flag ? sf::Color::White : sf::Color::Transparent);
	m_texts["Paused"].setOutlineColor(flag ? m_outlineColor : sf::Color::Transparent);
}

void SInterface::update()
{
	ImGui::SFML::Update(window, delta_clock.restart());
	update_player();
	update_texts();
	window.setTitle("FPS: " + std::to_string(1.f / delta_time));
}

void SInterface::update_player() const
{
	const auto& player     = EntityManager::get().get_player();
	const auto& playerInfo = player->info->player_info;

	ImGui::Begin("Player Info");
	ImGui::PushFont(m_uiFont);
	ImGui::Text("PLAYER CONTROL");
	ImGui::SliderFloat("Player Speed",
	                   &playerInfo->player_speed, 500.f, 2000.f);
	ImGui::SliderFloat("Movement Friction",
	                   &player->transform->friction, 0.f, 10.f);

	ImGui::Text("BULLET CONTROL");
	ImGui::SliderFloat("Bullet Speed",
	                   &playerInfo->bullet_speed, 100.f, 1000.f);
	ImGui::SliderInt("Bullet Count",
	                 &playerInfo->fire_dir, 1, 100);
	ImGui::PopFont();
	ImGui::End();
}

void SInterface::update_texts()
{
	std::string str = trimming_number
			(EntityManager::get().get_player()->info->player_info->score, 8);
	m_texts["Score Count"].setString(str);

	str = trimming_number
			(static_cast<int>(EntityManager::get().get_entities().size()), 8);
	m_texts["Instance Count"].setString(str);

	str = trimming_number
			(static_cast<int>(EntityManager::get().get_deleted_count()), 8);
	m_texts["Reserved Instance Count"].setString(str);

	str = trimming_number
			(static_cast<int>(EntityManager::get().get_entity_count()), 8);
	m_texts["Total Count"].setString(str);

	str = trimming_number
			(EntityManager::get().get_player()->info->player_info->health, 4, ' ');
	m_texts["Health Point"].setString(str);
}
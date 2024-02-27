#include "../stdafx.h"
#include "SInterface.h"

#include "../Entities/Entity.h"
#include "../Components/Transform.hpp"

void SInterface::create_font(const string& name, const string& filepath)
{
    string err = "";

    if (m_fonts.at(name) != nullptr)
    {
        err = "Font already exists: " + name;
        goto font_creation_error;
    }

    m_fonts.at(name) = make_shared<sf::Font>();

    if (!m_fonts.at(name)->loadFromFile(filepath))
    {
        err = "Font file doesn't exists at: " + filepath;
        goto font_creation_error;
    }
    return;

font_creation_error:
    {
        cerr << err << "\n";
        quick_exit(-1);
    }
}

shared_ptr<sf::Text> SInterface::create_text(
    const wstring& text, int size, const string& font_name)
{
    const shared_ptr<sf::Font> font = m_fonts.at(font_name);
    auto                       obj  = std::make_shared<sf::Text>(text, *font, size);
    m_texts.insert({m_textId++, obj});
    m_textsPtr.insert({obj, m_textId});

    return obj;
}

void SInterface::delete_text(const std::shared_ptr<sf::Text>& obj)
{
    const auto& id = m_textsPtr.at(obj);
    m_texts.erase(id);
    m_textsPtr.erase(obj);
}

void SInterface::delete_text(const size_t id)
{
    const auto& obj = m_texts.at(id);
    m_textsPtr.erase(obj);
    m_texts.erase(id);
}

void SInterface::update()
{
    ImGui::SFML::Update(window, delta_clock.restart());
    update_player();
}

void SInterface::update_player()
{
    const auto& player     = EntityManager::get().get_player();
    const auto& playerInfo = player->info->player_info;

    ImGui::Begin("Player Info");
    ImGui::SliderInt("Player fire direction count",
                     &playerInfo->fire_dir_count, 1, 100);
	ImGui::End();
}

void SInterface::reset()
{
    m_textId = 0;
    m_texts.clear();
    m_textsPtr.clear();
    m_fonts.clear();
}

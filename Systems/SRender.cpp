#include "../stdafx.h"
#include "SRender.h"
#include "../Components/Shape.h"

void SRender::set_background(const sf::Color color)
{
    m_background = color;
}

void SRender::set_background(const int r, const int g, const int b)
{
    m_background = sf::Color(static_cast<sf::Uint8>(r),
                             static_cast<sf::Uint8>(g),
                             static_cast<sf::Uint8>(b));
}

void SRender::update() const
{
    if (!enabled)
        return;

    window.clear(m_background);
    render(EntityManager::get().get_entities());
    ImGui::SFML::Render(window);
    window.display();
}

void SRender::render(const ENTITY_SET& entities)
{
    for(auto iter = entities.begin(); iter != entities.end(); ++iter)
    {
        window.draw((*iter)->shape->circle);
    }
}

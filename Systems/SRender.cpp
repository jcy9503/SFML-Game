#include "../stdafx.h"
#include "SRender.h"

#include "SInterface.h"
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
	window.clear(m_background);
    render_objects();
	render_uis();
    window.display();
}

void SRender::render_objects()
{
	render_entities("Enemy");
	render_entities("Bullet");
	render_entities("Player");
}

void SRender::render_entities(const std::string& tag)
{
	const ENTITY_SET& entities = EntityManager::get().get_entities(tag);
	
	for(const auto& entity : entities)
	{
		window.draw(entity->shape->circle);
		Shape::update_rotation(*entity->shape);
	}
}

void SRender::render_uis()
{
	const auto& texts = SInterface::get().get_texts();
	for (const auto& [key, text] : texts)
	{
		window.draw(text);
	}
	ImGui::SFML::Render(window);
}

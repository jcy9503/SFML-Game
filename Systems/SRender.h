#pragma once
#include "../Entities/Entity.h"

/* Render System class
 * -------------------
 * - Singleton class
 * - Contains only static methods dealing with entities
 */

class SRender
{
    SRender()  = default;
    ~SRender() = default;

    sf::Color m_background = sf::Color::Black;

public:
    static SRender& get()
    {
        static SRender renderSystem;
        return renderSystem;
    }

    SRender(SRender const&)            = delete;
    SRender(SRender&&)                 = delete;
    SRender& operator=(SRender const&) = delete;
    SRender& operator=(SRender&&)      = delete;

    void set_background(sf::Color color);
    void set_background(int r, int g, int b);

    void        update() const;
    static void render(const ENTITY_SET& entities);

    bool enabled = true;
};

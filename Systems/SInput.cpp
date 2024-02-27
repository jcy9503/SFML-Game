#include "../stdafx.h"
#include "SInput.h"
#include "SPhysics.h"
#include "SRender.h"
#include "../Entities/Behavior.hpp"
#include "../Components/Transform.hpp"

void SInput::update()
{
    while (window.pollEvent(m_event))
    {
        ImGui::SFML::ProcessEvent(window, m_event);
        
        get_window_event();

        if (!enabled)
            break;

        get_mouse_event();
        get_key_event();
    }

    if(m_move != vec2_zero)
    {
        EntityManager::get().get_player()->transform->direction = m_move;
        m_move = vec2_zero;
    }
}

void SInput::get_window_event()
{
    if (m_event.type == sf::Event::Closed)
        window.close();
/*
    if (m_event.type == sf::Event::LostFocus)
    {
        enabled           = false;
        SRender::get().enabled  = false;
        SPhysics::get().enabled = false;
    }

    if (m_event.type == sf::Event::GainedFocus)
    {
        enabled           = true;
        SRender::get().enabled  = true;
        SPhysics::get().enabled = true;
    }

    if (m_event.type == sf::Event::Resized)
    {
        const sf::Vector2u size{m_event.size.width, m_event.size.height};
        window.setSize(size);
        window_size = size;
    }*/
}

void SInput::get_mouse_event()
{
    // if (m_event.type == sf::Event::MouseButtonPressed);
    // // TODO
    //
    // if (m_event.type == sf::Event::MouseButtonReleased);
    // // TODO
}

void SInput::get_key_event()
{
    const std::shared_ptr<Entity> player = EntityManager::get().get_player();
    if (m_event.type == sf::Event::KeyPressed)
    {
        switch (m_event.key.code)
        {
        case sf::Keyboard::A: m_move -= vec2_unit_x;
        //case sf::Keyboard::B: break;
        //case sf::Keyboard::C: break;
        case sf::Keyboard::D: m_move += vec2_unit_x;
        //case sf::Keyboard::E: break;
        // case sf::Keyboard::F: break;
        // case sf::Keyboard::G: break;
        // case sf::Keyboard::H: break;
        // case sf::Keyboard::I: break;
        // case sf::Keyboard::J: break;
        // case sf::Keyboard::K: break;
        // case sf::Keyboard::L: break;
        // case sf::Keyboard::M: break;
        // case sf::Keyboard::N: break;
        // case sf::Keyboard::O: break;
        // case sf::Keyboard::P: break;
        // case sf::Keyboard::Q: break;
        // case sf::Keyboard::R: break;
        case sf::Keyboard::S: m_move += vec2_unit_y;
        // case sf::Keyboard::T: break;
        // case sf::Keyboard::U: break;
        // case sf::Keyboard::V: break;
        case sf::Keyboard::W: m_move -= vec2_unit_y;
        // case sf::Keyboard::X: break;
        // case sf::Keyboard::Y: break;
        // case sf::Keyboard::Z: break;
        // case sf::Keyboard::Num0: break;
        // case sf::Keyboard::Num1: break;
        // case sf::Keyboard::Num2: break;
        // case sf::Keyboard::Num3: break;
        // case sf::Keyboard::Num4: break;
        // case sf::Keyboard::Num5: break;
        // case sf::Keyboard::Num6: break;
        // case sf::Keyboard::Num7: break;
        // case sf::Keyboard::Num8: break;
        // case sf::Keyboard::Num9: break;
        // case sf::Keyboard::Escape: break;
        // case sf::Keyboard::LControl: break;
        // case sf::Keyboard::LShift: break;
        // case sf::Keyboard::LAlt: break;
        // case sf::Keyboard::LSystem: break;
        // case sf::Keyboard::RControl: break;
        // case sf::Keyboard::RShift: break;
        // case sf::Keyboard::RAlt: break;
        // case sf::Keyboard::RSystem: break;
        // case sf::Keyboard::Menu: break;
        // case sf::Keyboard::LBracket: break;
        // case sf::Keyboard::RBracket: break;
        // case sf::Keyboard::Semicolon: break;
        // case sf::Keyboard::Comma: break;
        // case sf::Keyboard::Period: break;
        // case sf::Keyboard::Apostrophe: break;
        // case sf::Keyboard::Slash: break;
        // case sf::Keyboard::Backslash: break;
        // case sf::Keyboard::Grave: break;
        // case sf::Keyboard::Equal: break;
        // case sf::Keyboard::Hyphen: break;
        case sf::Keyboard::Space: fire();
        // case sf::Keyboard::Enter: break;
        // case sf::Keyboard::Backspace: break;
        // case sf::Keyboard::Tab: break;
        // case sf::Keyboard::PageUp: break;
        // case sf::Keyboard::PageDown: break;
        // case sf::Keyboard::End: break;
        // case sf::Keyboard::Home: break;
        // case sf::Keyboard::Insert: break;
        // case sf::Keyboard::Delete: break;
        // case sf::Keyboard::Add: break;
        // case sf::Keyboard::Subtract: break;
        // case sf::Keyboard::Multiply: break;
        // case sf::Keyboard::Divide: break;
        // case sf::Keyboard::Left: break;
        // case sf::Keyboard::Right: break;
        // case sf::Keyboard::Up: break;
        // case sf::Keyboard::Down: break;
        // case sf::Keyboard::Numpad0: break;
        // case sf::Keyboard::Numpad1: break;
        // case sf::Keyboard::Numpad2: break;
        // case sf::Keyboard::Numpad3: break;
        // case sf::Keyboard::Numpad4: break;
        // case sf::Keyboard::Numpad5: break;
        // case sf::Keyboard::Numpad6: break;
        // case sf::Keyboard::Numpad7: break;
        // case sf::Keyboard::Numpad8: break;
        // case sf::Keyboard::Numpad9: break;
        // case sf::Keyboard::F1: break;
        // case sf::Keyboard::F2: break;
        // case sf::Keyboard::F3: break;
        // case sf::Keyboard::F4: break;
        // case sf::Keyboard::F5: break;
        // case sf::Keyboard::F6: break;
        // case sf::Keyboard::F7: break;
        // case sf::Keyboard::F8: break;
        // case sf::Keyboard::F9: break;
        // case sf::Keyboard::F10: break;
        // case sf::Keyboard::F11: break;
        // case sf::Keyboard::F12: break;
        // case sf::Keyboard::F13: break;
        // case sf::Keyboard::F14: break;
        // case sf::Keyboard::F15: break;
        // case sf::Keyboard::Pause: break;
        // case sf::Keyboard::KeyCount: break;
        // case sf::Keyboard::Unknown: break;
        default: ;
        }
    }

    if (m_event.type == sf::Event::KeyReleased)
    {
        switch (m_event.key.code)
        {
        // case sf::Keyboard::A: break;
        // case sf::Keyboard::B: break;
        // case sf::Keyboard::C: break;
        // case sf::Keyboard::D: break;
        // case sf::Keyboard::E: break;
        // case sf::Keyboard::F: break;
        // case sf::Keyboard::G: break;
        // case sf::Keyboard::H: break;
        // case sf::Keyboard::I: break;
        // case sf::Keyboard::J: break;
        // case sf::Keyboard::K: break;
        // case sf::Keyboard::L: break;
        // case sf::Keyboard::M: break;
        // case sf::Keyboard::N: break;
        // case sf::Keyboard::O: break;
        // case sf::Keyboard::P: break;
        // case sf::Keyboard::Q: break;
        // case sf::Keyboard::R: break;
        // case sf::Keyboard::S: break;
        // case sf::Keyboard::T: break;
        // case sf::Keyboard::U: break;
        // case sf::Keyboard::V: break;
        // case sf::Keyboard::W: break;
        // case sf::Keyboard::X: break;
        // case sf::Keyboard::Y: break;
        // case sf::Keyboard::Z: break;
        // case sf::Keyboard::Num0: break;
        // case sf::Keyboard::Num1: break;
        // case sf::Keyboard::Num2: break;
        // case sf::Keyboard::Num3: break;
        // case sf::Keyboard::Num4: break;
        // case sf::Keyboard::Num5: break;
        // case sf::Keyboard::Num6: break;
        // case sf::Keyboard::Num7: break;
        // case sf::Keyboard::Num8: break;
        // case sf::Keyboard::Num9: break;
        // case sf::Keyboard::Escape: break;
        // case sf::Keyboard::LControl: break;
        // case sf::Keyboard::LShift: break;
        // case sf::Keyboard::LAlt: break;
        // case sf::Keyboard::LSystem: break;
        // case sf::Keyboard::RControl: break;
        // case sf::Keyboard::RShift: break;
        // case sf::Keyboard::RAlt: break;
        // case sf::Keyboard::RSystem: break;
        // case sf::Keyboard::Menu: break;
        // case sf::Keyboard::LBracket: break;
        // case sf::Keyboard::RBracket: break;
        // case sf::Keyboard::Semicolon: break;
        // case sf::Keyboard::Comma: break;
        // case sf::Keyboard::Period: break;
        // case sf::Keyboard::Apostrophe: break;
        // case sf::Keyboard::Slash: break;
        // case sf::Keyboard::Backslash: break;
        // case sf::Keyboard::Grave: break;
        // case sf::Keyboard::Equal: break;
        // case sf::Keyboard::Hyphen: break;
        // case sf::Keyboard::Space: break;
        // case sf::Keyboard::Enter: break;
        // case sf::Keyboard::Backspace: break;
        // case sf::Keyboard::Tab: break;
        // case sf::Keyboard::PageUp: break;
        // case sf::Keyboard::PageDown: break;
        // case sf::Keyboard::End: break;
        // case sf::Keyboard::Home: break;
        // case sf::Keyboard::Insert: break;
        // case sf::Keyboard::Delete: break;
        // case sf::Keyboard::Add: break;
        // case sf::Keyboard::Subtract: break;
        // case sf::Keyboard::Multiply: break;
        // case sf::Keyboard::Divide: break;
        // case sf::Keyboard::Left: break;
        // case sf::Keyboard::Right: break;
        // case sf::Keyboard::Up: break;
        // case sf::Keyboard::Down: break;
        // case sf::Keyboard::Numpad0: break;
        // case sf::Keyboard::Numpad1: break;
        // case sf::Keyboard::Numpad2: break;
        // case sf::Keyboard::Numpad3: break;
        // case sf::Keyboard::Numpad4: break;
        // case sf::Keyboard::Numpad5: break;
        // case sf::Keyboard::Numpad6: break;
        // case sf::Keyboard::Numpad7: break;
        // case sf::Keyboard::Numpad8: break;
        // case sf::Keyboard::Numpad9: break;
        // case sf::Keyboard::F1: break;
        // case sf::Keyboard::F2: break;
        // case sf::Keyboard::F3: break;
        // case sf::Keyboard::F4: break;
        // case sf::Keyboard::F5: break;
        // case sf::Keyboard::F6: break;
        // case sf::Keyboard::F7: break;
        // case sf::Keyboard::F8: break;
        // case sf::Keyboard::F9: break;
        // case sf::Keyboard::F10: break;
        // case sf::Keyboard::F11: break;
        // case sf::Keyboard::F12: break;
        // case sf::Keyboard::F13: break;
        // case sf::Keyboard::F14: break;
        // case sf::Keyboard::F15: break;
        // case sf::Keyboard::Pause: break;
        // case sf::Keyboard::KeyCount: break;
        // case sf::Keyboard::Unknown: break;
        default: ;
        }
    }
}

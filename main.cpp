#include "stdafx.h"

#include "Engine/GameEngine.h"

int main()
{
    GameEngine::initialize();
    
    while (window.isOpen())
    {
        GameEngine::main_loop();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

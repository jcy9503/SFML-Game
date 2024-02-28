#include "stdafx.h"

#include "Engine/GameEngine.h"

int main()
{
    GameEngine::get().initialize();
    
    while (window.isOpen())
    {
        GameEngine::get().main_loop();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

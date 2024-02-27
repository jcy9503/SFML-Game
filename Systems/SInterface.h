#pragma once

using namespace std;

class SInterface
{
    SInterface() = default;
    ~SInterface() = default;
    
    map<string, shared_ptr<sf::Font>> m_fonts    = {};
    size_t                            m_textId   = 0;
    map<size_t, shared_ptr<sf::Text>> m_texts    = {};
    map<shared_ptr<sf::Text>, size_t> m_textsPtr = {};

public:
    static SInterface& get()
    {
        static SInterface interfaceSystem;
        return interfaceSystem;
    }

    SInterface(SInterface const&) = delete;
    SInterface(SInterface&&) = delete;
    SInterface& operator=(SInterface const&) = delete;
    SInterface& operator=(SInterface&&) = delete;
    
    void                      create_font(const std::string& name, const std::string& filepath);
    std::shared_ptr<sf::Text> create_text(const std::wstring& text, int size, const std::string& font_name);
    void                      delete_text(const std::shared_ptr<sf::Text>& obj);
    void                      delete_text(size_t id);
    void                      update();
    void                      update_player();
    void                      reset();
};

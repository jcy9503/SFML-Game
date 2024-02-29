#pragma once

using namespace std;

class SInterface
{
	SInterface()  = default;
	~SInterface() = default;

	sf::Font              m_font;
	ImFont*               m_uiFont = nullptr;
	map<string, sf::Text> m_texts;
	sf::Color             m_outlineColor = sf::Color::Magenta;

public:
	static SInterface& get()
	{
		static SInterface interfaceSystem;
		return interfaceSystem;
	}

	SInterface(SInterface const&)            = delete;
	SInterface(SInterface&&)                 = delete;
	SInterface& operator=(SInterface const&) = delete;
	SInterface& operator=(SInterface&&)      = delete;

	void initialize(const std::string& font_file);
	void update();
	void update_player() const;
	void update_texts();
	void create_text(
		const std::string& key, const Vec2& pos, unsigned size = 30,
		const sf::Color&   color                               = sf::Color::White);
	void                         delete_text(const string& name);
	const map<string, sf::Text>& get_texts();
	void                         game_over(bool flag);
	void                         pause(bool flag);
};
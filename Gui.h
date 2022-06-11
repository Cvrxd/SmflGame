#pragma once

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace GUI
{
	class Button
	{
	private:
		//vaeiables
		// core
		short unsigned buttonState;
		short unsigned id;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color texActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		sf::RectangleShape shape;

		sf::Font*  font;
		sf::Text   text;

	public:
		Button(const float& x, const float& y, const float& width, const float& height,
			sf::Font* font, const std::string& text, const unsigned& charcter_size,
			const sf::Color& text_idle_color, const sf::Color& text_hover_color, const sf::Color& text_active_color,
			const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor, 
			const sf::Color& outlineIdleColor = sf::Color::Transparent, const sf::Color& outlineHoverColor = sf::Color::Transparent, const sf::Color& outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0)                  noexcept;

		Button              (const GUI::Button& other)       noexcept;
		Button              (GUI::Button&& other)            noexcept;
		Button& operator=   (const GUI::Button& other)       noexcept;
		Button& operator=   (GUI::Button&& other)            noexcept;

		~Button();

		//Accessors
		const short unsigned&	getId()         const;
		const bool				isPressed()     const;
		const sf::Vector2f      getPosition()   const;

		std::string				getText();
		sf::FloatRect			getGlobalBounds();
		sf::Text&				getSfText();

		//Seters
		void setText  (std::string text);
		void setId    (const short unsigned& id);

		//Functions
		void update   (const sf::Vector2i& mousePosition);
		void render   (sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		using VectorButtons = std::vector<std::shared_ptr<GUI::Button>>;
		using ButtonPtr     = std::shared_ptr<GUI::Button>;

		//Variables
		bool           showDropBox;
		sf::Font&      font;

		float          keyTime;
		float          keyTimeMax;

		ButtonPtr      activeBox;
		VectorButtons  dropBox;
		 
	public:
		DropDownList(const float& x, const float& y, const float& width, const float& hight, 
			sf::Font& font, std::string text_list[], const unsigned& number_of_elements, const unsigned& default_index = 0) noexcept;
		~DropDownList();

		//Accessors
		const unsigned short&  getActiveBoxId() const;
		const sf::Vector2f     getPosition() const;

		//Functions
		const bool  getKeyTime     ();
		void        updateKeyTime  (const float& dt);
		void        update         (const sf::Vector2i& mousePosition, const float& dt);
		void        render         (sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		using ButtonPtr = std::shared_ptr<GUI::Button>;

		//Variables
		bool       active;
		bool       hiden;
		unsigned   gridSize;

		float      keyTime;
		float      keyTimeMax;

		ButtonPtr  hideButton;

		sf::Sprite          sheet;
		sf::IntRect         textureRect;
		sf::RectangleShape  selector;
		sf::RectangleShape  bounds;

		sf::Vector2u        mousePosGrid;
	
		//Functions
		void initBounds                (const float& x, const float& y, const float& width_bounds, const float& height_bounds);
		void initSpriteSheet           (const float& x, const float& y, const sf::Texture& texture_sheet);
		void initSelector_TextureRect  (const float& x, const float& y);

	public:
		TextureSelector (const float& x, const float& y, const float& width_bounds, const float& hight_bounds, 
			const unsigned& gridSize, const sf::Texture& texture_sheet, sf::Font& font) noexcept;

		~TextureSelector();

		//Accessors
		const sf::IntRect&	getTextureRect()   const;
		const bool&			getActive()        const;
		const bool			getKeyTime();

		//Fuctions
		void updateKeyTime  (const float& dt);
		void update         (const sf::Vector2i& mousePosWindow, const float& dt);
		void render         (sf::RenderTarget& target);
	};
}

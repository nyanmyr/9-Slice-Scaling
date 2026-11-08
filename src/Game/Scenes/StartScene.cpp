#include <SFML/Graphics.hpp>

#include <optional>
#include <queue>
#include <print>

#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

class SlicedSprite : public sf::Drawable, public sf::Transformable
{
private:
	sf::Texture texture;
	std::optional<sf::Sprite> topLeft;
	std::optional<sf::Sprite> top;
	std::optional<sf::Sprite> topRight;
	std::optional<sf::Sprite> left;
	std::optional<sf::Sprite> middle;
	std::optional<sf::Sprite> right;
	std::optional<sf::Sprite> bottomLeft;
	std::optional<sf::Sprite> bottom;
	std::optional<sf::Sprite> bottomRight;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();

		target.draw(*topLeft, states);
		target.draw(*top, states);
		target.draw(*topRight, states);
		target.draw(*left, states);
		target.draw(*middle, states);
		target.draw(*right, states);
		target.draw(*bottomLeft, states);
		target.draw(*bottom, states);
		target.draw(*bottomRight, states);
	}

	void setDefaults
	(
		const sf::IntRect& rect,
		std::optional<sf::Sprite>& sprite
	)
	{
		sprite->setPosition
		(
			sf::Vector2f
			{
				static_cast<float>(rect.position.x),
				static_cast<float>(rect.position.y)
			}
		);

		sprite->setOrigin
		(
			sf::Vector2f
			{
				static_cast<float>(texture.getSize().x * 0.5f),
				static_cast<float>(texture.getSize().y * 0.5f),
			}
		);

		sprite->setTextureRect
		(
			sf::IntRect
			{
				sf::Vector2i
				{
					rect.position.x,
					rect.position.y,
				},
				sf::Vector2i
				{
					rect.size.x,
					rect.size.y,
				}
			}
		);
	}

public:
	SlicedSprite
	(
		const sf::Texture& texture,
		const sf::IntRect& topLeftRect,
		const sf::IntRect& topRect,
		const sf::IntRect& topRightRect,
		const sf::IntRect& leftRect,
		const sf::IntRect& middleRect,
		const sf::IntRect& rightRect,
		const sf::IntRect& bottomLeftRect,
		const sf::IntRect& bottomRect,
		const sf::IntRect& bottomRightRect
	) : texture(texture)
	{
		topLeft.emplace(texture);
		top.emplace(texture);
		topRight.emplace(texture);
		left.emplace(texture);
		middle.emplace(texture);
		right.emplace(texture);
		bottomLeft.emplace(texture);
		bottom.emplace(texture);
		bottomRight.emplace(texture);

		setDefaults
		(
			topLeftRect,
			topLeft
		);

		setDefaults
		(
			topRect,
			top
		);

		setDefaults
		(
			topRightRect,
			topRight
		);

		setDefaults
		(
			leftRect,
			left
		);

		setDefaults
		(
			middleRect,
			middle
		);

		setDefaults
		(
			rightRect,
			right
		);

		setDefaults
		(
			bottomLeftRect,
			bottomLeft
		);

		setDefaults
		(
			bottomRect,
			bottom
		);

		setDefaults
		(
			bottomRightRect,
			bottomRight
		);
	}
};

void startScene()
{

	// game state variables
	sf::Clock clock;
	std::queue<Entity> renderQueue;

	Component::Singleton::TexturesContainer loadedTextures{};

	// onstart systems
	Start::setText();
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

	sf::Texture texture(SPRITES_PATH "nacre_button.png");

	SlicedSprite splicedSprite
	(
		texture,
		sf::IntRect
		{
			sf::Vector2i
			{
				0,
				0,
			},
			sf::Vector2i
			{
				60,
				60,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				60,
				0,
			},
			sf::Vector2i
			{
				392,
				60,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				452,
				0,
			},
			sf::Vector2i
			{
				60,
				60,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				0,
				60,
			},
			sf::Vector2i
			{
				60,
				392,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				60,
				60,
			},
			sf::Vector2i
			{
				392,
				392,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				452,
				60,
			},
			sf::Vector2i
			{
				60,
				392,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				0,
				452,
			},
			sf::Vector2i
			{
				60,
				60,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				60,
				452,
			},
			sf::Vector2i
			{
				392,
				60,
			}
		},
		sf::IntRect
		{
			sf::Vector2i
			{
				452,
				452,
			},
			sf::Vector2i
			{
				60,
				60,
			}
		}
	);

	//std::println();

	while (Asset::window().isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		const auto& pixelPos = sf::Mouse::getPosition(Asset::window());
		const auto& worldPos = Asset::window().mapPixelToCoords(pixelPos);

		while (const std::optional event = Asset::window().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				Asset::window().close();
			}
		}

		// update systems
		Update::move(dt);

		Asset::window().clear();
		// render systems
		Render::doZIndex(renderQueue);
		Render::render
		(
			Asset::window(),
			renderQueue
		);

		Asset::window().draw(splicedSprite);

		Asset::window().display();
	}
}
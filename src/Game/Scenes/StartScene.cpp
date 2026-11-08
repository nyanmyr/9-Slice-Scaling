#include <SFML/Graphics.hpp>

#include <optional>
#include <queue>
#include <print>

#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

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

	std::optional<sf::Sprite> topLeft;
	topLeft.emplace(texture);

	topLeft->setPosition
	(
		sf::Vector2f
		{
			0.f,
			0.f
		}
	);

	topLeft->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(topLeft->getTextureRect().getCenter().x),
			static_cast<float>(topLeft->getTextureRect().getCenter().y),
		}
	);

	topLeft->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> top;
	top.emplace(texture);

	top->setPosition
	(
		sf::Vector2f
		{
			60.f,
			0.f
		}
	);

	top->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(top->getTextureRect().getCenter().x),
			static_cast<float>(top->getTextureRect().getCenter().y),
		}
		);

	top->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> topRight;
	topRight.emplace(texture);

	topRight->setPosition
	(
		sf::Vector2f
		{
			452.f,
			0.f
		}
	);

	topRight->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(topRight->getTextureRect().getCenter().x),
			static_cast<float>(topRight->getTextureRect().getCenter().y),
		}
		);

	topRight->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> left;
	left.emplace(texture);

	left->setPosition
	(
		sf::Vector2f
		{
			0.f,
			60.f
		}
	);

	left->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(left->getTextureRect().getCenter().x),
			static_cast<float>(left->getTextureRect().getCenter().y),
		}
	);

	left->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> middle;
	middle.emplace(texture);

	middle->setPosition
	(
		sf::Vector2f
		{
			60.f,
			60.f
		}
	);

	middle->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(middle->getTextureRect().getCenter().x),
			static_cast<float>(middle->getTextureRect().getCenter().y),
		}
	);

	middle->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> right;
	right.emplace(texture);

	right->setPosition
	(
		sf::Vector2f
		{
			452.f,
			60.f
		}
	);

	right->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(right->getTextureRect().getCenter().x),
			static_cast<float>(right->getTextureRect().getCenter().y),
		}
		);

	right->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> bottomLeft;
	bottomLeft.emplace(texture);

	bottomLeft->setPosition
	(
		sf::Vector2f
		{
			0.f,
			452.f
		}
	);

	bottomLeft->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(bottomLeft->getTextureRect().getCenter().x),
			static_cast<float>(bottomLeft->getTextureRect().getCenter().y),
		}
		);

	bottomLeft->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> bottom;
	bottom.emplace(texture);

	bottom->setPosition
	(
		sf::Vector2f
		{
			60.f,
			452.f
		}
	);

	bottom->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(bottom->getTextureRect().getCenter().x),
			static_cast<float>(bottom->getTextureRect().getCenter().y),
		}
		);

	bottom->setTextureRect
	(
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
		}
	);

	std::optional<sf::Sprite> bottomRight;
	bottomRight.emplace(texture);

	bottomRight->setPosition
	(
		sf::Vector2f
		{
			452.f,
			452.f
		}
	);

	bottomRight->setOrigin
	(
		sf::Vector2f
		{
			static_cast<float>(bottomRight->getTextureRect().getCenter().x),
			static_cast<float>(bottomRight->getTextureRect().getCenter().y),
		}
		);

	bottomRight->setTextureRect
	(
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

		Asset::window().draw(*topLeft);
		Asset::window().draw(*top);
		Asset::window().draw(*topRight);
		Asset::window().draw(*left);
		Asset::window().draw(*middle);
		Asset::window().draw(*right);
		Asset::window().draw(*bottomLeft);
		Asset::window().draw(*bottom);
		Asset::window().draw(*bottomRight);

		Asset::window().display();
	}
}
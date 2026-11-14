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

	Entity slicedSprite = EntityMaker::slicedSprite
	(
		Component::Color{ .data = sf::Color::White },
		Component::ZIndex{ .index = static_cast<int>(Enum::Layer::MAIN) },
		Component::Texture{ .data = Enum::Texture::NACRE_BUTTON },
		Component::Position
		{
			.x = 0.0,
			.y = 0.0,
		},
		Component::Transform
		{
			.width = 150.0,
			.height = 150.0,
		},
		Component::OriginPoint{ .data = Enum::OriginPoint::CENTER },
		Component::SlicedSpriteRects
		{
			.topLeft = sf::IntRect
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
			.top = sf::IntRect
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
			.topRight = sf::IntRect
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
			.left = sf::IntRect
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
			.middle = sf::IntRect
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
			.right = sf::IntRect
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
			.bottomLeft = sf::IntRect
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
			.bottom = sf::IntRect
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
			.bottomRight = sf::IntRect
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
			},
		}
	);

	Component::Singleton::TexturesContainer loadedTextures{};

	// onstart systems
	Start::setText();
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::loadSlicedSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

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

		Asset::window().display();
	}
}
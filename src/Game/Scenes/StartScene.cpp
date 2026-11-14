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

	sf::IntRect topLeftRect;
	sf::IntRect topRect;
	sf::IntRect topRightRect;
	sf::IntRect leftRect;
	sf::IntRect middleRect;
	sf::IntRect rightRect;
	sf::IntRect bottomLeftRect;
	sf::IntRect bottomRect;
	sf::IntRect bottomRightRect;

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
		const sf::Vector2f& localPos,
		std::optional<sf::Sprite>& sprite
	)
	{
		sprite->setPosition(localPos);

		sprite->setOrigin
		(
			sf::Vector2f
			{
				static_cast<float>(rect.size.x * 0.5f),
				static_cast<float>(rect.size.y * 0.5f),
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
	)
		: texture(texture),
		topLeftRect(topLeftRect),
		topRect(topRect),
		topRightRect(topRightRect),
		leftRect(leftRect),
		middleRect(middleRect),
		rightRect(rightRect),
		bottomLeftRect(bottomLeftRect),
		bottomRect(bottomRect),
		bottomRightRect(bottomRightRect)
	{
		topLeft.emplace(this->texture);
		top.emplace(this->texture);
		topRight.emplace(this->texture);
		left.emplace(this->texture);
		middle.emplace(this->texture);
		right.emplace(this->texture);
		bottomLeft.emplace(this->texture);
		bottom.emplace(this->texture);
		bottomRight.emplace(this->texture);

		setDefaults
		(
			this->topLeftRect,
			sf::Vector2f
			{
				-((texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f)),
				-((texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f)),
			},
			topLeft
		);

		setDefaults
		(
			this->topRect,
			sf::Vector2f
			{
				0.f,
				-((texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f)),
			},
			top
		);

		setDefaults
		(
			this->topRightRect,
			sf::Vector2f
			{
				(texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f),
				-((texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f)),
			},
			topRight
		);

		setDefaults
		(
			this->leftRect,
			sf::Vector2f
			{
				-((texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f)),
				0.f,
			},
			left
		);

		setDefaults
		(
			this->middleRect,
			sf::Vector2f
			{
				0.f,
				0.f,
			},
			middle
		);

		setDefaults
		(
			this->rightRect,
			sf::Vector2f
			{
				(texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f),
				0.f,
			},
			right
		);

		setDefaults
		(
			this->bottomLeftRect,
			sf::Vector2f
			{
				-((texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f)),
				(texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f),
			},
			bottomLeft
		);

		setDefaults
		(
			this->bottomRect,
			sf::Vector2f
			{
				0.f,
				(texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f),
			},
			bottom
		);

		setDefaults
		(
			this->bottomRightRect,
			sf::Vector2f
			{
				(texture.getSize().x * 0.5f) - (topLeftRect.size.x * 0.5f),
				(texture.getSize().y * 0.5f) - (topLeftRect.size.y * 0.5f),
			},
			bottomRight
		);
	}

	sf::Vector2f getSize() const
	{
		return sf::Vector2f
		{
			texture.getSize().x * this->getScale().x,
			texture.getSize().y * this->getScale().y
		};
	}

	// TODO: below minimum size case
	void setSize(const sf::Vector2f& size)
	{
		std::println("New SizeX: {}", size.x);
		std::println("New SizeY: {}", size.y);

		if (size.x != texture.getSize().x * this->getScale().x)
		{
			// top, middle, bottom
			float newTopX = size.x * ((1.f + this->getScale().x) / topRect.size.x);
			float newMiddleX = size.x * ((1.f + this->getScale().x) / middleRect.size.x);
			float newBottomX = size.x * ((1.f + this->getScale().x) / bottomRect.size.x);

			//std::println("New MiddleX: {}", newMiddleX);

			top->setScale
			(
				sf::Vector2f
				{
					newTopX,
					top->getScale().y,
				}
			);

			middle->setScale
			(
				sf::Vector2f
				{
					newMiddleX,
					middle->getScale().y,
				}
			);

			bottom->setScale
			(
				sf::Vector2f
				{
					newBottomX,
					bottom->getScale().y,
				}
			);

			float newMiddleSizeX = this->getScale().x * (middleRect.size.x * middle->getScale().x);

			float topLeftSizeX = this->getScale().x * (topLeftRect.size.x * topLeft->getScale().x);
			float topRightSizeX = this->getScale().x * (topRightRect.size.x * topRight->getScale().x);
			float leftSizeX = this->getScale().x * (leftRect.size.x * left->getScale().x);
			float bottomLeftSizeX = this->getScale().x * (bottomLeftRect.size.x * bottomLeft->getScale().x);
			float bottomRightSizeX = this->getScale().x * (bottomRightRect.size.x * bottomRight->getScale().x);
			float rightSizeX = this->getScale().x * (rightRect.size.x * right->getScale().x);

			std::println("test1: {}", newMiddleSizeX);
			std::println("topLeftSizeX: {}", topLeftSizeX);

			topLeft->setPosition
			(
				sf::Vector2f
				{
					-newMiddleSizeX - topLeftSizeX,
					topLeft->getPosition().y,
				}
			);
			topRight->setPosition
			(
				sf::Vector2f
				{
					newMiddleSizeX + topRightSizeX,
					topRight->getPosition().y,
				}
			);
			left->setPosition
			(
				sf::Vector2f
				{
					-newMiddleSizeX - leftSizeX,
					left->getPosition().y,
				}
			);
			bottomLeft->setPosition
			(
				sf::Vector2f
				{
					-newMiddleSizeX - bottomLeftSizeX,
					bottomLeft->getPosition().y,
				}
			);
			bottomRight->setPosition
			(
				sf::Vector2f
				{
					newMiddleSizeX + bottomRightSizeX,
					bottomRight->getPosition().y,
				}
			);
			right->setPosition
			(
				sf::Vector2f
				{
					newMiddleSizeX + rightSizeX,
					right->getPosition().y,
				}
			);

			std::println("Width Resized!");
		}

		if (size.y != texture.getSize().y * this->getScale().y)
		{
			std::println("Height Resized!");
		}
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

	splicedSprite.setScale
	(
		sf::Vector2f
		{
			0.5f,
			0.5f
		}
	);

	std::println("SplicedSprite SizeX: {}", splicedSprite.getSize().x);
	std::println("SplicedSprite SizeY: {}", splicedSprite.getSize().y);

	//splicedSprite.setSize
	//(
	//	sf::Vector2f
	//	{
	//		splicedSprite.,
	//		0.5f
	//	}
	//);

	splicedSprite.setSize
	(
		sf::Vector2f
		{
			500.f,
			300.f
		}
	);

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
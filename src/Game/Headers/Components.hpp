#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>
#include <unordered_map>

#include "Scenes.hpp"
#include "Enums.hpp"

namespace Transformable
{
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

		void setSize(const sf::Vector2f& size)
		{
			//std::println("New SizeX: {}", size.x);
			//std::println("New SizeY: {}", size.y);

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

				//std::println("test1: {}", newMiddleSizeX);
				//std::println("topLeftSizeX: {}", topLeftSizeX);

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

				//std::println("Width Resized!");
			}

			if (size.y != texture.getSize().y * this->getScale().y)
			{
				// top, middle, bottom
				float newLeftY = size.y * ((1.f + this->getScale().y) / leftRect.size.y);
				float newMiddleY = size.y * ((1.f + this->getScale().y) / middleRect.size.y);
				float newRightY = size.y * ((1.f + this->getScale().y) / rightRect.size.y);

				//std::println("New MiddleX: {}", newMiddleX);

				left->setScale
				(
					sf::Vector2f
					{
						left->getScale().x,
						newLeftY
					}
				);

				middle->setScale
				(
					sf::Vector2f
					{
						middle->getScale().x,
						newMiddleY
					}
				);

				right->setScale
				(
					sf::Vector2f
					{
						right->getScale().x,
						newRightY
					}
				);

				float newMiddleSizeY = this->getScale().y * (middleRect.size.y * middle->getScale().y);

				float topLeftSizeY = this->getScale().y * (topLeftRect.size.y * topLeft->getScale().y);
				float topRightSizeY = this->getScale().y * (topRightRect.size.y * topRight->getScale().y);
				float topSizeY = this->getScale().y * (topRect.size.y * top->getScale().y);
				float bottomLeftSizeY = this->getScale().y * (bottomLeftRect.size.y * bottomLeft->getScale().y);
				float bottomRightSizeY = this->getScale().y * (bottomRightRect.size.y * bottomRight->getScale().y);
				float bottomSizeY = this->getScale().y * (bottomRect.size.y * bottom->getScale().y);

				topLeft->setPosition
				(
					sf::Vector2f
					{
						topLeft->getPosition().x,
						-newMiddleSizeY - topLeftSizeY
					}
				);
				topRight->setPosition
				(
					sf::Vector2f
					{
						topRight->getPosition().x,
						-newMiddleSizeY - topRightSizeY
					}
				);
				top->setPosition
				(
					sf::Vector2f
					{
						top->getPosition().x,
						-newMiddleSizeY - topSizeY
					}
				);
				bottomLeft->setPosition
				(
					sf::Vector2f
					{
						bottomLeft->getPosition().x,
						newMiddleSizeY + bottomLeftSizeY
					}
				);
				bottomRight->setPosition
				(
					sf::Vector2f
					{
						bottomRight->getPosition().x,
						newMiddleSizeY + bottomRightSizeY
					}
				);
				bottom->setPosition
				(
					sf::Vector2f
					{
						bottom->getPosition().x,
						newMiddleSizeY + bottomSizeY
					}
				);

				//std::println("Height Resized!");
			}
		}
	};
}

namespace Component {
	struct Position
	{
		double x = 0.0;
		double y = 0.0;
	};

	struct Transform
	{
		double width = 0.0;
		double height = 0.0;
	};

	struct OriginOffsets
	{
		double x = 0.0;
		double y = 0.0;
	};

	struct OriginPoint
	{
		Enum::OriginPoint data;
	};

	struct Text
	{
		std::optional<sf::Text> box{};
		std::string string = "";
		int size = 12;
		sf::Color color = sf::Color::White;
		Enum::TextFormat format = Enum::TextFormat::CENTER;
	};

	struct NextScene
	{
		Scene next = Scene::START;
	};

	struct ZIndex
	{
		int index = 0;
		bool visible = true;
	};

	struct Velocity
	{
		double minX = 0.0;
		double minY = 0.0;
		double maxX = 0.0;
		double maxY = 0.0;
		double x = 0.0;
		double y = 0.0;
	};

	struct Acceleration
	{
		double x = 0.0;
		double y = 0.0;
	};

	struct Sprite
	{
		std::optional<sf::Sprite> body{};
	};

	struct SlicedSprite
	{
		std::optional<Transformable::SlicedSprite> body{};
	};

	struct SlicedSpriteRects
	{
		sf::IntRect topLeft;
		sf::IntRect top;
		sf::IntRect topRight;
		sf::IntRect left;
		sf::IntRect middle;
		sf::IntRect right;
		sf::IntRect bottomLeft;
		sf::IntRect bottom;
		sf::IntRect bottomRight;
	};

	struct Texture
	{
		Enum::Texture data;
	};

	struct Color
	{
		sf::Color data = sf::Color::White;
	};

	namespace Singleton
	{
		struct TexturesContainer
		{
			std::unordered_map<Enum::Texture, sf::Texture> map;
		};
	}
}

#endif
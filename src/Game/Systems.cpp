#include "Headers/Systems.hpp"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <utility>
#include <vector>
#include <stdexcept>

#include "../Engine/NacreCoordinator.hpp"
#include "Headers/Components.hpp"
#include "Headers/Enums.hpp"
#include "Headers/Events.hpp"

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
namespace Start
{
	void setText()
	{
		const auto& textArray = nc().getComponentArray<Component::Text>();

		for (auto& [entity, text] : textArray->getAll())
		{
			nc().call<Event::SetTextString>
				(
					Event::SetTextString
					{ entity, text.string, text.box }
				);
			nc().call<Event::SetTextSize>
				(
					Event::SetTextSize
					{ entity, text.size, text.box }
				);
			nc().call<Event::SetTextColor>
				(
					Event::SetTextColor
					{ entity, text.color, text.box }
				);
		}
	}
	void setTextOrigin()
	{
		const auto& textArray = nc().getComponentArray<Component::Text>();

		for (auto& [entity, text] : textArray->getAll())
		{
			nc().call<Event::SetTextOrigin>
				(
					Event::SetTextOrigin
					{ entity, text }
				);
		}
	}
	void setSpriteOrigin()
	{
		const auto& originOffsetsArray = nc().getComponentArray<Component::OriginOffsets>();
		const auto& originPointArray = nc().getComponentArray<Component::OriginPoint>();

		for (auto& [entity, origin] : originOffsetsArray->getAll())
		{
			if (!originPointArray->hasData(entity)) continue;

			auto& originPoint = originPointArray->getData(entity);

			nc().call<Event::SetSpriteOrigin>
				(
					Event::SetSpriteOrigin
					{ entity, origin, originPoint }
				);
		}
	}
	void loadTextures(Component::Singleton::TexturesContainer& loadedTextures)
	{
		loadedTextures.map.emplace(Enum::Texture::TEXTURE_PLACEHOLDER, sf::Texture(SPRITES_PATH "placeholder_texture.jpeg"));
	}
	void loadSprites(const Component::Singleton::TexturesContainer& loadedTextures)
	{
		const auto& spriteArray = nc().getComponentArray<Component::Sprite>();

		for (auto& [entity, sprite] : spriteArray->getAll())
		{
			nc().call<Event::LoadSprite>
				(
					Event::LoadSprite
					{ entity, sprite, loadedTextures }
				);
		}
	}
	void setColor()
	{
		const auto& colorArray = nc().getComponentArray<Component::Color>();

		for (auto& [entity, color] : colorArray->getAll())
		{
			nc().call<Event::SetColor>
				(
					Event::SetColor
					{ entity, color }
				);
		}
	}
}

// -------------------------------------------------------
// control systems
// -------------------------------------------------------
namespace Control
{
}

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
namespace Update
{
	template<typename T>
	static T easeOutElastic(T current, T max, T min)
	{
		T progress = 1.0 - [](T target, T min, T max)
			{
				return (target - min) / (max - min);
			}
		(current, min, max);

		static const double c4 = (2 * std::acos(-1.0)) / 3;

		if (progress <= 0) return 0.0;
		else if (progress >= 1) return 1.0;

		return std::pow(2.0, -10.0 * progress) *
			std::sin((progress * 10.0 - 0.75) * c4) + 1.0;
	}
	void move(const DeltaTime dt)
	{
		const auto& velocityArray = nc().getComponentArray<Component::Velocity>();

		for (auto& [entity, velocity] : velocityArray->getAll())
		{
			auto& pos = nc().getComponent<Component::Position>(entity);
			pos.x += (velocity.x * dt);
			pos.y += (velocity.y * dt);
		}
	}
}

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
namespace Render
{
	void doZIndex(std::queue<Entity>& renderQueue)
	{
		const auto& zIndexArray = nc().getComponentArray<Component::ZIndex>();

		std::vector<std::pair<int, Entity>> renderVector;
		for (auto& [entity, zIndex] : nc().getComponentArray<Component::ZIndex>()->getAll())
		{
			if (zIndex.visible) renderVector.emplace_back(zIndex.index, entity);
		}
		std::sort(renderVector.begin(), renderVector.end());

		for (auto& [zIndex, entity] : renderVector)
		{
			renderQueue.push(entity);
		}
	}
	void render
	(
		sf::RenderWindow& window,
		std::queue<Entity>& renderQueue
	)
	{
		const auto& spriteArray = nc().getComponentArray<Component::Sprite>();
		const auto& positionArray = nc().getComponentArray<Component::Position>();
		const auto& textArray = nc().getComponentArray<Component::Text>();

		while (!renderQueue.empty())
		{
			Entity& popped = renderQueue.front();
			////std::cout << "popped: " << popped << "\n";

			if (!positionArray->hasData(popped))
			{
				// this means the entity does not have a position component
				continue;
			}

			auto& pos = positionArray->getData(popped);

			if (spriteArray->hasData(popped))
			{
				auto& sprite = spriteArray->getData(popped);

				sprite.body->setPosition
				(
					sf::Vector2f
					(
						pos.x,
						pos.y
					)
				);
				window.draw(sprite.body.value());
			}

			if (textArray->hasData(popped))
			{
				auto& text = textArray->getData(popped);

				text.box->setPosition
				(
					sf::Vector2f
					(
						pos.x,
						pos.y
					)
				);
				window.draw(text.box.value());
			}

			renderQueue.pop();
		}
	}
}
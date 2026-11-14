#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../../Engine/Core.hpp"
#include "Scenes.hpp"
#include "Enums.hpp"
#include "Components.hpp"

namespace EntityMaker
{
	Entity slicedSprite
	(
		const Component::Color& color,
		const Component::ZIndex& zIndex,
		const Component::Texture& texture,
		const Component::Position& position,
		const Component::Transform& transform,
		const Component::OriginPoint& originPoint,
		const Component::SlicedSpriteRects& slicedSpriteRects
	);
}

#endif
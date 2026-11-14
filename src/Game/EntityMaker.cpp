#include "Headers/EntityMaker.hpp"

#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/Enums.hpp"

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
	)
	{
		Entity entity = nc().createEntity();

		nc().addComponent
		(
			entity,
			color
		);

		nc().addComponent
		(
			entity,
			zIndex
		);

		nc().addComponent
		(
			entity,
			texture
		);

		nc().addComponent
		(
			entity,
			position
		);

		nc().addComponent
		(
			entity,
			transform
		);

		nc().addComponent
		(
			entity,
			Component::OriginOffsets{}
		);

		nc().addComponent
		(
			entity,
			originPoint
		);

		nc().addComponent
		(
			entity,
			slicedSpriteRects
		);

		return entity;
	}
}

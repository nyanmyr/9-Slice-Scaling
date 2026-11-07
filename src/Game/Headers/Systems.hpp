#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/Core.hpp"
#include "Components.hpp"
#include <queue>

namespace Start
{
	void setText();
	void setTextOrigin();
	void setSpriteOrigin();
	void loadTextures(Component::Singleton::TexturesContainer& loadedTextures);
	void loadSprites(const Component::Singleton::TexturesContainer& loadedTextures);
	void setColor();
}

namespace Control
{
}

namespace Update
{
	void move(const DeltaTime dt);
}

namespace Render
{
	void doZIndex(std::queue<Entity>& renderQueue);
	void render
	(
		sf::RenderWindow& window,
		std::queue<Entity>& renderQueue
	);
}

#endif

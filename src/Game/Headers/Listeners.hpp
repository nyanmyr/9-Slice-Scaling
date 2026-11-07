#ifndef LISTENERS_HPP
#define LISTENERS_HPP

#include "../../Engine/NacreCoordinator.hpp"
#include "Events.hpp"

namespace Listener
{
	void setSpriteOrigin(Event::SetSpriteOrigin event);
	void setColor(Event::SetColor event);
	void loadSprite(Event::LoadSprite event);

	void setTextString(Event::SetTextString event);
	void setTextSize(Event::SetTextSize event);
	void setTextColor(Event::SetTextColor event);
	void setTextOrigin(Event::SetTextOrigin event);
}

#endif
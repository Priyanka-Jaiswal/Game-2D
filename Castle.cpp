#include <cmath>
#include <random>
#include <functional>
#include "Castle.h"
#include "gamedata.h"
#include "renderContext.h"

Castle::Castle(const std::string& name) :
	  Drawable(name,
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
	 Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
	 Vector2f(0, 0)),
	 image( RenderContext::getInstance()->getImage(name) )
         {}

Castle::Castle(const Castle& s) :
	  Drawable(s),
	  image(s.image)
          {}

Castle& Castle::operator=(const Castle& rhs) {
	  Drawable::operator=( rhs );
	  image = rhs.image;
	  return *this;
}

void Castle::draw() const {
	  image->draw(getX(), getY(), 0.5);
}

void Castle::update(Uint32 ticks) {
	  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	  setPosition(getPosition() + incr);
}


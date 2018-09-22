#ifndef CASTLE__H
#define CASTLE__H

#include <string>
#include "drawable.h"

class Castle : public Drawable {
   public:
   Castle(const std::string&);
   Castle(const Castle&);
   virtual ~Castle() { }
   Castle& operator=(const Castle&);
   virtual void draw() const;
   virtual void update(Uint32 ticks);
   virtual const Image* getImage() const { return image; }
   virtual const SDL_Surface* getSurface() const { return image->getSurface(); }
   int getScaledWidth()  const { return getScale()*image->getWidth();  }
   int getScaledHeight() const { return getScale()*image->getHeight(); }
   private:
    const Image * image;
};
#endif


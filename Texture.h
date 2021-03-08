#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Constant.h"

class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		bool loadFromFile( std::string path );

		void free();

		void render( int x, int y, SDL_Rect* clip = NULL );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};


#endif // TEXTURE_H_

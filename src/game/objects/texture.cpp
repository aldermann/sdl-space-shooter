#include <SDL_image.h>
#include "engine/render/renderer.hpp"
#include "utils/error/sdl_error.hpp"
#include "texture.hpp"

Texture::Texture(const char* path, int imagePosX, int imagePosY, int width, int height, int posX, int posY)
		:srcRect{imagePosX, imagePosY, width, height}, dstRect{posX, posY, width, height}
{
	boundingBox = new BoundingBox::RectangleBox(width, height, 0);
	// Load file ảnh
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if( loadedSurface == NULL ){ 
		std::cout << IMG_GetError() << '\n';
	}

	// Convert Surface thành Texture
	newTexture = SDL_CreateTextureFromSurface( Renderer::getSDLRenderer(), loadedSurface );
	if( newTexture == NULL ) throw FatalSDLError();
	mTexture = newTexture;

	// Giải phóng Surface sau khi ko cần dùng nx
	SDL_FreeSurface( loadedSurface );
}

Texture::~Texture() {
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
	}
}

void Texture::render()
{
	SDL_RenderCopy( Renderer::getSDLRenderer(), mTexture, &srcRect, &dstRect);
}

int Texture::getWidth() { return srcRect.w;}
int Texture::getHeight() { return srcRect.h;}
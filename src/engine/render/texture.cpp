#include "texture.hpp"

#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <filesystem>

#include "engine/render/renderer.hpp"
#include "utils/error/sdl_error.hpp"

Texture::Texture() : mTexture(nullptr), cropRect() {}
Texture::Texture(const char* path) : Texture(path, 0, 0, 0, 0, 0, 0) {}
Texture::Texture(const char* path, int outputWidth, int outputHeight)
    : Texture(path, 0, 0, 0, 0, outputWidth, outputHeight) {}

Texture::Texture(const std::string& path,
                 int cropTop,
                 int cropBottom,
                 int cropLeft,
                 int cropRight,
                 int outputWidth,
                 int outputHeight)
    : cropRect() {
  std::filesystem::path cwd = std::filesystem::current_path();
  mTexture = IMG_LoadTexture(Renderer::getSDLRenderer(), (cwd / path).c_str());
  if (mTexture == nullptr) {
    throw FatalSDLError();
  }
  int imageW, imageH;
  SDL_QueryTexture(mTexture, nullptr, nullptr, &imageW, &imageH);
  SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
  cropRect.x = cropLeft;
  cropRect.y = cropTop;
  cropRect.h = imageH - cropTop - cropBottom;
  cropRect.w = imageW - cropLeft - cropRight;
  this->outputHeight = outputHeight ? outputHeight : cropRect.h;
  this->outputWidth = outputWidth ? outputWidth : cropRect.w;
}

Texture::Texture( std::string textureText, SDL_Color textColor ):cropRect{0, 0, 0, 0}
{
	// Render xâu lên surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	  std::cerr << "Unable to render text surface! SDL_ttf Error : " << TTF_GetError(); 
	else
	{
		// Tạo Texture từ Surface
    mTexture = SDL_CreateTextureFromSurface(Renderer::getSDLRenderer(), textSurface );
		if( mTexture == NULL )
			std::cerr <<  "Unable to create texture from rendered text! SDL Error: "<<  SDL_GetError();
		else
		{
			outputWidth = textSurface->w;
			outputHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}
}

Texture::~Texture() {
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

SDL_Rect Texture::getRenderArea(const Geometry::Point& pos) const {
  SDL_Rect res;
  res.w = outputWidth;
  res.h = outputHeight;
  res.x = (int) pos.x - res.w / 2;
  res.y = (int) pos.y - res.h / 2;
  return res;
}

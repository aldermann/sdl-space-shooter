#pragma once

#include <iostream>
#include "engine/object/object.hpp"

class Texture : public GameObject
{
	public:
		// Đưa vào đường dẫn ảnh để load lên texture 
		Texture(const char* path, int imagePosX, int imagePosY, int width, int height, int posX, int posY);
		~Texture();

		// Render texture, có chọn render một phần, xoay, flip texture
		void render() override;

		// In kích thước texture
		int getWidth();
		int getHeight();

	// Con trỏ trỏ tới biến SDL_Texture, kích thước Texture
	private:
		SDL_Texture* mTexture;
		// vị trí để cắt 1 phần của ảnh
		SDL_Rect srcRect;
		// vị trí render ảnh lên screen
		SDL_Rect dstRect;
};


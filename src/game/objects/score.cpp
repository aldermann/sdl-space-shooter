#include "score.hpp"
#include "engine/render/color.hpp"

#include <string> 

void Score::render(){
    std::string s = "hahahahahaha";
    SDL_Color textColor = {255, 0, 0, 255};
    Texture currentScore = Texture(s, textColor);
    //Texture currentScore = Texture("assets/ball.png", 60, 60);
    Renderer* renderer = Renderer::getInstance();
    renderer->drawTexture(currentScore, {1248, 32}, 0);
}
#pragma once

#include "engine/object/object.hpp"
#include "engine/render/color.hpp"
#include "engine/render/renderer.hpp"

class Map : public GameObject 
{
    private:
        Geometry::Rectangle rect;
        Color col;

    public:
        Map(Geometry::Point position, int width, int height, int angle, Color _col);

        void render(const Geometry::Point &position);
};
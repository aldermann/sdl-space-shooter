#include "map.hpp"
#include "const.hpp"

Map::Map(Geometry::Point position, int width, int height, int angle, Color _col) : 
         rect(position, width, height, angle), col(_col) 
{
    boundingBox = new BoundingBox::RectangleBox(width, height, angle);
    type = MAP;
    dynamic = {position, false};
}
        
void Map::render(const Geometry::Point &position)
{
    Renderer::getInstance()->drawRectangle(rect, col);
}
    
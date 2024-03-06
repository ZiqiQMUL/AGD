#include "../utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    // IX.A Implement this function, that returns true if the point <x,y> is inside this rectangle.
    return (x > topLeft.x && x < bottomRight.x) && (y > topLeft.y && y < bottomRight.y);
}

bool Rectangle::interesects(const Rectangle& rectangle) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
	return inside(rectangle.topLeft.x, rectangle.topLeft.y)
		|| inside(rectangle.topLeft.x, rectangle.bottomRight.y)
		|| inside(rectangle.bottomRight.x, rectangle.topLeft.y)
		|| inside(rectangle.bottomRight.x, rectangle.bottomRight.y);
}


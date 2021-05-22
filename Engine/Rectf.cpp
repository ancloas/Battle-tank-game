#include "Rectf.h"
#include <assert.h>
#include <math.h>

Rectf::Rectf(const float left, const float right, const float top, const float bottom)
	:Rectf(Vec2((left + right) / 2, (top + bottom) / 2), abs(right-left), abs(bottom-top))
{
}

Rectf::Rectf(const Vec2 & start, const Vec2 & end)
	:Rectf((start+end)*(1.0f/2.0f),end.x-start.x, end.y-start.y)
{
	assert(end.x >= start.x);
	assert(start.y<=end.y);
}

Rectf::Rectf(const Vec2 & centre, float width, float height)
	 :centre(centre),
	width(width),
	height(height)
{
}

bool Rectf::Overlaps_With(const Rectf & Rect)
{
 
	return (Rect.get_left() < get_right()) && (get_left() < Rect.get_right()) && (get_top() < Rect.get_bottom()) && (Rect.get_top() < get_bottom());
}

void Rectf::draw_solid(Graphics & gfx, Color color)
{
	gfx.DrawRectangle_by_Centre(int(centre.x), int(centre.y), int(width), int(height), color);
}


void Rectf::Displaced(Vec2 displacement)
{
	centre += displacement;
}

const Vec2 Rectf::Get_Centre() const
{
	
	return centre;
}
void Rectf::Get_Hit(float Damage)
{
}
const float Rectf::get_left() const
{
	return centre.x - width / 2;
}
const float Rectf::get_top() const
{
	return centre.y - height / 2;
}
const float Rectf::get_right() const
{
	return centre.x + width / 2;
}
const float Rectf::get_bottom() const
{
	return centre.y + height / 2;
}

void Rectf::flip_horizontly()
{
	float temp = width;
	width = height;
	height = temp;
}
#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
class Rectf
{
public:
	Rectf() = default;
	Rectf(const float left,const float right,const float top,const float bottom);
	Rectf(const Vec2 & start, const Vec2 & end);
	Rectf(const Vec2 & centre, float width, float height);
	void flip_horizontly();
	bool Overlaps_With(const Rectf& Rect);
	void draw_solid(Graphics & gfx, Color color);
	void Displaced(Vec2 Displacement);
	const Vec2 Get_Centre() const;
    virtual void Get_Hit(float Damage);
	const float get_left() const;
	const float get_top() const;
	const float get_right() const;
	const float get_bottom() const;

public:
	Vec2 centre;
	float width;
	float height;
};
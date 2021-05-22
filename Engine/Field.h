#pragma once
#include "Graphics.h"
#include "Vec2.h"
//incomplete
class Field
{
public:
	//Field(const Vec2& Origin, const float unit_cell, const float width, const float height, Graphics &gfx);
	//void Draw_cell();
	

private:
	float unit_cell;
	float width;
	float height;
	Vec2 origin;
	Graphics  gfx;
	bool isempty = true;


};

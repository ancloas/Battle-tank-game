#pragma once
#include "Vec2.h"
#include "Rectf.h"
#include "Graphics.h"
#include <vector>

enum obstacle_type { clay, steel, grass};
class Obstacle: public Rectf{
public:
	Obstacle(Vec2 centre, float width, float height, obstacle_type type);
	void Draw(Graphics &gfx);

private:
	std::vector<Rectf> bricks;
	float brick_height=5.0f;
	float brick_width=5.0f;
	obstacle_type type=clay;
};
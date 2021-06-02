#include "Obstacle.h"

Obstacle::Obstacle(Vec2 centre, float width, float height, obstacle_type type)
	:Rectf(centre, width - int(width) % 5, height - int(height) % 5),
	type(type)
{//cell = topleft + width +hight*row_num
	int row_num = this->width/brick_width;
	int col_num = this->height / brick_height;
	bricks.resize(row_num*col_num);
	for (int i = 0; i < col_num; i++)
	{
		for (int j = 0; j < row_num; j++)
		{
			Vec2 brk_centre(this->get_left() + brick_width / 2 + j * brick_width,
				this->get_top() + brick_height / 2 + i * brick_height);
			Rectf brick(brk_centre, brick_width, brick_height);
			bricks[i*row_num + j]=brick;
		}
	}
}

void Obstacle::Draw(Graphics &gfx)
{
	Color c;

	if (type == clay)
		c = Colors::MakeRGB(245, 129, 66);
	if(type==steel)
		c = Colors::MakeRGB( 184, 186, 186);
	if (type == grass)
		c = Colors::Green;

	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i].draw_solid(gfx,c);
	}
}

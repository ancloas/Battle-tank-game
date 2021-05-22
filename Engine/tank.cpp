#include "Tank.h"

Tank::Tank(Vec2 centre, float  speed, float length, float breadth, Color color)
	:
	body(centre, length, breadth),
	speed(speed),
	front(RIGHT),
	bulletlist(),
	color(color),
	barrel(Vec2(centre.x + 3.0f / 4.0f * length, centre.y), length / 2.0f, breadth / 8.0f)
{
}

void Tank::fire_bullet()
{ 
	float bulletpower = bullet_power();
	if (front == RIGHT)
	{
		bullet *b = new bullet(Vec2(barrel.get_right() + bullet_length, barrel.centre.y), Vec2(bullet_speed, 0.0f), bullet_length, bullet_breadth,bulletpower, bullet_type);
		bulletlist.add_bullet(b);
	}
	if (front == LEFT)
	{
		bullet * b= new bullet(Vec2(barrel.get_left() - bullet_length, barrel.centre.y), Vec2(-bullet_speed, 0.0f), bullet_length, bullet_breadth, bulletpower, bullet_type);
		bulletlist.add_bullet(b);
	}
	if (front == UP)
	{
		bullet * b = new bullet(Vec2( barrel.centre.x, barrel.get_top() - bullet_length), Vec2(0.0f, -bullet_speed), bullet_breadth, bullet_length, bulletpower, bullet_type);

		bulletlist.add_bullet(b);
	}
	if (front == DOWN)
	{
		bullet * b = new bullet(Vec2(barrel.centre.x, barrel.get_top() + bullet_length), Vec2(0.0f, bullet_speed), bullet_breadth, bullet_length, bulletpower, bullet_type);
		bulletlist.add_bullet(b);
	}
	cool_down = 0.1f;
}

void Tank::move_right(const float& dt)
{// front ==right move dt*velocity
//else 
	if (front != RIGHT)
	{
		if(!(front==LEFT))
		{
			body.flip_horizontly();
			barrel.flip_horizontly();
			barrel.centre.y = body.centre.y;//change the barrel of y coordinate to be same as x
		}
		barrel.centre.x = body.get_right() + barrel.width / 2; // make the barrel at right side of the 
	}
	    body.centre.x += speed*dt;
		barrel.centre.x += speed * dt;
		front = RIGHT;
}

void Tank::move_left(const float & dt)
{
	if (front != LEFT)
	{
		if (!(front == RIGHT))
		{
			body.flip_horizontly();
			barrel.flip_horizontly();
			barrel.centre.y = body.centre.y;  //change barrel y coordinate to same as centre of tank body
		}
		barrel.centre.x = body.get_left() - barrel.width / 2; // make the barrel at right side of the 
	}
	body.centre.x -= speed * dt;
	barrel.centre.x -= speed * dt;
	front = LEFT;
}

void Tank::move_down(const float &dt)
{
	if (front != DOWN)
	{
		if (!(front == UP))
		{
			body.flip_horizontly();
			barrel.flip_horizontly();
			barrel.centre.x = body.centre.x;  //change barrel x coordinate to same as centre of tank body
		}
		barrel.centre.y = body.get_bottom() + barrel.height / 2; // make the barrel at right side of the 
	}
	body.centre.y += speed * dt;
	barrel.centre.y += speed * dt;
	front = DOWN;
}

void Tank::move_up(const float &dt)
{
	if (front != UP)
	{
		if (!(front == DOWN))
		{
			body.flip_horizontly();
			barrel.flip_horizontly();
			barrel.centre.x = body.centre.x;  //change barrel x coordinate to same as centre of tank body
		}
		barrel.centre.y = body.get_top() - barrel.height / 2; // make the barrel at right side of the 
	}
	body.centre.y -= speed * dt;
	barrel.centre.y -= speed * dt;
	front = UP;
}
void Tank::Update(const float& dt, Keyboard& Kbd)
{
	if (Kbd.KeyIsPressed(VK_RIGHT))
	{
      move_right(dt);
	}
	else if (Kbd.KeyIsPressed(VK_LEFT))
	{
		move_left(dt);
	}
	else if (Kbd.KeyIsPressed(VK_UP))
	{
		move_up(dt);
	}
	else if (Kbd.KeyIsPressed(VK_DOWN))
	{
		move_down(dt);
	}

	bulletlist.Update(dt);
	cool_down -= dt;
}
void Tank::Update(const float& dt, const Tank & tnk)
{
}

void Tank::draw_Tank(Graphics &gfx)
{
	bulletlist.draw(gfx);
	barrel.draw_solid(gfx,color);
	body.draw_solid(gfx,color);
}

 bool Tank::Shoot(Tank & enemy)
{
	if (bulletlist.hit_target(enemy))
		return true;
	return false;
	
}
void Tank::Get_Hit(float Damage)
{
	health -= Damage;
}

bool Tank::Overlaps_with_Rect(const Rectf & rect)
{
	return body.Overlaps_With(rect) || barrel.Overlaps_With(rect);
}

float Tank:: bullet_power()
{
	if (bullet_type == light)
		return 1.0f;
	if (bullet_type == medium)
		return 3.0f;
	if (bullet_type == heavy)
		return 5.0f;
	return 1.0f;
}

bool Tank::isInCoolDown(const float& dt)
{
	if (cool_down <= 0)
		return false;
	return true;
}

#include "Tank.h"

Tank::Tank(Vec2 centre, Vec2 velocity, float length, float breadth, Color color)
	:
	body(centre, length, breadth),
    velocity(velocity),
	front(RIGHT),
	bulletlist(),
	color(color),
	barrel(Vec2(body.get_right()+length/8.0f, centre.y), length/4.0f, breadth / 8.0f)
{
	update_velocity();
}

void Tank::fire_bullet()
{ 
	float bulletpower = bullet_power();
	Vec2 bullet_velocity = Get_Bullet_Velocity();
	bullet * b = new bullet(barrel.centre,bullet_velocity, bullet_length, bullet_breadth, bulletpower, bullet_type);
	if (front == UP || front == DOWN)
		b->flip_horizontly();
    bulletlist.add_bullet(b);
	cool_down = 0.2f;
}

void Tank::turn_right()
{// front ==right move dt*velocity
//else 
	if (front == RIGHT)
		return;

	if (front == LEFT)
	{
		Rotate_90_degree_cw();
		Rotate_90_degree_cw();
	}
	else if (front == UP)
			Rotate_90_degree_cw();
	else Rotate_90_degree_acw();
	front = RIGHT;
}

void Tank::turn_left()
{
	if (front == LEFT)
		return;
	if (front == RIGHT)
	{
		Rotate_90_degree_cw();
		Rotate_90_degree_cw();
	}
	else if (front == UP)
		Rotate_90_degree_acw();
	else Rotate_90_degree_cw();
	front = LEFT;	
}

void Tank::turn_down()
{
	if (front == DOWN)
		return;
    if (front == UP)
    {
    	Rotate_90_degree_cw();
    	Rotate_90_degree_cw();
    }
    else if (front == LEFT)
    	Rotate_90_degree_acw();
    else Rotate_90_degree_cw();
    front = DOWN;
}

void Tank::turn_up()
{
	if (front == UP)
		return;
	if (front == DOWN)
	{
		Rotate_90_degree_cw();
		Rotate_90_degree_cw();
	}
	else if (front == RIGHT)
		Rotate_90_degree_acw();
	else Rotate_90_degree_cw();
	front = UP;
}
void Tank::Update(const float& dt, Keyboard& Kbd)
{
	in_Motion = false;
		if (Kbd.KeyIsPressed(VK_RIGHT))
		{
			if (front != RIGHT)
			{
				turn_right();
				//in_Motion = false;
			}
				in_Motion = true;
		}
		if (Kbd.KeyIsPressed(VK_LEFT))
		{
			if (front != LEFT)
			{
				turn_left();
				//in_Motion = false;
			}
				in_Motion = true;
		}
		if (Kbd.KeyIsPressed(VK_UP))
		{
			if (front != UP)
			{
				turn_up();
				//in_Motion = false;
			}
				in_Motion = true;
		}
		if (Kbd.KeyIsPressed(VK_DOWN))
		{
			if (front != DOWN)
			{
				turn_down();
			//	in_Motion = false;
			}
				in_Motion = true;
		}
	update_velocity(); //updating direction of velocity
	if (in_Motion)
	{
		Displace(velocity*dt);
	}
	if (Kbd.KeyIsPressed(VK_SPACE)&&(!isInCoolDown()))
	{
		fire_bullet();
		bulletFired = true;
	}
	else {
		bulletFired = false;
	}

	bulletlist.Update(dt);
	cool_down -= dt;
}
void Tank::Update(const float& dt, const Tank & tnk, const Rectf& Wall)
{   Vec2 Dir_2_Move =tnk.body.centre-body.centre;
    float x_dist = Dir_2_Move.x;
	float y_dist = Dir_2_Move.y;

	if (int(Dir_2_Move.y) == 0)
	{
		if (Dir_2_Move.x > 0 && front != RIGHT)
			turn_right();
		else
			if (Dir_2_Move.x < 0 && front != LEFT)
				turn_left();
	}
	if (int(Dir_2_Move.x) == 0)
	{
		if (Dir_2_Move.y < 0 && front != UP)
			turn_up();
		else
		if (Dir_2_Move.y > 0 && front != DOWN)
				turn_down();
	}
if (int(x_dist) == 0 || int(y_dist) == 0)
{
	if(!isInCoolDown())
	fire_bullet();
	bulletFired = true;
}
else { bulletFired = false; }

    update_velocity(); //
	
	
	//updating direction of velocity
	Displace(velocity*dt);
	bulletlist.Update(dt);

	cool_down -= dt;
	if (Touched_Wall(Wall))
	{
		front = stance((front + 2) % 4);
		Rotate_90_degree_cw();
		Rotate_90_degree_cw();
		update_velocity();//
  	}
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
	if (health < 0)
	{
		isDestroyed = true;
	}
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

bool Tank::isInCoolDown()
{
	if (cool_down <= 0)
		return false;
	return true;
}

Vec2 Tank::Get_Bullet_Velocity()
{
   return velocity.GetNormalized()*float(bullet_type)+velocity*in_Motion;
}

bool Tank::Touched_Wall(const Rectf &Wall)
{   
	bool  is_touched = false;
	if (barrel.get_right() > Wall.get_right())
	{
		Displace(Vec2(Wall.get_right() - barrel.get_right(), 0));
		is_touched = true;
	}
	if (barrel.get_left() < Wall.get_left())
	{
		Displace(Vec2(Wall.get_left() - barrel.get_left(), 0));
		is_touched = true;
	}
	if (barrel.get_bottom() > Wall.get_bottom())
	{
		Displace(Vec2(0, Wall.get_bottom() - barrel.get_bottom()));
	    is_touched = true;
	}
	if (barrel.get_top() < Wall.get_top())
	{
		Displace(Vec2(0, Wall.get_top() - barrel.get_top()));
		is_touched = true;
	}
	return is_touched;
}                  
void Tank::Displace(const Vec2 & displacement)
{
	body.Displaced(displacement);
	barrel.Displaced(displacement);
}
void Tank::Rotate_90_degree_cw()
{
	body.flip_horizontly();
	barrel.flip_horizontly();
	barrel.centre.Rotate_by_90_degree_clockwise_wrt_origin(body.centre);
}
void Tank::Rotate_90_degree_acw()
{
	body.flip_horizontly();
	barrel.flip_horizontly();
	barrel.centre.Rotate_by_90_degree_anticlockwise_wrt_origin(body.centre);
}
void Tank::update_velocity()
{
	float magnitude = velocity.GetLength();
	if (front == RIGHT)
		velocity = Vec2(1, 0)*magnitude;
	if (front == LEFT)
		velocity = Vec2(-1, 0)*magnitude;
	if (front == DOWN)
		velocity = Vec2(0, 1)*magnitude;
	if (front == UP)
		velocity = Vec2(0, -1)*magnitude;

}
void Tank::Respawn(const Vec2& Origin)
{
	if ((life >= 0) &&(isDestroyed))
	{
		life--;
		turn_up();
		health = 5.0f;
		turn_right();
		Displace(Origin + Vec2(body.width / 2 - body.centre.x, body.height / 2 - body.centre.y));
		isDestroyed = false;
	}
}
const float& Tank::Get_health() const
{
	return health;
} 
const float& Tank::Get_Life() const
{
	return float(life);
}
const bool Tank::If_Destroyed() const
{
	return isDestroyed;
}
const bool Tank::If_Bullet_Fired() const
{
	return bulletFired;
}
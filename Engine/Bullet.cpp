#include "Bullet.h"
#include "Graphics.h"
#include "assert.h"
#include "tank.h"

bullet::bullet(Vec2& centre, Vec2 & velocity, float& width,  float& height,  float& Damage_Power,  bullet_type& Type)
	: Damage_Power(Damage_Power),
	Rectf(centre,width,height),
	type(Type),
	velocity(velocity),
	width(width),
	height(height)
{
}

bullet::bullet(){}

void bullet::Update_Coordinate(const float& dt)
{
	centre += velocity * dt;
}
bool bullet::touched_boundary()
{   
	if (get_right()>= Graphics::ScreenWidth)
		return true;
	if (get_left()<=0)
		return true;
	if (get_bottom() >= Graphics::ScreenHeight)
		return true;
	if ( get_top() <= 0)
		return true;
	return false;
}

void bullet::Draw(Graphics &gfx)
{
	Color c;
	if (type == light)
		c = Colors::Gray;
	if (type == medium)
		c = Colors::Red;
	if (type == heavy)
		c = Colors::Green;
	draw_solid(gfx, c);
}

const float & bullet::Get_Damage_Power()
{
	return Damage_Power;
}

bullet::~bullet()
{
}

void bullet_list::draw(Graphics &gfx)
{  
	bullet * curr=first;
	while (curr != NULL)
	{
		curr->Draw(gfx);
		curr = curr->next;
	}
	
}


bool bullet_list::empty()
{
	return last == NULL;
}
void bullet_list::Update(const float & dt) 
{
	if (empty())
		return;
	bullet * curr=first, *prev=NULL;

	while (curr != NULL)
	{// middle // last //first // empty
		curr->Update_Coordinate(dt);
		if (curr->touched_boundary())
		{
			if (curr != first)
			{
				prev->next = curr->next;
			}else
			{
				first = curr->next;
			}
			if (curr == last)
				last = prev;
			bullet * temp=curr;
			curr = curr->next;
			delete temp;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}
void bullet_list::add_bullet(bullet * b)
{
	b->next = first;
	first = b;
	if (last == NULL)
		last = first;
}

bool bullet_list::hit_target(Rectf &rect)
{
bullet *ptr = first;
	while (ptr != NULL)
	{
		if (ptr->Overlaps_With(rect))
		{
			rect.Get_Hit(ptr->Get_Damage_Power());
			return true;
		}
	}
	return false;
}

bool bullet_list::hit_target(Tank & tank )
{
	bullet *ptr = first;
	while (ptr != NULL)
	{
		if (tank.Overlaps_with_Rect(*ptr))
		{
			tank.Get_Hit(ptr->Get_Damage_Power());
			return true;
		}
	}
	return false;
}
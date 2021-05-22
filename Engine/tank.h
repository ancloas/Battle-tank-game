#pragma once
#include "Bullet.h"
#include "assert.h"
#include "Keyboard.h"
#include "Rectf.h"
#include "Vec2.h"

enum stance { RIGHT, LEFT, UP, DOWN};
class Tank {
public:
	Tank(Vec2  centre, float  speed, float length, float breadth, Color color);
	void fire_bullet();
	void move_right(const float & dt);
	void move_left(const float & dt);
	void move_down(const float & dt);
	void move_up(const float & dt);
	void Update(const float& dt, Keyboard & Kbd);
	void Update(const  float& dt, const Tank & tnk);
	void draw_Tank(Graphics &gfx);
	bool Shoot(Tank & enemy);
	void Get_Hit(float Damage);
	bool Overlaps_with_Rect(const Rectf & rect);
	float bullet_power();
	bool isInCoolDown(const float & dt);
private:
	const float speed=100.0f;
	Rectf body;
	Rectf barrel;
	stance front = RIGHT;
	bullet_list bulletlist;
	bool isDestroyed=false;
	Color color;
	enum Power {
		None, Invincible, HeavyBullet, SpeedUp, LifeUp, Heal, NuclearBomb
	};
	Power PowerUP = None;
	float health = 5.0;
	float bullet_speed=300.0f;
	float bullet_length = 3.0f;
	float bullet_breadth = 2.0f;
	bullet_type bullet_type=light;
	float cool_down = 0.1f;
};
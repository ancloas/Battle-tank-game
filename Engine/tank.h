#pragma once
#include "Bullet.h"
#include "assert.h"
#include "Keyboard.h"
#include "Rectf.h"
#include "Vec2.h"

enum stance { LEFT = 0, UP=1, RIGHT=2, DOWN=3 };
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
	float Get_Bullet_speed();
	bool Touched_Wall(const Rectf & Wall);
	void Displace(const Vec2 & displacement);
	void Rotate_90_degree();
private:
	const float speed;
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
	float bullet_length = 20.0f;
	float bullet_breadth = 5.0f;
	bullet_type bullet_type=light;
	float cool_down = 0.2f;
	bool in_Motion = false;
};
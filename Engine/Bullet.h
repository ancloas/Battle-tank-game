#pragma once
#include "Graphics.h"
#include "Rectf.h"

enum bullet_type{light=500, medium=600, heavy=700};
class bullet : public Rectf {
public:
	bullet( Vec2& centre,  Vec2&  velocity,  float & width,  float& height, float& Damage_Power, bullet_type &  Type);
	bullet();
	void Update_Coordinate(const float& dt);
	bool touched_boundary();
	void Draw(Graphics & gfx);
	const float& Get_Damage_Power();
	~bullet();
	bullet * next;
private:
	float Damage_Power;
	bullet_type type;
	Vec2 velocity;
	float width;
	float height;
};
class bullet_list 
{
public:
	void draw(Graphics &gfx);
	bool empty();
	void Update(const float & dt);
	void add_bullet(bullet * b);
	bool hit_target(Rectf & b);
	bool hit_target(class Tank & tank);

private:
	bullet * first;
	bullet * last;
};
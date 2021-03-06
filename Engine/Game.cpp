/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chilpmi DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	Wall(Vec2(400, 300), 600, 500),
	Origin(Vec2(Wall.get_left(), Wall.get_top())),
	Player1(Origin + Vec2(300.0f, 300.0f), Vec2(200.0f, 0.0f), 30.0f, 25.0f, Colors::Green),
	rng(rd()),
	xDist(15, int(Wall.width) - 17),
	yDist(15, int(Wall.height) - 17),
	stanceDist(0, 3),
	bulletSound({ L"Sound\\bullet fire.wav" }),
	explosionSound({ L"Sound\\big explosion.wav" }, 0.2f, 0.25f),
	obstacle(Vec2(200.0f, 100.0f), 100.0f, 50.0f, obstacle_type::grass)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsed_time = ft.Mark();
	while (elapsed_time > 0)
	{  
		float dt = std::min(elapsed_time, 0.025f);
		UpdateModel(dt);
		elapsed_time -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(const float & dt)
{
	if (!GameOver)
	{
		SpawnTime += dt;
		if (SpawnTime >= Enemy_spawn_interval)
		{
			Spawn_Enemy();
			SpawnTime -= Enemy_spawn_interval;
		}

		//Movement
		Player1.Update(dt, wnd.kbd);
		//Checking if touching the wall
		Player1.Touched_Wall(Wall);

		//Checking if alive
		if (Player1.Get_Life() >= 0 && Player1.Get_health() <= 0)
		{
			Player1.Respawn(Origin);
		}
		for (auto i = 0; i < Enemy.size(); i++)
		{
			Enemy[i].Update(dt, Player1, Wall);
			Enemy[i].Shoot(Player1);
			if (Enemy[i].If_Bullet_Fired())
				bulletSound.Play(rng, 0.2f);
			if (Player1.Shoot(Enemy[i]))
			{
				explosionSound.Play(rng, 0.05f);
				Enemy.erase(Enemy.begin() + i--);
			}
		}
		if (Player1.If_Bullet_Fired())
			bulletSound.Play(rng, 0.2f);
		if (Player1.If_Destroyed())
			explosionSound.Play(rng, 0.05f);

		//if Player dies game over
		if (Player1.If_Destroyed() && Player1.Get_Life() < 0)
		{
			GameOver = true;
		}
	}
	else 
	{

	}
	}

void Game::Spawn_Enemy()
{
	Tank evil(Origin + Vec2(float(xDist(rng)), float(yDist(rng))), Vec2(200.0f, 0.0f), 30.0f, 25.0f, Colors::Yellow);
	stance front = stance(stanceDist(rng));
	if (front == RIGHT)
	    evil.turn_right();
	if (front == LEFT)
		evil.turn_left();
	if (front == UP)
		evil.turn_up();
	if (front == DOWN)
		evil.turn_down();
	evil.update_velocity();
	Enemy.push_back(evil);
}
void Game::ComposeFrame()
{
	if (!GameOver)
	{
		Player1.draw_Tank(gfx);
		Wall.draw_hollow(gfx, Colors::Magenta);
		for (auto i = 0; i < Enemy.size(); i++)
		{
			Enemy[i].draw_Tank(gfx);
		}
		obstacle.Draw(gfx);
	}
	for (int i = 0; i < Player1.Get_Life(); i++)
	{
		gfx.DrawRectangle(10 * i+10, 20, 5, 20, Colors::Green);
	}

}

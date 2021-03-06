/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "tank.h"
#include "FrameTimer.h"
#include "Rectf.h"
#include "Vec2.h"
#include "vector"
#include <random>
#include "SoundEffect.h"
#include "Obstacle.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	int x_pos, y_pos;
	int centre_x = 400, centre_y = 300;
	int dx=0, dy=0;
	bool k = false;
	int gb = 255;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(const float &dt);
	/********************************/
	/*  User Functions              */
	void Spawn_Enemy();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;

	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	Rectf Wall;
	Vec2 Origin;
	Tank Player1;
	std::vector<Tank> Enemy;
	float SpawnTime=0.0f;
	float Enemy_spawn_interval = 5.0f;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	std::uniform_int_distribution<int> stanceDist;
	SoundEffect bulletSound;
	SoundEffect explosionSound;
	bool GameOver=false;
	Obstacle obstacle;
	//30 secs spawn time
 	/********************************/
};
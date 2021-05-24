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
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	Player1(Vec2(300.0f,300.0f),Vec2(50.0f,0.0f), 30.0f, 20.0f, Colors::Green),
	Wall(Vec2(400,300),600, 600),
	Origin(Vec2(Wall.get_left(),Wall.get_top()))
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

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!Player1.isInCoolDown(dt))
			Player1.fire_bullet();
	}
	Player1.Update(dt, wnd.kbd);
	Player1.Touched_Wall(Wall);
	}

void Game::ComposeFrame()
{
	Player1.draw_Tank(gfx);
	
}

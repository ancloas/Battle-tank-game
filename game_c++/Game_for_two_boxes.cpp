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
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{   
	
	// Movements for box1
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (!box1.inhibitRight)
		{
			box1.increase_speed_x();
				box1.inhibitRight=true;
		}
		else{}
	}
	else{
		box1.inhibitRight = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (!box1.inhibitLeft)
		{
			box1.decrease_speed_x();
			box1.inhibitLeft = true;
		}
		else {}
	}
	else {
		box1.inhibitLeft = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (!box1.inhibitDown)
		{
			box1.increase_speed_y();
			box1.inhibitDown = true;
		}
		else {}
	}
	else {
		box1.inhibitDown = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (!box1.inhibitUp)
		{
			box1.decrease_speed_y();
			box1.inhibitUp = true;
		}
		else {}
	}
	else {
		box1.inhibitUp = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		box1.increase_size(1);
	}
	if (wnd.kbd.KeyIsPressed(0x51))
	{
		box1.decrease_size(1);
	}


	//Movements for Box2
	if (wnd.kbd.KeyIsPressed(VK_NUMPAD6))
	{
		if (!box2.inhibitRight)
		{
			box2.increase_speed_x();
			box2.inhibitRight = true;
		}
		else {}
	}
	else {
		box2.inhibitRight = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_NUMPAD4))
	{
		if (!box2.inhibitLeft)
		{
			box2.decrease_speed_x();
			box2.inhibitLeft = true;
		}
		else {}
	}
	else {
		box2.inhibitLeft = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_NUMPAD8))
	{
		if (!box2.inhibitDown)
		{
			box2.decrease_speed_y();
			box2.inhibitDown = true;
		}
		else {}
	}
	else {
		box2.inhibitDown = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_NUMPAD2))
	{
		if (!box2.inhibitUp)
		{
			box2.increase_speed_y();
			box2.inhibitUp = true;
		}
		else {}
	}
	else {
		box2.inhibitUp = false;
	}
	if (wnd.kbd.KeyIsPressed(0x50))
	{
		box2.increase_size(1);
	}
	if (wnd.kbd.KeyIsPressed(0x4F))
	{
		box2.decrease_size(1);
	}
	/*	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
		{
			if (gb == 255)
				gb = 0;
			else gb = 255;
		}
*/		

	//collision detection
	if (box1.collission_detection(box2))
	{
		box1.r = 0;
		box2.g = 0;
	}
	else {
		box1.r = 255;
		box2.g = 255;
	}

	//centre_x += dx;
	//centre_y += dy;
	//if (centre_x + 9 >= gfx.ScreenWidth)
	//	centre_x = 10;
	//if (centre_x - 9 <= 0)
	//	centre_x = gfx.ScreenWidth - 9;
	//if (centre_y + 9 >= gfx.ScreenHeight)
	//	centre_y = 10;
	//if (centre_y - 9 <= 0)
	//	centre_y = gfx.ScreenHeight - 9;
	
}

void Game::ComposeFrame()
{
	box1.draw(gfx);
	box2.draw(gfx);
	tank1.draw_tank(gfx);

//	if(k)
//	{
//		
//		for (int j = 3; j < 6; j++)
//		{
//			gfx.PutPixel(centre_x, centre_y - j, 255, gb, gb);
//			gfx.PutPixel(centre_x, centre_y + j, 255, 255, 255);
//		}
//		for (int i = 3; i < 6; i++)
//		{
//			gfx.PutPixel(centre_x - i, centre_y, 255,gb, gb);
//			gfx.PutPixel(centre_x + i, centre_y, 255,gb, gb);
//		}
//	}
//	else {
//		for (int j = 3; j < 6; j++)
//		{
//			gfx.PutPixel(centre_x+j, centre_y - j, 255, gb, gb);
//			gfx.PutPixel(centre_x+j, centre_y + j, 255, gb, gb);
//		}
//		for (int i = 3; i < 6; i++)
//		{
//			gfx.PutPixel(centre_x - i, centre_y-i, 255, gb, gb);
//			gfx.PutPixel(centre_x - i, centre_y+i, 255, gb, gb);
//		}
//	}
}

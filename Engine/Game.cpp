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
#include "Vec2.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	camera(-2.05,2.05,2.05,-2.05)
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
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		camera.MoveUp();
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		camera.MoveDown();
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		camera.MoveLeft();
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		camera.MoveRight();
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		camera.MoveFaster();
	}
	else if (wnd.kbd.KeyIsPressed('S')) {
		camera.MoveSlower();
	}
	if (wnd.kbd.KeyIsPressed('Q')) {
		plane.DecreaseIterations();
	}
	else if (wnd.kbd.KeyIsPressed('E')) {
		plane.IncreaseIterations();
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		camera.Reset();
		plane.Reset();
	}
	if (wnd.mouse.LeftIsPressed())
	{
		camera.ZoomIn(plane.gridsX, plane.gridsY);
	}
	else if (wnd.mouse.RightIsPressed()) {
		camera.ZoomOut();
	}
}

void Game::ComposeFrame()
{
	plane.DoFullIteration(gfx, camera);
}

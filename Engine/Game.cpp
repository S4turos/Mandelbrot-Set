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
}

void Game::ComposeFrame()
{
	for (int i = 0; i < Matrix::grids; i++) {
		int x = i % Matrix::gridsX;
		int y = i / Matrix::gridsY;
		Vec2 c(double(x - halfX) / scalerX, -double(y - halfY) / scalerY);
		int p = 0;
		Vec2 iteration(0.0f, 0.0f);
		while (true) {
			// Aquí debes hacer todos los cálculos para cada casilla
			// p es cada pass
			double xnew = iteration.x * iteration.x - iteration.y * iteration.y + c.x;
			iteration.y = 2 * iteration.x * iteration.y + c.y;
			iteration.x = xnew;
			double result = iteration.x * iteration.x + iteration.y * iteration.y;
			if (result >= 4.0f || p == limit - 1) {
				break;
			}
			p++;
		}

		Matrix::DrawCell({ x * CellWidth, y * CellHeight },
		{ x * CellWidth + CellWidth, y * CellHeight + CellHeight }, gfx, pass[p]);
	}
}

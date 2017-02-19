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
	const float dif = (155.0f + 255.0f * 5.0f) / float(limit);
	float r = 0;
	float g = 0;
	float b = 100; // 1 color { 0, 0, 100 }
	int col = 0;
	for (int i = 0; i < limit; i++) {
		pass[i] = Color(int(r), int(g), int(b));
		if (b <= 255 && col == 0) {
			// 2 color { 0,0,255 }
			b += dif;
		}
		if (b > 255 && col == 0) {
			b = 255;
			col = 1;
			continue;
		}
		if (g <= 255 && col == 1) {
			// 3 color { 0,255,255 }
			g += dif;
		}
		if (g > 255 && col == 1) {
			g = 255;
			col = 2;
			continue;
		}
		if (r <= 255 && col == 2) {
			// 4 color { 255,255,0 }
			r += dif;
			b -= dif;
		}
		if (r > 255 && col == 2) {
			r = 255;
			b = 0;
			col = 3;
			continue;
		}
		if (g >= 0 && col == 3) {
			// 5 color { 255,0,0 }
			g -= dif;
		}
		if (g < 0 && col == 3) {
			g = 0;
			col = 4;
			continue;
		}
		if (b <= 255 && col == 4) {
			// 6 color { 255,0,255 }
			b += dif;
		}
		if (b > 255 && col == 4) {
			b = 255;
			col = 5;
			continue;
		}
		if (col == 5) {
			r = 0;
			g = 0;
			b = 0;
		}
	}
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

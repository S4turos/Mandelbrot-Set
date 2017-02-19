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
#include "Matrix.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Matrix matrix;
	const int limit = 20;
	/********************************/
	const double CellWidth = double(Graphics::ScreenWidth) / double(Matrix::gridsX);
	const double CellHeight = double(Graphics::ScreenHeight) / double(Matrix::gridsY);
	const int halfX = (Matrix::gridsX - 1) / 2;
	const int halfY = (Matrix::gridsY - 1) / 2;
	const double scalerX = (Matrix::gridsX - 1) / 4.0f;
	const double scalerY = (Matrix::gridsY - 1) / 4.0f;
	const double dif = 255.0f / double(limit);
	Color pass[20] = {
		{ 5,7,103 },
		{ 17,57,151 },
		{ 21, 100, 147 },
		{ 32,125,136 },
		{ 31,137,87 },
		{ 46,138,30 },
		{ 131,147,21 },
		{ 204,215,6 },
		{ 217,153,4 },
		{ 220,105,1 },
		{ 221, 66, 0 },
		{ 187, 37, 0 },
		{ 187, 0, 0 },
		{ 210, 0, 0 },
		{ 255, 0, 0 },
		{ 190,0,0 },
		{ 140,0,0 },
		{ 90, 0, 0 },
		{ 45,0,0 },
		{ 0,0,0 }
	};
};
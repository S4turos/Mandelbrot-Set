#include "Matrix.h"

Matrix::Matrix(const Vec2 & topleft, const Vec2 & bottomright)
	:
	topleft(topleft),
	bottomright(bottomright)
{
}

void Matrix::DrawCell(Graphics & gfx, Color c) const
{
	gfx.DrawRect(topleft, bottomright, c);
}

void Matrix::DrawCell(const Vec2& cell, Graphics & gfx, Color c, Matrix matrix[])
{
	const int y = -int(cell.y) + (gridsY - 1) / 2;
	const int x = int(cell.x) + (gridsX - 1) / 2;
	const int index = y * gridsX + x;
	matrix[index].DrawCell(gfx, c);
}

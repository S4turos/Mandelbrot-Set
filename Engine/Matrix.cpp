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

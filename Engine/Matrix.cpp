#include "Matrix.h"

Matrix::Matrix(const Vec2 & topleft, const Vec2 & bottomright, const Vec2& c, Color color)
	:
	topleft(topleft),
	bottomright(bottomright),
	c(c),
	color(color)
{
}

void Matrix::DrawCell(Graphics & gfx) const
{
	gfx.DrawRect(topleft, bottomright, color);
}
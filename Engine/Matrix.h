#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Matrix {
public:
	Matrix() = default;
	Matrix(const Vec2& topleft, const Vec2& bottomright);
	void DrawCell(Graphics& gfx, Color c) const;
private:
	Vec2 topleft;
	Vec2 bottomright;
};
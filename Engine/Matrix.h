#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Matrix {
public:
	Matrix() = default;
	Matrix(const Vec2& topleft, const Vec2& bottomright, const Vec2& c, Color color);
	void DrawCell(Graphics& gfx) const;
private:
	Vec2 topleft;
	Vec2 bottomright;
	Vec2 c;
	Color color;
public:
	static constexpr int gridsX = 187;
	static constexpr int gridsY = 187;
	static constexpr int grids = gridsX * gridsY;
};
#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Matrix {
public:
	Matrix() = default;
	Matrix(const Vec2& topleft, const Vec2& bottomright, const Vec2& c, Color color);
	static void DrawCell(const Vec2& topleft, const Vec2& bottomright, Graphics& gfx, Color color);
private:
	Vec2 topleft;
	Vec2 bottomright;
	Vec2 c;
	Color color;
public:
	static constexpr int gridsX = 800;
	static constexpr int gridsY = 800;
	static constexpr int grids = gridsX * gridsY;
};
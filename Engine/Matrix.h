#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Matrix {
public:
	Matrix() = default;
	Matrix(const Vec2& topleft, const Vec2& bottomright);
	void DrawCell(Graphics& gfx, Color c) const;
	static void DrawCell(const Vec2& cell, Graphics& gfx, Color c, Matrix matrix[]);
private:
	Vec2 topleft;
	Vec2 bottomright;
public:
	static constexpr int gridsX = 81;
	static constexpr int gridsY = 81;
	static constexpr int grids = gridsX * gridsY;
};
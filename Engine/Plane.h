#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"

class Plane {
public:
	Plane();
	void DrawCell(const Vec2& topleft, const Vec2& bottomright, Graphics& gfx, Color color) const;
	void DoFullIteration(Graphics& gfx) const;
	void ZoomIn();
	void ZoomOut();
	void Move(Keyboard& kbd);
private:
	const double VelZoom = 0.1;
	double limitTop = 2.0;
	double limitBottom = -2.0;
	double limitLeft = -2.0;
	double limitRight = 2.0;
	static constexpr int iterations = 100;
	Color colorpass[iterations];
	static constexpr int gridsX = 800;
	static constexpr int gridsY = 800;
	static constexpr int grids = gridsX * gridsY;
	static constexpr double CellWidth = double(Graphics::ScreenWidth) / double(gridsX);
	static constexpr double CellHeight = double(Graphics::ScreenHeight) / double(gridsY);
};
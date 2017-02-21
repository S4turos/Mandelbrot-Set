#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"
#include <vector>

class Plane {
public:
	Plane();
	Plane(const double limitLeft, const double limitRight, const double limitTop, const double limitBottom);
	void CreateColors();
	void DrawCell(const Vec2& topleft, const Vec2& bottomright, Graphics& gfx, Color color) const;
	void DoFullIteration(Graphics& gfx) const;
	void ZoomIn();
	void ZoomOut();
	void Move(Keyboard& kbd);
private:
	double speed = 1.0 / 40.0;
	int iterations = 100;
	std::vector<Color> colorpass;
	double limitTop = 2.0;
	double limitBottom = -2.0;
	double limitLeft = -2.0;
	double limitRight = 2.0;
	static constexpr int gridsX = 800;
	static constexpr int gridsY = 800;
	static constexpr int grids = gridsX * gridsY;
	static constexpr double CellWidth = double(Graphics::ScreenWidth) / double(gridsX);
	static constexpr double CellHeight = double(Graphics::ScreenHeight) / double(gridsY);
};
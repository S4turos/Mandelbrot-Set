#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Camera.h"
#include <vector>

class Plane {
public:
	Plane();
	void CreateColors();
	void DrawCell(const Vec2& topleft, const Vec2& bottomright, Graphics& gfx, Color color) const;
	void DoFullIteration(Graphics& gfx, Camera& camera) const;
	void IncreaseIterations();
	void DecreaseIterations();
	void Reset();
private:
	int iterations = 100;
	std::vector<Color> colorpass;
	static constexpr int gridsX = 800;
	static constexpr int gridsY = 800;
	static constexpr int grids = gridsX * gridsY;
	static constexpr double CellWidth = double(Graphics::ScreenWidth) / double(gridsX);
	static constexpr double CellHeight = double(Graphics::ScreenHeight) / double(gridsY);
};
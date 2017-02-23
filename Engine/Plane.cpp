#include "Plane.h"
#include <assert.h>


Plane::Plane()
{
	CreateColors();
}

void Plane::CreateColors()
{
	colorpass.clear();
	static constexpr int ncolors = 6;
	int colors[ncolors * 3] = {
		0,6,90,
		34,110,204,
		151,214,245,
		254,157,0,
		51,2,47,
		255,255,255
	};
	colorpass.push_back(Color(colors[0], colors[1], colors[2]));
	const float steps = (float(iterations) - 2) / (float(ncolors) - 1);
	int k = 0;
	int j = 0;
	for (int i = 1; i < ncolors; i++) {
		k++;
		int times = int(steps * k);
		int actualIndex = (k - 1) * 3;
		int nextIndex = k * 3;
		assert(nextIndex < ncolors * 3); // checks if the index of the array is out of range
		float r = float(colors[actualIndex]);
		float g = float(colors[actualIndex + 1]);
		float b = float(colors[actualIndex + 2]);
		float rdif = (colors[nextIndex] - colors[actualIndex]) / float(times - j);
		float gdif = (colors[nextIndex + 1] - colors[actualIndex + 1]) / float(times - j);
		float bdif = (colors[nextIndex + 2] - colors[actualIndex + 2]) / float(times - j);
		for (j; j < times; j++) {
			colorpass.push_back(Color(int(r += rdif), int(g += gdif), int(b += bdif)));
		}
	}
	colorpass.push_back(Color(0, 0, 0));
}

void Plane::DrawCell(const Vec2 & topleft, const Vec2 & bottomright, Graphics & gfx, Color color) const
{
	gfx.DrawRect(topleft, bottomright, color);
}

void Plane::DoFullIteration(Graphics & gfx, Camera& camera) const
{
	const double left = camera.GetLeft();
	const double right = camera.GetRight();
	const double top = camera.GetTop();
	const double bottom = camera.GetBottom();
	const double difX = (right - left) / double(gridsX);
	const double difY = (top - bottom) / double(gridsY);

	for (int i = 0; i < grids; i++) {
		int x = i % gridsX;
		int y = i / gridsY;
		Vec2 c(x * difX + left, -y * difY + top);
		int p = 0;
		Vec2 iteration(0.0f, 0.0f);
		while (true) {
			// here is where the result of every grid is calculated
			// p is the number for every pass or iteration
			double xnew = iteration.x * iteration.x - iteration.y * iteration.y + c.x;
			iteration.y = 2 * iteration.x * iteration.y + c.y;
			iteration.x = xnew;
			double result = iteration.x * iteration.x + iteration.y * iteration.y;
			if (result > 4.0f || p == iterations - 1) {
				break;
			}
			p++;
		}
		assert(p < colorpass.size()); // checks if the index of the vector is out of range
		DrawCell({ x * CellWidth, y * CellHeight },
		{ x * CellWidth + CellWidth, y * CellHeight + CellHeight }, gfx, colorpass[p]);
	}
}

void Plane::IncreaseIterations()
{
	if (iterations < 1500) {
		iterations += 50;
		CreateColors();
	}
}

void Plane::DecreaseIterations()
{
	if (iterations > 100) {
		iterations -= 50;
		CreateColors();
	}
}

void Plane::Reset()
{
	iterations = 100;
	CreateColors();
}

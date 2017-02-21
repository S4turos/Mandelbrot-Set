#include "Plane.h"



Plane::Plane()
{
	const float dif = (155.0f + 255.0f * 5.0f) / float(iterations);
	float r = 0;
	float g = 0;
	float b = 100; // 1 color { 0, 0, 100 }
	int col = 0;
	for (int i = 0; i < iterations; i++) {
		colorpass[i] = Color(int(r), int(g), int(b));
		if (b <= 255 && col == 0) {
			// 2 color { 0,0,255 }
			b += dif;
		}
		if (b > 255 && col == 0) {
			b = 255;
			col = 1;
			continue;
		}
		if (g <= 255 && col == 1) {
			// 3 color { 0,255,255 }
			g += dif;
		}
		if (g > 255 && col == 1) {
			g = 255;
			col = 2;
			continue;
		}
		if (r <= 255 && col == 2) {
			// 4 color { 255,255,0 }
			r += dif;
			b -= dif;
		}
		if (r > 255 && col == 2) {
			r = 255;
			b = 0;
			col = 3;
			continue;
		}
		if (g >= 0 && col == 3) {
			// 5 color { 255,0,0 }
			g -= dif;
		}
		if (g < 0 && col == 3) {
			g = 0;
			col = 4;
			continue;
		}
		if (b <= 255 && col == 4) {
			// 6 color { 255,0,255 }
			b += dif;
		}
		if (b > 255 && col == 4) {
			b = 255;
			col = 5;
			continue;
		}
		if (col == 5) {
			r = 0;
			g = 0;
			b = 0;
		}
	}
}

void Plane::DrawCell(const Vec2 & topleft, const Vec2 & bottomright, Graphics & gfx, Color color) const
{
	gfx.DrawRect(topleft, bottomright, color);
}

void Plane::DoFullIteration(Graphics & gfx) const
{
	const int halfWidth = gridsX / 2;
	const int halfHeight = gridsY / 2;
	Vec2 scaler;
	scaler.x = double(halfWidth) / limitRight;
	scaler.y = double(halfHeight) / limitTop;
	for (int i = 0; i < grids; i++) {
		int x = i % gridsX;
		int y = i / gridsY;
		Vec2 c(double(x - halfWidth) / scaler.x, -double(y - halfHeight) / scaler.y);
		int p = 0;
		Vec2 iteration(0.0f, 0.0f);
		while (true) {
			// Aquí debes hacer todos los cálculos para cada casilla
			// p es cada pass
			double xnew = iteration.x * iteration.x - iteration.y * iteration.y + c.x;
			iteration.y = 2 * iteration.x * iteration.y + c.y;
			iteration.x = xnew;
			double result = iteration.x * iteration.x + iteration.y * iteration.y;
			if (result >= 4.0f || p == iterations - 1) {
				break;
			}
			p++;
		}

		DrawCell({ x * CellWidth, y * CellHeight },
		{ x * CellWidth + CellWidth, y * CellHeight + CellHeight }, gfx, colorpass[p]);
	}
}

void Plane::ZoomIn()
{
	limitTop -= VelZoom;
	limitRight -= VelZoom;
	limitLeft += VelZoom;
	limitBottom += VelZoom;
}

void Plane::ZoomOut()
{
	limitTop += VelZoom;
	limitRight += VelZoom;
	limitLeft -= VelZoom;
	limitBottom -= VelZoom;
	if (limitTop > 2.0) {
		limitTop = 2.0;
	}
	if (limitRight > 2.0) {
		limitRight = 2.0;
	}
	if (limitLeft < -2.0) {
		limitLeft = -2.0;
	}
	if (limitBottom < -2.0) {
		limitBottom = 2.0;
	}
}

void Plane::Move(Keyboard & kbd)
{
	if (kbd.KeyIsPressed('A')) {
		limitLeft -= VelZoom;
		limitRight -= VelZoom;
	}
	else if (kbd.KeyIsPressed('S')) {
		limitTop -= VelZoom;
		limitBottom -= VelZoom;
	}
	else if (kbd.KeyIsPressed('D')) {
		limitLeft += VelZoom;
		limitRight += VelZoom;
	}
	else if (kbd.KeyIsPressed('W')) {
		limitTop += VelZoom;
		limitBottom += VelZoom;
	}
	if (limitLeft < -2.0) {
		limitLeft = -2.0;
	}
	if (limitRight > 2.0) {
		limitRight = 2.0;
	}
	if (limitTop > 2.0) {
		limitTop = 2.0;
	}
	if (limitBottom < -2.0) {
		limitBottom = -2.0;
	}
}

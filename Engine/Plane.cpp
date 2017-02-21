#include "Plane.h"


Plane::Plane()
{
	CreateColors();
}

Plane::Plane(const double limitLeft, const double limitRight, const double limitTop, const double limitBottom)
	:
	limitLeft(limitLeft),
	limitRight(limitRight),
	limitTop(limitTop),
	limitBottom(limitBottom)
{
	CreateColors();
}

void Plane::CreateColors()
{
	colorpass.clear();
	const float dif = (155.0f + 255.0f * 5.0f) / float(iterations);
	float r = 0;
	float g = 0;
	float b = 100; // 1 color { 0, 0, 100 }
	int col = 0;
	for (int i = 0; i < iterations; i++) {
		colorpass.push_back(Color(int(r), int(g), int(b)));
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
	const double difX = (limitRight - limitLeft) / double(gridsX);
	const double difY = (limitTop - limitBottom) / double(gridsY);

	for (int i = 0; i < grids; i++) {
		int x = i % gridsX;
		int y = i / gridsY;
		Vec2 c(x * difX + limitLeft, -y * difY + limitTop);
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
	const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
	const double vel = levelzoom * speed;
	limitTop -= vel;
	limitRight -= vel;
	limitLeft += vel;
	limitBottom += vel;
}

void Plane::ZoomOut()
{
	const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
	const double vel = levelzoom * speed;
	limitTop += vel;
	limitRight += vel;
	limitLeft -= vel;
	limitBottom -= vel;
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
		limitBottom = -2.0;
	}
}

void Plane::Move(Keyboard & kbd)
{
	if (kbd.KeyIsPressed(VK_LEFT)) {
		const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
		const double vel = levelzoom * speed;
		limitLeft -= vel;
		limitRight -= vel;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT)) {
		const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
		const double vel = levelzoom * speed;
		limitLeft += vel;
		limitRight += vel;
	}
	if (kbd.KeyIsPressed(VK_DOWN)) {
		const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
		const double vel = levelzoom * speed;
		limitTop -= vel;
		limitBottom -= vel;
	}
	else if (kbd.KeyIsPressed(VK_UP)) {
		const double levelzoom = limitTop - limitBottom + limitRight - limitLeft;
		const double vel = levelzoom * speed;
		limitTop += vel;
		limitBottom += vel;
	}
	if (kbd.KeyIsPressed('Q')) {
		if (iterations > 100) {
			iterations -= 100;
			CreateColors();
		}
	}
	else if (kbd.KeyIsPressed('E')) {
		if (iterations < 1000) {
			iterations += 100;
			CreateColors();
		}
	}
	if (kbd.KeyIsPressed(VK_SPACE)) {
		limitTop = 2.0;
		limitBottom = -2.0;
		limitLeft = -2.0;
		limitRight = 2.0;
		speed = 1.0 / 40.0;
		iterations = 100;
		CreateColors();
	}
	if (kbd.KeyIsPressed('W')) {
		if (speed < 1.0 / 10.0) {
			double denominador = 1.0 / speed;
			denominador -= 10.0;
			speed = 1.0 / denominador;
		}
	}
	else if (kbd.KeyIsPressed('S')) {
		if (speed > 1.0 / 100.0) {
			double denominador = 1.0 / speed;
			denominador += 10.0;
			speed = 1.0 / denominador;
		}
	}
	if (limitLeft < -2.0) {
		const double dif = -limitLeft - 2.0;
		limitLeft += dif;
		limitRight += dif;
	}
	if (limitRight > 2.0) {
		const double dif = limitRight - 2.0;
		limitLeft -= dif;
		limitRight -= dif;
	}
	if (limitTop > 2.0) {
		const double dif = limitTop - 2.0;
		limitTop -= dif;
		limitBottom -= dif;
	}
	if (limitBottom < -2.0) {
		const double dif = -limitBottom - 2.0;
		limitTop += dif;
		limitBottom += dif;
	}
}

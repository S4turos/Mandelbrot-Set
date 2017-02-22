#include "Plane.h"
#include <assert.h>


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
		assert(nextIndex < ncolors * 3); // checks if array out of range
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
			if (result > 4.0f || p == iterations - 1) {
				break;
			}
			p++;
		}
		assert(p < colorpass.size()); // checks if vector out of range
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

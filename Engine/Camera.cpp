#include "Camera.h"
#include "Graphics.h"
#include <assert.h>

Camera::Camera(const double borderLeft, const double borderRight, const double borderTop, const double borderBottom)
	:
	borderLeft(borderLeft),
	borderRight(borderRight),
	borderTop(borderTop),
	borderBottom(borderBottom)
{
}

void Camera::MoveLeft()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	left -= vel;
	right -= vel;
	if (left < borderLeft) {
		const double dif = borderLeft - left;
		left += dif;
		right += dif;
	}
}

void Camera::MoveRight()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	left += vel;
	right += vel;
	if (right > borderRight) {
		const double dif = right - borderRight;
		left -= dif;
		right -= dif;
	}
}

void Camera::MoveUp()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	top += vel;
	bottom += vel;
	if (top > borderTop) {
		const double dif = top - borderTop;
		top -= dif;
		bottom -= dif;
	}
}

void Camera::MoveDown()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	top -= vel;
	bottom -= vel;
	if (bottom < borderBottom) {
		const double dif = borderBottom - bottom;
		top += dif;
		bottom += dif;
	}
}

void Camera::ZoomIn()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	top -= vel;
	right -= vel;
	left += vel;
	bottom += vel;

	if (top - bottom < double(Graphics::ScreenHeight) * 0.0000000000000001 || 
		right - left < double(Graphics::ScreenWidth) * 0.0000000000000001) {
		top += vel;
		right += vel;
		left -= vel;
		bottom -= vel;
	}
}

void Camera::ZoomOut()
{
	const double levelzoom = GetZoom();
	const double vel = levelzoom * speed;
	top += vel;
	right += vel;
	left -= vel;
	bottom -= vel;

	if (top > borderTop) {
		top = borderTop;
		const double height = top - bottom;
		const double width = right - left;
		bottom -= width - height;
		if (bottom < borderBottom) {
			bottom = borderBottom;
		}
	}
	if (right > borderRight) {
		right = borderRight;
		const double height = top - bottom;
		const double width = right - left;
		left -= height - width;
		if (left < borderLeft) {
			left = borderLeft;
		}
	}
	if (left < borderLeft) {
		left = borderLeft;
		const double height = top - bottom;
		const double width = right - left;
		right += height - width;
		if (right > borderRight) {
			right = borderRight;
		}
	}
	if (bottom < borderBottom) {
		bottom = borderBottom;
		const double height = top - bottom;
		const double width = right - left;
		top += width - height;
		if (top > borderTop) {
			top = borderTop;
		}
	}
	assert(left >= borderLeft);
	assert(right <= borderRight);
	assert(top <= borderTop);
	assert(bottom >= borderBottom);
}

void Camera::MoveFaster()
{
	if (speed < 1.0 / 10.0) {
		double denominator = 1.0 / speed;
		denominator -= 10.0;
		speed = 1.0 / denominator;
	}
}

void Camera::MoveSlower()
{
	if (speed > 1.0 / 100.0) {
		double denominator = 1.0 / speed;
		denominator += 10.0;
		speed = 1.0 / denominator;
	}
}

void Camera::Reset()
{
	top = borderTop;
	bottom = borderBottom;
	left = borderLeft;
	right = borderRight;
	speed = 1.0 / 40.0;
}

double Camera::GetZoom() const
{
	return top - bottom + right - left;
}

double Camera::GetLeft() const
{
	return left;
}

double Camera::GetRight() const
{
	return right;
}

double Camera::GetTop() const
{
	return top;
}

double Camera::GetBottom() const
{
	return bottom;
}

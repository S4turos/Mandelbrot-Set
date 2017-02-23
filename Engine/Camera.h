#pragma once

class Camera {
public:
	Camera(const double borderLeft, const double borderRight, const double borderTop, const double borderBottom);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void ZoomIn(const int gridsX, const int gridsY);
	void ZoomOut();
	void MoveFaster();
	void MoveSlower();
	void Reset();
	double GetZoom() const;
	double GetLeft() const;
	double GetRight() const;
	double GetTop() const;
	double GetBottom() const;
private:
	double speed = 1.0 / 40.0;
	const double borderLeft;
	const double borderRight;
	const double borderTop;
	const double borderBottom;
	double left = borderLeft;
	double right = borderRight;
	double top = borderTop;
	double bottom = borderBottom;
};
#pragma once
#include "Header.h"

typedef struct Bounds
{
	float top, bottom, left, right;

	Bounds()
	{
		top = left = 0;
		right = bottom = 1;
	}
	Bounds(float top, float left, float bottom, float right)
	{
		this->top = top;
		this->left = left;
		this->bottom = bottom;
		this->right = right;
	}
	Bounds(Vector2 topLeft, Vector2 size)
	{
		top = topLeft.y;
		left = topLeft.x;
		right = left + size.x;
		bottom = top + size.y;
	}
	~Bounds() = default;

	Vector2 TopLeft() const { return Vector2(top, left); }
	Vector2 Size() const { return Vector2(right - left, bottom - top); }

	void GetBounds(float &t, float &l, float &r, float &b)
	{
		t = top; l = left; r = right; b = bottom;
	}


	Bounds& operator= (const Bounds &_bounds) = default;
};

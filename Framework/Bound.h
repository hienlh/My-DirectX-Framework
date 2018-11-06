#pragma once
#include "stdafx.h"

typedef struct Bound
{
	float top, bottom, left, right;

	Bound()
	{
		top = left = 0;
		right = bottom = 1;
	}
	Bound(float top, float left, float bottom, float right)
	{
		this->top = top;
		this->left = left;
		this->bottom = bottom;
		this->right = right;
	}
	Bound(Vector2 topLeft, Vector2 size)
	{
		top = topLeft.y;
		left = topLeft.x;
		right = left + size.x;
		bottom = top + size.y;
	}
	~Bound() = default;

	Vector2 TopLeft() const { return Vector2(top, left); }
	Vector2 Size() const { return Vector2(right - left, bottom - top); }

	void GetBound(float &t, float &l, float &r, float &b)
	{
		t = top; l = left; r = right; b = bottom;
	}

	Bound& operator= (const Bound &_bounds) = default;
};
#pragma once

namespace IsoEngine
{
	class Vector2D
	{
	public:
		float x;
		float y;
		
		Vector2D() {}
		Vector2D(float x, float y);
		Vector2D(const Vector2D& vector);

		Vector2D operator+(const Vector2D& other);
		Vector2D operator-(const Vector2D& other);
		Vector2D operator*(float scalar);
		Vector2D operator+=(const Vector2D& other);
		Vector2D operator-=(const Vector2D& other);

		static const Vector2D Zero;
		static const Vector2D One;
		static const Vector2D Left;
		static const Vector2D Right;
		static const Vector2D Up;
		static const Vector2D Down;

	};
}



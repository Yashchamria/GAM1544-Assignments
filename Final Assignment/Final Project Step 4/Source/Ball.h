#pragma once

#include <GameDev2D.h>


namespace GameDev2D
{
	class Ball : public Drawable
	{
	public:
		Ball();
		~Ball();

		void Update(double delta);
		void Draw();
		void Reset();

		float GetWidth();
		float GetHeight();

		float GetRadius();

		void SetVelocity(const Vector2& velocity);
		Vector2 GetVelocity();

		void ApplyGravity(Vector2 gravity, double delta);

	private:
		//Member variables
		Polygon* m_Ball;
		Vector2 m_Velocity;
	};
}
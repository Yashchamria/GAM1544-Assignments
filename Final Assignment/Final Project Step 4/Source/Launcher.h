#pragma once

#include <GameDev2D.h>
#include "Ball.h"

namespace GameDev2D
{
	class Launcher
	{
	public: 
		Launcher(Ball* ball);
		~Launcher();

		void Update(double delta);
		void Draw();

		void HandleMouseMove(float x, float y);

		Vector2 GetLaunchPosition();
		Vector2 GetInitialVelocity();

		void Fire();

        void ResetBall(bool resetBall);

	private:
		Ball* m_Ball;
		Polygon* m_Body;
		Polygon* m_Arm;
        bool m_ResetBall;
	};
}
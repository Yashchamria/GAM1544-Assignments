#pragma once

#include <GameDev2D.h>


namespace GameDev2D
{
	class Trajectory
	{
	public:
		Trajectory();
		~Trajectory();

		void Draw();

		void Clear();

		void Add(const Vector2& position);
		
		void Show();
		void Hide();

	private:
		std::vector<Vector2> m_Path;
		Polygon* m_PathPoint;
		bool m_CanDraw;
	};
}
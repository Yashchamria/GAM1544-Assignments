#pragma once

#include <GameDev2D.h>
#include "Timer.h"


namespace GameDev2D
{
	class Catcher : public Drawable
	{
	public:
		Catcher();
		~Catcher();

		void Update(double delta);
		void Draw();

		float GetWidth();
		float GetHeight();

	private:
		Polygon* m_Box;
		Timer m_Timer;
	};
}
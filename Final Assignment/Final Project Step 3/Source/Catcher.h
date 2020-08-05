#pragma once
#include "Timer.h"
#include "Constants.h"
#include <GameDev2D.h>

class Catcher
{
private:
	GameDev2D::Polygon* m_catcher;
	Timer m_timer;

public:
	Catcher();
	void Draw();
	void Update(double delta);
	GameDev2D::Vector2 Getposition();
};
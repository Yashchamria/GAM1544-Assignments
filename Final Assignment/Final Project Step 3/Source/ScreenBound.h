#pragma once
#include <GameDev2D.h>

class ScreenBound
{
private:
	GameDev2D::Polygon* m_leftBound;
	GameDev2D::Polygon* m_rightBound;
	GameDev2D::Polygon* m_line;

public:
	ScreenBound();
	~ScreenBound();
	void Draw();
	GameDev2D::Vector2 GetLeftPosition();
	GameDev2D::Vector2 GetRightPosition();
};
#pragma once
#include <GameDev2D.h>

class Launcher
{
private:
	GameDev2D::Polygon* m_turretBase;
	GameDev2D::Polygon* m_turret;

public:
	Launcher();
	~Launcher();
	GameDev2D::Vector2 GetPosition();
	void SetRadians(float angle);
	void Update(float angle);
	void Draw();
	void Reset(bool Enable, int j);
};
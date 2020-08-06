#pragma once
#include <GameDev2D.h>


class Trajectory
{
private:
    GameDev2D::Polygon* m_TrajectoryPoint;
    std::vector<GameDev2D::Vector2> m_Trajectory;
    GameDev2D::Vector2 m_velocity;


public:
    Trajectory();
    ~Trajectory();
    void Draw();
    void Trajectory::Update(GameDev2D::Vector2 position, float angle);
};
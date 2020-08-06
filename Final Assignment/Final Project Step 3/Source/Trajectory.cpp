#include "Trajectory.h"
#include <vector>
#include "Constants.h"

Trajectory::Trajectory()
{
    m_TrajectoryPoint = new GameDev2D::Polygon();
    m_TrajectoryPoint->MakeCircle(3.0f, true);
}

Trajectory::~Trajectory()
{
    if (m_TrajectoryPoint != nullptr)
    {
        delete m_TrajectoryPoint;
        m_TrajectoryPoint = nullptr;
    }
}

void Trajectory::Draw()
{
    for (int i = 0; i < m_Trajectory.size(); i++)
    {
        GameDev2D::Vector2 point = m_Trajectory.at(i);
        m_TrajectoryPoint->SetPosition(point);
        m_TrajectoryPoint->Draw();
    }
}

void Trajectory::Update(GameDev2D::Vector2 ballPosition, float angle)
{
    GameDev2D::Vector2 position = ballPosition;

    GameDev2D::Vector2 velocity = GameDev2D::Vector2(cosf(angle), sinf(angle)) * SPEED;

    if (GameDev2D::Math::RadiansToDegrees(angle) <= 0)
    {
        m_Trajectory.clear();

        for (int i = 0; i < 240; i++)
        {
            GameDev2D::Vector2 point = GameDev2D::Math::CalculateTrajectory(position, velocity, GRAVITY, TARGET_FPS, i);
            m_Trajectory.push_back(point);
        }
    }
}


#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
    m_turretBase = new GameDev2D::Polygon();
    m_turretBase->MakeRectangle(100, 130, true);
    m_turretBase->SetAnchor(0, 0);
    m_turretBase->SetPosition(50, 0);

    m_turretTop = new GameDev2D::Polygon();
    m_turretTop->MakeCircle(50, true, 48.0f);
    m_turretTop->SetAnchor(0, 0);
    m_turretTop->SetPosition(50, 80);

    m_turret = new GameDev2D::Polygon();
    m_turret->MakeRectangle(24, 90, true);
    m_turret->SetAnchor(0.5f, 0);
    m_turret->SetPosition(100, 130);

    m_ball = new GameDev2D::Polygon();
    m_ball->MakeCircle(12, true, 36.0f);
    m_ball->SetAnchor(0.5f, 0.5f);
    m_ball->SetPosition(m_turret->GetPosition().x, m_turret->GetPosition().y + 90);
    m_ball->SetColor(Color::CrimsonRedColor());

    m_TrajectoryPoint = new GameDev2D::Polygon();
    m_TrajectoryPoint->MakeCircle(3.0f, true);

}

Game::~Game()
{
    if (m_TrajectoryPoint != nullptr)
    {
        delete m_TrajectoryPoint;
        m_TrajectoryPoint = nullptr;
    }

    if (m_ball != nullptr)
    {
        delete m_ball;
        m_ball = nullptr;
    }

    if (m_turret != nullptr)
    {
        delete m_turret;
        m_turret = nullptr;
    }

    if (m_turretTop != nullptr)
    {
        delete m_turretTop;
        m_turretTop = nullptr;
    }

    if (m_turretBase != nullptr)
    {
        delete m_turretBase;
        m_turretBase = nullptr;
    }
}

void Game::Update(double delta)
{
    m_direction = m_TargetPosition - m_turret->GetPosition();
    m_angle = atan2f(m_direction.y, m_direction.x);

    if (Math::RadiansToDegrees(m_angle) < 180 && Math::RadiansToDegrees(m_angle) > 0)
    {
        m_turret->SetRadians(m_angle - Math::DegreesToRadians(90));
    }

    if (Math::RadiansToDegrees(m_angle) < 180 && Math::RadiansToDegrees(m_angle) > 0)
    {
        m_ballPosition = m_turret->GetPosition() + GameDev2D::Vector2(cos(m_angle),
            sin(m_angle)) * 90;

        m_ball->SetPosition(m_ballPosition);
    }

    Vector2 position = m_ball->GetPosition();
    GameDev2D::Vector2 increment = GameDev2D::Vector2(m_velocity.x + SPEED, m_velocity.y) * delta;
    m_TrajectoryPoint->SetPosition(position + increment);


    Vector2 velocity = Vector2(cosf(m_angle), sinf(m_angle)) * SPEED;

    if (Math::RadiansToDegrees(m_angle) < 180 && Math::RadiansToDegrees(m_angle) > 0)
    {
        m_Trajectory.clear();

        for (int i = 0; i < 240; i++)
        {
            Vector2 point = Math::CalculateTrajectory(m_ball->GetPosition(), velocity, GRAVITY, TARGET_FPS, i);
            m_Trajectory.push_back(point);
        }
    }
    if (m_ballEnable)
    {
        Vector2 point = Math::CalculateTrajectory(m_ball->GetPosition(), velocity, GRAVITY, TARGET_FPS, i);
        m_ball->SetPosition(point);
        i++;
    }
}

void Game::Draw()
{
    for (int i = 0; i < m_Trajectory.size(); i++)
    {
        Vector2 point = m_Trajectory.at(i);
        m_TrajectoryPoint->SetPosition(point);
        m_TrajectoryPoint->Draw();
    }

    m_turretBase->Draw();
    m_turretTop->Draw();
    m_ball->Draw();
    m_turret->Draw();
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{
    m_ballEnable = true;
}

void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
{
    m_TargetPosition = GameDev2D::Vector2(aMouseX, aMouseY);
}

void Game::HandleKeyPress(Keyboard::Key aKey)
{
    if( aKey == Keyboard::Key::Escape )
    {
        Services::GetApplication()->Shutdown();
    }
}

void Game::HandleKeyReleased(Keyboard::Key key)
{
    if (key == Keyboard::Key::R)
    {
        m_ballEnable = false;
        i = 0;
    }
}

#include "Ball.h"
#include "Constants.h"
Ball::Ball()
{
    m_ball = new GameDev2D::Polygon();
    m_ball->MakeCircle(BALL_RADIUS, true, 24.0f);
    m_ball->SetAnchor(0.5f, 0.5f);
    m_ball->SetColor(GameDev2D::Color::CrimsonRedColor());
}

Ball::~Ball()
{
    if (m_ball != nullptr)
    {
        delete m_ball;
        m_ball = nullptr;
    }
}

void Ball::SetBallPosition(GameDev2D::Vector2 position)
{
    m_ball->SetPosition(position);
}

GameDev2D::Vector2 Ball::GetBallPosition()
{
    return m_ball->GetPosition();
}

void Ball::SetBallVelocity(GameDev2D::Vector2 velocity)
{
    m_ballVelocity = velocity;
}

GameDev2D::Vector2 Ball::GetBallVelocity()
{
    return m_ballVelocity;
}

void Ball::SetBallLaunchPosition(GameDev2D::Vector2 launchPosition)
{
    m_ballLaunchPosition = launchPosition;
}

GameDev2D::Vector2 Ball::GetBallLaunchPosition()
{
    return m_ballLaunchPosition;
}

void Ball::Draw()
{
    m_ball->Draw();
}

void Ball::Update(float angle, GameDev2D::Vector2 launcherPosition)
{
    if (GameDev2D::Math::RadiansToDegrees(angle) <= 0)
    {
        m_ball->SetPosition(launcherPosition + GameDev2D::Vector2(cos(angle), sin(angle)) * 120);
    }
}

/*void Ball::IsEnable(bool enable, int j, int chances)
{
    if (enable)
    {
        GameDev2D::Vector2 point = GameDev2D::Math::CalculateTrajectory(m_ballLaunchPosition, m_ballVelocity, GRAVITY, TARGET_FPS, j);
        m_ball->SetPosition(point);

        if (!(m_ball->GetPosition().x >= WINDOW_WIDTH + 6 || m_ball->GetPosition().x <= -6 || m_ball->GetPosition().y <= -6))
        {
            j++;
        }
        else
        {
            if (chances > 0)
            {
                chances--;
            }

            Reset(enable, j);
        }
    }
}

void Ball::Reset(bool Enable, int k)
{
    Enable = false;
    k = 0;
}*/
#include <GameDev2D.h>
#include "Game.h"

using namespace GameDev2D;

Game::Game()
{
    m_Catcher = new Catcher();
    m_screenBound = new ScreenBound();

    m_line = new GameDev2D::Polygon();
    m_line->MakeRectangle(WINDOW_WIDTH, 2, true);
    m_line->SetAnchor(0.5f, 0.5f);
    m_line->SetPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT - 15);

    m_turretBase = new GameDev2D::Polygon();
    m_turretBase->MakeCircle(90, true, 48.0f);
    m_turretBase->SetAnchor(0.5, 0.5);
    m_turretBase->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 15);

    m_turret = new GameDev2D::Polygon();
    m_turret->MakeRectangle(24, 120, true);
    m_turret->SetAnchor(0.5f, 0);
    m_turret->SetPosition(m_turretBase->GetPosition());

    m_ball = new GameDev2D::Polygon();
    m_ball->MakeCircle(BALL_RADIUS, true, 24.0f);
    m_ball->SetAnchor(0.5f, 0.5f);
    m_ball->SetPosition(m_turret->GetPosition().x, m_turret->GetPosition().y + 120);
    m_ball->SetColor(Color::CrimsonRedColor());

    m_TrajectoryPoint = new GameDev2D::Polygon();
    m_TrajectoryPoint->MakeCircle(3.0f, true, 24.0f);

    int gap = 0;
    for (int i = 0; i < MAXIMUM_LIMIT; i++)
    {
        m_remainingBalls[i] = new GameDev2D::Polygon();
        m_remainingBalls[i]->MakeCircle(7.5f, true, 24.0f);
        m_remainingBalls[i]->SetAnchor(Vector2(0.5f, 0.5f));
        m_remainingBalls[i]->SetPosition(Vector2(7.5 + gap, WINDOW_HEIGHT - 5.75f));
        gap += 15;
    }

    LoadFont("heavy_data_150");
    m_label = new GameDev2D::SpriteFont("heavy_data_150");
    m_label->SetAnchor(GameDev2D::Vector2(0.5f, 0.5f));
    m_label->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

Game::~Game()
{
    if (m_TrajectoryPoint != nullptr)
    {
        delete m_TrajectoryPoint;
        m_TrajectoryPoint = nullptr;
    }

    if (m_Catcher != nullptr)
    {
        delete m_Catcher;
        m_Catcher = nullptr;
    }
    
    if (m_screenBound != nullptr)
    {
        delete m_screenBound;
        m_screenBound = nullptr;
    }

    //if(m_remainingBalls != nullptr)
    //    delete[] m_remainingBalls;

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

    if (m_line != nullptr)
    {
        delete m_line;
        m_line = nullptr;
    }

    if (m_turretBase != nullptr)
    {
        delete m_turretBase;
        m_turretBase = nullptr;
    }

    UnloadFont("heavy_data_150");

    if (m_label != nullptr)
    {
        delete m_label;
        m_label = nullptr;
    }
}

void Game::Update(double delta)
{
    m_direction = m_TargetPosition - m_turret->GetPosition();
    m_angle = atan2f(m_direction.y, m_direction.x);

    if (Math::RadiansToDegrees(m_angle) <= 0)
    {
        m_turret->SetRadians(m_angle - Math::DegreesToRadians(90));

        m_ballPosition = m_turret->GetPosition() + GameDev2D::Vector2(cos(m_angle),sin(m_angle)) * 120;

       m_ball->SetPosition(m_ballPosition);
    }

    Vector2 position = m_ball->GetPosition();
    Vector2 velocity = Vector2(cosf(m_angle), sinf(m_angle)) * SPEED;

    if (Math::RadiansToDegrees(m_angle) <= 0)
    {
        m_Trajectory.clear();

        for (int i = 0; i < 240; i++)
        {
            Vector2 point = Math::CalculateTrajectory(position, velocity, GRAVITY, TARGET_FPS, i);
            m_Trajectory.push_back(point);
        }
    }

    if (m_ballEnable)
    {
        Vector2 point = Math::CalculateTrajectory(m_ballLaunchPosition, m_ballVelocity, GRAVITY, TARGET_FPS, i);
        m_ball->SetPosition(point);

        if (!(m_ball->GetPosition().x >= WINDOW_WIDTH + 6 || m_ball->GetPosition().x <= -6 || m_ball->GetPosition().y <= -6))
        {
            i++;
        }
        else
        {
            if (m_totalChance > 0)
            {
                m_totalChance--;
            }

            Reset();
        }
    }

    m_Catcher->Update(delta);

    GameDev2D::Vector2 closestPoint = GameDev2D::Math::CalculateClosestPoint(m_ball->GetPosition(), BALL_RADIUS, 
        m_Catcher->Getposition() + GameDev2D::Vector2(0, PLATFORM_HEIGHT / 2),
        m_Catcher->Getposition() + GameDev2D::Vector2(PLATFORM_WIDTH, PLATFORM_HEIGHT / 2));
     

    //Calculate collision
    float distanceSquared = m_ball->GetPosition().DistanceSquared(closestPoint);

    if (distanceSquared <= BALL_RADIUS * BALL_RADIUS)
    {       
        m_label->SetText("Free Ball!");
        m_counter = 1;

        m_totalChance++;
        Reset();

        if (m_totalChance > MAXIMUM_LIMIT)
        {
            m_totalChance = MAXIMUM_LIMIT;
        }
    }

    if (m_counter >= 0)
    {
        m_counter -= delta;
    }
    else
    {
        m_label->SetText("");
    }

    //Left Screen Bound

    GameDev2D::Vector2 leftPoint = GameDev2D::Math::CalculateClosestPoint(m_ball->GetPosition(), BALL_RADIUS,
        m_screenBound->GetLeftPosition(), m_screenBound->GetLeftPosition() + GameDev2D::Vector2(0, WINDOW_HEIGHT));

    float leftWallDistanceSquared = m_ball->GetPosition().DistanceSquared(leftPoint);

    //Calculate the collision response
    if (leftWallDistanceSquared <= BALL_RADIUS * BALL_RADIUS)
    {
        float distance = sqrtf(leftWallDistanceSquared);
        GameDev2D::Vector2 ballNormal = m_ballVelocity.Normalized();
        //GameDev2D::Vector2 wallNormal = (leftPoint - m_ball->GetPosition()) / distance;
        GameDev2D::Vector2 wallNormal = GameDev2D::Vector2(-1, 0);

        if (ballNormal.DotProduct(leftPoint - m_ball->GetPosition()) < 0)
        {
            wallNormal *= -1.0f;
        }

        if (wallNormal != GameDev2D::Vector2::Zero)
        {
            float dotResult = wallNormal.DotProduct(m_ballVelocity);
            GameDev2D::Vector2 reflection = (-2.0f * dotResult * wallNormal) + m_ballVelocity;
            m_ballVelocity = reflection;
            m_ball->SetPosition(closestPoint);
        }
    }

    //Right Screen Bound

    GameDev2D::Vector2 rightPoint = GameDev2D::Math::CalculateClosestPoint(m_ball->GetPosition(), BALL_RADIUS,
        m_screenBound->GetRightPosition(), m_screenBound->GetRightPosition() + GameDev2D::Vector2(0, WINDOW_HEIGHT));

    float rightWallDistanceSquared = m_ball->GetPosition().DistanceSquared(rightPoint);

    //Calculate the collision response
    if (rightWallDistanceSquared <= BALL_RADIUS * BALL_RADIUS)
    {
        float distance = sqrtf(rightWallDistanceSquared);
        GameDev2D::Vector2 ballNormal = m_ballVelocity.Normalized();
        //GameDev2D::Vector2 wallNormal = (rightPoint - m_ball->GetPosition()) / distance;
        GameDev2D::Vector2 wallNormal = GameDev2D::Vector2(1, 0);

        if (ballNormal.DotProduct(rightPoint - m_ball->GetPosition()) < 0)
        {
            wallNormal *= -1.0f;
        }

        if (wallNormal != GameDev2D::Vector2::Zero)
        {
            float dotResult = wallNormal.DotProduct(m_ballVelocity);
            GameDev2D::Vector2 reflection = (-2.0f * dotResult * wallNormal) + m_ballVelocity;
            m_ballVelocity = reflection;
        }
    }
}

void Game::Draw()
{
    m_label->Draw();
    m_screenBound->Draw();
 
    if (m_totalChance > 0)
    {
        for (int i = 0; i < m_Trajectory.size(); i++)
        {
            Vector2 point = m_Trajectory.at(i);
            m_TrajectoryPoint->SetPosition(point);
            m_TrajectoryPoint->Draw();
        }

        m_ball->Draw();
    }

    m_Catcher->Draw();

    m_turretBase->Draw();
    m_line->Draw();
    m_turret->Draw();

    for (int i = 0; i < m_totalChance; i++)
    {
        m_remainingBalls[i]->Draw();
    }
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{
    if (!m_ballEnable)
    {
        m_ballVelocity = Vector2(cosf(m_angle), sinf(m_angle)) * SPEED;
        m_ballLaunchPosition = m_ball->GetPosition();
    }
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

}

void Game::Reset()
{
    m_ballEnable = false;
    i = 0;
}
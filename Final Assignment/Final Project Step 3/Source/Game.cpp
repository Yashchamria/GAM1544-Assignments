#include <GameDev2D.h>
#include "Game.h"

using namespace GameDev2D;

Game::Game()
{
    m_Catcher = new Catcher();
    m_screenBound = new ScreenBound();
    m_trajectory = new Trajectory();
    m_launcher = new Launcher();

    m_Ball = new Ball();
    m_Ball->SetBallPosition(GameDev2D::Vector2(m_launcher->GetPosition().x, m_launcher->GetPosition().y + 120));

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
    if (m_trajectory != nullptr)
    {
        delete m_trajectory;
        m_trajectory = nullptr;
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

    if (m_Ball != nullptr)
    {
        delete m_Ball;
        m_Ball = nullptr;
    }

    if (m_launcher != nullptr)
    {
        delete m_launcher;
        m_launcher = nullptr;
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
    m_direction = m_TargetPosition - m_launcher->GetPosition();
    m_angle = atan2f(m_direction.y, m_direction.x);

    m_launcher->Update(m_angle);
    m_Ball->Update(m_angle, m_launcher->GetPosition());

    m_trajectory->Update(m_Ball->GetBallPosition(), m_angle);

    if (m_ballEnable)
    {
        Vector2 point = Math::CalculateTrajectory(m_Ball->GetBallLaunchPosition(), m_Ball->GetBallVelocity(), GRAVITY, TARGET_FPS, i);
        m_Ball->SetBallPosition(point);

        if (!(m_Ball->GetBallPosition().x >= WINDOW_WIDTH + 6 || m_Ball->GetBallPosition().x <= -6 || m_Ball->GetBallPosition().y <= -6))
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

    GameDev2D::Vector2 closestPoint = GameDev2D::Math::CalculateClosestPoint(m_Ball->GetBallPosition(), BALL_RADIUS,
        m_Catcher->Getposition() + GameDev2D::Vector2(0, PLATFORM_HEIGHT / 2),
        m_Catcher->Getposition() + GameDev2D::Vector2(PLATFORM_WIDTH, PLATFORM_HEIGHT / 2));
     

    //Calculate collision
    float distanceSquared = m_Ball->GetBallPosition().DistanceSquared(closestPoint);

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

    //Screen Bound Collision Response
    CollisionResponse(m_screenBound->GetLeftPosition());
    CollisionResponse(m_screenBound->GetRightPosition());
}

void Game::Draw()
{
    m_label->Draw();
    m_screenBound->Draw();

    if (m_totalChance > 0)
    {
        m_trajectory->Draw();
        m_Ball->Draw();
    }

    m_Catcher->Draw();
    m_launcher->Draw();

    for (int i = 0; i < m_totalChance; i++)
    {
        m_remainingBalls[i]->Draw();
    }
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{
    if (!m_ballEnable)
    {
        m_Ball->SetBallVelocity(Vector2(cosf(m_angle), sinf(m_angle)) * SPEED);
        m_Ball->SetBallLaunchPosition(m_Ball->GetBallPosition());
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

void Game::CollisionResponse(GameDev2D::Vector2 position)
{
    GameDev2D::Vector2 Point = GameDev2D::Math::CalculateClosestPoint(m_Ball->GetBallPosition(), BALL_RADIUS,
        position, position + GameDev2D::Vector2(0, WINDOW_HEIGHT));

    float WallDistanceSquared = m_Ball->GetBallPosition().DistanceSquared(Point);

    //Calculate the collision response
    if (WallDistanceSquared <= BALL_RADIUS * BALL_RADIUS)
    {
        float distance = sqrtf(WallDistanceSquared);
        GameDev2D::Vector2 ballNormal = m_Ball->GetBallVelocity().Normalized();
        GameDev2D::Vector2 wallNormal = GameDev2D::Vector2(-1, 0);

        if (ballNormal.DotProduct(Point - m_Ball->GetBallPosition()) < 0)
        {
            wallNormal *= -1.0f;
        }

        if (wallNormal != GameDev2D::Vector2::Zero)
        {
            float dotResult = wallNormal.DotProduct(m_Ball->GetBallVelocity());
            GameDev2D::Vector2 reflection = (-2.0f * dotResult * wallNormal) + m_Ball->GetBallVelocity();
            m_Ball->SetBallVelocity(reflection);
        }
    }
}

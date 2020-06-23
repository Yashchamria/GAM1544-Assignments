#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
    LoadTexture("Tank");

    m_tank = new SpriteAtlas("Tank");
    m_tank->UseFrame("Body");
    m_tank->SetAnchor(0.5f, 0.5f);

    m_turret = new SpriteAtlas("Tank");
    m_turret->UseFrame("Turret");
    m_turret->SetAnchor(0.15f, 0.5f);

}

Game::~Game()
{
    if (m_turret != nullptr)
    {
        delete m_turret;
        m_turret = nullptr;
    }

    if (m_tank != nullptr)
    {
        delete m_tank;
        m_tank = nullptr;
    }

    UnloadTexture("Tank");
}

void Game::Update(double delta)
{
    if (IsKeyDown(Keyboard::A) && IsKeyDown(Keyboard::W))
    {
        m_tankAngle += TANK_ANGULAR_VELOCITY * delta;
        m_turretAngle += TANK_ANGULAR_VELOCITY * delta;

    }


    if (IsKeyDown(Keyboard::D)&& IsKeyDown(Keyboard::W))
    {
        m_tankAngle -= TANK_ANGULAR_VELOCITY * delta;
        m_turretAngle -= TANK_ANGULAR_VELOCITY * delta;
    }

    if (IsKeyDown(Keyboard::W))
    {
        m_speed += TANK_ACCELERATION * delta;

        if (m_speed >= TANK_MAX_SPEED)
        {
            m_speed = TANK_MAX_SPEED;
        }
    }
    else
    {
        float drag = 1.0f - TANK_DRAG;
        m_speed *= drag;

        if (m_speed < 1.5)
        {
            m_speed = 0.0f;
        }
    }

    if (IsKeyDown(Keyboard::S))
    {
        m_speed = 0;
    }

    if (IsKeyDown(Keyboard::Left))
    {
        m_turretAngle += TANK_ANGULAR_VELOCITY * delta;
    }

    if (IsKeyDown(Keyboard::Right))
    {
        m_turretAngle -= TANK_ANGULAR_VELOCITY * delta;
    }

    Vector2 direction = Rotation::Degrees(m_tankAngle).GetDirection();
    Vector2 velocity = direction * m_speed;
    Vector2 position = m_tank->GetPosition() + velocity * delta;

    m_tank->SetPosition(position);
    m_tank->SetDegrees(m_tankAngle);

    m_turret->SetPosition(position);
    m_turret->SetDegrees(m_turretAngle);
}

void Game::Draw()
{
    m_tank->Draw();
    m_turret->Draw();
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
{

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

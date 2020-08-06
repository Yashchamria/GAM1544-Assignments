#include "Launcher.h"
#include "Constants.h"

Launcher::Launcher()
{
    m_turretBase = new GameDev2D::Polygon();
    m_turretBase->MakeCircle(90, true, 48.0f);
    m_turretBase->SetAnchor(0.5, 0.5);
    m_turretBase->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 15);

    m_turret = new GameDev2D::Polygon();
    m_turret->MakeRectangle(24, 120, true);
    m_turret->SetAnchor(0.5f, 0);
    m_turret->SetPosition(m_turretBase->GetPosition());
}

Launcher::~Launcher()
{
    if (m_turret != nullptr)
    {
        delete m_turret;
        m_turret = nullptr;
    }

    if (m_turretBase != nullptr)
    {
        delete m_turretBase;
        m_turretBase = nullptr;
    }
}

GameDev2D::Vector2 Launcher::GetPosition()
{
    return m_turret->GetPosition();
}

void Launcher::SetRadians(float angle)
{
    m_turret->SetRadians(angle);
}

void Launcher::Update(float angle)
{
    if (GameDev2D::Math::RadiansToDegrees(angle) <= 0)
    {
        m_turret->SetRadians(angle - GameDev2D::Math::DegreesToRadians(90));

        //m_Ball->SetBallPosition(m_turret->GetPosition() + GameDev2D::Vector2(cos(angle), sin(angle)) * 120);
    }
}

void Launcher::Draw()
{
    m_turretBase->Draw();
    m_turret->Draw();
}

void Launcher::Reset(bool Enable, int j)
{
}





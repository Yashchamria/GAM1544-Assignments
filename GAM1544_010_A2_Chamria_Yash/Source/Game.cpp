#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
    m_ScreenCenter = GameDev2D::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    m_pUnitCircle = new GameDev2D::Polygon();
    m_pUnitCircle->MakeCircle(RADIUS, false, 72);
    m_pUnitCircle->SetAnchor(0.5f, 0.5f);  
    m_pUnitCircle->SetPosition(m_ScreenCenter);

    LoadFont("OpenSans-CondBold_22");
    m_pLabel = new SpriteFont("OpenSans-CondBold_22");
    m_pLabel->SetAnchor(1.0f, 1.0f);
    m_pLabel->SetPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_pLabel->SetColor(GameDev2D::Color::YellowColor());

    m_pMousePoint = new GameDev2D::Polygon();
    m_pMousePoint->MakeCircle(3, true, 36);
    m_pMousePoint->SetAnchor(0.5f, 0.5f);
    m_pMousePoint->SetColor(GameDev2D::Color::YellowColor());

    m_pLine = new GameDev2D::Polygon();
    m_pLine->MakeCircle(1, false, 0);
    m_pLine->SetPosition(m_ScreenCenter);
    m_pLine->AddVertex(RADIUS,0);
    m_pLine->SetColor(GameDev2D::Color::YellowColor());


    for (int i = 0; i < 16; i++)
    {
        m_pImpPoints[i] = new GameDev2D::Polygon();
        m_pImpPoints[i]->MakeCircle(3, true, 12);
        m_pImpPoints[i]->SetAnchor(0.5f, 0.5f);

        impAngles[i] = Math::DegreesToRadians(impAngles[i]);
        m_ImpPointPosition = m_ScreenCenter + (GameDev2D::Vector2(cos(impAngles[i]), sin(impAngles[i])) * RADIUS);
        m_pImpPoints[i]->SetPosition(m_ImpPointPosition);
    }

    for (int i = 0; i < 16; i++)
    {
        m_pImpLine[i] = new GameDev2D::Polygon();
        m_pImpLine[i]->MakeCircle(1, false, 0);
        m_pImpLine[i]->SetPosition(m_ScreenCenter);
        m_pImpLine[i]->AddVertex(RADIUS, 0);
        m_pImpLine[i]->SetRadians(impAngles[i]);
    }
}

Game::~Game()
{
    for (int i = 0; i < 16; i++)
    {
        delete m_pImpLine[i];
    }
    for (int i = 0; i < 16; i++)
    {
        delete m_pImpPoints[i];
    }

    delete m_pLine;

    delete m_pMousePoint;

    if (m_pLabel != nullptr)
    {
        delete m_pLabel;
        m_pLabel = nullptr;
    }
    UnloadFont("OpenSans-CondBold_22");
    
    delete m_pUnitCircle;
}

void Game::Update(double delta)
{
    m_Text = "Degrees: " + std::to_string(Math::RadiansToDegrees(m_angle)) +
             "\nRadians: " + std::to_string(m_angle) + 
             "\ncos(" + std::to_string(m_angle) + "): " + std::to_string(cos(m_angle)) + 
             "\nsin(" + std::to_string(m_angle) + "): " + std::to_string(sin(m_angle));

    m_pLabel->SetText(m_Text);

    m_direction = m_TargetPosition - m_ScreenCenter;
    m_angle = atan2f(m_direction.y, m_direction.x);
    m_angle = Math::RadiansToDegrees(m_angle);
    if (m_angle < 0)
    {
        m_angle += 360;
    }
    m_angle = Math::DegreesToRadians(m_angle);
    m_MousePosition = m_ScreenCenter + (GameDev2D::Vector2(cos(m_angle), sin(m_angle)) * RADIUS);

    m_pMousePoint->SetPosition(m_MousePosition);
    m_pLine->SetRadians(m_angle);

    for (int i = 0; i < 16; i++)
    {
        if (m_pLine->GetDegrees() < impDegrees[i] + 5 && m_pLine->GetDegrees() > impDegrees[i] - 5)
        {
            m_pLine->SetRadians(impAngles[i]);

            m_angle = Math::DegreesToRadians(m_angle);
            m_MousePosition = m_ScreenCenter + (GameDev2D::Vector2(cos(impAngles[i]), sin(impAngles[i])) * RADIUS);

            m_pMousePoint->SetPosition(m_MousePosition);
        }
    }

    
}

void Game::Draw()
{
    m_pUnitCircle->Draw();
    m_pLabel->Draw();
    
    for (int i = 0; i < 16; i++)
    {
        m_pImpPoints[i]->Draw();
        m_pImpLine[i]->Draw();
    }

    m_pMousePoint->Draw();
    m_pLine->Draw();
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
{

}

void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
{
    m_TargetPosition = Vector2(aMouseX, aMouseY); 
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

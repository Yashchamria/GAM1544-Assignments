#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
    m_pCircle = new GameDev2D::Polygon();
    m_pCircle->MakeCircle(15.0f, true, 36);
    m_pCircle->SetAnchor(0.5f, 0.5f);
    m_pCircle->SetColor( Color (0.5f, 0, 0.5f, 1) );
    m_pCircle->SetPosition( 640.0f, 360.0f);
}

Game::~Game()
{
    delete m_pCircle;
}

void Game::Update(double delta)
{    

    if (m_MouseClickInput)
    {
        if (m_pCircle->GetPosition() < m_TargetPosition)
        {
            m_pCircle->SetPosition(m_pCircle->GetPosition() + m_Direction * MOVEMENT_SPEED * delta);
        }

        if (m_pCircle->GetPosition() > m_TargetPosition)
        {
            m_pCircle->SetPosition(m_pCircle->GetPosition() - m_Direction * MOVEMENT_SPEED * delta);
        }

    }
}

void Game::Draw()
{
    m_pCircle->Draw();
}

void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
{
    m_TargetPosition = Vector2 (aMouseX, aMouseY);

    m_Direction = m_TargetPosition - m_pCircle->GetPosition();
    m_Direction.Normalize();

    m_MouseClickInput = true;
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



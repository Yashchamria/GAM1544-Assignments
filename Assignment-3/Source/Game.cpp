#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"
#include "Timer.h"

using namespace GameDev2D;

Game::Game()
{
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    //Initialize the timer
    m_Timer.SetDuration( ANIMATION_DURATION );
    m_Timer.SetDoesLoop( true );
    m_Timer.Start();

    //To create Vertical Platform

    m_PlatformFront1 = new GameDev2D::Polygon();
    m_PlatformFront1->MakeRectangle(PLATFORM_WIDTH, PLATFORM_HEIGHT, true);
    m_PlatformFront1->SetAnchor(0.5f, 0.5f);
    m_PlatformFront1->SetColor(Color::CrimsonRedColor());

    m_PlatformBack1 = new GameDev2D::Polygon();
    m_PlatformBack1->MakeRectangle(PLATFORM_WIDTH + PLATFORM_STROKE, PLATFORM_HEIGHT + PLATFORM_STROKE, true);
    m_PlatformBack1->SetAnchor(0.5f, 0.5f);
    m_PlatformBack1->SetColor(Color::CharcoalColor());

    //To create Lower Horizontal Platform

    m_PlatformFront2 = new GameDev2D::Polygon();
    m_PlatformFront2->MakeRectangle(PLATFORM_WIDTH, PLATFORM_HEIGHT, true);
    m_PlatformFront2->SetAnchor(0.5f, 0.5f);
    m_PlatformFront2->SetColor(Color::GreenColor());

    m_PlatformBack2 = new GameDev2D::Polygon();
    m_PlatformBack2->MakeRectangle(PLATFORM_WIDTH + PLATFORM_STROKE, PLATFORM_HEIGHT + PLATFORM_STROKE, true);
    m_PlatformBack2->SetAnchor(0.5f, 0.5f);
    m_PlatformBack2->SetColor(Color::CharcoalColor());

    //To create Upper Horizontal Platform

    m_PlatformFront3 = new GameDev2D::Polygon();
    m_PlatformFront3->MakeRectangle(PLATFORM_WIDTH, PLATFORM_HEIGHT, true);
    m_PlatformFront3->SetAnchor(0.5f, 0.5f);
    m_PlatformFront3->SetColor(Color::BlueColor());

    m_PlatformBack3 = new GameDev2D::Polygon();
    m_PlatformBack3->MakeRectangle(PLATFORM_WIDTH + PLATFORM_STROKE, PLATFORM_HEIGHT + PLATFORM_STROKE, true);
    m_PlatformBack3->SetAnchor(0.5f, 0.5f);
    m_PlatformBack3->SetColor(Color::CharcoalColor());
}

Game::~Game()
{
    delete m_PlatformBack3;
    delete m_PlatformFront3;

    delete m_PlatformBack2;
    delete m_PlatformFront2;

    delete m_PlatformBack1;
    delete m_PlatformFront1;

}

void Game::Update(double aDelta)
{
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    //Update the timer
    m_Timer.Update(aDelta);

    float x = (WAVELENGTH * NUMWAVES * m_Timer.GetPercentage());
    float y = sinf((2 * PI * (x / WAVELENGTH))) * AMPLITUDE;

    //Intial Position(Center line for the platform)
    float intial_x = screenWidth * AXES_X_PERCENTAGE;
    float intial_y = screenHeight * AXES_Y_PERCENTAGE;

    //Vertical Platform
    m_PlatformFront1->SetPosition(intial_x, intial_y + y);
    m_PlatformBack1->SetPosition(m_PlatformFront1->GetPosition());
    
    //Lower Horizontal Platform
    m_PlatformFront2->SetPosition((WAVELENGTH*2) + PLATFORM_WIDTH - (intial_x / 2) + y, intial_y - AMPLITUDE);
    m_PlatformBack2->SetPosition(m_PlatformFront2->GetPosition());


    //Upper Horizontal Platform
    m_PlatformFront3->SetPosition((WAVELENGTH*2) + PLATFORM_WIDTH - (intial_x / 2) - y, intial_y + AMPLITUDE - 1);
    m_PlatformBack3->SetPosition(m_PlatformFront3->GetPosition());

}

void Game::Draw()
{   
    //To draw platforms
    m_PlatformBack1->Draw();
    m_PlatformFront1->Draw();
    m_PlatformBack2->Draw();
    m_PlatformFront2->Draw();
    m_PlatformBack3->Draw();
    m_PlatformFront3->Draw();

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

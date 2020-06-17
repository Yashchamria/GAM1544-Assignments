#include <GameDev2D.h>
#include "Game.h"
#include "Constants.h"

using namespace GameDev2D;

Game::Game()
{
    LoadTexture("Planets");

    m_space = new SpriteAtlas("Planets");
    m_space->UseFrame("Background");
    m_space->SetAnchor(0.5f, 0.5f);
    m_space->SetPosition(screenCentre);

    m_sun = new SpriteAtlas("Planets");
    m_sun->UseFrame("Sun");
    m_sun->SetAnchor(0.5f, 0.5f);
    m_sun->SetPosition(screenCentre);

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        m_planet[i] = new SpriteAtlas("Planets");
        m_planet[i]->UseFrame(PLANETS[i]);
        m_planet[i]->SetAnchor(0.5f, 0.5f);
        //m_planet[i]->SetPosition(screenCentre + GameDev2D::Vector2(cos(0), sin(0)) * PLANETS_DISTANCE[i] * TO_PIXEL);
    }

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        m_orbits[i] = new GameDev2D::Polygon();
        m_orbits[i]->MakeCircle(PLANETS_DISTANCE[i] * TO_PIXEL, false, (i+1) * 25);
        m_orbits[i]->SetAnchor(0.5f, 0.5f);
        m_orbits[i]->SetPosition(screenCentre);
    }

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        PLANETS_DURATION[i] = PLANETS_DURATION[i] * 24 * 3600;
    }
}

Game::~Game()
{
    for (int i = 0; i < NUM_PLANETS; i++)
    {
        if (m_orbits[i] != nullptr)
        {
            delete m_orbits[i];
            m_orbits[i] = nullptr;
        }
    }

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        if (m_planet[i] != nullptr)
        {
            delete m_planet[i];
            m_planet[i] = nullptr;
        }
    }

    if (m_sun != nullptr)
    {
        delete m_sun;
        m_sun = nullptr;
    }

    if (m_space != nullptr)
    {
        delete m_space;
        m_space = nullptr;
    }
  

    UnloadTexture("Planets");
}

void Game::Update(double delta)
{
    //To revolve all the planets

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        m_angle[i] += (((2 * M_PI) / PLANETS_DURATION[i]));
        m_elapsedTime = (m_angle[i] * delta * TO_PIXEL * MOVEMENT_SPEED);
        m_direction[i] = screenCentre + GameDev2D::Vector2(cos(m_elapsedTime), sin(m_elapsedTime)) * PLANETS_DISTANCE[i] * TO_PIXEL;
        m_planet[i]->SetPosition(m_direction[i]);
    }
}


void Game::Draw()
{
    m_space->Draw();
    m_sun->Draw();

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        m_orbits[i]->Draw();
    }

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        m_planet[i]->Draw();
    }
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

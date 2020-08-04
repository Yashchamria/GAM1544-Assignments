#pragma once
#include "Catcher.h"
#include <vector>


// Class definition
class Game
{
public:
    Game();  // Constructor
    ~Game(); // Destructor

    // Write game logic in the Update method
    void Update(double delta);

    // Render game objects in the Draw method
    void Draw();

    void Game::Reset();

    // Input methods
    void HandleLeftMouseClick(float mouseX, float mouseY);
    void HandleRightMouseClick(float mouseX, float mouseY);
    void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
    void HandleKeyPress(GameDev2D::Keyboard::Key key);
    void HandleKeyReleased(GameDev2D::Keyboard::Key key);

private:
    // Member variables GO HERE 

    GameDev2D::Polygon* m_turretBase;
    GameDev2D::Polygon* m_line;
    GameDev2D::Polygon* m_turret;
    GameDev2D::Polygon* m_ball;
    GameDev2D::Polygon* m_remainingBalls[TOTAL_CHANCE] = {};
    Catcher* m_Catcher;

    float m_angle = 0.0f;

    GameDev2D::Vector2 m_velocity, m_TargetPosition, m_direction, m_ballPosition, m_ballVelocity, m_ballLaunchPosition;

    GameDev2D::Polygon* m_TrajectoryPoint;
    std::vector<GameDev2D::Vector2> m_Trajectory;


    bool m_ballEnable = false;
    int i = 0;
    int m_totalChance = TOTAL_CHANCE;
};

#pragma once
#include "Catcher.h"
#include "Ball.h"
#include "ScreenBound.h"
#include "Trajectory.h"
#include "Launcher.h"
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
    void Reset();
    void CollisionResponse(GameDev2D::Vector2 position);
    void SetString(string string, double delta);

    // Input methods
    void HandleLeftMouseClick(float mouseX, float mouseY);
    void HandleRightMouseClick(float mouseX, float mouseY);
    void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
    void HandleKeyPress(GameDev2D::Keyboard::Key key);
    void HandleKeyReleased(GameDev2D::Keyboard::Key key);

private:
    // Member variables GO HERE 


    GameDev2D::Polygon* m_remainingBalls[MAXIMUM_LIMIT] = {};
    Catcher* m_Catcher;
    ScreenBound* m_screenBound;
    Ball* m_Ball;
    Trajectory* m_trajectory;
    Launcher* m_launcher;
    float m_angle = 0.0f;

    GameDev2D::Vector2 m_velocity, m_TargetPosition, m_direction;

    bool m_ballEnable = false;
    int i = 0;
    int m_totalChance = TOTAL_CHANCE;
    float m_counter=0;
    GameDev2D::SpriteFont* m_label;
};

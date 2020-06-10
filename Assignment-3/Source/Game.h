#pragma once

#include "Timer.h"

//Class definition
class Game
{
public:
    Game();  // Constructor
    ~Game(); // Destructor

    // Write game logic in the Update method
    void Update(double delta);

    // Render game objects in the Draw method
    void Draw();

    // Input methods
    void HandleLeftMouseClick(float mouseX, float mouseY);
    void HandleRightMouseClick(float mouseX, float mouseY);
    void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
    void HandleKeyPress(GameDev2D::Keyboard::Key key);
    void HandleKeyReleased(GameDev2D::Keyboard::Key key);

private:
	//Member variables
    
    //To create Platform
    GameDev2D::Polygon* m_PlatformFront1;
    GameDev2D::Polygon* m_PlatformBack1;
    GameDev2D::Polygon* m_PlatformFront2;
    GameDev2D::Polygon* m_PlatformBack2;
    GameDev2D::Polygon* m_PlatformFront3;
    GameDev2D::Polygon* m_PlatformBack3;

    Timer m_Timer;
};

#pragma once

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

    // Input methods
    void HandleLeftMouseClick(float mouseX, float mouseY);
    void HandleRightMouseClick(float mouseX, float mouseY);
    void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
    void HandleKeyPress(GameDev2D::Keyboard::Key key);
    void HandleKeyReleased(GameDev2D::Keyboard::Key key);
    bool Movement();

private:
    // Member variables GO HERE
    GameDev2D::Polygon* m_pCircle;
    double m_ElapsedTime;
    GameDev2D::Vector2 m_TargetPosition;
    GameDev2D::Vector2 m_Direction;
    bool m_MouseClickInput;
};

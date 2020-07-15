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

private:
    // Member variables GO HERE 
    GameDev2D::SpriteAtlas* m_tank;
    GameDev2D::SpriteAtlas* m_turret;
    GameDev2D::SpriteAtlas* m_shell;

    float m_tankAngle = 0, m_turretAngle = 0, m_speed, m_turrentRadius, m_time;

    GameDev2D::Vector2 m_tankPosition, m_tankVelocity, m_tankDirection,m_shellPosition, m_shellVelocity;

    bool m_shellEnable = false;

};

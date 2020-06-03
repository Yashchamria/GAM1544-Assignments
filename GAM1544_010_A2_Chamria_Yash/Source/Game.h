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
    GameDev2D::Polygon* m_pUnitCircle;
    GameDev2D::Polygon* m_pMousePoint;
    GameDev2D::Polygon* m_pImpPoints[16];
    GameDev2D::Polygon* m_pLine;
    GameDev2D::Polygon* m_pImpLine[16];

    GameDev2D::Vector2 m_TargetPosition, m_ScreenCenter, m_direction, m_MousePosition, m_ImpPointPosition;
    GameDev2D::SpriteFont* m_pLabel;
    std::string m_Text;
    float m_angle;
    //GameDev2D::Vector2 m_TargetPosition;


};

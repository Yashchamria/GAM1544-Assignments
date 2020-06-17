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
    static const int planetNum = 4;

    GameDev2D::Vector2 screenCentre = GameDev2D::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    GameDev2D::SpriteAtlas* m_space;
    GameDev2D::SpriteAtlas* m_sun;

    GameDev2D::SpriteAtlas* m_planet[planetNum];

    GameDev2D::Polygon* m_orbits[planetNum];

    GameDev2D::Vector2 m_TargetPosition;
    GameDev2D::Vector2 m_direction[planetNum];

    double m_angle[planetNum] = {};
    double m_elapsedTime = 0;
};

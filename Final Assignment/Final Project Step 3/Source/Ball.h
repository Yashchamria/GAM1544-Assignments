#pragma once
#include <GameDev2D.h>

class Ball
{
private:
    GameDev2D::Polygon* m_ball;
    GameDev2D::Vector2 m_ballVelocity, m_ballLaunchPosition;
public:
    Ball();
    ~Ball();
    void Draw();
    void Update(float angle, GameDev2D::Vector2 launcherPosition);

    void SetBallPosition(GameDev2D::Vector2 position);
    GameDev2D::Vector2 GetBallPosition();
    
    void SetBallVelocity(GameDev2D::Vector2 velocity);
    GameDev2D::Vector2 GetBallVelocity();
    
    void SetBallLaunchPosition(GameDev2D::Vector2 launchPosition);
    GameDev2D::Vector2 GetBallLaunchPosition();

    //void IsEnable(bool enable, int j, int chances);
    //void Reset(bool Enable, int k);

};
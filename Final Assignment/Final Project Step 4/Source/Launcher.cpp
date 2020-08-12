#include "Launcher.h"
#include "Ball.h"
#include "Constants.h"
#include <GameDev2D.h>

namespace GameDev2D
{
	Launcher::Launcher(Ball* aBall)
	{
		//Set the Ball pointer
		m_Ball = aBall;

		//Create the 'Body' (half circle) Polygon object
		m_Body = new Polygon();
		m_Body->MakeCircle(80.0f, true);
		m_Body->SetPosition(Vector2(GetScreenWidth() * 0.5f, GetScreenHeight()));
		m_Body->SetAnchor(Vector2(0.5f, 0.5f));

		//Create the arm Polygon object
		m_Arm = new Polygon();
		m_Arm->MakeRectangle(110.0f, 16.0f, true);
		m_Arm->SetPosition(Vector2(GetScreenWidth() * 0.5f, GetScreenHeight()));
		m_Arm->SetAnchor(Vector2(0.0f, 0.5f));
		m_Arm->SetDegrees(270.0f);

        m_ResetBall = true;
	}

	Launcher::~Launcher()
	{
        if (m_Body != nullptr)
        {
            delete m_Body;
            m_Body = nullptr;
        }

        if (m_Arm != nullptr)
        {
            delete m_Arm;
            m_Arm = nullptr;
        }
	}

	void Launcher::Update(double aDelta)
	{
		if (m_Ball->GetVelocity() == Vector2::Zero && m_ResetBall == true)
		{
            Vector2 launchPosition = GetLaunchPosition();
			m_Ball->SetPosition(launchPosition);
		}
	}

	void Launcher::Draw()
	{
		m_Body->Draw();
		m_Arm->Draw();
	}

	void Launcher::HandleMouseMove(float aX, float aY)
	{
		float radians = atan2f(aY - m_Arm->GetPosition().y, aX - m_Arm->GetPosition().x);
		m_Arm->SetRadians(radians);
	}

	Vector2 Launcher::GetLaunchPosition()
	{
		Vector2 position = m_Arm->GetPosition();
		Vector2 direction = m_Arm->GetDirection();
		float length = 110.0f;
		Vector2 launchPosition = position + direction * length;
		return launchPosition;
	}

	Vector2 Launcher::GetInitialVelocity()
	{
		Vector2 direction = m_Arm->GetDirection();
		Vector2 velocity = direction * BALL_INITIAL_SPEED;
		return velocity;
	}

	void Launcher::Fire()
	{
		m_Ball->SetVelocity(GetInitialVelocity());
	}
    void Launcher::ResetBall(bool resetBall)
    {
        m_ResetBall = resetBall;
    }
}
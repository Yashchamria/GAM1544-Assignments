#include "Ball.h"
#include "Constants.h"


namespace GameDev2D
{
	Ball::Ball() : Drawable()
	{
		//Initialize the velocity
		m_Velocity = Vector2::Zero;

		//Create the Polygon object
		m_Ball = new Polygon();
		m_Ball->MakeCircle(GetRadius(), true, 24.0f);
		m_Ball->SetAnchor(Vector2(0.5f, 0.5f));
		m_Ball->SetColor(Color::CrimsonRedColor());
        m_Ball->AttachTo(this);
	}

	Ball::~Ball()
	{
        if (m_Ball != nullptr)
        {
            delete m_Ball; 
            m_Ball = nullptr;
        }
	}

	void Ball::Update(double aDelta)
	{
		if (m_Velocity != Vector2::Zero)
		{
			//Increment the ball's position d = v * t
			Vector2 position = GetPosition();
			position += m_Velocity * aDelta;

			//Wall normal used for wall collisions
			Vector2 wallNormal = Vector2::Zero;

			//Is the ball's x position is offscreen
			if (position.x <= 0.0f)
			{
				wallNormal = Vector2::Left;
				position.x = 0.0f;

			}
			//Is the ball's x position is offscreen
			else if (position.x >= GetScreenWidth())
			{
				wallNormal = Vector2::Right;
				position.x = GetScreenWidth();
			}

			//Is the ball's y position is offscreen
			if (position.y >= GetScreenHeight() - BALL_RADIUS * 2.0f)
			{
				wallNormal = Vector2::Up;
				position.y = GetScreenHeight() - BALL_RADIUS * 2.0f;
			}

			//Was there collision? If wallNormal isn't zero, then there was
			if (wallNormal != Vector2::Zero)
			{
				Vector2 newVelocity = -2.0f * m_Velocity.DotProduct(wallNormal) * wallNormal + m_Velocity;
				SetVelocity(newVelocity);
			}

			//Set the ball's position
			SetPosition(position);
		}
	}

	void Ball::Draw()
	{
		m_Ball->Draw();
	}

	void Ball::Reset()
	{
		m_Velocity = Vector2::Zero;
	}

	float Ball::GetWidth()
	{
		return GetRadius() * 2.0f;
	}

	float Ball::GetHeight()
	{
		return GetRadius() * 2.0f;
	}

	float Ball::GetRadius()
	{
		return BALL_RADIUS;
	}

	void Ball::SetVelocity(const Vector2& aVelocity)
	{
		m_Velocity = aVelocity;
	}

	Vector2 Ball::GetVelocity()
	{
		return m_Velocity;
	}

	void Ball::ApplyGravity(Vector2 aGravity, double aDelta)
	{
		if (m_Velocity != Vector2::Zero)
		{
			//Next apply the effects of gravity
			m_Velocity +=  aGravity * aDelta;
		}
	}
}
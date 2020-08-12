#include "Catcher.h"
#include "Constants.h"


namespace GameDev2D
{
	Catcher::Catcher() : Drawable(),
		m_Timer(5.0f)
	{
		m_Box = new Polygon();
		m_Box->MakeRectangle(GetWidth(), GetHeight(), true);
		m_Box->SetAnchor(Vector2(0.5f, 0.5f));
		m_Box->SetColor(Color::OnyxColor());
        m_Box->AttachTo(this);

		m_Timer.SetDoesRepeat(true);
		m_Timer.Start();

        SetPosition(Vector2(GetScreenWidth() / 2.0f, 50.0f));
	}

	Catcher::~Catcher()
	{
        if (m_Box != nullptr)
        {
            delete m_Box;
            m_Box = nullptr;
        }
	}

	void Catcher::Update(double aDelta)
	{
		m_Timer.Update(aDelta);

		//Use a sine wave to move the catcher
		float radians = m_Timer.GetPercentage() * 2.0 * M_PI;
		float value = sinf(radians);
		float halfScreenWidth = GetScreenWidth() * 0.5f;
		float x = halfScreenWidth + value * halfScreenWidth;

		SetPosition(Vector2(x, 50.0f));
	}

	void Catcher::Draw()
	{
		m_Box->Draw();
	}

	float Catcher::GetWidth()
	{
		return CATCHER_WIDTH;
	}

	float Catcher::GetHeight()
	{
		return CATCHER_HEIGHT;
	}
}
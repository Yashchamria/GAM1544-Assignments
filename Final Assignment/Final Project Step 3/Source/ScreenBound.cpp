#include "ScreenBound.h"

ScreenBound::ScreenBound()
{
	m_leftBound = new GameDev2D::Polygon();
	m_leftBound->MakeRectangle(0.1f, WINDOW_HEIGHT, true);
	m_leftBound->SetPosition(0, 0);

	m_rightBound = new GameDev2D::Polygon();
	m_rightBound->MakeRectangle(0.1f, WINDOW_HEIGHT, true);
	m_rightBound->SetPosition(WINDOW_WIDTH - 1, 0);

	m_line = new GameDev2D::Polygon();
	m_line->MakeRectangle(WINDOW_WIDTH, 2, true);
	m_line->SetAnchor(0.5f, 0.5f);
	m_line->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 15);
}

ScreenBound::~ScreenBound()
{
	if (m_leftBound != nullptr)
	{
		delete m_leftBound;
		m_leftBound = nullptr;
	}

	if (m_rightBound != nullptr)
	{
		delete m_rightBound;
		m_rightBound = nullptr;
	}

	if (m_line != nullptr)
	{
		delete m_line;
		m_line = nullptr;
	}
}

void ScreenBound::Draw()
{
	m_leftBound->Draw();
	m_rightBound->Draw();
	m_line->Draw();
}

GameDev2D::Vector2 ScreenBound::GetLeftPosition()
{
	return m_leftBound->GetPosition();
}

GameDev2D::Vector2 ScreenBound::GetRightPosition()
{
	return m_rightBound->GetPosition();
}

#include "Peg.h"

GameDev2D::Peg::Peg()
{
	m_peg = new Polygon();
	m_peg->MakeCircle(GetRadius(), true, 24.0f);
	m_peg->SetAnchor(Vector2(0.5f, 0.5f));
	m_peg->SetColor(Color::BlueColor());
}

GameDev2D::Peg::~Peg()
{
	if (m_peg != nullptr)
	{
		delete m_peg;
		m_peg = nullptr;
	}
}

void GameDev2D::Peg::Update(double delta)
{
}

void GameDev2D::Peg::Draw()
{
	m_peg->Draw();
}

void GameDev2D::Peg::Reset()
{
}

void GameDev2D::Peg::SetPosition(Vector2 position)
{
	m_peg->SetPosition(position);
}

GameDev2D::Vector2 GameDev2D::Peg::GetPosition()
{
	return m_peg->GetPosition();
}

void GameDev2D::Peg::SetColor(Color color)
{
	m_peg->SetColor(color);
}

GameDev2D::Color GameDev2D::Peg::GetColor()
{
	return m_peg->GetColor();
}

void GameDev2D::Peg::SetTransparecy(double time)
{
	m_peg->SetAlpha(time);
}

double GameDev2D::Peg::GetTransparecy()
{
	return m_peg->GetAlpha();
}

void GameDev2D::Peg::HitResponse(double delta)
{
}

float GameDev2D::Peg::GetRadius()
{
	return BALL_RADIUS;
}

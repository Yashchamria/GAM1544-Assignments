#include "Catcher.h"

Catcher::Catcher()
{
	m_catcher = new GameDev2D::Polygon();
	m_catcher->MakeRectangle(PLATFORM_WIDTH, PLATFORM_HEIGHT, true);
	m_catcher->SetColor(GameDev2D::Color::CharcoalColor());
	m_catcher->SetPosition(0, 60);


	m_timer.SetDuration(ANIMATION_DURATION);
	m_timer.SetDoesLoop(true);
	m_timer.Start();
}

void Catcher::Draw()
{
	m_catcher->Draw();
}

void Catcher::Update(double delta)
{
	m_timer.Update(delta);

	float x = (WAVELENGTH * NUMWAVES * m_timer.GetPercentage());
	float y = sinf((2 * PI * (x / WAVELENGTH))) * AMPLITUDE;

	m_catcher->SetPosition((WAVELENGTH * 2) + y - 100, 60);
}

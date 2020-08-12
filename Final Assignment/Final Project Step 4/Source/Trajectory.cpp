#include "Trajectory.h"


namespace GameDev2D
{
	Trajectory::Trajectory()
	{
		m_CanDraw = true;

		m_PathPoint = new Polygon();
		m_PathPoint->SetAnchor(Vector2(0.5f, 0.5f));
		m_PathPoint->SetColor(Color::YellowColor());
		m_PathPoint->MakeCircle(2.0f, true, 12.0f);
	}

	Trajectory::~Trajectory()
	{
        if (m_PathPoint != nullptr)
        {
            delete m_PathPoint;
            m_PathPoint = nullptr;
        }
	}

	void Trajectory::Draw()
	{
		if (m_CanDraw == true)
		{
			//Set the path color
			m_PathPoint->SetColor(Color::WhiteColor());

			//Draw each point on the trajectory
			for (int i = 0; i < m_Path.size(); i++)
			{
				Vector2 position = m_Path.at(i);
				m_PathPoint->SetPosition(position);
				m_PathPoint->Draw();
			}
		}
	}

	void Trajectory::Clear()
	{
		m_Path.clear();
	}

	void Trajectory::Add(const Vector2& aPosition)
	{
		m_Path.push_back(aPosition);
	}

	void Trajectory::Show()
	{
		m_CanDraw = true;
	}

	void Trajectory::Hide()
	{
		m_CanDraw = false;
	}
}
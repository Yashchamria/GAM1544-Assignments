#include "Timer.h"

namespace GameDev2D
{
	Timer::Timer(double duration)
	{
		m_Elapsed = 0.0;
		m_Duration = duration;
		m_DoesRepeat = false;
		m_IsRunning = false;
	}

	Timer::Timer(const Timer& timer)
	{
		m_Elapsed = timer.m_Elapsed;
		m_Duration = timer.m_Duration;
		m_DoesRepeat = timer.m_DoesRepeat;
		m_IsRunning = timer.m_IsRunning;
	}

	Timer::Timer()
	{
		m_Elapsed = 0.0;
		m_Duration = 0.0;
		m_DoesRepeat = false;
		m_IsRunning = false;
	}

	void Timer::Update(double delta)
	{
		if (m_IsRunning == true)
		{
			m_Elapsed += delta;

			if (m_Elapsed >= m_Duration)
			{
				if (m_DoesRepeat == true)
				{
					m_Elapsed = 0.0;
				}
				else
				{
					m_Elapsed = m_Duration;
					m_IsRunning = false;
				}
			}
		}
	}

	void Timer::Start()
	{
		m_IsRunning = true;
	}

	void Timer::Stop()
	{
		m_IsRunning = false;
	}

	void Timer::Reset()
	{
		m_Elapsed = 0.0;
		m_IsRunning = false;
	}

	void Timer::Restart()
	{
		m_Elapsed = 0.0;
		m_IsRunning = true;
	}

	double Timer::GetElapsed()
	{
		return m_Elapsed;
	}

	double Timer::GetDuration()
	{
		return m_Duration;
	}

	void Timer::SetDuration(double duration)
	{
		m_Duration = duration;
	}

	float Timer::GetPercentage()
	{
		if (m_Duration != 0.0)
		{
			return (float)(m_Elapsed / m_Duration);
		}
		return 0.0f;
	}

	void Timer::SetDoesRepeat(bool aDoesRepeat)
	{
		m_DoesRepeat = aDoesRepeat;
	}

	bool Timer::DoesRepeat()
	{
		return m_DoesRepeat;
	}

	bool Timer::IsRunning()
	{
		return m_IsRunning;
	}
}
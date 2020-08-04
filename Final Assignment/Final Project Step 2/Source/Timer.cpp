#include "Timer.h"

Timer::Timer(double duration)
{
	m_Elapsed = 0.0;
	m_Duration = duration;
	m_IsRunning = false;
    m_DoesLoop = false;
}

Timer::Timer(const Timer& aTimer)
{
    m_Elapsed = aTimer.m_Elapsed;
    m_Duration = aTimer.m_Duration;
    m_IsRunning = aTimer.m_IsRunning;
    m_DoesLoop = aTimer.m_DoesLoop;
}

Timer::Timer()
{
    m_Elapsed = 0.0;
    m_Duration = 0.0;
    m_IsRunning = false;
    m_DoesLoop = false;
}

void Timer::Update(double delta)
{
	if (m_IsRunning == true)
	{
		m_Elapsed += delta;

		if (m_Elapsed >= m_Duration)
		{
            if (m_DoesLoop == true)
            {
                m_Elapsed = 0.0;
            }
            else
            {
                m_IsRunning = false;
                m_Elapsed = m_Duration;
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

void Timer::SetDuration(double aDuration)
{
    m_Duration = aDuration;
}

void Timer::SetDoesLoop(bool aDoesLoop)
{
    m_DoesLoop = aDoesLoop;
}

float Timer::GetPercentage()
{
	return (float)(m_Elapsed / m_Duration);
}

double Timer::GetElapsed()
{
    return m_Elapsed;
}

double Timer::GetDuration()
{
    return m_Duration;
}

bool Timer::IsRunning()
{
    return m_IsRunning;
}

bool Timer::DoesLoop()
{
    return m_DoesLoop;
}

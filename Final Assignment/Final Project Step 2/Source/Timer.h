#pragma once

class Timer
{
public: 
	Timer(double duration);
    Timer(const Timer& timer);
    Timer();

	void Update(double delta);

	void Start();
	void Stop();
	void Reset();

    void SetDuration(double duration);
    void SetDoesLoop(bool doesLoop);

	float GetPercentage();

    double GetElapsed();
    double GetDuration();
    bool IsRunning();
    bool DoesLoop();

private:
	double m_Duration;
	double m_Elapsed;
	bool m_IsRunning;
    bool m_DoesLoop;
};

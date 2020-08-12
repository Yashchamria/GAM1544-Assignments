#pragma once

namespace GameDev2D
{
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
		void Restart();

		double GetElapsed();
		double GetDuration();

		void SetDuration(double duration);

		float GetPercentage();

		void SetDoesRepeat(bool doesRepeat);
		bool DoesRepeat();

		bool IsRunning();

	private:
		double m_Duration;
		double m_Elapsed;
		bool m_DoesRepeat;
		bool m_IsRunning;
	};
}
#pragma once
#include "Constants.h"

#include <GameDev2D.h>

namespace GameDev2D
{
	class Peg
	{
	public:
		Peg();
		~Peg();

		void Update(double delta);
		void Draw();
		void Reset();

		void SetPosition(Vector2 position);
		Vector2 GetPosition();

		void SetColor(Color color);
		Color GetColor();

		void SetTransparecy(double time);
		double GetTransparecy();

		void HitResponse(double delta);

		float GetRadius();


	private:
		Polygon* m_peg;

	};
}

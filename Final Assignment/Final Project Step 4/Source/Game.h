#pragma once

#include <GameDev2D.h>
#include "Timer.h"
#include "Ball.h"
#include"Peg.h"
#include "Launcher.h"
#include "Catcher.h"
#include "Trajectory.h"
#include "Constants.h"

#include <vector>


namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor
		~Game(); //Destructor

		void Update(double delta);
		void Draw();
		void Reset();

		void BuildTrajectory();

		bool CheckCollision(Ball* ball, Catcher* catcher);
		void HandleCollision(Ball* ball, Catcher* catcher);

		bool CheckPegCollision(Ball* ball, Peg* Peg);
		void HandlePegCollision(Ball* ball, Peg* Peg);

		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);

		void PegsArrange(int counter, int size, int begin, float x, float y, int increment, int mod, float initial_x);


	private:
		//Member variables
		Ball* m_Ball;
		//Peg* m_Pegs[TOTAL_PEGS];

		std::vector<Peg*> m_Pegs;

		Launcher* m_Launcher;
		Trajectory* m_Trajectory;
        Catcher* m_Catcher;
		Polygon* m_TopLine;
		Polygon* m_BallsRemaining;
		unsigned int m_NumberOfBalls;
		SpriteFont* m_Label;
		Timer m_LabelTimer;
		Timer m_PegTimer;

		float m_counter = -1;
	};
}

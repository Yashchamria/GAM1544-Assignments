#include "Game.h"
#include <time.h>



namespace GameDev2D
{
	Game::Game() : 
		m_LabelTimer(1.0),
		m_PegTimer(0.75f)
    {
		//Create the Ball, Catcher, Launch and Trajectory objects
		m_Ball = new Ball();
		m_Launcher = new Launcher(m_Ball);
		m_Trajectory = new Trajectory();
        m_Catcher = new Catcher();

		//Create the top line Polygon object
		m_TopLine = new Polygon();
		m_TopLine->AddVertex(0.0f, 0.0f);
		m_TopLine->AddVertex(GetScreenWidth(), 0.0f);
		m_TopLine->SetRenderMode(RenderMode_LineStrip);
		m_TopLine->SetPosition(Vector2(0.0f, GetScreenHeight() - BALL_RADIUS * 2.0f));
		
		//Create the HUD ball Polygon object
		m_BallsRemaining = new Polygon();
		m_BallsRemaining->MakeCircle(BALL_RADIUS - 1.0f, true, 24.0f);
		m_BallsRemaining->SetAnchor(Vector2(0.5f, 0.5f));

		//Load the Font Data
		LoadFont("heavy_data_150");

		//Create the Label's SpriteFont
		m_Label = new SpriteFont("heavy_data_150");
		m_Label->SetPosition(Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f));
		m_Label->SetAnchor(Vector2(0.5f, 0.5f));
		m_Label->SetJustification(SpriteFont::JustifyCenter);
		m_Label->SetText("");

		//Initialize the number of balls
		m_NumberOfBalls = INITIAL_NUMBER_OF_BALLS;

		//Initialize the pegs
		for (int i = 0; i < TOTAL_PEGS; i++)
		{
			m_Pegs.push_back(new Peg());
		}

		PegsArrange(1, 32, 0, WINDOW_WIDTH / 9, 200, WINDOW_WIDTH / 9, 8, WINDOW_WIDTH / 9);
		PegsArrange(1, TOTAL_PEGS, 32, WINDOW_WIDTH / 6, 260, WINDOW_WIDTH / 9, 7, WINDOW_WIDTH / 6);

		srand(time(0));

		for (int i = 0; i < SPECIAL_PEGS; i++)
		{
			int temp = rand() % TOTAL_PEGS;

			while (m_Pegs[temp]->GetColor() == Color::OrangeColor())
			{
				temp = rand() % TOTAL_PEGS;
			}

			m_Pegs[temp]->SetColor(Color::OrangeColor());
		}

	}

	Game::~Game()
	{
        if (m_Ball != nullptr)
        {
            delete m_Ball;
            m_Ball = nullptr;
        }

        if (m_Launcher != nullptr)
        {
            delete m_Launcher;
            m_Launcher = nullptr;
        }

        if (m_Trajectory != nullptr)
        {
            delete m_Trajectory;
            m_Trajectory = nullptr;
        }

        if (m_Catcher != nullptr)
        {
            delete m_Catcher;
            m_Catcher = nullptr;
        }

		for (int i = 0; i < m_Pegs.size(); i++)
		{
			if (m_Pegs[i] != nullptr)
			{
				delete m_Pegs[i];
				m_Pegs[i] = nullptr;
			}
		}

        if (m_TopLine != nullptr)
        {
            delete m_TopLine;
            m_TopLine = nullptr;
        }

        if (m_BallsRemaining != nullptr)
        {
            delete m_BallsRemaining;
            m_BallsRemaining = nullptr;
        }

		if (m_Label != nullptr)
		{
			delete m_Label;
			m_Label = nullptr;
		}

		UnloadFont("heavy_data_150");
	}

    void Game::Update(double aDelta)
    {
		//Update the launcher and catcher
		m_Launcher->Update(aDelta);
		m_Catcher->Update(aDelta);

		//Is the Label Timer running? Update it!
		if (m_LabelTimer.IsRunning() == true)
		{
			m_LabelTimer.Update(aDelta);

			//Is the timer done?
			if (m_LabelTimer.GetPercentage() == 1.0f)
			{
				//Show the trajectory and clear the Label
				m_Trajectory->Show();
				m_Label->SetText("");
			}
			else
			{
				return;
			}
		}

		//Apply gravity to the ball and update it
		m_Ball->ApplyGravity(GRAVITY, aDelta);
		m_Ball->Update(aDelta);

		//Check collision with the catcher
		if (CheckCollision(m_Ball, m_Catcher) == true)
		{
			HandleCollision(m_Ball, m_Catcher);
		}

		//Did the ball go off the bottom of the screen?
		if (m_Ball->GetPosition().y <= 0.0f)
		{
			m_Ball->Reset();
			m_Trajectory->Show();

			//If there are no balls remaining, then its Game over
			if (m_NumberOfBalls == 0)
			{
				m_Trajectory->Hide();
				m_Launcher->ResetBall(false);
				m_Label->SetColor(Color::DarkGrayColor());
				m_Label->SetText("YOU LOSE!!");
			}
		}

		//Build the trajectory for the ball
		BuildTrajectory();

		//Peg 
		for (int i = 0; i < m_Pegs.size(); i++)
		{
			if (CheckPegCollision(m_Ball, m_Pegs[i]) == true)
			{
				HandlePegCollision(m_Ball, m_Pegs[i]);
			}
		}

		if (!(m_counter == -1.0f))
		{
			if (m_counter >= 0)
			{
				m_counter -= aDelta;
			}
			else
			{
				for (int i = 0; i < m_Pegs.size(); i++)
				{
					if (m_Pegs[i]->GetTransparecy() == 0.5f)
					{
						m_Pegs.erase(m_Pegs.begin() + i);
					}
				}
				m_counter = -1;
			}
		}

		//Win or Lose Condition
		int wincount = 0;
		for (int i = 0; i < m_Pegs.size(); i++)
		{
			if (m_Pegs[i]->GetColor() != Color::OrangeColor())
			{
				wincount++;
				
			}
		}

		if (wincount == m_Pegs.size())
		{
			m_Trajectory->Hide();
			m_Launcher->ResetBall(false);
			m_Label->SetColor(Color::Random());
			m_Label->SetText("YOU WIN!!");
		}
    }

	void Game::Draw()
	{
		//Draw the top line
		m_TopLine->Draw();

		for (int i = 0; i < m_Pegs.size(); i++)
		{
			m_Pegs[i]->Draw();

		}

		//Draw the number of balls remaining
		Vector2 position = Vector2(BALL_RADIUS, GetScreenHeight() - BALL_RADIUS);
		for (int i = 0; i < m_NumberOfBalls; i++)
		{
			//Draw the balls remaining polygon
			m_BallsRemaining->SetPosition(position);
			m_BallsRemaining->Draw();

			//Increment the position x value
			position.x += BALL_RADIUS * 2.0f;
		}

        //Draw the trajectory
        m_Trajectory->Draw();

		//Draw the launcher, the ball, the catcher
		m_Launcher->Draw();
        m_Catcher->Draw();
		m_Ball->Draw();

		//Draw the Label
		m_Label->Draw();
	}

	void Game::Reset()
	{
		//Reset the ball
		m_Ball->Reset();

		//Show the trajectory
		m_Trajectory->Show();

        //Reset the launcher - allows the ball to be set by the launcher
        m_Launcher->ResetBall(true);

		//Reset the number of balls and the number of pegs hit
		m_NumberOfBalls = INITIAL_NUMBER_OF_BALLS;

	}

	void Game::BuildTrajectory()
	{
		//Clear the trajectory
		m_Trajectory->Clear();

		//Get the launcher's current starting position and initial velocity
		Vector2 startingPosition = m_Launcher->GetLaunchPosition();
		Vector2 startingVelocity = m_Launcher->GetInitialVelocity();

		//Cycle through one second (60 fps) to determine the trajectory point for each frame
		for (int i = 0; i < 90; i++)
		{
			//Get the trajectory position for i
			Vector2 trajectoryPosition = Math::CalculateTrajectoryPoint(startingPosition, startingVelocity, GRAVITY, TARGET_FPS, i);

			//Add the trajectory position to the trajectory
			m_Trajectory->Add(trajectoryPosition);
		}
	}

	bool Game::CheckCollision(Ball* aBall, Catcher* aCatcher)
	{
		//Ensure the ball is moving
		if (aBall->GetVelocity() != Vector2::Zero)
		{
			//Calculate the closest point of the line
			Vector2 lineStart = aCatcher->GetPosition() - Vector2(aCatcher->GetWidth() / 2.0f, 0.0f);
			Vector2 lineEnd = aCatcher->GetPosition() + Vector2(aCatcher->GetWidth() / 2.0f, 0.0f);
			Vector2 closestPoint = Math::CalculateClosestPoint(aBall->GetPosition(), aBall->GetRadius(), lineStart, lineEnd);

			//Calculate the distance between the closest point and the center of the ball
			float distanceSquared = aBall->GetPosition().DistanceSquared(closestPoint);
			float radiiSquared = aBall->GetRadius() * aBall->GetRadius();

			//If the distance squared is less than the radii squared, then there's a collision
			bool didCollide = distanceSquared < radiiSquared;
			return didCollide;
		}
		return false;
	}

	void Game::HandleCollision(Ball* aBall, Catcher* aCatcher)
	{
		//Reset the ball and show the trajectory
		m_Ball->Reset();

		//Free ball
		m_NumberOfBalls++;

		//Set the spritefont text to Free Ball
		m_Label->SetColor(Color::ShamrockGreenColor());
		m_Label->SetText("FREE BALL!");
		m_LabelTimer.Restart();
	}

	bool Game::CheckPegCollision(Ball* ball, Peg* Peg)
	{
		for (int i = 0; i < m_Pegs.size(); i++)
		{
			Vector2 distanceV = ball->GetPosition() - Peg->GetPosition();
			float distance = distanceV.Length();

			if (distance * distance < 2 * (BALL_RADIUS * BALL_RADIUS))
			{
				return true;
			}

		}

		return false;


	}

	void Game::HandlePegCollision(Ball* ball, Peg* Peg)
	{
		for (int i = 0; i < m_Pegs.size(); i++)
		{
			Peg->SetTransparecy(0.5);
			//m_LabelTimer.Restart();
			m_counter = 0.75f;

			Vector2 distanceV = ball->GetPosition() - Peg->GetPosition();
			float distance = distanceV.Length();

			float overlap = (BALL_RADIUS * 2) - distance;
			Vector2 CollisionNormal = distanceV / distance;

			Vector2 correction = CollisionNormal * (overlap / 2);
			m_Ball->SetPosition(m_Ball->GetPosition() + correction);

			float ball = m_Ball->GetVelocity().DotProduct(CollisionNormal);
			Vector2 ballResponse = Vector2(0, 0);
			ballResponse.x = m_Ball->GetVelocity().x - ball * CollisionNormal.x - ball * CollisionNormal.x;
			ballResponse.y = m_Ball->GetVelocity().y - ball * CollisionNormal.y - ball * CollisionNormal.y;

			m_Ball->SetVelocity(ballResponse);
		}

	}

    void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
    {
        //Launch the ball
        m_Launcher->Fire();

        //Decrement the number of balls left
        m_NumberOfBalls--;
    }

	void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
	{
		m_Launcher->HandleMouseMove(aMouseX, aMouseY);  
	}

	void Game::HandleKeyPress(Keyboard::Key aKey)
	{
		if (aKey == Keyboard::R)
		{
            Reset();
		}
		else if (aKey == Keyboard::B)
		{
            //Cheat key to add another ball
			m_NumberOfBalls++;
		}
	}

	void Game::PegsArrange(int counter, int size, int begin, float x, float y, int increment, int mod, float initial_x)
	{
		for (int i = begin; i < size; i++)
		{
			m_Pegs[i]->SetPosition(Vector2(x, y));

			x += increment;

			if (counter % mod == 0)
			{
				y += 120;
				x = initial_x;
			}
			counter++;
		}
	}
}
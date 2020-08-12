#include "GameDev2D.h"


namespace GameDev2D
{
    void Run(std::function<void()> aInitCallback, std::function<void()> aShutdownCallback, std::function<void(double)> aUpdateCallback, std::function<void()> aDrawCallback)
    {
#if CHECK_FOR_MEMORY_LEAKS
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

        //Create the Window's PlatformLayer and initialize it and set the Root Scene
        Application application(WINDOW_TITLE, TARGET_FPS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_IS_FULLSCREEN);

        //Initialize the application with the callback functions
        application.Init(aInitCallback, aShutdownCallback, aUpdateCallback, aDrawCallback);

        //Message handling
        MSG message;
        do
        {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        } while (application.Loop() == true);
    }

    unsigned int GetScreenWidth()
    {
        return Services::GetApplication()->GetWindow()->GetWidth();
    }

    unsigned int GetScreenHeight()
    {
        return Services::GetApplication()->GetWindow()->GetHeight();
    }

	void LoadAudio(const std::string& aFilename)
	{
		Services::GetResourceManager()->LoadWaveFile(aFilename);
	}

	void UnloadAudio(const std::string& aFilename)
	{
		Services::GetResourceManager()->UnloadWaveFile(aFilename);
	}

    void LoadTexture(const std::string& aFilename)
    {
        Services::GetResourceManager()->LoadTexture(aFilename);
    }

    void UnloadTexture(const std::string& aFilename)
    {
        Services::GetResourceManager()->UnloadTexture(aFilename);
    }

	void LoadFont(const std::string& aFilename)
	{
		Services::GetResourceManager()->LoadFont(aFilename);
	}

	void UnloadFont(const std::string& aFilename)
	{
		Services::GetResourceManager()->UnloadFont(aFilename);
	}

    unsigned int GetTextureWidth(const std::string& aFilename)
    {
        if (Services::GetResourceManager()->IsTextureLoaded(aFilename) == true)
        {
            Texture* texture = Services::GetResourceManager()->GetTexture(aFilename);
            return texture->GetWidth();
        }
        return 0;
    }

    unsigned int GetTextureHeight(const std::string& aFilename)
    {
        if (Services::GetResourceManager()->IsTextureLoaded(aFilename) == true)
        {
            Texture* texture = Services::GetResourceManager()->GetTexture(aFilename);
            return texture->GetHeight();
        }
        return 0;
    }

	void DrawTexture(const std::string& aFilename, float aX, float aY, float aAngle, float aAlpha)
	{
		Texture* texture = Services::GetResourceManager()->GetTexture(aFilename);
		Services::GetGraphics()->DrawTexture(texture, Vector2(aX, aY), Rotation::Degrees(aAngle), aAlpha);
	}

    void DrawString(const std::string& aText, float aX, float aY, const Color& aColor)
    {
        FontData* font = Services::GetResourceManager()->GetDefaultFont();
        Services::GetGraphics()->DrawString(font, aText, Vector2(aX, aY), aColor);
    }

    void DrawRectangle(float aX, float aY, float aWidth, float aHeight, float aAngle, const Color& aColor, bool aIsFilled)
    {
        Services::GetGraphics()->DrawRectangle(Vector2(aX, aY), Vector2(aWidth, aHeight), Rotation::Degrees(aAngle), Vector2(0.0f, 0.0f), aColor, aIsFilled);
    }

    void DrawCircle(float aX, float aY, float aRadius, const Color& aColor, bool aIsFilled)
    {
        Services::GetGraphics()->DrawCircle(Vector2(aX, aY), aRadius, Vector2(0.0f, 0.0f), aColor, aIsFilled);
    }

    void DrawLine(float aStartX, float aStartY, float aEndX, float aEndY, const Color& aColor)
    {
        Services::GetGraphics()->DrawLine(Vector2(aStartX, aStartY), Vector2(aEndX, aEndY), aColor);
    }

	void RegisterKeyPressedCallback(std::function<void(Keyboard::Key)> aKeyPressedCallback)
	{
		Services::GetInputManager()->GetKeyboard()->RegisterKeyPressedCallback(aKeyPressedCallback);
	}

    void RegisterKeyReleasedCallback(std::function<void(Keyboard::Key)> aKeyReleasedCallback)
    {
        Services::GetInputManager()->GetKeyboard()->RegisterKeyReleasedCallback(aKeyReleasedCallback);
    }

    void RegisterLeftMouseButtonPressedCallback(std::function<void(float, float)> aLeftMouseButtonPressedCallback)
    {
        Services::GetInputManager()->GetMouse()->RegisterLeftMouseButtonPressedCallback(aLeftMouseButtonPressedCallback);
    }

    void RegisterLeftMouseButtonReleasedCallback(std::function<void(float, float)> aLeftMouseButtonReleasedCallback)
    {
        Services::GetInputManager()->GetMouse()->RegisterLeftMouseButtonReleasedCallback(aLeftMouseButtonReleasedCallback);
    }

    void RegisterRightMouseButtonPressedCallback(std::function<void(float, float)> aRightMouseButtonPressedCallback)
    {
        Services::GetInputManager()->GetMouse()->RegisterRightMouseButtonPressedCallback(aRightMouseButtonPressedCallback);
    }

    void RegisterRightMouseButtonReleasedCallback(std::function<void(float, float)> aRightMouseButtonReleasedCallback)
    {
        Services::GetInputManager()->GetMouse()->RegisterRightMouseButtonReleasedCallback(aRightMouseButtonReleasedCallback);
    }

	void RegisterMouseMoveCallback(std::function<void(float, float, float, float)> aMouseMoveCallback)
	{
		Services::GetInputManager()->GetMouse()->RegisterMouseMoveCallback(aMouseMoveCallback);
	}

    bool IsKeyUp(unsigned int aKey)
    {
        return Services::GetInputManager()->GetKeyboard()->GetState(static_cast<Keyboard::Key>(aKey)).keyState == Keyboard::KeyUp;
    }

    bool IsKeyDown(unsigned int aKey)
    {
        Keyboard::State keyboardState = Services::GetInputManager()->GetKeyboard()->GetState(static_cast<Keyboard::Key>(aKey));
        return keyboardState.keyState == Keyboard::KeyDown || keyboardState.keyState == Keyboard::KeyRepeat;
    }

    bool IsLeftMouseButtonUp()
    {
        return Services::GetInputManager()->GetMouse()->IsButtonPressed(Mouse::Left) == false;
    }

    bool IsLeftMouseButtonDown()
    {
        return Services::GetInputManager()->GetMouse()->IsButtonPressed(Mouse::Left) == true;
    }

    bool IsRightMouseButtonUp()
    {
        return Services::GetInputManager()->GetMouse()->IsButtonPressed(Mouse::Right) == false;
    }

    bool IsRightMouseButtonDown()
    {
        return Services::GetInputManager()->GetMouse()->IsButtonPressed(Mouse::Right) == true;
    }

    Vector2 GetMousePosition()
    {
        return Services::GetInputManager()->GetMouse()->GetPosition();
    }
}
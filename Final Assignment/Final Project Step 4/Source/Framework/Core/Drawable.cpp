#include "Drawable.h"


namespace GameDev2D
{
    Drawable::Drawable() : Transformable(),
        m_Shader(nullptr),
        m_Color(Color::WhiteColor()),
        m_Anchor(0.0f, 0.0f)
    {

    }

    Drawable::~Drawable()
    {

    }

    Shader* Drawable::GetShader()
    {
        return m_Shader;
    }

    void Drawable::SetShader(Shader* aShader)
    {
        m_Shader = aShader;
    }

    Color Drawable::GetColor()
    {
        return m_Color;
    }

    void Drawable::SetColor(Color aColor)
    {
        m_Color = aColor;
    }

	float Drawable::GetAlpha()
	{
		return m_Color.a;
	}

	void Drawable::SetAlpha(float aAlpha)
	{
		Color color = m_Color;
		color.a = aAlpha;
		SetColor(color);
	}

    Vector2 Drawable::GetAnchor()
    {
        return m_Anchor;
    }

    void Drawable::SetAnchor(Vector2 aAnchor)
    {
        m_Anchor = aAnchor;
    }
}
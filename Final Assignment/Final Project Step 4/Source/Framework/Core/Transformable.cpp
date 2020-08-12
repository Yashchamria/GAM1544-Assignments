#include "Transformable.h"
#include "../Debug/Log.h"


namespace GameDev2D
{
    Transformable::Transformable() :
        m_Transform(Matrix::Identity()),
        m_Rotation(),
        m_Position(0.0f, 0.0f),
        m_Scale(1.0f, 1.0f),
        m_IsTransformMatrixDirty(false),
        m_Parent(nullptr)
    {

    }

	Transformable::Transformable(const Transformable& aTransformable) :
		m_Transform(aTransformable.m_Transform),
		m_Rotation(aTransformable.m_Rotation),
		m_Position(aTransformable.m_Position),
		m_Scale(aTransformable.m_Scale),
		m_IsTransformMatrixDirty(aTransformable.m_IsTransformMatrixDirty),
        m_Parent(aTransformable.m_Parent)
	{

	}

	Transformable::~Transformable()
	{

	}

	Matrix Transformable::GetTransformMatrix()
	{
		if (m_IsTransformMatrixDirty == true)
		{
			Matrix translationMatrix = Matrix::MakeTranslation(m_Position);
			Matrix rotationMatrix = Matrix::MakeRotation(m_Rotation);
			Matrix scaleMatrix = Matrix::MakeScale(m_Scale);

			m_Transform = translationMatrix * rotationMatrix * scaleMatrix;
			m_IsTransformMatrixDirty = false;
		}

        if (m_Parent != nullptr)
        {
            return m_Parent->GetTransformMatrix() * m_Transform;
        }

		return m_Transform;
	}

    Vector2 Transformable::GetPosition()
    {
        return m_Position;
    }

    void Transformable::SetPosition(Vector2 aPosition)
    {
        m_Position = aPosition;
        m_IsTransformMatrixDirty = true;
    }

    void Transformable::Translate(Vector2 aOffset)
    {
        m_Position += aOffset;
        m_IsTransformMatrixDirty = true;
    }

    float Transformable::GetDegrees()
    {
        return m_Rotation.GetDegrees();
    }

	float Transformable::GetRadians()
	{
		return m_Rotation.GetRadians();
	}

    void Transformable::SetDegrees(float aDegrees)
    {
        m_Rotation.SetDegrees(aDegrees);
        m_IsTransformMatrixDirty = true;
    }

	void Transformable::SetRadians(float aRadians)
	{
		m_Rotation.SetRadians(aRadians);
		m_IsTransformMatrixDirty = true;
	}

    void Transformable::Rotate(Rotation& aRotation)
    {
        m_Rotation.SetRadians(m_Rotation.GetRadians() + aRotation.GetRadians());
        m_IsTransformMatrixDirty = true;
    }

    Vector2 Transformable::GetDirection()
    {
        return m_Rotation.GetDirection();
    }

    void Transformable::SetDirection(Vector2 aDirection)
    {
        m_Rotation.SetDirection(aDirection);
        m_IsTransformMatrixDirty = true;
    }

    Vector2 Transformable::GetScale()
    {
        return m_Scale;
    }

    void Transformable::SetScale(Vector2 aScale)
    {
        m_Scale = aScale;
        m_IsTransformMatrixDirty = true;
    }

    void Transformable::AttachTo(Transformable* parent)
    {
        m_Parent = parent;
    }

    Transformable* Transformable::GetParent()
    {
        return m_Parent;
    }

    void Transformable::Log()
    {
        Log::Message(Log::Verbosity_Debug, "[Transformable] Position(%f, %f), Rotation(%f), Scale(%f, %f)", m_Position.x, m_Position.y, m_Rotation.GetRadians(), m_Scale.x, m_Scale.y);
    }
}
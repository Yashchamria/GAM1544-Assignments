#include "Math.h"
#include <math.h>
#include <stdlib.h>


namespace GameDev2D
{
#ifdef RANDOM_SEED
    Random Math::s_Random(RANDOM_SEED);
#else
    Random Math::s_Random = Random();
#endif

    float Math::DegreesToRadians(float aDegrees)
    {
        return aDegrees * 0.01745329251f;
    }

    float Math::RadiansToDegrees(float aRadians)
    {
        return aRadians * 57.2957795131f;
    }

    float Math::Clamp(float aValue, float aMin, float aMax)
    {
        if (aValue < aMin)
        {
            return aMin;
        }

        if (aValue > aMax)
        {
            return aMax;
        }

        return aValue;
    }

    Vector2 Math::Clamp(const Vector2& aValue, const Vector2& aMin, const Vector2& aMax)
    {
        if (aValue < aMin)
        {
            return aMin;
        }

        if (aValue > aMax)
        {
            return aMax;
        }

        return aValue;
    }

    int Math::RandomInt(int aMin, int aMax)
    {
        return s_Random.RandomInt(aMin, aMax);
    }

    float Math::RandomFloat()
    {
        return RandomFloat(0.0f, 1.0f);
    }

    float Math::RandomFloat(float aMin, float aMax)
    {
        return s_Random.RandomFloat(aMin, aMax);
    }

    double Math::RandomDouble()
    {
        return RandomDouble(0.0, 1.0);
    }

    double Math::RandomDouble(double aMin, double aMax)
    {
        return s_Random.RandomDouble(aMin, aMax);
    }

    bool Math::IsClose(float aValue, float aTarget, float aRange)
    {
        if (aValue > aTarget - aRange && aValue < aTarget + aRange)
        {
            return true;
        }

        return false;
    }
    Vector2 Math::CalculateTrajectory(const Vector2& startingPosition, const Vector2& startingVelocity, const Vector2& gravity, float targetFPS, float frame)
    {
        float delta = 1.0f / targetFPS;
        Vector2 frameVelocity = startingVelocity * delta;
        Vector2 frameGravity = gravity * delta * delta;
        return startingPosition + frame * frameVelocity + 0.5f * (frame * frame + frame) * frameGravity;
    }
    Vector2 Math::CalculateClosestPoint(const Vector2& circleCenter, float circleRadius, const Vector2& lineStart, const Vector2& lineEnd)
    {
        Vector2 lineV = lineEnd - lineStart;
        Vector2 circleV = circleCenter - lineStart;
        Vector2 normalizeV = lineV.Normalized();
        float projectionMagnitude = normalizeV.DotProduct(circleV);
        Vector2 projectionV = normalizeV * projectionMagnitude;
        Vector2 closestPoint = lineStart + projectionV;
        return Clamp(closestPoint, lineStart, lineEnd);
    }
}
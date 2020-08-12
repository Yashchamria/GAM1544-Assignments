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

    Vector2 Math::CalculateOrbit(const Vector2& aPivot, Rotation aAngle, float aDistance)
    {
        float angleRadians = aAngle.GetRadians();
        float x = (aPivot.x + cosf(angleRadians) * aDistance);
        float y = (aPivot.y + sinf(angleRadians) * aDistance);
        return Vector2(x, y);
    }

    Vector2 Math::CalculateTrajectoryPoint(const Vector2& aStartingPosition, const Vector2& aStartingVelocity, const Vector2& aGravity, float aTargetFPS, float aStep)
    {
        float t = 1.0f / aTargetFPS;
        Vector2 stepVelocity = t * aStartingVelocity;
        Vector2 stepGravity = t * t * aGravity;
        return aStartingPosition + aStep * stepVelocity + 0.5f * (aStep * aStep + aStep) * stepGravity;
    }

    Vector2 Math::CalculateClosestPoint(const Vector2& aCircleCenter, float aRadius, const Vector2& aLineStart, const Vector2& aLineEnd)
    {
        //Calculate the circle vector        
        Vector2 circleVector = aCircleCenter - aLineStart;

        //Calculate the line segment vector        
        Vector2 lineVector = aLineEnd - aLineStart;

        //Normalize the line segment vector        
        Vector2 normalizedVector = lineVector.Normalized();

        //Calculate the dot product between the circle vector and the normalized line segment vector       
        float magnitude = normalizedVector.DotProduct(circleVector);

        //Calculate the projection using the result of the dot product and multiply it by the normalized line segment        
        Vector2 projection = normalizedVector * magnitude;

        //Calculate the closest point on the line segment, by adding the project vector to the line start vector        
        Vector2 closestPoint = aLineStart + projection;
        return Clamp(closestPoint, aLineStart, aLineEnd);
    }
}
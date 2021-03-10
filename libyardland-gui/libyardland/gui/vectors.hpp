/* 
 * ************************************************ *
 *      Copyrigtht H4ck Software 2017-2021          *
 *                                                  *
 *      Author: Joseph Hans Diaz Gonzalez.          *
 *                                                  *
 *                  Vectors.hpp                     *   
 *   Implementation of Unity-like Vector Classes    *
 * ************************************************ *
 */

#pragma once

#include <cmath>

/**
 * \brief Unity-like Vector2 Class.
 */
class Vector2
{
public:

    /**
     * \brief Short-hand for writing Vector2(0.0f, -1.0f).
     */
    static const Vector2 up();
    /**
     * \brief Short-hand for writing Vector2(0.0f, 1.0f).
     */
    static const Vector2 down();
    /**
     * \brief Short-hand for writing Vector2(-1.0f, 0.0f).
     */
    static const Vector2 left();
    /**
     * \brief Short-hand for writing Vector2(1.0f, 0.0f).
     */
    static const Vector2 right();
    /**
     * \brief Short-hand for writing Vector2(1.0f, 1.0f).
     */
    static const Vector2 one();
    /**
     * \brief Short-hand for writing Vector2(0.0f, 0.0f).
     */
    static const Vector2 zero();

    Vector2(float x, float y);
    Vector2();

    const float magnitude();
    const Vector2 normalized();
    
    float x, y;

    void Normalize();
    void Set(float x, float y);

    static const float Angle(Vector2 from, Vector2 to);
    static const float Distance(Vector2 a, Vector2 b);
    static const float Dot(Vector2 lhs, Vector2 rhs);
    static const void Lerp(Vector2* current, Vector2* target, float t);
    static const void MoveTowards(Vector2* current, Vector2* target, float maxDistanceDelta);

    bool operator ==(const Vector2& rhs);
    Vector2 operator +(const Vector2& rhs);
    Vector2 operator -(const Vector2& rhs);
    Vector2 operator *(const float& d);

private:
    static float inaccuracy;
};

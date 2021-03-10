#include <projectsg/physics/vectors.ipp>

float Vector2::inaccuracy = 1E-5f;

Vector2::Vector2(float x, float y)
{
    this->x = x, this->y = y;

    return;
}

Vector2::Vector2()
{
    this->x = 0.0f, this->y = 0.0f;

    return;
}

bool Vector2::operator ==(const Vector2& rhs)
{
    Vector2 difference(this->x - rhs.x, this->y - rhs.y);

    return (std::abs(difference.x) <= this->inaccuracy && std::abs(difference.y) <= this->inaccuracy);
}

Vector2 Vector2::operator +(const Vector2& rhs)
{
    Vector2 result;

    result.x = this->x + rhs.x;
    result.y = this->y + rhs.y;

    return result;
}

Vector2 Vector2::operator -(const Vector2& rhs)
{
    Vector2 result;

    result.x = this->x - rhs.x;
    result.y = this->y - rhs.y;

    return result;
}

Vector2 Vector2::operator *(const float& d)
{
    Vector2 result;

    result.x = this->x * d;
    result.y = this->y * d;

    return result;
}

const void Vector2::Lerp(Vector2* current, Vector2* target, float t)
{
        Vector2 vt(target->x - current->x, target->y - current->y);
        float length = vt.magnitude();

        if (length > t)
        {
            // move towards the goal
            current->x = (current->x + t* vt.x / length);
            current->y = (current->y + t* vt.y / length);
        }
        else
        {
            // already there
            current->x = target->x;
            current->y = target->y;
        }
}

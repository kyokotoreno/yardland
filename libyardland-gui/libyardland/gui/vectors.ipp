#include <projectsg/physics/vectors.hpp>

inline const Vector2 Vector2::up() { return Vector2(0.0f, -1.0f); }

inline const Vector2 Vector2::down() { return Vector2(0.0f, 1.0f); }

inline const Vector2 Vector2::left() { return Vector2(-1.0f, 0.0f); }

inline const Vector2 Vector2::right() { return Vector2(1.0f, 0.0f); }

inline const Vector2 Vector2::one() { return Vector2(1.0f, 1.0f); }

inline const Vector2 Vector2::zero() { return Vector2(); }

inline const float Vector2::magnitude()
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}

#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>

namespace GameEngine
{
    namespace maths
    {
        class Vec2
        {
        public:
            float _x;
            float _y;
            Vec2();
            Vec2(const float & x, const float & y);

            Vec2 & add(const Vec2 & src);
            Vec2 & sub(const Vec2 & src);
            Vec2 & mul(const Vec2 & src);
            Vec2 & div(const Vec2 & src);

            Vec2 operator+(const Vec2 & src);
            Vec2 operator-(const Vec2 & src);
            Vec2 operator*(const Vec2 & src);
            Vec2 operator/(const Vec2 & src);
            Vec2 & operator=(const Vec2 & src);

            bool operator==(const Vec2 & src);
            bool operator!=(const Vec2 & src);
            // bool & operator>(const Vec2 & src) const;
            // bool & operator<(const Vec2 & src) const;
            // bool & operator>=(const Vec2 & src) const;
            // bool & operator<=(const Vec2 & src) const;
        };
        std::ostream &operator<<(std::ostream &out, const Vec2 & src);
    }
}

#endif
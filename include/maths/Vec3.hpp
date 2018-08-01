#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

namespace GameEngine
{
    namespace maths
    {
        class Vec3
        {
        public:
            float _x;
            float _y;
            float _z;
            Vec3();
            Vec3(const float & x, const float & y, const float & z);

            Vec3 & add(const Vec3 & src);
            Vec3 & sub(const Vec3 & src);
            Vec3 & mul(const Vec3 & src);
            Vec3 & div(const Vec3 & src);

            Vec3 operator+(const Vec3 & src);
            Vec3 operator-(const Vec3 & src);
            Vec3 operator*(const Vec3 & src);
            Vec3 operator/(const Vec3 & src);
            Vec3 & operator=(const Vec3 & src);

            bool operator==(const Vec3 & src);
            bool operator!=(const Vec3 & src);
            // bool & operator>(const Vec3 & src) const;
            // bool & operator<(const Vec3 & src) const;
            // bool & operator>=(const Vec3 & src) const;
            // bool & operator<=(const Vec3 & src) const;
        };
        std::ostream &operator<<(std::ostream &out, const Vec3 & src);
    }
}

#endif
#ifndef VEC4_HPP
#define VEC4_HPP

#include <iostream>

namespace GameEngine
{
    namespace maths
    {
        class Vec4
        {
        public:
            float _x;
            float _y;
            float _z;
            float _w;

            Vec4();
            Vec4(const float & x, const float & y, const float & z, const float & w);

            Vec4 & add(const Vec4 & src);
            Vec4 & sub(const Vec4 & src);
            Vec4 & mul(const Vec4 & src);
            Vec4 & div(const Vec4 & src);

            Vec4 operator+(const Vec4 & src);
            Vec4 operator-(const Vec4 & src);
            Vec4 operator*(const Vec4 & src);
            Vec4 operator/(const Vec4 & src);
            Vec4 & operator=(const Vec4 & src);

            bool operator==(const Vec4 & src);
            bool operator!=(const Vec4 & src);
            // bool & operator>(const Vec4 & src) const;
            // bool & operator<(const Vec4 & src) const;
            // bool & operator>=(const Vec4 & src) const;
            // bool & operator<=(const Vec4 & src) const;
        };
        std::ostream &operator<<(std::ostream &out, const Vec4 & src);
    }
}

#endif
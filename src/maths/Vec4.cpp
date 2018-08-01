#include <maths/Vec4.hpp>

namespace GameEngine
{
    namespace maths
    {
        Vec4::Vec4()
        {
            this->_x = 0.0f;
            this->_y = 0.0f;
            this->_z = 0.0f;
            this->_w = 0.0f;
        }

        Vec4::Vec4(const float &x, const float &y, const float &z, const float &w)
        {
            this->_x = x;
            this->_y = y;
            this->_z = z;
            this->_w = w;
        }

        Vec4 &Vec4::add(const Vec4 &src)
        {
            this->_x += src._x;
            this->_y += src._y;
            this->_z += src._z;
            this->_w += src._w;
            return *this;
        }

        Vec4 &Vec4::sub(const Vec4 &src)
        {
            this->_x -= src._x;
            this->_y -= src._y;
            this->_z -= src._z;
            this->_w -= src._w;
            return *this;
        }

        Vec4 &Vec4::mul(const Vec4 &src)
        {
            this->_x *= src._x;
            this->_y *= src._y;
            this->_z *= src._z;
            this->_w *= src._w;
            return *this;
        }

        Vec4 &Vec4::div(const Vec4 &src)
        {
            this->_x /= src._x;
            this->_y /= src._y;
            this->_z /= src._z;
            this->_w /= src._w;
            return *this;
        }

        Vec4 Vec4::operator+(const Vec4 &src)
        {
            Vec4 ans(this->_x + src._x, this->_y + src._y, this->_z + src._z, this->_w + src._w);
            return ans;
        }

        Vec4 Vec4::operator-(const Vec4 &src)
        {
            Vec4 ans(this->_x - src._x, this->_y - src._y, this->_z - src._z, this->_w - src._w);
            return ans;
        }

        Vec4 Vec4::operator*(const Vec4 &src)
        {
            Vec4 ans(this->_x * src._x, this->_y * src._y, this->_z * src._z, this->_w * src._w);
            return ans;
        }

        Vec4 Vec4::operator/(const Vec4 &src)
        {
            Vec4 ans(this->_x / src._x, this->_y / src._y, this->_z / src._z, this->_w / src._w);
            return ans;
        }

        Vec4 &Vec4::operator=(const Vec4 & src)
        {
            this->_x = src._x;
            this->_y = src._y;
            this->_z = src._z;
            this->_w = src._w;
            return *this;
        }

        std::ostream &operator<<(std::ostream &out, const Vec4 & src)
        {
            out << "Vec4 (" << src._x << ", " << src._y << ", " << src._z << ", " << src._w << ")";
            return out;
        }

        bool Vec4::operator==(const Vec4 & src)
        {
            if (this->_x == src._x && this->_y == src._y && this->_z == src._z && this->_w == src._w)
                return true;
            return false;
        }

        bool Vec4::operator!=(const Vec4 & src)
        {
            return !(*this == src);
        }
    } // namespace maths
} // namespace GameEngine
#include <maths/Vec3.hpp>

namespace GameEngine
{
    namespace maths
    {
        Vec3::Vec3()
        {
            this->_x = 0.0f;
            this->_y = 0.0f;
            this->_z = 0.0f;
        }

        Vec3::Vec3(const float &x, const float &y, const float &z)
        {
            this->_x = x;
            this->_y = y;
            this->_z = z;
        }

        Vec3 &Vec3::add(const Vec3 &src)
        {
            this->_x += src._x;
            this->_y += src._y;
            this->_z += src._z;
            return *this;
        }

        Vec3 &Vec3::sub(const Vec3 &src)
        {
            this->_x -= src._x;
            this->_y -= src._y;
            this->_z -= src._z;
            return *this;
        }

        Vec3 &Vec3::mul(const Vec3 &src)
        {
            this->_x *= src._x;
            this->_y *= src._y;
            this->_z *= src._z;
            return *this;
        }

        Vec3 &Vec3::div(const Vec3 &src)
        {
            this->_x /= src._x;
            this->_y /= src._y;
            this->_z /= src._z;
            return *this;
        }

        Vec3 Vec3::operator+(const Vec3 &src)
        {
            Vec3 ans(this->_x + src._x, this->_y + src._y, this->_z + src._z);
            return ans;
        }

        Vec3 Vec3::operator-(const Vec3 &src)
        {
            Vec3 ans(this->_x - src._x, this->_y - src._y, this->_z - src._z);
            return ans;
        }

        Vec3 Vec3::operator*(const Vec3 &src)
        {
            Vec3 ans(this->_x * src._x, this->_y * src._y, this->_z * src._z);
            return ans;
        }

        Vec3 Vec3::operator/(const Vec3 &src)
        {
            Vec3 ans(this->_x / src._x, this->_y / src._y, this->_z / src._z);
            return ans;
        }

        Vec3 &Vec3::operator=(const Vec3 & src)
        {
            this->_x = src._x;
            this->_y = src._y;
            this->_z = src._z;
            return *this;
        }

        std::ostream &operator<<(std::ostream &out, const Vec3 & src)
        {
            out << "Vec3 (" << src._x << ", " << src._y << ", " << src._z << ")";
            return out;
        }

        bool Vec3::operator==(const Vec3 & src)
        {
            if (this->_x == src._x && this->_y == src._y && this->_z == src._z)
                return true;
            return false;
        }

        bool Vec3::operator!=(const Vec3 & src)
        {
            return !(*this == src);
        }
    } // namespace maths
} // namespace GameEngine
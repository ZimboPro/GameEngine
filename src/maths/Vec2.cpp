#include <maths/Vec2.hpp>

namespace GameEngine
{
    namespace maths
    {
        Vec2::Vec2()
        {
            this->_x = 0.0f;
            this->_y = 0.0f;
        }

        Vec2::Vec2(const float &x, const float &y)
        {
            this->_x = x;
            this->_y = y;
        }

        Vec2 &Vec2::add(const Vec2 &src)
        {
            this->_x += src._x;
            this->_y += src._y;
            return *this;
        }

        Vec2 &Vec2::sub(const Vec2 &src)
        {
            this->_x -= src._x;
            this->_y -= src._y;
            return *this;
        }

        Vec2 &Vec2::mul(const Vec2 &src)
        {
            this->_x *= src._x;
            this->_y *= src._y;
            return *this;
        }

        Vec2 &Vec2::div(const Vec2 &src)
        {
            this->_x /= src._x;
            this->_y /= src._y;
            return *this;
        }

        Vec2 Vec2::operator+(const Vec2 &src)
        {
            Vec2 ans(this->_x + src._x, this->_y + src._y);
            return ans;
        }

        Vec2 Vec2::operator-(const Vec2 &src)
        {
            Vec2 ans(this->_x - src._x, this->_y - src._y);
            return ans;
        }

        Vec2 Vec2::operator*(const Vec2 &src)
        {
            Vec2 ans(this->_x * src._x, this->_y * src._y);
            return ans;
        }

        Vec2 Vec2::operator/(const Vec2 &src)
        {
            Vec2 ans(this->_x / src._x, this->_y / src._y);
            return ans;
        }

        Vec2 &Vec2::operator=(const Vec2 & src)
        {
            this->_x = src._x;
            this->_y = src._y;
            return *this;
        }

        std::ostream &operator<<(std::ostream &out, const Vec2 & src)
        {
            out << "Vec2 (" << src._x << ", " << src._y << ")";
            return out;
        }

        bool Vec2::operator==(const Vec2 & src)
        {
            if (this->_x == src._x && this->_y == src._y)
                return true;
            return false;
        }

        bool Vec2::operator!=(const Vec2 & src)
        {
            return !(*this == src);
        }
    } // namespace maths
} // namespace GameEngine
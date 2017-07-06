#include "Vector3D.h"
#include <cmath>
namespace GaiaEngine::Core {
    Vector3D::Vector3D(double x, double y, double z)
    {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    Vector3D Vector3D::Normalize()
    {
        return *this / sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    Vector3D& Vector3D::operator+=(const Vector3D &rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D &rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        return *this;
    }

    Vector3D& Vector3D::operator/=(double rhs)
    {
        x_ /= rhs;
        y_ /= rhs;
        z_ /= rhs;
        return *this;
    }

    Vector3D& Vector3D::Cross(Vector3D &other)
    {
        return  Vector3D(y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_);
    }

    double Vector3D::Dot(Vector3D &other)
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
    {
        Vector3D sum = lhs;
        sum += rhs;
        return sum;
    }

    Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
    {
        Vector3D sub = lhs;
        sub -= rhs;
        return sub;
    }

    Vector3D operator/(const Vector3D &lhs, double rhs)
    {
        Vector3D quotient = lhs;
        quotient /= rhs;
        return quotient;
    }
}
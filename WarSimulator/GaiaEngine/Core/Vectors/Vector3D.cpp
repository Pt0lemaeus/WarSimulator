#include "Vector3D.h"
#include <cmath>
namespace GaiaEngine::Core {


    Vector3D::Vector3D(double x, double y, double z):x_(x),y_(y),z_(z)
    {
    }

    Vector3D Vector3D::Normalize()
    {
        return *this / sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    Vector3D& Vector3D::operator=(const Vector3D &rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        return *this;
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

    Vector3D Vector3D::Cross(const Vector3D &other)
    {
        return  Vector3D(y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_);
    }

    double Vector3D::Dot(Vector3D &other)
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vector3D Vector3D::MultiplyComponents(const Vector3D& scale)
    {
        return  Vector3D(x_ * scale.x_, y_ * scale.y_, z_ * scale.z_);
    }

    double Vector3D::MagnitudeSquared()
    {
        return x_ * x_ + y_ * y_ + z_ * z_;
    }

    double Vector3D::Magnitude()
    {
        return sqrt(MagnitudeSquared());
    }

    double Vector3D::AngleBetween(Vector3D other)
    {
        return acos(Normalize().Dot(other.Normalize()));
    }

    Vector3D Vector3D::RotateAroundAxis(Vector3D axis, double theta)
    {
        double u = axis.x_;
        double v = axis.y_;
        double w = axis.z_;

        double cosTheta = cos(theta);
        double sinTheta = sin(theta);

        double ms = axis.MagnitudeSquared();
        double m = sqrt(ms);

        return Vector3D(
            ((u * (u * x_ + v * y_ + w * z_)) +
            (((x_ * (v * v + w * w)) - (u * (v * y_ + w * z_))) * cosTheta) +
                (m * ((-w * y_) + (v * z_)) * sinTheta)) / ms,

                ((v * (u * x_ + v * y_ + w * z_)) +
            (((y_ * (u * u + w * w)) - (v * (u * x_ + w * z_))) * cosTheta) +
                    (m * ((w * x_) - (u * z_)) * sinTheta)) / ms,

                    ((w * (u * x_ + v * y_ + w * z_)) +
            (((z_ * (u * u + v * v)) - (w * (u * x_ + v * y_))) * cosTheta) +
                        (m * (-(v * x_) + (u * y_)) * sinTheta)) / ms);
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

    Vector3D operator*(const Vector3D &lhs, double rhs)
    {
        return Vector3D(lhs.x_ * rhs, lhs.y_ * rhs, lhs.z_ * rhs);
    }

    Vector3D operator*( double lhs, const Vector3D &rhs)
    {
        return operator*(rhs, lhs);
    }

}
#pragma once
namespace GaiaEngine::Core {
    class Vector3D {
    public:
        double x_;
        double y_;
        double z_;

        Vector3D() = default;
        Vector3D(double, double, double);
        Vector3D Normalize(void);
        Vector3D &operator= (const Vector3D&);
        Vector3D &operator+= (const Vector3D&);
        Vector3D &operator-= (const Vector3D&);
        Vector3D &operator/= (double);
        double Dot(Vector3D&);
        Vector3D& Cross(Vector3D&);
        Vector3D& MultiplyComponents(const Vector3D&);
    };
    Vector3D operator+ (const Vector3D&, const Vector3D&);
    Vector3D operator-(const Vector3D&, const Vector3D&);
    Vector3D operator/ (const Vector3D&, double);
}


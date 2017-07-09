#include "Ellipsoid.h"

namespace GaiaEngine::Core {
    Ellipsoid::Ellipsoid(Vector3D radii)
    {
        if ((radii.x_ <= 0.0) || (radii.y_ <= 0.0) || (radii.z_ <= 0.0))
        {
            throw  std::out_of_range("negative radii");
        }

        radii_ = radii;
        radiiSquared_ = Vector3D(
            radii.x_ * radii.x_,
            radii.y_ * radii.y_,
            radii.z_ * radii.z_);
        radiiToTheFourth_ = Vector3D(
            radiiSquared_.x_ * radiiSquared_.x_,
            radiiSquared_.y_ * radiiSquared_.y_,
            radiiSquared_.z_ * radiiSquared_.z_);
        oneOverRadiiSquared_ = Vector3D(
            1.0 / (radii.x_ * radii.x_),
            1.0 / (radii.y_ * radii.y_),
            1.0 / (radii.z_ * radii.z_));
    }

    Ellipsoid::Ellipsoid(double x, double y, double z) 
    {
        Ellipsoid(Vector3D(x, y, z));
    }

    Vector3D Ellipsoid::GeodeticSurfaceNormal(Vector3D positionOnEllipsoid)
    {
        return (positionOnEllipsoid.MultiplyComponents(oneOverRadiiSquared_)).Normalize();
    }
}
#include "Ellipsoid.h"
#include <cmath>

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

    Vector3D Ellipsoid::GeodeticSurfaceNormal(Geodetic3D geodetic)
    {
        double cosLatitude = cos(geodetic.latitude_);
        return Vector3D(
            cosLatitude*cos(geodetic.longitude_),
            cosLatitude*sin(geodetic.longitude_),
            sin(geodetic.latitude_));
    }

    Vector3D Ellipsoid::ToVector3D(Geodetic3D geodetic)
    {
        Vector3D n = GeodeticSurfaceNormal(geodetic);
        Vector3D k = radiiSquared_.MultiplyComponents(n);
        double gamma = sqrt(
            k.x_ * n.x_ +
            k.y_ * n.y_ +
            k.z_ * n.z_);

        Vector3D rSurface = k / gamma;
        return rSurface + (geodetic.height_ * n);
    }
}
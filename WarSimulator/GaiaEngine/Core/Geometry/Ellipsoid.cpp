#include "Ellipsoid.h"
#include <cmath>
#include "..\..\..\..\..\Common\MathHelper.h"

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

    //Converting from geographic to WGS84 
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

    Vector3D Ellipsoid::GeodeticSurfaceNormal(Vector3D p)
    {
        Vector3D normal = p.MultiplyComponents(oneOverRadiiSquared_);
        return normal.Normalize();
    }

    //Converting surface points from WGS84 to geographic
    Geodetic2D Ellipsoid::ToGeodetic2D(Vector3D p)
    {
        Vector3D n = GeodeticSurfaceNormal(p);
        return Geodetic2D(
            atan2(n.y_, n.x_),
            asin(n.z_ / n.Magnitude())
        );
    }

    //Scaling a point to the surface along the geocentric surface normal
    Vector3D Ellipsoid::ScaleToGeocentricSurface(Vector3D position)
    {
        double beta = 1.0 / sqrt(
            (position.x_*position.x_)* oneOverRadiiSquared_.x_ +
            (position.y_*position.y_)* oneOverRadiiSquared_.y_ +
            (position.z_*position.z_)* oneOverRadiiSquared_.z_);
        return beta * position;
    }

    //Scaling a point to the surface along the geodetic surface normal
    Vector3D Ellipsoid::ScaleToGeodeticSurface(Vector3D position)
    {
        double beta = 1.0 / sqrt(
            (position.x_ * position.x_) * oneOverRadiiSquared_.x_ +
            (position.y_ * position.y_) * oneOverRadiiSquared_.y_ +
            (position.z_ * position.z_) * oneOverRadiiSquared_.z_);
        double n = Vector3D(
            beta * position.x_ * oneOverRadiiSquared_.x_,
            beta * position.y_ * oneOverRadiiSquared_.y_,
            beta * position.z_ * oneOverRadiiSquared_.z_).Magnitude();
        double alpha = (1.0 - beta) * (position.Magnitude() / n);

        double x2 = position.x_ * position.x_;
        double y2 = position.y_ * position.y_;
        double z2 = position.z_ * position.z_;

        double da = 0.0;
        double db = 0.0;
        double dc = 0.0;
        double s = 0.0;
        double dSdA = 1.0;

        do
        {
            alpha -= (s / dSdA);

            da = 1.0 + (alpha * oneOverRadiiSquared_.x_);
            db = 1.0 + (alpha * oneOverRadiiSquared_.y_);
            dc = 1.0 + (alpha * oneOverRadiiSquared_.z_);

            double da2 = da * da;
            double db2 = db * db;
            double dc2 = dc * dc;

            double da3 = da * da2;
            double db3 = db * db2;
            double dc3 = dc * dc2;

            s = x2 / (radiiSquared_.x_ * da2) +
                y2 / (radiiSquared_.y_ * db2) +
                z2 / (radiiSquared_.z_ * dc2) - 1.0;

            dSdA = -2.0 *
                (x2 / (radiiToTheFourth_.x_ * da3) +
                    y2 / (radiiToTheFourth_.y_ * db3) +
                    z2 / (radiiToTheFourth_.z_ * dc3));
        } while (abs(s) > 1E-10);

            return  Vector3D(
                position.x_ / da,
                position.y_ / db,
                position.z_ / dc);
    }

    //Converting a WGS84 point to geographic coordinates
    Geodetic3D Ellipsoid::ToGeodetic3D(Vector3D position)
    {
        Vector3D p = ScaleToGeodeticSurface(position);
        Vector3D h = position - p;
        double height = MathHelper::sgn((h.Dot(position))) * h.Magnitude;
        return  Geodetic3D(ToGeodetic2D(p), height);
    }

    //Computing a curve on the ellipsoid between two surface points
    std::list<Vector3D> Ellipsoid::ComputerCurve(Vector3D start, Vector3D stop, double granularity)
    {
        if (granularity <= 0.0)
        {
            throw  std::out_of_range("Granularity must be greater than zero.");
        }

        Vector3D normal = start.Cross(stop).Normalize();
        double theta = start.AngleBetween(stop);
        int n =fmax((int)(theta / granularity) - 1, 0);

        std::list<Vector3D> positions(2 + n);

        positions.push_back(start);

        for (int i = 1; i <= n; ++i)
        {
            double phi = (i * granularity);
            //add for P38 test
            //positions.Add(0.8 * ScaleToGeocentricSurface(start.RotateAroundAxis(normal, phi)));
            //commit for P38 test
            positions.push_back(ScaleToGeocentricSurface(start.RotateAroundAxis(normal, phi)));
        }

        positions.push_back(stop);

        return positions;
    }
}
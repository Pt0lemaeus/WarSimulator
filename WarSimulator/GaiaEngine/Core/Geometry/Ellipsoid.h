#pragma once
#include "../Vectors/Vector3D.h"
#include "../Geodetic3D.h"
#include "../Geodetic2D.h"
#include <stdexcept>
#include <list>

namespace GaiaEngine::Core {
    class Ellipsoid {
    public:
        Ellipsoid(Vector3D);
        Ellipsoid(double, double, double);
        Vector3D GeodeticSurfaceNormal(Vector3D);
        Vector3D GeodeticSurfaceNormal(Geodetic3D); 
        Vector3D ToVector3D(Geodetic3D); //Converting from geographic to WGS84 
        //Vector3D GeodeticSurfaceNormal(Vector3D);
        Geodetic2D ToGeodetic2D(Vector3D); //Converting surface points from WGS84 to geographic
        Vector3D ScaleToGeocentricSurface(Vector3D); //Scaling a point to the surface along the geocentric surface normal
        Vector3D ScaleToGeodeticSurface(Vector3D); //Scaling a point to the surface along the geodetic surface normal
        Geodetic3D ToGeodetic3D(Vector3D); //Converting a WGS84 point to geographic coordinates
        std::list<Vector3D> ComputerCurve(Vector3D, Vector3D, double); //Computing a curve on the ellipsoid between two surface points


        Vector3D radii_;
        Vector3D radiiSquared_;
        Vector3D radiiToTheFourth_;
        Vector3D oneOverRadiiSquared_;
    };
}
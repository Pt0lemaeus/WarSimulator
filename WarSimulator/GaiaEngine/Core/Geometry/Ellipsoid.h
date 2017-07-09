#pragma once
#include "../Vectors/Vector3D.h"
#include <stdexcept>

namespace GaiaEngine::Core {
    class Ellipsoid {
    public:
        Ellipsoid(Vector3D);
        Ellipsoid(double, double, double);
        Vector3D GeodeticSurfaceNormal(Vector3D);

        Vector3D radii_;
        Vector3D radiiSquared_;
        Vector3D radiiToTheFourth_;
        Vector3D oneOverRadiiSquared_;
    };
}
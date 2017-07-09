#pragma once
#include "Geodetic3D.h"

namespace GaiaEngine::Core {
    class Geodetic3D;
    class Geodetic2D {
    public:
        double longitude_;
        double latitude_;
    public:
        Geodetic2D(double, double);
        Geodetic2D(Geodetic3D);
    };
}
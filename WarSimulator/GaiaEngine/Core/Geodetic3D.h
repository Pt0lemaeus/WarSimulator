#pragma once
#include"Geodetic2D.h"
namespace GaiaEngine::Core {
    class Geodetic2D;
    class Geodetic3D {
    public:
        double longitude_;
        double latitude_;
        double height_;
    public:
        Geodetic3D(double, double, double);
        Geodetic3D(double, double);
        Geodetic3D(Geodetic2D);
        Geodetic3D(Geodetic2D, double);
    };
}


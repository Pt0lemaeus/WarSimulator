#pragma once
#include "Geodetic3D.h"

namespace GaiaEngine::Core {
    class Geodetic2D {
    public:
        double longitude_;
        double latitude_;
    public:
        Geodetic2D(double longitude, double latitude)
        {
            longitude_ = longitude;
            latitude_ = latitude;
        };

        Geodetic2D(Geodetic3D geodetic3D)
        {
            longitude_ = geodetic3D.longitude_;
            latitude_ = geodetic3D.longitude_;
        };
    };
}
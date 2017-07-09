#include "Geodetic2D.h"

namespace GaiaEngine::Core {

    Geodetic2D::Geodetic2D(double longitude, double latitude)
    {
        longitude_ = longitude;
        latitude_ = latitude;
    };

    Geodetic2D::Geodetic2D(Geodetic3D geodetic3D)
    {
        longitude_ = geodetic3D.longitude_;
        latitude_ = geodetic3D.longitude_;
    };
}
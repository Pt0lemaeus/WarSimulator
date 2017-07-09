#include "Geodetic3D.h"

namespace GaiaEngine::Core {
    Geodetic3D::Geodetic3D(double longitude, double latitude, double height)
    {
        longitude_ = longitude;
        latitude_ = latitude;
        height_ = height;
    }

    Geodetic3D::Geodetic3D(double longitude, double latitude)
    {
        longitude_ = longitude;
        latitude_ = latitude;
        height_ = 0;
    }

    Geodetic3D::Geodetic3D(Geodetic2D geodetic2D)
    {
        longitude_ = geodetic2D.longitude_;
        latitude_ = geodetic2D.latitude_;
        height_ = 0;
    }

    Geodetic3D::Geodetic3D(Geodetic2D geodetic2D, double height)
    {
        longitude_ = geodetic2D.longitude_;
        latitude_ = geodetic2D.latitude_;
        height_ = height;
    }
}
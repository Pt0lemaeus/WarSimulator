#pragma once
#include "../Vectors/Vector3D.h"
#include <stdexcept>

namespace GaiaEngine::Core {
    class Ellipsoid {
    public:
        Ellipsoid(Vector3D radii)
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
            radiiToTheFourth_ =  Vector3D(
                radiiSquared_.x_ * radiiSquared_.x_,
                radiiSquared_.y_ * radiiSquared_.y_,
                radiiSquared_.z_ * radiiSquared_.z_);
            oneOverRadiiSquared_ =  Vector3D(
                1.0 / (radii.x_ * radii.x_),
                1.0 / (radii.y_ * radii.y_),
                1.0 / (radii.z_ * radii.z_));
        }

        Vector3D radii_;
        Vector3D radiiSquared_;
        Vector3D radiiToTheFourth_;
        Vector3D oneOverRadiiSquared_;
    };
}
#pragma once
#include <windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "../../../../Common/MathHelper.h"

namespace GaiaEngine::Core{
    const double OneOverPi = 1.0 / MathHelper::Pi;
    const double PiOverTwo = MathHelper::Pi * 0.5;
    const double PiOverThree = MathHelper::Pi / 3.0;
    const double PiOverFour = MathHelper::Pi / 4.0;
    const double PiOverSix = MathHelper::Pi / 6.0;
    const double ThreePiOver2 = (3.0 * MathHelper::Pi) * 0.5;
    const double TwoPi = 2.0 * MathHelper::Pi;
    const double OneOverTwoPi = 1.0 / (2.0 * MathHelper::Pi);
    const double RadiansPerDegree = MathHelper::Pi / 180.0;
}
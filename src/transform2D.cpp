#include "transform2D.hpp"

float Transform2D::deg2rad(float orientation_deg)
{
    return (PI * orientation_deg / 180.0f);
}

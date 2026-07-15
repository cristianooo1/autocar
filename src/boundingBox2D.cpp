#include "boundingBox2D.hpp"

std::vector<raylib::Vector2> BoundingBox2D::GetCorners(Transform2D &transform)
{
    float TLx = -width / 2;
    float TLy = -height * 2 / 3;

    float TRx = +width / 2;
    float TRy = -height * 2 / 3;

    float BLx = -width / 2;
    float BLy = +height / 3;

    float BRx = +width / 2;
    float BRy = +height / 3;

    float car_orientationRad = transform.deg2rad(transform.orientationDeg);
    // std::cout << "rad: " << car_orientationRad << "\n";

    float wTLx = TLx * std::cos(car_orientationRad) - TLy * std::sin(car_orientationRad) + transform.position.x;
    float wTLy = TLx * std::sin(car_orientationRad) + TLy * std::cos(car_orientationRad) + transform.position.y;

    float wTRx = TRx * std::cos(car_orientationRad) - TRy * std::sin(car_orientationRad) + transform.position.x;
    float wTRy = TRx * std::sin(car_orientationRad) + TRy * std::cos(car_orientationRad) + transform.position.y;

    float wBLx = BLx * std::cos(car_orientationRad) - BLy * std::sin(car_orientationRad) + transform.position.x;
    float wBLy = BLx * std::sin(car_orientationRad) + BLy * std::cos(car_orientationRad) + transform.position.y;

    float wBRx = BRx * std::cos(car_orientationRad) - BRy * std::sin(car_orientationRad) + transform.position.x;
    float wBRy = BRx * std::sin(car_orientationRad) + BRy * std::cos(car_orientationRad) + transform.position.y;

    std::vector<raylib::Vector2> corners4{};
    corners4.push_back({wTLx, wTLy});
    corners4.push_back({wTRx, wTRy});
    corners4.push_back({wBLx, wBLy});
    corners4.push_back({wBRx, wBRy});

    return corners4;
}
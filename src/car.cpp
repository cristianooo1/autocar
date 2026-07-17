#include "car.hpp"

Car::Car(raylib::Vector2 dimensions, raylib::Vector2 origin, raylib::Vector2 position)
    : _carTransform{.position = position}, _carBB{.width = dimensions.x, .height = dimensions.y, .origin = origin}
{
    car_throttle = 10.0f;
    car_speed = 0.0f;
    car_brake = 0.97f;
    car_max_speed = 5.0f;

    car_direction = -1;

    car_steering_angle = 0.0f;
    car_steering_angle_speed = 2.0f;
    car_max_steering_angle = 4.0f;
    car_steering_brake = 0.04f;
}

Car::~Car()
{
}

void Car::Update()
{

    // std::cout << "orient_deg: " << _carTransform.orientationDeg << "\n";

    // 90deg offset for car_origin axes to match screen_origin axes!!!!!!!!!!!!
    float radians = _carTransform.deg2rad(_carTransform.orientationDeg + 90.0f);

    _carTransform.position.x += car_speed * std::cos(radians);
    _carTransform.position.y += car_speed * std::sin(radians);

    // upper wall
    // if (_carTransform.position.y - (_carBB.height * 2 / 3) < 0)
    // {
    //     _carTransform.position.y = _carBB.height * 2 / 3;
    // }

    // // lower wall
    // if (_carTransform.position.y + (_carBB.height / 3) > GetScreenHeight())
    // {
    //     _carTransform.position.y = GetScreenHeight() - _carBB.height / 3;
    // }
    // std::cout << "orientation: " << car_orientation << " Speed: " << car_speed << "\n";
}

void Car::Draw()
{
    float w = _carBB.width * _carTransform.scale;
    float h = _carBB.height * _carTransform.scale;

    raylib::Vector2 drawingPosition = {
        _carTransform.position.x - w * (_carBB.width / 2),
        _carTransform.position.y - h * (_carBB.height * 2 / 3),
    };
    _car_draw_rec.x = _carTransform.position.x;
    _car_draw_rec.y = _carTransform.position.y;
    _car_draw_rec.width = _carBB.width;
    _car_draw_rec.height = _carBB.height;

    DrawRectanglePro(_car_draw_rec,
                     _carBB.origin,
                     this->_carTransform.orientationDeg,
                     raylib::Color::White());

    DrawCircle(_carTransform.position.x, _carTransform.position.y, 5.0f, raylib::Color::Red());
    // std::cout << car_rectangle.x << " and " << car_rectangle.y << "\n";
}

raylib::Vector2 Car::GetCarPosition()
{
    return _carTransform.position;
}

std::vector<raylib::Vector2> Car::GetCarBoundaries()
{
    return _carBB.GetCorners(_carTransform);
}

void Car::SetThrottle(int direction, float dt)
{
    if (direction == -1)
    {
        car_speed -= car_throttle * dt;
        if (std::abs(car_speed) > car_max_speed)
        {
            car_speed = -car_max_speed;
        }
    }
    else if (direction == 1)
    {
        car_speed += car_throttle * dt;
        if (std::abs(car_speed) > car_max_speed)
        {
            car_speed = car_max_speed;
        }
    }
    else
    {
        car_speed = car_brake * car_speed;
        if (std::abs(car_speed) < 0.2f)
        {
            car_speed = 0.0f;
        }
    }
    // std::cout << "dt from car: " << dt << "\n";
    // std::cout << "Direction: " << direction << " Speed: " << car_speed << "\n";
}

void Car::SetSteering(int direction, float dt)
{
    // rotate left
    if (direction == -1)
    {
        car_steering_angle -= car_steering_angle_speed * dt * std::abs(car_speed);
        if (car_steering_angle < -car_max_steering_angle)
        {
            car_steering_angle = -car_max_steering_angle;
        }
    }
    // rotate right
    else if (direction == 1)
    {
        car_steering_angle += car_steering_angle_speed * dt * std::abs(car_speed);
        if (car_steering_angle > car_max_steering_angle)
        {
            car_steering_angle = car_max_steering_angle;
        }
    }
    car_steering_angle = car_steering_angle * (1 - car_steering_brake);

    this->_carTransform.orientationDeg += car_steering_angle;
    if (this->_carTransform.orientationDeg > 360.0f)
    {
        this->_carTransform.orientationDeg -= 360.0f;
    }
    else if (this->_carTransform.orientationDeg < -360.0f)
    {
        this->_carTransform.orientationDeg += 360.0f;
    }

    // std::cout << "dt from car: " << dt << "\n";
    // std::cout << "steering angle: " << car_steering_angle << "\n";
    // std::cout << "orientation: " << car_orientation << "\n";
}

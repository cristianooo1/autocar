#include "car.hpp"

Car::Car()
{
    car_dimensions = raylib::Vector2(CAR_WIDTH, CAR_LENGTH);
    car_rectangle.SetSize(car_dimensions);

    car_origin_pos = raylib::Vector2(CAR_WIDTH / 2,
                                     CAR_LENGTH * 2 / 3);
    car_origin.SetSize(1.0f, 1.0f);

    car_position = raylib::Vector2{100.0f, 100.0f};

    car_throttle = 10.0f;
    car_speed = 0.0f;
    car_brake = 0.97f;
    car_max_speed = 5.0f;

    car_direction = -1;
    car_orientation = 0.0f;

    car_steering_angle = 0.0f;
    car_steering_angle_speed = 2.0f;
    car_max_steering_angle = 4.0f;
    car_steering_brake = 0.04f;
}

Car::~Car()
{
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
    car_orientation += car_steering_angle;

    // std::cout << "dt from car: " << dt << "\n";
    // std::cout << "steering angle: " << car_steering_angle << "\n";
    // std::cout << "orientation: " << car_orientation << "\n";
}

void Car::UpdatePosition()
{
    // 90deg offset for car_origin axes to match screen_origin axes
    float radians = PI * (car_orientation + 90) / 180;

    car_position.x += car_speed * std::cos(radians);
    car_position.y += car_speed * std::sin(radians);

    // upper wall
    if (car_position.y - (CAR_LENGTH * 2 / 3) < 0)
    {
        car_position.y = CAR_LENGTH * 2 / 3;
    }

    // lower wall
    if (car_position.y + (CAR_LENGTH / 3) > GetScreenHeight())
    {
        car_position.y = GetScreenHeight() - CAR_LENGTH / 3;
    }
    // std::cout << "orientation: " << car_orientation << " Speed: " << car_speed << "\n";
}

void Car::Draw()
{
    car_rectangle.SetPosition(car_position);
    car_origin.SetPosition(car_position);

    car_rectangle.Draw({car_origin_pos.x, car_origin_pos.y},
                       car_orientation,
                       raylib::Color::Blue());

    car_origin.Draw(raylib::Vector2(0, 0),
                    0.0f,
                    raylib::Color::Red());

    // std::cout << car_rectangle.x << " and " << car_rectangle.y << "\n";
}
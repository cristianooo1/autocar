#include "rayCasting.hpp"

RayCasting::RayCasting()
{
}

RayCasting::~RayCasting()
{
}

void RayCasting::calculateVisibilityPolygon(float ox, float oy, float radius, std::vector<MapGenerator::Line> &_edges)
{
    // ox and oy: ORIGIN = center point from where rays are shot from

    // must clear to prevent memory reallocation
    this->vectorPolygons.clear();

    for (const MapGenerator::Line &edge : _edges)
    {

        for (int i = 0; i < 2; i++)
        {
            float rdx, rdy;
            if (i == 0)
            {
                rdx = edge.start.x - ox;
                rdy = edge.start.y - oy;
            }
            else
            {
                rdx = edge.end.x - ox;
                rdy = edge.end.y - oy;
            }

            float base_ang = std::atan2(rdy, rdx);

            float ang = 0.0f;

            // cast 3 rays for each point
            for (int j = 0; j < 3; j++)
            {
                if (j == 0)
                {
                    ang = base_ang - 0.0001f;
                }
                else if (j == 1)
                {
                    ang = base_ang;
                }
                else // j==2
                {
                    ang = base_ang + 0.0001f;
                }

                // create ray
                rdx = radius * std::cos(ang);
                rdy = radius * std::sin(ang);

                float min_t1 = INFINITY;
                float min_px = 0.0f, min_py = 0.0f, min_ang = 0.0f;
                float localDist = 0.0f;
                bool isValid = false;

                for (const MapGenerator::Line &_edge2 : _edges)
                {
                    float sdx = _edge2.end.x - _edge2.start.x;
                    float sdy = _edge2.end.y - _edge2.start.y;

                    float denom = (sdx * rdy - sdy * rdx);
                    if (std::fabs(denom) > 0.001f)
                    {
                        // t2: normalized distance from line segment start to line segment end of intersect pos
                        float t2 = (rdx * (_edge2.start.y - oy) + (rdy * (ox - _edge2.start.x))) / denom;

                        // t1: normalized distance form source along ray to ray length of intersect pos
                        float t1 = 0.0f;
                        if (std::fabs(rdx) > std::fabs(rdy))
                        {

                            t1 = (_edge2.start.x + sdx * t2 - ox) / rdx;
                        }
                        else
                        {
                            t1 = (_edge2.start.y + sdy * t2 - oy) / rdy;
                        }

                        if (t1 > 0.0f && t1 <= 1.0f && t2 >= 0.0f && t2 <= 1.0f)
                        {
                            if (t1 < min_t1)
                            {
                                min_t1 = t1;
                                min_px = ox + rdx * t1;
                                min_py = oy + rdy * t1;
                                localDist = t1 * radius;
                                min_ang = std::atan2(min_py - oy, min_px - ox);
                                isValid = true;
                            }
                        }
                    }
                }

                // if (!isValid)
                // {
                //     min_px = ox + rdx;
                //     min_py = oy + rdy;
                //     localDist = radius;
                //     min_ang = std::atan2(min_py - oy, min_px - ox);
                //     isValid = true;
                // }

                if (isValid)
                {
                    // float theta_norm = min_ang + (PI * 90.0f / 180.0f);
                    float theta_norm = min_ang;
                    if (theta_norm > PI)
                    {
                        theta_norm -= (2.0f * PI);
                    }
                    else if (theta_norm < -PI)
                    {
                        theta_norm += (2.0f * PI);
                    }
                    this->vectorPolygons.push_back(Polygon{
                        .theta = theta_norm,
                        .px = min_px,
                        .py = min_py,
                        .distance = localDist});
                }
            }
        }
    }

    // sort polygon vector by angle from source
    std::sort(
        this->vectorPolygons.begin(),
        this->vectorPolygons.end(),
        [&](const Polygon &t1, const Polygon &t2)
        {
            if (t1.theta < t2.theta)
            {
                return true;
            }
            else
            {
                return false;
            }
        });
    this->raysCasted.rayCast = this->vectorPolygons.size();

    // remove duplicates in the polygon vector
    auto it = std::unique(

        this->vectorPolygons.begin(),
        this->vectorPolygons.end(),
        [&](const Polygon &t1, const Polygon &t2)
        {
            if (std::fabs(t1.px - t2.px) < 0.1f && std::fabs(t1.py - t2.py) < 0.1f)
            {
                return true;
            }
            else
            {
                return false;
            }
        });

    this->vectorPolygons.resize(std::distance(vectorPolygons.begin(), it));
    this->raysCasted.rayCastUnique = this->vectorPolygons.size();
}

void RayCasting::getLidarRays(float ox, float oy, float resolution, float maxRange, float carHeadingRad, const std::vector<MapGenerator::Line> &_edges)
{
    this->vectorLidarRays.clear();

    int idx = 0;
    for (float angleRad = -PI; angleRad < (PI - 0.0001f); angleRad += resolution)
    {

        // global angle of ray
        float currentLidarRayAngle = angleRad + carHeadingRad;

        // WRAP to [-PI,PI]
        while (currentLidarRayAngle > PI)
        {
            currentLidarRayAngle -= (2.0f * PI);
        }
        while (currentLidarRayAngle < -PI)
        {
            currentLidarRayAngle += (2.0f * PI);
        }

        // ray direction vector
        float rdx = std::cos(currentLidarRayAngle);
        float rdy = std::sin(currentLidarRayAngle);

        float closestDistance = maxRange;
        bool hitSomething = false;

        // test ray against all edges
        // ADD SPATIAL PARTITIONING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // group edges in chunks and only check the chunk closest to the car!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for (const MapGenerator::Line &edge : _edges)
        {
            float sdx = edge.end.x - edge.start.x;
            float sdy = edge.end.y - edge.start.y;

            float denom = (rdx * sdy - rdy * sdx);

            // check if lines are parallel
            if (std::fabs(denom) > 0.0001f)
            {
                // t1: distance along the lidar ray
                float t1 = ((edge.start.x - ox) * sdy - (edge.start.y - oy) * sdx) / denom;

                // t2: position along the line segment normalized 0.0 to 1.0
                float t2 = ((edge.start.x - ox) * rdy - (edge.start.y - oy) * rdx) / denom;

                if (t2 >= 0.0f && t2 <= 1.0f && t1 > 0.0f)
                {
                    if (t1 < closestDistance)
                    {
                        closestDistance = t1;
                        hitSomething = true;
                    }
                }
            }
        }

        vectorLidarRays.push_back(LidarRay{
            .hit = hitSomething,
            .angle = angleRad,
            .distance = closestDistance});
    }
    this->raysCasted.rayLidar = this->vectorLidarRays.size();
}

void RayCasting::DrawVisibilityPolygon(raylib::Vector2 source)
{
    if (this->vectorPolygons.size() > 1)
    {
        for (int i = 0; i < vectorPolygons.size(); i++)
        {
            int next_idx = (i + 1) % vectorPolygons.size();
            raylib::Vector2 p1 = {vectorPolygons[i].px, vectorPolygons[i].py};
            raylib::Vector2 p2 = {vectorPolygons[next_idx].px, vectorPolygons[next_idx].py};

            // Draw the perimeter the Lidar tests against in bright MAGENTA
            DrawLineEx(p1, p2, 2.0f, raylib::Color::Magenta());

            // Draw a small circle at the vertex to see the points
            DrawCircleV(p1, 3.0f, raylib::Color::Green());

            // Optional: Draw the ID to see the sorting order
            // DrawText(TextFormat("id:%i", i), p1.x + 5, p1.y + 5, 10, WHITE);
            // // DrawTriangleLines(
            // //     source,
            // //     {this->vectorPolygons[i + 1].px, this->vectorPolygons[i + 1].py},
            // //     {this->vectorPolygons[i].px, this->vectorPolygons[i].py},
            // //     raylib::Color::Yellow());
            // DrawLineV(source, {vectorPolygons[i].px, vectorPolygons[i].py}, raylib::Color::Yellow());
            // DrawText(TextFormat("r:%i", i), vectorPolygons[i].px + 10, vectorPolygons[i].py + 10, 20, RED);
        }

        // close triangle at the end
        // DrawTriangleLines(
        //     source,
        //     {this->vectorPolygons[0].px, this->vectorPolygons[0].py},
        //     {this->vectorPolygons[vectorPolygons.size() - 1].px, this->vectorPolygons[vectorPolygons.size() - 1].py},
        //     raylib::Color::Yellow());
    }
}

RayCasting::RayCast RayCasting::getNumberRays()
{
    return {raysCasted.rayCast, raysCasted.rayCastUnique, raysCasted.rayLidar};
}

void RayCasting::printVisibilityPolygon(int nr)
{

    std::cout << "nr polys: " << vectorPolygons.size() << "\n";
    int idx = 0;
    for (const RayCasting::Polygon poly : vectorPolygons)
    {
        std::cout << "id: " << idx << "; ox: " << poly.px << "; oy: " << poly.py << "; theta: " << poly.theta << "; dist= " << poly.distance << "\n";
        idx++;
    }
    idx = 0;
}

void RayCasting::DrawLidarRays(raylib::Vector2 source, float carHeadingRad)
{
    if (this->vectorLidarRays.size() > 1)
    {
        for (int i = 0; i < vectorLidarRays.size(); i++)
        {
            float globalAngle = vectorLidarRays[i].angle + carHeadingRad;
            float hitx = source.x + std::cos(globalAngle) * vectorLidarRays[i].distance;
            float hity = source.y + std::sin(globalAngle) * vectorLidarRays[i].distance;

            if (vectorLidarRays[i].hit)

                DrawLineV(source, {hitx, hity}, raylib::Color::Red());
            else
                DrawLineV(source, {hitx, hity}, raylib::Color::DarkBlue());

            DrawText(TextFormat("%i, ang:%02.02f, d:%02.02f", i, vectorLidarRays[i].angle, vectorLidarRays[i].distance), hitx + 10, hity + 10, 20, RED);
        }
    }
}
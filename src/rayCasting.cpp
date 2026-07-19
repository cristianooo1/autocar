#include "rayCasting.hpp"

RayCasting::RayCasting()
{
}

RayCasting::~RayCasting()
{
}

void RayCasting::calculateVisibilityPolygon(float ox, float oy, float radius, std::vector<MapGenerator::Line> &_edges)
{
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
                                min_ang = std::atan2(min_py - oy, min_px - ox);
                                isValid = true;
                            }
                        }
                    }
                }

                // add intersection to polygon vector
                // only if ray hit something
                if (isValid)
                {
                    this->vectorPolygons.push_back(Polygon{
                        .theta = min_ang,
                        .ox = min_px,
                        .oy = min_py,
                    });
                }
                // else
                // {
                //     this->vectorPolygons.push_back(Polygon{
                //         .theta = ang,
                //         .ox = ox + rdx,
                //         .oy = oy + rdy,
                //     });
                // }
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
            if (std::fabs(t1.ox - t2.ox) < 0.1f && std::fabs(t1.oy - t2.oy) < 0.1f)
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

void RayCasting::Draw(raylib::Vector2 source)
{
    if (this->vectorPolygons.size() > 1)
    {
        for (int i = 0; i < vectorPolygons.size() - 1; i++)
        {
            DrawTriangleLines(
                source,
                {this->vectorPolygons[i + 1].ox, this->vectorPolygons[i + 1].oy},
                {this->vectorPolygons[i].ox, this->vectorPolygons[i].oy},
                raylib::Color::Yellow());

            // DrawTriangleLines(
            //     source,
            //     {this->vectorPolygons[i].ox, this->vectorPolygons[i].oy},
            //     {this->vectorPolygons[i + 1].ox, this->vectorPolygons[i + 1].oy},
            //     raylib::Color::Yellow());
        }

        // close triangle at the end
        DrawTriangleLines(
            source,
            {this->vectorPolygons[0].ox, this->vectorPolygons[0].oy},
            {this->vectorPolygons[vectorPolygons.size() - 1].ox, this->vectorPolygons[vectorPolygons.size() - 1].oy},
            raylib::Color::Yellow());
    }
}

RayCasting::RayCast RayCasting::getNumberRays()
{
    return {raysCasted.rayCast, raysCasted.rayCastUnique};
}
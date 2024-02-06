#include "curves.h"

bool Circle::isParamValid(double t) const
{
    if (t < 0.0 || t > 2.0 * PI || std::fabs(2.0 * PI - t) < SIGMA)
        throw std::runtime_error("Invalid parameter \"t\" for circle.");
    else
        return true;
}

const Point &Circle::getPoint(double t)
{
    if (isParamValid(t))
    {
        double x = r * cos(t);
        double y = r * sin(t);

        std::fabs(x) < SIGMA ? point.x = 0.0 : point.x = x;
        std::fabs(y) < SIGMA ? point.y = 0.0 : point.y = y;

        point.z = 0.0;

        return point;
    }
}

const DerivativeVector &Circle::getDerivative(double t)
{
    if (isParamValid(t))
    {
        double i = -r * sin(t);
        double j = r * cos(t);

        std::fabs(i) < SIGMA ? vector.i = 0.0 : vector.i = i;
        std::fabs(j) < SIGMA ? vector.j = 0.0 : vector.j = j;

        vector.k = 0.0;

        return vector;
    }
}

double Circle::getRadius() const
{
    return r;
}

const int &Circle::getCurveID() const
{
    return id;
}

bool Oval::isParamValid(double t) const
{
    if (t < 0 || t > 2 * PI || std::fabs(2 * PI - t) < SIGMA)
        throw std::runtime_error("Invalid parameter \"t\" for Oval.");
    else
        return true;
}

const Point &Oval::getPoint(double t)
{
    if (isParamValid(t))
    {
        double x = rx * cos(t);
        double y = ry * sin(t);

        std::fabs(x) < SIGMA ? point.x = 0.0 : point.x = x;
        std::fabs(y) < SIGMA ? point.y = 0.0 : point.y = y;

        point.z = 0.0;

        return point;
    }
}

const DerivativeVector &Oval::getDerivative(double t)
{
    if (isParamValid(t))
    {
        double i = -rx * sin(t);
        double j = ry * cos(t);

        std::fabs(i) < SIGMA ? vector.i = 0.0 : vector.i = i;
        std::fabs(j) < SIGMA ? vector.j = 0.0 : vector.j = j;

        vector.k = 0.0;

        return vector;
    }
}

const int &Oval::getCurveID() const
{
    return id;
}

bool Helix::isParamValid(double t) const
{
    if (t < 0.0)
        throw std::runtime_error("Invalid parameter \"t\" for helix.");
    else
        return true;
}

const Point &Helix::getPoint(double t)
{
    if (isParamValid(t))
    {
        double x = r * cos(t);
        double y = r * sin(t);
        double z = step * t / (2 * PI);

        std::fabs(x) < SIGMA ? point.x = 0.0 : point.x = x;
        std::fabs(y) < SIGMA ? point.y = 0.0 : point.y = y;
        std::fabs(z) < SIGMA ? point.y = 0.0 : point.z = z;

        return point;
    }
}

const DerivativeVector &Helix::getDerivative(double t)
{
    if (isParamValid(t))
    {
        double i = -r * sin(t);
        double j = r * cos(t);

        std::fabs(i) < SIGMA ? vector.i = 0.0 : vector.i = i;
        std::fabs(j) < SIGMA ? vector.j = 0.0 : vector.j = j;

        vector.k = step / (2 * PI);

        return vector;
    }
}

const int &Helix::getCurveID() const
{
    return id;
}

std::shared_ptr<Curve> Curve::createCurve(int id)
{
    std::shared_ptr<Curve> ptr = nullptr;
    srand(time(NULL));
    switch (id)
    {
    case 0:
    {
        double r = std::rand() % 20 + 1.0;
        ptr = std::make_shared<Circle>(r);
        std::cout << "Circle create" << std::endl;
        break;
    }
    case 1:
    {
        double rx = std::rand() % 20 + 1.0;
        double ry = std::rand() % 10 + 1.0;
        ptr = std::make_shared<Oval>(rx, ry);
        std::cout << "Oval create" << std::endl;
        break;
    }
    case 2:
    {
        double r = std::rand() % 20 + 1.0;
        double step = std::rand() % 5 + 1.0;
        ptr = std::make_shared<Helix>(r, step);
        std::cout << "Helix create" << std::endl;
        break;
    }
    default:
        break;
    }

    return ptr;
}
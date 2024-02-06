#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <memory>

#ifndef SIGMA
#define SIGMA 0.01
#endif

#ifndef PI
#define PI 3.141
#endif

#ifdef CURVESLIBRARYDYNAMIC_EXPORTS
#define CURVESLIBRARYDYNAMIC_API __declspec(dllexport)
#else
#define CURVESLIBRARYDYNAMIC_API __declspec(dllimport)
#endif

CURVESLIBRARYDYNAMIC_API struct Point
{
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

CURVESLIBRARYDYNAMIC_API struct DerivativeVector
{
public:
    double i = 0.0;
    double j = 0.0;
    double k = 0.0;
};

class Curve
{
public:
    CURVESLIBRARYDYNAMIC_API virtual const Point &getPoint(double) = 0;
    CURVESLIBRARYDYNAMIC_API virtual const DerivativeVector &getDerivative(double) = 0;
    CURVESLIBRARYDYNAMIC_API virtual const int& getCurveID() const = 0;
    virtual ~Curve() {std::cout << "Destructor" << std::endl;}
    CURVESLIBRARYDYNAMIC_API static std::shared_ptr<Curve> createCurve(int id);
};

CURVESLIBRARYDYNAMIC_API class Circle : public Curve
{
private:
    int id = 0;
    Point point;
    DerivativeVector vector;
    double r = 0.0;
    CURVESLIBRARYDYNAMIC_API bool isParamValid(double) const;

public:
    Circle(double _r) : r(_r){}
    CURVESLIBRARYDYNAMIC_API const Point &getPoint(double) override;
    CURVESLIBRARYDYNAMIC_API const DerivativeVector &getDerivative(double) override;
    CURVESLIBRARYDYNAMIC_API double getRadius() const;
    CURVESLIBRARYDYNAMIC_API virtual const int &getCurveID() const override;
};

CURVESLIBRARYDYNAMIC_API class Oval : public Curve
{
private:
    int id = 1;
    Point point;
    DerivativeVector vector;
    double rx = 0.0;
    double ry = 0.0;
    CURVESLIBRARYDYNAMIC_API bool isParamValid(double) const;

public:
    Oval(double _rx, double _ry) : rx(_rx), ry(_ry){}
    CURVESLIBRARYDYNAMIC_API const Point &getPoint(double) override;
    CURVESLIBRARYDYNAMIC_API const DerivativeVector &getDerivative(double) override;
    CURVESLIBRARYDYNAMIC_API virtual const int &getCurveID() const override;
};

CURVESLIBRARYDYNAMIC_API class Helix : public Curve
{
private:
    int id = 2;
    Point point;
    DerivativeVector vector;
    double r = 0.0;
    double step = 0.0;
    CURVESLIBRARYDYNAMIC_API bool isParamValid(double) const;

public:
    Helix(double _r, double _step) : r(_r), step(_step){}
    CURVESLIBRARYDYNAMIC_API const Point &getPoint(double) override;
    CURVESLIBRARYDYNAMIC_API const DerivativeVector &getDerivative(double) override;
    CURVESLIBRARYDYNAMIC_API virtual const int &getCurveID() const override;
};
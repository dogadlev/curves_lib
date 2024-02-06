#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>
#include <thread>
#include <chrono>
#include <memory>
#include "curves.h"

void printPoint(const Point &p)
{
    std::cout << "{" << p.x << "; " << p.y << "; " << p.z << "}" << std::endl;
}

void printDerivative(const DerivativeVector &d)
{
    std::cout << "(" << d.i << "i, " << d.j << "j, " << d.k << "k)" << std::endl;
}

int main(int argc, char **argv)
{
    try
    {
        // Filling vector with pointers which pointed to objects inherited from Curve;
        int curvQuan = 10;
        std::vector<std::shared_ptr<Curve>> vDif;
        while (curvQuan-- > 0)
        {
            int id = rand() % 3;
            vDif.push_back(Curve::createCurve(id));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::vector<std::shared_ptr<Curve>> vCirc;

        // Get and print points and derivatives. Filling second vector with pointers which pointed to circles;
        std::cout << "Points and derivatives: " << std::endl;
        for (auto &el : vDif)
        {
            if (el->getCurveID() == 0)
            {
                vCirc.push_back(el);
            }
            printPoint(el->getPoint(PI / 4.0));
            printDerivative(el->getDerivative(PI / 4.0));
        }

        // Sorting vector which contains circle pointers;
        std::sort(vCirc.begin(), vCirc.end(), [](std::shared_ptr<Curve> ptrA, std::shared_ptr<Curve> ptrB)
                  {
            auto ptrCA = std::dynamic_pointer_cast<Circle>(ptrA);
            auto ptrCB = std::dynamic_pointer_cast<Circle>(ptrB);
            if(ptrCA && ptrCB)
            {
                return ptrCA->getRadius() < ptrCB->getRadius();
            } });

        // Printing radii of circles. Calculating sum of circles radii;
        double radiiSum = 0;
        std::cout << "Radii of circles: " << std::endl;
        ;
        for (auto &el : vCirc)
        {
            auto ptr = std::dynamic_pointer_cast<Circle>(el);
            if (ptr)
            {
                int radius = ptr->getRadius();
                std::cout << radius << std::endl;
                radiiSum += radius;
            }
        }

        std::cout << "Radii sum: " << radiiSum << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Error!" << std::endl;
    }

    return 0;
}
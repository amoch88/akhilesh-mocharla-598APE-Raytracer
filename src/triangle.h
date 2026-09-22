#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "plane.h"

class Triangle : public Plane{
public:
   double thirdX;

   // Precomputed triangle edges for fast ray intersection.
   Vector edge1;
   Vector edge2;

   Triangle(Vector c, Vector b, Vector a, Texture* t);
   double getIntersection(const Ray& ray);
   bool getLightIntersection(const Ray& ray, double* fill);
};

#endif

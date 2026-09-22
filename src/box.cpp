#include "box.h"

Box::Box(const Vector &c, Texture* t, double ya, double pi, double ro, double tx, double ty):Plane(c, t, ya, pi, ro, tx, ty){}
Box::Box(const Vector &c, Texture* t, double ya, double pi, double ro, double tx):Plane(c, t, ya, pi, ro, tx,tx){}

double Box::getIntersection(const Ray& ray){
   const double time = Plane::getIntersection(ray);

   if(time == inf)
      return inf;

   const Vector offset = ray.point + ray.vector * time - center;

   const double x = offset.dot(right);
   const double y = offset.dot(up);

   return (((x >= 0) ? x : -x) > textureX / 2 ||
           ((y >= 0) ? y : -y) > textureY / 2)
          ? inf : time;
}

bool Box::getLightIntersection(const Ray& ray, double* fill){
   const double t = ray.vector.dot(vect);
   const double norm = vect.dot(ray.point)+d;
   const double r = -norm/t;
   if(r<=0. || r>=1.) return false;

   const Vector offset = ray.point + ray.vector * r - center;

   const double distX = offset.dot(right);
   const double distY = offset.dot(up);

   if( ((distX>=0)?distX:-distX)>textureX/2 || ((distY>=0)?distY:-distY)>textureY/2 ) return false;

   if(texture->opacity>1-1E-6) return true;   
   unsigned char temp[4];
   double amb, op, ref;
   texture->getColor(temp, &amb, &op, &ref,fix(distX/textureX-.5), fix(distY/textureY-.5));
   if(op>1-1E-6) return true;
   fill[0]*=temp[0]/255.;
   fill[1]*=temp[1]/255.;
   fill[2]*=temp[2]/255.;
   return false;
}
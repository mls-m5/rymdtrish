#ifndef _spark_h_
#define _spark_h_
#include "body.h"

class Spark: public Body{
 private:
  
 public:
  Spark(){Body();};
  Spark(double x, double y, double vx, double vy);
  void update(double dt);
  void draw() const ;
};

#endif

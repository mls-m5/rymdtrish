#ifndef _body_h_
#define _body_h_

#define PI 3.14159265

class Body
{
 public:
  Body();
  Body(double x, double y, double angle);
  Body(double x, double y, double angle,
       double vx, double vy, double vangle);
  virtual void update(double dt);
  virtual void draw() const {};
  virtual void kill();
  virtual bool inside(double x, double y) const;

  virtual void hit(double d);

  void setDuration(double d);
  void setHitPoints(double hp);

  void setColor(double r, double g, double b) 
  {
    this->r = r; this->g = g; this->b = b;
  }
  void setSize(double size)
  {
    this->size = size;
  }
 protected:
  // Position and angle
  // units is in ship lengths, angle is in radians
  double x;
  double y;
  double angle;
  // Velocity
  double vx;
  double vy;
  double vangle;
  // Size
  double size;
  // Color
  double r, b, g;

  //duration = the time before the object by itself calls kill()
  //if set to -1 the duration is infinite
  double duration;
  //the vitalaty of the object
  //if less than zero the kill() function is to be called
  double hitPoints;
};

#endif

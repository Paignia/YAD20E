#include "Entity.h"
#ifndef __MOVENTITY__
#define __MOVENTITY__

enum DIRECTION {UP=0,DOWN,LEFT,RIGHT};

struct Point2d
{
    int x;
    int y;
};

class MovingEntity:public Entity
{
private:
    Point2d *dest;

    float velx,vely;
protected:
    Point2d dir;
public:
    MovingEntity(SDL_Texture *t,int w,int h);
    MovingEntity(const MovingEntity &anentity);
    virtual ~MovingEntity();
    void SetVelocity(float vx,float vy);
    void SetDestination(Point2d *p);
    void SetDestination(int x,int y);
    virtual void Update(float time);
    void setPosition(int x,int y);
    bool reachedDestination();

};

#endif // __ENTITY__

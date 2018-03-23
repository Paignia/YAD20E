#include "Turn.h"
#include <SDL2/SDL.h>
#include <deque>
#include <set>
#include "InfoSurface.h"
#include "AIEntity.h"

#ifndef __TURN_ENGINE__
#define  __TURN_ENGINE__

class Camera;
class TurnEngine
{

private:
    Turn *the_turn;
    Camera *camera;
    std::deque<unsigned int> turn_order;
    std::unordered_map<unsigned int,BaseCharacter*>::iterator it;
    InfoSurface *Log;

public:
    TurnEngine(Camera *camera);
    virtual ~TurnEngine();
    void Update(float time);
    void Handle_Events(SDL_Event *event);
    Turn* NextTurn();
    Turn* GetTurn();
    Camera* GetCamera();

};

#endif
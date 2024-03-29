#include <SDL2/SDL.h>
#include <unordered_map>
#include "AnimatedEntity.h"
using std::unordered_map;
#ifndef __DOODAD_H__
#define __DOODAD_H__

//adjust accordingly
//Overload to create doodads specific to your game or just provide doodadfuncs
class Doodad;
typedef void (*DoodadFunction)(Doodad *doodad);
class Doodad
{
 private:
  unsigned int ID;
  AnimatedEntity *anim_entity;
  //HealthStats *health_stats;
  int cur_state;
  int visibility;
  unordered_map<int,DoodadFunction> state_functions;
 public:
  Doodad(AnimatedEntity *anim_entity);
  virtual ~Doodad();
  virtual void Update(float time);
  void Draw(SDL_Texture *screen);
  void Trigger();//advances to next state cyclically
  void Toggle();//executes the current state_func
  void SetState(int state);
  void AddState(DoodadFunction dood_func);
  int GetCurrentState();
  AnimatedEntity* GetEntity();
  void SetID(unsigned int id);
  unsigned int GetID();
  int getVisibility();
	void setVisibility(int visibility);
};
#endif


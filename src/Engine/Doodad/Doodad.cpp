#include "Doodad.h"


Doodad::Doodad(AnimatedEntity *anim_entity):anim_entity(anim_entity)
{
  cur_state=-1;
  ID=-1;
  anim_entity->setAnimation(0);
}


void Doodad::SetID(unsigned int id)
{
  this->ID=id;
}
unsigned int Doodad::GetID()
{
  return this->ID;
}
Doodad::~Doodad()
{

}
void Doodad::Update(float time)
{
  
}
void Doodad::Draw(SDL_Texture *screen)
{
  anim_entity->Draw(screen);
}
void Doodad::Trigger()
{
  cur_state++;
  if(cur_state>=state_functions.size())
    cur_state=0;
  state_functions[cur_state](this);
}

void Doodad::Toggle()
{
  state_functions[cur_state](this);
}
void Doodad::SetState(int state)
{
  cur_state=state;
}

void Doodad::AddState(DoodadFunction dood_func)
{
  state_functions[state_functions.size()]=dood_func;
}

int Doodad::GetCurrentState()
{
  return cur_state;
}

AnimatedEntity* Doodad::GetEntity()
{
  return anim_entity;
}

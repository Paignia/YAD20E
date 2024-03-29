#include "Blast.h"


Blast::Blast(AnimatedEntity *animentity):animentity(animentity)
{

  this->Active=false;
  //animentity->setAnimLoop(YES);
  animentity->setAnimation(0);
}

Blast::  Blast(const Blast &ablast)
{
  this->Active=ablast.Active;
  this->animentity=new AnimatedEntity(*ablast.animentity);
}

Blast::~Blast()
{
  delete animentity;
}


void Blast::Update(float time)
{
   if(this->Active)
  this->animentity->Update(time);


}


void Blast::Draw(SDL_Texture *screen)
{

  if(this->Active)
  this->animentity->Draw(screen);

}


void Blast::MakeActive(bool Active)
{
  this->Active=Active;
}


void Blast::SetPosition(int x, int y)
{

  this->animentity->setPosition(x,y+animentity->getPosition().h/2);

}


bool Blast::Done()
{

  return animentity->getCur_Anim()->Done();
}

void Blast::Reset()
{
  animentity->setAnimation(0);
}

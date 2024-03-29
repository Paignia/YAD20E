#include <SDL2/SDL.h>
#include "Spell.h"

#ifndef __EOTSPELL_H
#define __EOTSPELL_H

class EOTSpell: public Spell
{
protected:
  AnimatedEntity *spell_entity;
  int duration;
  int orig_duration;
  
public:
  EOTSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity,int duration);
  EOTSpell(const EOTSpell &aspell);
  virtual ~EOTSpell();
  virtual void Update(float time);
  virtual void Draw(SDL_Texture *screen);
  virtual void OnCast();
  virtual void OnDone();
  void Place();
  void Reset();
  void Trigger();
  void SetDuration(int duration);
  int  GetDuration();
 

};


#endif

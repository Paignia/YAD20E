#include "TargetSpell.h"


TargetSpell::TargetSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *animated_entity):
  Spell(spell_info,caster,Effect),animated_entity(animated_entity)
{
  projectile=NULL;
}

TargetSpell::TargetSpell(const TargetSpell &aspell):Spell(aspell)
{
  this->animated_entity=new AnimatedEntity(*aspell.animated_entity);
  this->projectile=new Projectile(*aspell.projectile);
}

TargetSpell::~TargetSpell()
{
  if(projectile)
    delete projectile;
  delete animated_entity;
}

void TargetSpell::Update(float time)
{

  if(IsCast())
    {
      if(projectile)
	{
	  if(!projectile->Hit())
	    {
	      projectile->Update(time);
	    }
	  else
	    {
	      Effect(sp_stats);
	      OnDone();
	    }
	}
    }
}

void TargetSpell::Draw(SDL_Texture *screen)
{

  if(projectile)
    {
      if(!projectile->Hit())
	{
	  projectile->Draw(screen);
	}
    }
 

}

void TargetSpell::Reset()
{
  projectile->Place(caster->GetBaseEntity()->getPosition(),caster->GetDirection());
  projectile->Reset();
  projectile->SetUp();
  projectile->MakeActive(true);
}

void TargetSpell::OnCast()
{


  if(sp_stats)
    {
      SDL_Rect target{(short)(sp_stats->GetTarget().first),(short)(sp_stats->GetTarget().second),60,60};
      if(!projectile)
	{
	  projectile=new Projectile(animated_entity,target,10);
	}
      else
	{
	  projectile->setTarget(target);
	}
      Reset();
	  
    }
}

void TargetSpell::OnDone()
{
  SetCast(false);
  projectile->MakeActive(false);
  

}

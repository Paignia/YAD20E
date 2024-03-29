#include "ConeSpell.h"

ConeSpell::ConeSpell(SpellInfo *spell_info,BaseCharacter *caster,void (*Effect)(SpellStats *sp_stats),AnimatedEntity *spell_entity)
  :IncrementingSpell(spell_info,caster,Effect,spell_entity)
{
  increment=0;
}
ConeSpell::~ConeSpell()
{
 
}

void ConeSpell::Draw(SDL_Texture *screen)
{

  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(IsCast())
    {
      int chunks=increment/tile_size;
      if( GetSpellStats()->GetDirection()==S_UP )
	{
	  spell_entity->setAnimation(0);
	  for(int i=0;i<chunks;i++)
	    { 
	      spell_entity->DrawFrame(0,(-1-i)*tile_size,(-i-1)*tile_size+tile_size/2,screen);
	      for(int j=-i-1;j<i;j++)
		{
		  spell_entity->DrawFrame(1,(1+j)*tile_size,(-i-1)*tile_size+tile_size/2,screen);
		}
	      spell_entity->DrawFrame(2,(1+i)*tile_size,(-i-1)*tile_size+tile_size/2,screen);
	    }
	}
      else if( GetSpellStats()->GetDirection()==S_DOWN )
	{
	  spell_entity->setAnimation(1);
	  for(int i=0;i<chunks;i++)
	    { 
	      spell_entity->DrawFrame(0,(-1-i)*tile_size,(i-1)*tile_size+tile_size/2,screen);
	      for(int j=-i-1;j<i;j++)
		{
		  spell_entity->DrawFrame(1,(1+j)*tile_size,(i-1)*tile_size+tile_size/2,screen);
		}
	      spell_entity->DrawFrame(2,(1+i)*tile_size,(i-1)*tile_size+tile_size/2,screen);
	    }
	}
      else if(GetSpellStats()->GetDirection()==S_LEFT )
	{
	  spell_entity->setAnimation(3);
	  for(int i=0;i<chunks;i++)
	    { 
	      //aoe_tiles.push_back(pair<int,int>((-i),(i)));
	      spell_entity->DrawFrame(2,(-i)*tile_size,(i)*tile_size+tile_size/2,screen);
	      for(int j=-i-1;j<i;j++)
		{
		  //aoe_tiles.push_back(pair<int,int>((-i),(-1-j)));
		  spell_entity->DrawFrame(1,(-i)*tile_size,(-j-2)*tile_size+tile_size/2,screen);
		}
	      //	      aoe_tiles.push_back(pair<int,int>((-i),(-i-1)));
	      spell_entity->DrawFrame(0,(-i)*tile_size,(-i-2)*tile_size+tile_size/2,screen);
	    }
	}
      else if(GetSpellStats()->GetDirection()==S_RIGHT )
	{
	  spell_entity->setAnimation(2);
	  for(int i=0;i<chunks;i++)
	    {
	       spell_entity->DrawFrame(2,(i)*tile_size,(i)*tile_size+tile_size/2,screen);
	      //  aoe_tiles.push_back(pair<int,int>((i),(i+1)));
	      for(int j=-i-1;j<i;j++)
		{
		  //  aoe_tiles.push_back(pair<int,int>((i),(1+j)));
		  spell_entity->DrawFrame(1,(i)*tile_size,(-j-2)*tile_size+tile_size/2,screen);
		}
	      // aoe_tiles.push_back(pair<int,int>((i),(-i-1)));
	       spell_entity->DrawFrame(0,(i)*tile_size,(-i-2)*tile_size+tile_size/2,screen);
	    }
	}
    }
}

void ConeSpell::OnCast()
{
  spell_entity->setAnimation(0);
  spell_entity->setPosition(sp_stats->GetTarget().first,sp_stats->GetTarget().second+spell_entity->getPosition().h/2);
}


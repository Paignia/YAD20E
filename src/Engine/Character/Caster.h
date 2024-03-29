#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <utility>
using std::unordered_map;
using std::multiset;
using std::set;
using std::string;
using std::vector;
using std::pair;
#include "BasicCharacter.h"
#include "Spell.h"
#include "EOTSpell.h"
#include "Stats.h"


#ifndef __CASTER_H
#define __CASTER_H

static int std_spells_tbl[6][10]
{
  {3,2,0,0,0,0,0,0,0,0} //1
  ,{3,3,0,0,0,0,0,0,0,0}//2
  ,{3,3,2,0,0,0,0,0,0,0}//3
  ,{3,4,3,0,0,0,0,0,0,0}//4
  ,{3,4,3,2,0,0,0,0,0,0}//5
  ,{3,4,4,3,0,0,0,0,0,0}//6	      
};

static int std_ranks_tbl[8] {1,1,1,1,1,1,1,1};

class Caster:public BaseCharacter
{
 private:
  CasterStats *casterstats;

 protected:
  unordered_map<string,Spell*> Spells;
  int num_prepared;
  multiset<string> Prepared;
  Spell *the_spell;
  vector<EOTSpell*> eotspells;
  
 public:
  Caster(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats);//use std_spells_tbl
  Caster(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,CasterStats *casterstats);
  virtual ~Caster();
  //Preparing,casting and Learning might be kinda different for each caster class
  virtual bool Prepare(string spellName);
  virtual bool CastSpell(string spellName,pair<int,int> target);
  virtual bool LearnSpell(Spell *the_spell);
  bool Forget(string spellName);
  void SetCastAnimation(pair<int,int> pos);
  //
  virtual bool Active();
  virtual void Update(float t);
  virtual void Draw(SDL_Texture *screen);
  void HandleActiveSpells();
  //
  void AddEOTSpell(EOTSpell *eotspell);
  //
  Spell* GetSpell();
  Spell* GetSpell(string spellName);
  void   SetSpell(Spell *spell);
  vector<EOTSpell*>& GetEotSpells();
  unsigned int GetNumPreparedSpells();
  //
  void OnTurnStart();
  //
  multiset<Spell*> GetPreparedSpells();
  set<Spell*> GetKnownSpells();
  //
  void SetCasterStats(CasterStats *casterstats);
  CasterStats* GetCasterStats();
  //
  int getNumSlots(int spell_level);
};

#endif

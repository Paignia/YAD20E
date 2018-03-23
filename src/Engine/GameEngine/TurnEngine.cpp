#include "TurnEngine.h"
#include "KnowledgePool.h"
TurnEngine::TurnEngine(Camera *camera):camera(camera)
{
  it= KnowledgePool::Instance()->getCharacters().begin();
  for(it; it!=KnowledgePool::Instance()->getCharacters().end(); ++it)
    {
      turn_order.push_back(it->second->getID());
    }
  the_turn=NextTurn();
}


TurnEngine::~TurnEngine()
{
  if(the_turn)
    delete the_turn;
}
void TurnEngine::Update(float time)
{
  if(the_turn!=NULL)
    {
      the_turn->Update(time);
      if(the_turn->Turn_Done() && turn_order.size() >=0)
	{
	  delete the_turn;
	  the_turn=NextTurn();
	  if(!the_turn)
	    return;
	}
    }
}


void TurnEngine::Handle_Events(SDL_Event *event)
{
  //TURN ENGINE SPECIFIC EVENTS OR CHARACTER EVENTS NOT IN THE TURN CLASS
  if(the_turn!=NULL)
    the_turn->Handle_Events(event);


}

Turn* TurnEngine::GetTurn()
{
  return this->the_turn;
}

Turn* TurnEngine::NextTurn()
{
  //GET NEW CHARACTER AND HIS CAMERA;
  Turn *new_turn=NULL;
  if(turn_order.size()>0)
    {    cout<<"Front of queue:"<<turn_order.front()<<endl;
      std::unordered_map<unsigned int,AIEntity*>::iterator ait=KnowledgePool::Instance()->getAI().begin();


      while(KnowledgePool::Instance()->getCharacter(turn_order.front())->getGeneralStats()->getHp()<=0)
	{    
	      cout<<"removing"<<turn_order.front()<<endl;
	      MapIndex::Instance()->getMap()->Set(KnowledgePool::Instance()->getCharacter(turn_order.front())->GetBaseEntity()->getPosition().x/MapIndex::Instance()->getMap()->getTileSize(),
						  KnowledgePool::Instance()->getCharacter(turn_order.front())->GetBaseEntity()->getPosition().y/MapIndex::Instance()->getMap()->getTileSize(),
						  0,LCOLISION);
	      turn_order.pop_front();
	  
	}
      if(turn_order.size()<1)
	return NULL;
      
      if(KnowledgePool::Instance()->getAI().find(turn_order.front())!=KnowledgePool::Instance()->getAI().end())
	{
	  new_turn=new Turn( KnowledgePool::Instance()->getCharacter(turn_order.front()),camera,KnowledgePool::Instance()->getAI().find(turn_order.front())->second);
	}
      else
	{
	  //No-AI
	  new_turn=new Turn( KnowledgePool::Instance()->getCharacter(turn_order.front()),camera,NULL);
	  MapIndex::Instance()->ComputeVision(KnowledgePool::Instance()->getCharacter(turn_order.front())->getPosition());
	}
      
      turn_order.push_back(turn_order.front());
      turn_order.pop_front();
    }
  
  return new_turn;
}


Camera* TurnEngine::GetCamera()
{
  return this->camera;
}

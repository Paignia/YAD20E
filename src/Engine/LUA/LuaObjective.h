#include "Objective.h"
#include <lua.hpp>


#ifndef LUA_OBJECTIVE_H
#define LUA_OBJECTIVE_H

class LuaObjective: public Objective
{
private:
	string lua_func;
	lua_State *l;
public:
	LuaObjective(string name,string lua_func, lua_State *l);
	virtual bool success();
	bool magic();
};


#endif
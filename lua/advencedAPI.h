#ifndef ADVENCEDAPI_H
#define ADVENCEDAPI_H

//+========================================================================+
//|Implementacje zaawansowanych funkcji api lua zadeklarowanych w lua/api.h|
//+========================================================================+

namespace gameApi
{
    int api_SHset(lua_State * L)
    {
        if(lua_gettop(L) != 1)
            return 1;

        statek.shield = lua_tointeger(L, 1);
        lua_pushinteger(L, 1);
        return 1;
    }
    int api_HPset(lua_State * L)
    {
        if(lua_gettop(L) != 1)
            return 1;

        statek.HP = lua_tointeger(L, 1);
        lua_pushinteger(L, 1);
        return 1;
    }

    int api_SHgetMax(lua_State * L)
    {
        if(lua_gettop(L) != 0)
            return 1;

        lua_pushinteger(L, statek.shieldMax);
        return 1;
    }
    int api_HPgetMax(lua_State * L)
    {
        if(lua_gettop(L) != 0)
            return 1;

        lua_pushinteger(L, statek.maxHP);
        return 1;
    }
}

#endif

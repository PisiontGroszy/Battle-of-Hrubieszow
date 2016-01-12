#ifndef API_H_INCLUDED
#define API_H_INCLUDED

namespace api
{
    int api_read(lua_State * L)
    {
        if(lua_gettop(L) != 1)
            return 1;

        luaVirtualMachine * LVM = (luaVirtualMachine*) lua_tointeger(L, 1);
        LVM -> reguiresData(true);
        for(;;)
        {
            if(!(LVM -> reguiresData()))
            {
                lua_pushstring(L, LVM -> input.c_str());
                break;
            }
        }
        return 1;
    }

    int api_flush(lua_State * L)
    {
        if(lua_gettop(L) < 1)
            return 1;

        luaVirtualMachine * LVM = (luaVirtualMachine*) lua_tointeger(L, 1);
        LVM -> sentData(true);

        return 1;
    }

    int api_write(lua_State * L)
    {
        if(lua_gettop(L) != 2 and lua_gettop(L) != 3)
            return 1;

        luaVirtualMachine * LVM = (luaVirtualMachine*) lua_tointeger(L, 1);

        LVM -> output += lua_tostring(L, 2);
        LVM -> output += '\n';
        LVM -> outColor = (lua_gettop(L) == 2 and lua_tointeger(L, 3) == 0) ? sf::Color(40, 40, 255) : sf::Color(240, 20, 20);

        return 1;
    }

    int api_writeln(lua_State * L)
    {
        if(lua_gettop(L) != 2 and lua_gettop(L) != 3)
            return 1;

        luaVirtualMachine * LVM = (luaVirtualMachine*) lua_tointeger(L, 1);

        LVM -> output += lua_tostring(L, 2);
        LVM -> output += '\n';
        LVM -> outColor = (lua_gettop(L) == 2 and lua_tointeger(L, 3) == 0) ? sf::Color(40, 40, 255) : sf::Color(240, 20, 20);

        api_flush(L);

        return 1;
    }

    int api_sleep(lua_State * L)
    {
        int milisec = 0;
        struct timespec req = {0};
        time_t sec;

        milisec=luaL_optint(L, 1, 0); // obtain parameter

        if (milisec == 0)
           return 0;

        sec=(int)(milisec / 1000);

        milisec = milisec - (sec * 1000);
        req.tv_sec = sec;
        req.tv_nsec = milisec * 1000000L;

        while(nanosleep(&req, &req) == -1)
             continue;

        return 1;
    }

    int api_random(lua_State * L)
    {
        if(lua_gettop(L) != 2)
            return 1;

        int _from = lua_tointeger(L, 1);
        int _to = lua_tointeger(L, 2);

        lua_pushinteger(L, (rand() % (_to - _from)) + _from);

        return 1;
    }
}

//+=============================================================================================+
//|Deklaracje funkcji zaimplementowanych dalej w kodzie ze względu na zależności między klasami.|
//+=============================================================================================+
namespace gameApi
{
    int api_SHset(lua_State * L);
    int api_HPset(lua_State * L);

    int api_SHgetMax(lua_State * L);
    int api_HPgetMax(lua_State * L);
}
#endif // API_H_INCLUDED

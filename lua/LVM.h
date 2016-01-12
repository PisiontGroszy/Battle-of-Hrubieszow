#ifndef LVM_H_INCLUDED
#define LVM_H_INCLUDED

extern "C" {
    #include "lua5.2/lua.h"
    #include "lua5.2/lualib.h"
    #include "lua5.2/lauxlib.h"
}

struct ColorAndText
{
    std::string text;
    sf::Color color;
};

class luaVirtualMachine
{
private:
    sf::Thread luaScript;
    lua_State * state;
    char * _file;

    void execute();

    bool ready;
    bool running;

    std::atomic<bool> _reguiresData;
    std::atomic<bool> _sentData;
public:
    sf::Color outColor;
    std::string output;
    std::string input;

    luaVirtualMachine();
    luaVirtualMachine(const char * file);
    ~luaVirtualMachine();

    bool open(const char * file);
    bool close();
    bool launch();

    bool isRunning();

    bool reguiresData();
    void reguiresData(bool opt);

    bool sentData();
    void sentData(bool opt);

    void putstring(std::string c);
    ColorAndText getstring();

    bool registerFunc(const char * name, void* funcPointer);
};

void luaVirtualMachine::execute()
{
    lua_pushinteger(state, (uint64_t) this);
    lua_setglobal(state, "ID");

    lua_pushinteger(state, -1);
    lua_setglobal(state, "STATE_ERR");

    lua_pushinteger(state, 0);
    lua_setglobal(state, "STATE_OK");

    luaL_dofile(state, _file);
    running = false;
}

luaVirtualMachine::luaVirtualMachine() : luaScript(&luaVirtualMachine::execute, this)
{
    ready = false;
    running = false;
    sentData(false);
    reguiresData(false);
}
luaVirtualMachine::luaVirtualMachine(const char * file) : luaScript(&luaVirtualMachine::execute, this)
{
    ready = false;
    open(file);
    running = false;
    sentData(false);
    reguiresData(false);
}
luaVirtualMachine::~luaVirtualMachine()
{
    close();
}

bool luaVirtualMachine::open(const char * file)
{
    if(ready)
        return false;

    state = luaL_newstate();
    luaL_openlibs(state);

    _file = new char[strlen(file) + 1];
    strcpy(_file, file);

    ready = true;
    return true;
}
bool luaVirtualMachine::close()
{
    if(!ready)
        return false;

    lua_close(state);
    luaScript.terminate();
    ready = false;
    delete _file;
    return true;
}
bool luaVirtualMachine::launch()
{
    if(!ready)
        return false;

    running = true;
    luaScript.launch();
    return true;
}

bool luaVirtualMachine::isRunning()
{
    return running;
}

bool luaVirtualMachine::reguiresData()
{
    return _reguiresData;
}
void luaVirtualMachine::reguiresData(bool opt)
{
    _reguiresData = opt;
}

bool luaVirtualMachine::sentData()
{
    return _sentData;
}
void luaVirtualMachine::sentData(bool opt)
{
    _sentData = opt;
}

void luaVirtualMachine::putstring(std::string s)
{
    input = s;
    reguiresData(false);
}
ColorAndText luaVirtualMachine::getstring()
{
    sentData(false);
    ColorAndText tmp;
    tmp.text = output;
    tmp.color = outColor;

    output.clear();

    return tmp;
}

bool luaVirtualMachine::registerFunc(const char * name, void* funcPointer)
{
    if(!ready or running)
        return false;

    lua_register(state, name, (lua_CFunction) funcPointer);
    return true;
}
#endif // LVM_H_INCLUDED

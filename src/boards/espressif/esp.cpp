#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>
#include "lua/lua.hpp"

static int restart(lua_State *L)
{
    ESP.restart();
    return 0;
}

static int deepSleep(lua_State *L)
{
    uint32_t t = luaL_checkinteger(L, 1);
    ESP.deepSleep(t);
    return 0;
}

static const struct luaL_Reg esp_lib[] = {
    {"restart", restart},
    {"deepSleep", deepSleep},
    {NULL, NULL}
};

int luaopen_esp(lua_State *L)
{
    luaL_newlib(L, esp_lib);
    return 1;
}

#endif
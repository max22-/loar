#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>
#include "lua/lua.hpp"

static int restart(lua_State *L)
{
    ESP.restart();
    return 0;
}

static const struct luaL_Reg esp_lib[] = {
    {"restart", restart},
    {NULL, NULL}
};

int luaopen_esp(lua_State *L)
{
    luaL_newlib(L, esp_lib);
    return 1;
}

#endif
#include "loar_sd.h"
#ifdef LOAR_USE_SD

#include <Arduino.h>
#ifdef ARDUINO_ARCH_ESP32
#include <FS.h>
#endif
#include <SD.h>
#include "lua/lua.hpp"

static int begin(lua_State *L) {
    bool res = SD.begin();
    lua_pushboolean(L, res);
    return 1;
}

static const struct luaL_Reg sd_lib[] = {
    {"begin", begin},
    {NULL, NULL}
};

int luaopen_sd(lua_State *L)
{
    luaL_newlib(L, sd_lib);
    return 1;
}

#endif
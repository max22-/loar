#include "loar_libraries.h"
#include "lua/lua.hpp"
#include "SD/loar_sd.h"

int luaopen_loar_libraries(lua_State *L) {
    luaL_requiref(L, "SD", luaopen_sd, 1);
    lua_pop(L, 1);
    return 1;
}

#include "loar_libraries.h"
#include "lua/lua.hpp"
#include "SD/loar_sd.h"
#include "Keypad/loar_keypad.h"
#include "TFT_eSPI/loar_tft_espi.h"

int luaopen_loar_libraries(lua_State *L) {

    #ifdef LOAR_USE_SD
    luaL_requiref(L, "SD", luaopen_sd, 1);
    lua_pop(L, 1);
    #endif

    #ifdef LOAR_USE_KEYPAD
    luaL_requiref(L, "Keypad", luaopen_keypad, 1);
    lua_pop(L, 1);
    #endif

    #ifdef LOAR_USE_TFT_ESPI
    luaL_requiref(L, "TFT", luaopen_tft_espi, 1);
    lua_pop(L, 1);
    #endif

    
    return 1;
}

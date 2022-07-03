#include "loar_libraries.h"
#include "lua/lua.hpp"
#include "SD/loar_sd.h"
#include "Keypad/loar_keypad.h"
#include "TFT_eSPI/loar_tft_espi.h"
#include "MQTT/loar_mqtt.h"
#include "Serial/loar_serial.h"
#include "SPI/loar_spi.h"

int luaopen_loar_libraries(lua_State *L) {

    #ifdef LOAR_USE_SD
    luaL_requiref(L, "sd", luaopen_sd, 1);
    lua_pop(L, 1);
    #endif

    #ifdef LOAR_USE_KEYPAD
    luaL_requiref(L, "keypad", luaopen_keypad, 1);
    lua_pop(L, 1);
    #endif

    #ifdef LOAR_USE_TFT_ESPI
    luaL_requiref(L, "tft", luaopen_tft_espi, 1);
    lua_pop(L, 1);
    #endif

    #ifdef LOAR_USE_MQTT
    luaL_requiref(L, "mqtt", luaopen_mqtt, 1);
    lua_pop(L, 1);
    #endif

    luaL_requiref(L, "Serial", luaopen_serial, 1);
    lua_pop(L, 1);

    #ifdef LOAR_USE_SPI
    luaL_requiref(L, "spi", luaopen_spi, 1);
    lua_pop(L, 1);
    #endif

    
    return 1;
}

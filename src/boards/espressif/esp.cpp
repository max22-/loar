#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>
#include <time.h>
#include "lua/lua.hpp"
#include "loar.h"

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

static int wakeupCause(lua_State *L)
{
    lua_pushinteger(L, esp_sleep_get_wakeup_cause());
    return 1;
}

static int configTime(lua_State *L)
{
    long gmtOffset_sec = luaL_checkinteger(L, 1);
    int daylightOffset_sec = luaL_checkinteger(L, 2);
    const char *server = luaL_checkstring(L, 3);
    configTime(gmtOffset_sec, daylightOffset_sec, server);
    return 0;
}

static const struct luaL_Reg esp_lib[] = {
    {"restart", restart},
    {"deepSleep", deepSleep},
    {"wakeupCause", wakeupCause},
    {"configTime", configTime},
    {NULL, NULL}
};

int luaopen_esp(lua_State *L)
{
    luaL_newlib(L, esp_lib);
    
    /* Wake-up causes */
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_UNDEFINED);    //!< In case of deep sleep, reset was not caused by exit from deep sleep
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_ALL);          //!< Not a wakeup cause, used to disable all wakeup sources with esp_sleep_disable_wakeup_source
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_EXT0);         //!< Wakeup caused by external signal using RTC_IO
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_EXT1);         //!< Wakeup caused by external signal using RTC_CNTL
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_TIMER);        //!< Wakeup caused by timer
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_TOUCHPAD);     //!< Wakeup caused by touchpad
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_ULP);          //!< Wakeup caused by ULP program
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_GPIO);         //!< Wakeup caused by GPIO (light sleep only)
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_UART);         //!< Wakeup caused by UART (light sleep only)
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_WIFI);              //!< Wakeup caused by WIFI (light sleep only)
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_COCPU);             //!< Wakeup caused by COCPU int
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG);   //!< Wakeup caused by COCPU crash
    LUA_REGISTER_CONSTANT(ESP_SLEEP_WAKEUP_BT); 
    return 1;
}

#endif
#include "loar_keypad.h"
#ifdef LOAR_USE_KEYPAD
#include "lua/lua.hpp"
#include <Keypad.h>

#warning remove
#include <Arduino.h>
#include "loar_user_setup.h"

static Keypad *keypad = nullptr;
static char *keymap = nullptr;
static uint8_t *row_pins = nullptr;
static uint8_t *col_pins = nullptr;

static int begin(lua_State *L)
{
    if(keypad != nullptr)
        return luaL_error(L, "Keypad already initialized");
    const char *keymap_from_lua = luaL_checkstring(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);  /* row pins */
    luaL_checktype(L, 3, LUA_TTABLE);  /* column pins */

    size_t keymap_keys = strlen(keymap_from_lua);
    lua_Integer rows = luaL_len(L, 2);
    lua_Integer columns = luaL_len(L, 3);
    if(keymap_keys != rows * columns)
        return luaL_error(L, "incompatible keymap and row/col lengths");

    keymap = (char*)loar_malloc(keymap_keys);
    if(!keymap) return luaL_error(L, "Not enough memory");
    strncpy(keymap, keymap_from_lua, keymap_keys);

    row_pins = (uint8_t*)loar_malloc(rows);
    if(!row_pins) {
        loar_free(keymap);
        return luaL_error(L, "Not enough memory");
    }
    col_pins = (uint8_t*)loar_malloc(columns);
    if(!col_pins) {
        loar_free(keymap);
        loar_free(row_pins);
        return luaL_error(L, "Not enough memory");
    }
    for(int j = 0; j < rows; j++) {
        lua_geti(L, 2, j+1);
        row_pins[j] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }
    for(int i = 0; i < columns; i++) {
        lua_geti(L, 3, i+1);
        col_pins[i] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    keypad = new Keypad(keymap, row_pins, col_pins, rows, columns);
    if(!keypad) {
        loar_free(keymap);
        loar_free(row_pins);
        loar_free(col_pins);
        return luaL_error(L, "Failed to instantiate Keypad");
    }
    return 0;
}

int getKey(lua_State *L)
{
    char buf[2] = {0};
    if(keypad == nullptr) return luaL_error(L, "Keypad not initialized");
    buf[0] = keypad->getKey();
    lua_pushstring(L, buf);
    return 1;
}

static const struct luaL_Reg keypad_lib[] = {
    {"begin", begin},
    {"getKey", getKey},
    {NULL, NULL}
};

int luaopen_keypad(lua_State *L)
{
    luaL_newlib(L, keypad_lib);
    return 1;
}

#endif
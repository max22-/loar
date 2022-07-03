#include "loar_user_setup.h"

#ifdef LOAR_USE_KEYPAD
struct lua_State;
int luaopen_keypad(lua_State *);
#endif
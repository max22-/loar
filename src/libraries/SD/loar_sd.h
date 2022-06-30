#include "loar_user_setup.h"

#ifdef LOAR_USE_SD
struct lua_State;
int luaopen_sd(lua_State *);
#endif
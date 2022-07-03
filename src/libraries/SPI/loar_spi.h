#include "loar_user_setup.h"

#ifdef LOAR_USE_SPI
struct lua_State;
int luaopen_spi(lua_State *);
#endif
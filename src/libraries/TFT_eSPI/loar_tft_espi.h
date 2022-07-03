#include "loar_user_setup.h"

#ifdef LOAR_USE_TFT_ESPI
struct lua_State;
int luaopen_tft_espi(lua_State *);
#endif
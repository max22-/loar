#include "loar_user_setup.h"

#ifdef LOAR_USE_MQTT
struct lua_State;
int luaopen_mqtt(lua_State *);
#endif
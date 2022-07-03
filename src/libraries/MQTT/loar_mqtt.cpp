#include "loar_mqtt.h"
#ifdef LOAR_USE_MQTT
#include "loar.h"
#include "lua/lua.hpp"
#include <WiFi.h>
#include <PubSubClient.h>

static WiFiClient espClient;
static PubSubClient client(espClient);

static int setServer(lua_State *L)
{
    const char *host = luaL_checkstring(L, 1);
    uint16_t port = luaL_checkinteger(L, 2);
    client.setServer(host, port);
    return 0;
}

static int connect(lua_State *L)
{
    const char *id = luaL_checkstring(L, 1);
    lua_pushboolean(L, client.connect(id));
    return 1;
}

static int connected(lua_State *L)
{
    lua_pushboolean(L, client.connected());
    return 1;
}

static int publish(lua_State *L)
{
    const char *topic = luaL_checkstring(L, 1);
    const char *payload = luaL_checkstring(L, 2);
    if(lua_gettop(L) == 3) {
        bool retained = lua_toboolean(L, 3);
        client.publish(topic, payload, retained);
    } else client.publish(topic, payload);
    return 0;
}

static const struct luaL_Reg mqtt_lib[] = {
    {"setServer", setServer},
    {"connect", connect},
    {"connected", connected},
    {"publish", publish},
    {NULL, NULL}
};

int luaopen_mqtt(lua_State *L)
{
    luaL_newlib(L, mqtt_lib);
    return 1;
}

#endif
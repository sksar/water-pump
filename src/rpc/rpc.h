/**
 * RPC Functions
 */

#include "mgos_rpc.h"



//---------------------------------------------------------------------------
// Start
//---------------------------------------------------------------------------

static void rpc_start(
    struct mg_rpc_request_info *ri, void *cb_arg,
    struct mg_rpc_frame_info *fi,
    struct mg_str a)
{
    int minutes = 0;
    if (json_scanf(a.p, a.len, ri->args_fmt, &minutes) != 1) {
        mg_rpc_send_errorf(ri, 400, "minutes is required");
        return;
    }
    pump_start(minutes);
    mg_rpc_send_responsef(ri, "OK");
}



//---------------------------------------------------------------------------
// Stop
//---------------------------------------------------------------------------

static void rpc_stop(
    struct mg_rpc_request_info *ri, void *cb_arg,
    struct mg_rpc_frame_info *fi,
    struct mg_str a)
{
    pump_stop();
    mg_rpc_send_responsef(ri, "OK");
}


//---------------------------------------------------------------------------
// State
//---------------------------------------------------------------------------

static void rpc_state(
    struct mg_rpc_request_info *ri, void *cb_arg,
    struct mg_rpc_frame_info *fi,
    struct mg_str a)
{
    mg_rpc_send_responsef(ri, "{ ttl: %d }", ttl);
}



//---------------------------------------------------------------------------
// Init
//---------------------------------------------------------------------------

void init_rpc() {
    mg_rpc_add_handler(mgos_rpc_get_global(), "Start", "{minutes: %d}", rpc_start, NULL);
    mg_rpc_add_handler(mgos_rpc_get_global(), "Stop", "{}", rpc_stop, NULL);
    mg_rpc_add_handler(mgos_rpc_get_global(), "State", "{}", rpc_state, NULL);
}
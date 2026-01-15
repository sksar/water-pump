#include "mgos.h"


//----------------------------------------------------------------
// Modules
//----------------------------------------------------------------

#include "notification/notify.h"
#include "notification/led.h"

#include "core/relays.h"
#include "core/pump.h"
#include "core/cron.h"

#include "rpc/rpc.h"

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------

enum mgos_app_init_result mgos_app_init(void){

	init_relays();
	init_pump();
	init_cron();

	init_rpc();
	init_led();

	// At boot stop pump
	pump_stop();

	return MGOS_APP_INIT_SUCCESS;
}

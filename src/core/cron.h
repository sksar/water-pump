/*
 * Cron Jobs
 */

#include "mgos_cron.h"

//----------------------------------------------------------------
// Jobs
//----------------------------------------------------------------

void cron_stop() {
    if (pump_running()) return;
    pump_stop();
}

void cron_start() {
    if (pump_running()) return;
    if (!mgos_sys_config_get_app_cron_start_enable()) return;
    pump_start(5);
}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------


void init_cron() {
    // Stop Cron
    mgos_cron_add("0 */15 * * * *", cron_stop, NULL);

    // Start Cron
    mgos_cron_add(mgos_sys_config_get_app_cron_start_expr(), cron_start, NULL);
}
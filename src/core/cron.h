/*
 * Cron Jobs
 */

#include "mgos_cron.h"

//----------------------------------------------------------------
// Jobs
//----------------------------------------------------------------

void cron_stop() {
    LOG(LL_INFO, ("Executing cron stop"));
    if (pump_running()) return;
    pump_stop();
}

void cron_start() {
    LOG(LL_INFO, ("Executing cron start"));
    if (pump_running()) return;
    if (!mgos_sys_config_get_app_cron_start_enable()) return;
    pump_start(mgos_sys_config_get_app_cron_start_duration());
}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------


void init_cron() {
    // Auto Stop
    mgos_cron_add("0 */15 * * * *", cron_stop, NULL);

    // Auto Start
    mgos_cron_add(mgos_sys_config_get_app_cron_start_expr(), cron_start, NULL);
}
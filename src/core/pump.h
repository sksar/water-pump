/*
 * Pump Core (Software Layer)
 */

//----------------------------------------------------------------
// State
//----------------------------------------------------------------

int ttl = 0;

bool pump_running() {
	return ttl > 0;
}

//----------------------------------------------------------------
// API
//----------------------------------------------------------------

void pump_start(int minutes) {
    if (pump_running()) return;
    if (minutes < 1) minutes = 1;
    if (minutes > 60) minutes = 60;
    ttl = minutes * 60;
    push_start_button();
    led_on();
    notify("🟢 Pump started for %d minutes", minutes);
	LOG(LL_INFO, ("Pump started for %d minutes", minutes));
}

void pump_stop() {
    ttl = 0;
    push_stop_button();
    mgos_set_timer(5000, 0, push_stop_button, NULL);
    led_off();
	LOG(LL_INFO, ("Pump stopped"));
}

void pump_stop_and_notify() {
    pump_stop();
    notify("🔴 Pump Stopped");
}


//----------------------------------------------------------------
// Timer
//----------------------------------------------------------------

void pump_timer() {
	if (!pump_running()) return;
    if (--ttl == 0) pump_stop_and_notify();
}

//----------------------------------------------------------------
// Init
//----------------------------------------------------------------

void init_pump() {
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, pump_timer, NULL);
}


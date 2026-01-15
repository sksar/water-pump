/**
 * Relay Controls (Hardware Layer)
 */


// Pins
#define START   5   // GPIO 5 => d1
#define STOP    4   // GPIO 4 => d2

// Mode
#define ON  0
#define OFF 1


// Init -------------------------------------------------------------

void init_relays() {
    // Setup
    mgos_gpio_set_mode(START, MGOS_GPIO_MODE_OUTPUT);
    mgos_gpio_set_mode(STOP, MGOS_GPIO_MODE_OUTPUT);

    // Defaults
    mgos_gpio_write(START, OFF);
    mgos_gpio_write(STOP, OFF);
}

// Stop Button ------------------------------------------------------

bool stop_button_active = false;

void release_stop_button() {
	mgos_gpio_write(STOP, OFF);
	stop_button_active = false;
}

void push_stop_button() {
	if (stop_button_active) return;
	stop_button_active = true;
	mgos_gpio_write(STOP, ON);
	mgos_set_timer(2000, 0, release_stop_button, NULL);
}

// Start Button -----------------------------------------------------

bool start_button_active = false;

void release_start_button() {
	mgos_gpio_write(START, OFF);
	start_button_active = false;
}

void push_start_button() {
	if (stop_button_active) return;
	if (start_button_active) return;
	start_button_active = true;
	mgos_gpio_write(START, ON);
	mgos_set_timer(2000, 0, release_start_button, NULL);
}

/**
 * Led Notify
 */

int led_pin = -1;

void init_led() {
    led_pin = mgos_sys_config_get_board_led1_pin();
    mgos_gpio_set_mode(led_pin, MGOS_GPIO_MODE_OUTPUT);
    mgos_gpio_write(led_pin, 1);
}

void led_on() {
    mgos_gpio_blink(led_pin, 500, 500);
}

void led_off() {
    mgos_gpio_blink(led_pin, 0, 0);
    mgos_gpio_write(led_pin, 1);
}
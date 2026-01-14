/*
 *  Notification Logic
 */

#include <stdio.h>
#include <stdarg.h>
#include "mgos_telegram.h"



void send_telegram_message(const char *msg) {
    int32_t chat_id = mgos_sys_config_get_app_telegram_chat_id();
    LOG(LL_INFO, ("Sending message to chat id: %ld", chat_id));
    mgos_telegram_send_message(chat_id, msg);
}



void notify(const char *fmt, ...) {

    // Format
    char s[1000];
    va_list args;
    va_start(args, fmt);
    vsnprintf(s, sizeof(s), fmt, args);
    va_end(args);

    // Send
    send_telegram_message(s);
    LOG(LL_INFO, ("Notification sent: %s", s));
}
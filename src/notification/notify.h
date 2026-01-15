/*
 *  Notification Logic
 */

#include <stdio.h>
#include <stdarg.h>
#include "mgos_telegram.h"

//----------------------------------------------------------------
// Telegram Send Message
//----------------------------------------------------------------

void send_telegram_message(const char *msg) {
    const char *chat_id = mgos_sys_config_get_app_telegram_chat_id();
    LOG(LL_INFO, ("Sending message to chat id: %s", chat_id));
    mgos_telegram_send_message(atoll(chat_id), msg);
}

//----------------------------------------------------------------
// API
//----------------------------------------------------------------

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
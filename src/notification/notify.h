/*
 *  Notification Logic
 */

#include <stdio.h>
#include <stdarg.h>

void notify(const char *fmt, ...) {

    // Format
    char s[1000];
    va_list args;
    va_start(args, fmt);
    vsnprintf(s, sizeof(s), fmt, args);
    va_end(args);

    // Send
    LOG(LL_INFO, ("Notification sent: %s", s));
}
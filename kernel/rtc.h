/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef RTC_H
#define RTC_H

#include "kernel/types.h"

uint32_t boottime;

void rtc_init();
void rtc_read(struct rtc_time *t);
uint32_t rtc_time_to_timestamp(struct rtc_time *t);

#endif

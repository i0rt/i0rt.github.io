/* apm.h -- Header file for sample APM interface routines
 * Created: Mon Jan  8 11:40:50 1996 by r.faith@ieee.org
 * Revised: Thu Apr  4 21:57:31 1996 by r.faith@ieee.org
 * Copyright 1996 Rickard E. Faith (r.faith@ieee.org)
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * $Id: apm.h,v 1.7 1999/07/05 22:31:11 apenwarr Exp $
 * 
 */
#ifndef _APM_H
#define _APM_H 1

#ifndef __KERNEL_STRICT_NAMES
#define __KERNEL_STRICT_NAMES
#endif

#include <linux/apm_bios.h>
#include <sys/types.h>

#define APM_PROC   "/proc/apm"
#define APM_DEVICE "/dev/apm_bios"

#define APM_DEV  "/proc/devices"
#define APM_NAME "apm_bios"

#ifndef APM_32_BIT_SUPPORT
#define APM_32_BIT_SUPPORT      0x0002
#endif

typedef struct apm_info
{
    const char driver_version[10];
    int apm_version_major;
    int apm_version_minor;
    int apm_flags;
    int ac_line_status;
    int battery_status;
    int battery_flags;
    int battery_percentage;
    int battery_time;
    int using_minutes;
}
apm_info;

/*
 * Encodings for apm_info
 */
#define AC_LINE_STATUS_OFF      (0)
#define AC_LINE_STATUS_ON       (1)
#define AC_LINE_STATUS_BACKUP   (2)
#define AC_LINE_STATUS_UNKNOWN  (0xff)

#define BATTERY_STATUS_HIGH     (0)
#define BATTERY_STATUS_LOW      (1)
#define BATTERY_STATUS_CRITICAL (2)
#define BATTERY_STATUS_CHARGING (3)
#define BATTERY_STATUS_ABSENT   (4)
#define BATTERY_STATUS_UNKNOWN  (0xff)

#define BATTERY_FLAGS_HIGH      (0x1)
#define BATTERY_FLAGS_LOW       (0x2)
#define BATTERY_FLAGS_CRITICAL  (0x4)
#define BATTERY_FLAGS_CHARGING  (0x8)
#define BATTERY_FLAGS_ABSENT    (0x80)

#define BATTERY_PERCENTAGE_UNKNOWN  (-1)

#define BATTERY_TIME_UNKNOWN        (-1)

extern int apm_exists(void);
extern int apm_read(apm_info * i);
extern dev_t apm_dev(void);
extern int apm_open(void);
extern int apm_close(int fd);
extern int apm_get_events(int fd, int timeout, apm_event_t * events, int n);
extern int apm_suspend(int fd);
extern int apm_standby(int fd);
extern int apm_set_ignore(int fd, int mode);
extern const char *apm_error_name( unsigned int err );
extern const char *apm_event_name(apm_event_t event);
extern const char *apm_time(time_t t);
extern const char *apm_delta_time(time_t then, time_t now);
extern const char *apm_time_nosec(time_t t);

#ifdef APM_IOC_REJECT
extern int apm_reject(int fd);
#else
#define apm_reject(fd)   (-EINVAL)
#endif

#endif
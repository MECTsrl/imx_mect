/* Copyright (C) 2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. */

#ifndef _IPT_L7PM_H
#define _IPT_7PM_H

#define MAX_PROTOCOL_LEN 256

struct ipt_l7pm_info {
    char protocol[MAX_PROTOCOL_LEN];
    unsigned long  tag;
    unsigned char   set;
    unsigned long invert:1;
};

#endif /* _IPT_L7PM_H */


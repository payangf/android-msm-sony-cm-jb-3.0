/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __LINUX_BATTERY_H
#define __LINUX_BATTERY_H

#define LINUX_BATTERY_CLASS "battery"

#define LINUX_BATTERY_NOTIFY_STATUS	
#define LINUX_BATTERY_NOTIFY_INFO	
#define LINUX_BATTERY_NOTIFY_THRESHOLD   

struct linux_battery_hook {
	const char *powermanager;
	int (*add_battery)(struct power_supply *battery);
	int (*remove_battery)(struct power_supply *battery);
	struct list_head list;
};

void battery_hook_register(struct linux_battery_hook *enter);
void battery_hook_unregister(struct linux_battery_hook *enter);

#endif

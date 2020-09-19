/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  linux/include/linux/clock_cooling.h
 *
 *  Copyright (C) 2014 Eduardo Valentin <edubezval@gmail.com>
 *
 *  Copyright (C) 2013	Texas Instruments Inc.
 *  Contact:  Eduardo Valentin <eduardo.valentin@ti.com>
 *
 *  Highly based on cpufreq_cooling.c.
 *  Copyright (C) 2012	Samsung Electronics Co., Ltd(http://www.samsung.com)
 *  Copyright (C) 2012  Amit Daniel <amit.kachhap@linaro.org>
 */

#ifndef __CPU_COOLING_H__
#define __CPU_COOLING_H__

#include <linux/of_device.h>
#include <linux/thermal.h>

#ifdef CONFIG_CLOCK_THERMAL
/**
 * clock_cooling_register - function to create clock cooling device.
 * @dev: struct device pointer to the device used as clock cooling device.
 * @clock_name: string containing the clock used as cooling mechanism.
 */
struct thermal_cooling_device *
clock_cooling_register(struct device *dev, const char *clock_name);

/**
 * clock_cooling_unregister - function to remove clock cooling device.
 * @cdev: thermal cooling device pointer.
 */
void clock_cooling_unregister(struct thermal_cooling_device *cdev);

unsigned long clock_cooling_get_level(struct thermal_cooling_device *cdev,
				      unsigned long freq);
#else /* !CONFIG_CLOCK_THERMAL */
static inline struct thermal_cooling_device *
clock_cooling_register(struct device *dev, const char *clock_name)
{
	return NULL;
}
static inline
void clock_cooling_unregister(struct thermal_cooling_device *cdev)
{
}
static inline
unsigned long clock_cooling_get_level(struct thermal_cooling_device *cdev,
				      unsigned long freq)
{
	return THERMAL_CSTATE_INVALID;
}
#endif	/* CONFIG_CLOCK_THERMAL */

#endif /* __CPU_COOLING_H__ */
/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

#include "drm_sun_timer.h"

void
init_timer(struct timer_list *timer)
{
	mutex_init(&timer->lock, NULL, MUTEX_DRIVER, NULL);
}

void
destroy_timer(struct timer_list *timer)
{
	mutex_destroy(&timer->lock);
}

void
setup_timer(struct timer_list *timer, void (*func)(void *), void *arg)
{
	timer->func = func;
	timer->arg = arg;
	timer->expired_time = 0;
}

void
mod_timer(struct timer_list *timer, clock_t expires)
{
	mutex_enter(&timer->lock);
	/*
	 * If timer is already being updated, let previous caller do the work
	 * Note that we must drop timer->lock before the untimeout, as the
	 * callback might call mod_timer and deadlock.  So the guard is
	 * centered around the overloading of the timer->expires element.
	 */
	if (timer->expires == -1) {
		mutex_exit(&timer->lock);
		return;
	}
	timer->expires = -1;
	mutex_exit(&timer->lock);

	(void) untimeout(timer->timer_id);
	timer->expired_time = jiffies + expires;
	timer->timer_id = timeout(timer->func, timer->arg, expires);

	mutex_enter(&timer->lock);
	timer->expires = 0;
	mutex_exit(&timer->lock);
}

void
del_timer(struct timer_list *timer)
{
	(void) untimeout(timer->timer_id);
}

void
test_set_timer(struct timer_list *timer, clock_t expires)
{
	if (time_after(jiffies, timer->expired_time)) {
		timer->expired_time = jiffies + expires;
		timer->timer_id = timeout(timer->func, timer->arg, expires);
	}
}

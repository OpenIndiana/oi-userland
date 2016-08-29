/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
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

#include <sys/sunddi.h>
#include <sys/types.h>

#include "drm_sun_workqueue.h"

int
__queue_work(struct workqueue_struct *wq, struct work_struct *work)
{
	int	ret;

	ASSERT(wq->taskq != NULL);
	ASSERT(work->func != NULL);
	/*
	 * ddi_taskq_dispatch can fail if there aren't enough memory
	 * resources.  In theory, since we are requesting a SLEEP
	 * allocation, it would be very rare to fail
	 */
	if ((ret = ddi_taskq_dispatch(wq->taskq, work->func, work, DDI_SLEEP))
	    == DDI_FAILURE)
		cmn_err(CE_WARN, "queue_work: ddi_taskq_dispatch failure");
	return (ret);
}

void
init_work(struct work_struct *work, void (*func)(void *))
{
	work->func = func;
}

struct workqueue_struct *
create_workqueue(dev_info_t *dip, char *name)
{
	struct workqueue_struct *wq;

	wq = kmem_zalloc(sizeof (struct workqueue_struct), KM_SLEEP);
	wq->taskq = ddi_taskq_create(dip, name, 1, TASKQ_DEFAULTPRI, 0);
	if (wq->taskq == NULL)
		goto fail;
	wq->name = name;

	return wq;

fail :
	kmem_free(wq, sizeof (struct workqueue_struct));
	return (NULL);
}

void
destroy_workqueue(struct workqueue_struct *wq)
{
	if (wq) {
		ddi_taskq_destroy(wq->taskq);
		kmem_free(wq, sizeof (struct workqueue_struct));
	}
}

void
cancel_delayed_work(struct workqueue_struct *wq)
{
	ddi_taskq_wait(wq->taskq);
}
void
flush_workqueue(struct workqueue_struct *wq)
{
	ddi_taskq_wait(wq->taskq);
}

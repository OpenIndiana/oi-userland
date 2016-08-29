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

#include "drmP.h"

void
drm_debug_print(int cmn_err, const char *func, int line, const char *fmt, ...)
{
	va_list ap;
	char format[256];

	(void) snprintf(format, sizeof (format), "[drm:%s:%d] %s",
	    func, line, fmt);

	va_start(ap, fmt);
	vcmn_err(cmn_err, format, ap);
	va_end(ap);
}

void
drm_debug(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vcmn_err(CE_NOTE, fmt, ap);
	va_end(ap);
}

void
drm_error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vcmn_err(CE_WARN, fmt, ap);
	va_end(ap);
}

void
drm_info(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vcmn_err(CE_NOTE, fmt, ap);
	va_end(ap);
}

/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.time.client.swing;

import java.util.Date;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.model.AbstractModel;
import com.oracle.solaris.vp.panels.time.TimeMXBean;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class TimeModel extends AbstractModel<TimePanelDescriptor> {

    private static final long OFFSET_NONE = Long.MAX_VALUE;

    private long offset_ = OFFSET_NONE;

    public TimeModel(TimePanelDescriptor source) {
	super(source);
    }

    //
    // Model methods
    //

    public void load() {
	try {
	    offset_ = getSource().getTimeMXBean().gettime().getTime() -
		System.currentTimeMillis();
	} catch (ObjectException e) {
	    offset_ = 0;
	}
    }

    public void save() throws ActionFailedException,
	ActionUnauthorizedException {

	TimeMXBean bean = getSource().getTimeMXBean();

	try {
	    bean.settime(new Date(System.currentTimeMillis() + offset_));

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);

	} catch (ObjectException e) {
	    throw new ActionFailedException(Finder.getString(
		"time.time.error.syserror"), e);
	}
    }

    public boolean isInitialized() {
	return (offset_ == OFFSET_NONE);
    }

    public void validate() throws ActionFailedException {
	assert (isInitialized());
    }

    //
    // TimeModel methods
    //

    public long getOffset() {
	return offset_;
    }

    public void setOffset(long offset) {
	offset_ = offset;
    }
}

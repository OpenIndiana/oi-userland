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

package com.oracle.solaris.vp.util.swing.time;

import java.util.*;
import com.oracle.solaris.vp.util.swing.GUIUtil;

public class TimeModelUpdater extends TimerTask {
    //
    // Static data
    //

    private static final int _DELAY = 1000;

    //
    // Instance data
    //

    private Timer timer = new Timer("TimeModelUpdater");
    private final List<TimeModel> clocks = new LinkedList<TimeModel>();
    private int delay_;

    //
    // Constructors
    //

    public TimeModelUpdater(int delay, TimeModel... clocks) {
	add(clocks);
	delay_ = delay;
    }

    public TimeModelUpdater(TimeModel... clocks) {
	this(_DELAY, clocks);
    }

    //
    // TimerTask methods
    //

    @Override
    public void run() {
	/*
	 * Drop/coalesce events if we fire too late.
	 */
	if (System.currentTimeMillis() - this.scheduledExecutionTime() > delay_)
	    return;

	/*
	 * This fires on the java.util.Timer provided thread, but we need
	 * to execute on the UI event thread.
	 */
	GUIUtil.invokeAndWait(new Runnable() {
	    public void run() {
		synchronized (clocks) {
		    for (TimeModel clock : clocks) {
			clock.updateTime();
		    }
		}
	    }
	});
    }

    //
    // TimeModelUpdater methods
    //

    public void add(TimeModel... clocks) {
	synchronized (clocks) {
	    for (TimeModel clock : clocks) {
		this.clocks.add(clock);
	    }
	}
    }

    public boolean remove(TimeModel clock) {
	return clocks.remove(clock);
    }

    public void start() {
	timer.scheduleAtFixedRate(this,
	    new Date(((System.currentTimeMillis() / 1000) + 1) * 1000), delay_);
    }
}

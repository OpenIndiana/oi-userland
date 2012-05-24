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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.zconsole.client.text;

import java.util.logging.Logger;
import com.oracle.solaris.rad.zonesbridge.IOMXBean;

public abstract class ZoneIOThread extends Thread {
    //
    // Static data
    //

    protected static int BLOCKSIZE = 1024;

    //
    // Instance data
    //

    private IOMXBean bean;
    private long token;

    //
    // Constructors
    //

    public ZoneIOThread(IOMXBean bean, long token) {
	this.bean = bean;
	this.token = token;
    }

    //
    // ZoneIOThread methods
    //

    /**
     * Called when this {@code Runnable} is stopped.
     *
     * @param	    success
     *		    whether the operation was successful
     */
    public abstract void done(boolean success);

    public IOMXBean getBean() {
	return bean;
    }

    protected Logger getLog() {
	return Logger.getLogger(getClass().getPackage().getName());
    }

    public long getToken() {
	return token;
    }
}

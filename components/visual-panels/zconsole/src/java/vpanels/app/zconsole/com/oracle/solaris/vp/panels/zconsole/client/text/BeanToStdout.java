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

import java.io.IOException;
import java.util.logging.Level;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.zonesbridge.IOMXBean;

public abstract class BeanToStdout extends ZoneIOThread {
    //
    // Constructors
    //

    public BeanToStdout(IOMXBean bean, long token) {
	super(bean, token);
    }

    //
    // Runnable methods
    //

    @Override
    public void run() {
	boolean success = true;
	IOMXBean bean = getBean();
	long token = getToken();

	try {
	    byte[] bytes;
	    while ((bytes = bean.read(token, BLOCKSIZE)) != null) {
		System.out.write(bytes);
		System.out.flush();
	    }
	} catch (ObjectException e) {
	    // Console has been closed

	} catch (IOException e) {
	    success = false;
	    getLog().log(Level.SEVERE, "unable to write to stdout", e);
	}

	done(success);
    }
}

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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common;

import com.oracle.solaris.vp.util.misc.event.*;

public class ConnectionListeners extends EventListeners<ConnectionListener>
    implements ConnectionListener {

    //
    // Static data
    //

    private static final EventDispatcher<ConnectionEvent, ConnectionListener>
	changeDispatcher =
	new EventDispatcher<ConnectionEvent, ConnectionListener>() {
	    @Override
	    public void dispatch(ConnectionListener listener,
		ConnectionEvent event) {
		listener.connectionChanged(event);
	    }
	};

    private static final EventDispatcher<ConnectionEvent, ConnectionListener>
	failDispatcher =
	new EventDispatcher<ConnectionEvent, ConnectionListener>() {
	    @Override
	    public void dispatch(ConnectionListener listener,
		ConnectionEvent event) {
		listener.connectionFailed(event);
	    }
	};

    //
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent e) {
	dispatch(changeDispatcher, e);
    }

    @Override
    public void connectionFailed(ConnectionEvent e) {
	dispatch(failDispatcher, e);
    }
}

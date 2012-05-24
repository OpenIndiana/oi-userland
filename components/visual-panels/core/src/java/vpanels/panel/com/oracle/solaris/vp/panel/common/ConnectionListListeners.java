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

/**
 * The {@code ConnectionListListeners} class encapsulates event listener
 * management.
 */
public class ConnectionListListeners extends
        EventListeners<ConnectionListListener>
        implements ConnectionListListener {

    //
    // Static data
    //

    private static final
	    EventDispatcher<ConnectionEvent, ConnectionListListener>
	addDispatcher =
	    new EventDispatcher<ConnectionEvent, ConnectionListListener>() {
		@Override
		public void dispatch(ConnectionListListener listener,
			ConnectionEvent event) {
		    listener.connectionAdded(event);
		}
	    };

    private static final
            EventDispatcher<ConnectionEvent, ConnectionListListener>
	removeDispatcher =
	    new EventDispatcher<ConnectionEvent, ConnectionListListener>() {
		@Override
		public void dispatch(ConnectionListListener listener,
			ConnectionEvent event) {
		    listener.connectionRemoved(event);
		}
	    };

    private static final
	    EventDispatcher<ConnectionEvent, ConnectionListListener>
	selectedDispatcher =
	    new EventDispatcher<ConnectionEvent, ConnectionListListener>() {
		@Override
		public void dispatch(ConnectionListListener listener,
			ConnectionEvent event) {
		    listener.connectionSelected(event);
		}
	    };

    //
    // ConnectionListListener methods
    //

    @Override
    public void connectionAdded(ConnectionEvent e) {
	dispatch(addDispatcher, e);
    }

    @Override
    public void connectionRemoved(ConnectionEvent e) {
	dispatch(removeDispatcher, e);
    }

    @Override
    public void connectionSelected(ConnectionEvent e) {
	dispatch(selectedDispatcher, e);
    }
}

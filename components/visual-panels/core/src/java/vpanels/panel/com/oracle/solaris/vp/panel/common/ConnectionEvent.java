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

import java.util.EventObject;

@SuppressWarnings({"serial"})
public class ConnectionEvent extends EventObject {
    //
    // Instance data
    //

    private ConnectionInfo newInfo;
    private ConnectionInfo oldInfo;

    //
    // Constructors
    //

    /**
     * Constructs a {@code ConnectionEvent}.
     *
     * @param	    source
     *		    the source of this event
     *
     * @param	    newInfo
     *		    the new {@link ConnectionInfo}
     *
     * @param	    oldInfo
     *		    the old {@link ConnectionInfo}
     */
    public ConnectionEvent(Object source, ConnectionInfo newInfo,
	ConnectionInfo oldInfo) {

	super(source);
	this.newInfo = newInfo;
	this.oldInfo = oldInfo;
    }

    /**
     * Constructs a {@code ConnectionEvent}.
     *
     * @param	    source
     *		    the source of this event
     *
     * @param	    info
     *		    the current {@link ConnectionInfo}
     */
    public ConnectionEvent(Object source, ConnectionInfo info) {
	this(source, info, null);
    }

    //
    // ConnectionEvent methods
    //

    /**
     * Gets the primary {@link ConnectionInfo} involved in this event.
     */
    public ConnectionInfo getConnectionInfo() {
	return newInfo;
    }

    /**
     * Gets the old {@link ConnectionInfo}, if any, involved in this event.
     */
    public ConnectionInfo getOldConnectionInfo() {
	return oldInfo;
    }
}

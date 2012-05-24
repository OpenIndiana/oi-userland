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

package com.oracle.solaris.vp.panel.common.control;

/**
 * The {@code UITransitionManager} class manages all {@link NavigationListener}s
 * that handle the UI transitions that occur as a result of navigation.
 * Presumably only one such {@link NavigationListener} should handle any given
 * transition -- this class allows the instigators of the navigation to specify
 * which.
 */
public class UITransitionManager implements NavigationListener {
    //
    // Instance data
    //

    private NavigationListener handler;

    //
    // Constructors
    //

    public UITransitionManager() {
    }

    public UITransitionManager(NavigationListener handler) {
	setHandler(handler);
    }

    //
    // NavigationListener methods
    //

    /**
     * Delegates the event to the handler, if non-{@code null}.
     */
    @Override
    public void navigationStarted(NavigationStartEvent event) {
	if (handler != null) {
	    handler.navigationStarted(event);
	}
    }

    /**
     * Delegates the event to the handler, if non-{@code null}.
     */
    @Override
    public void navigationStopped(NavigationStopEvent event) {
	if (handler != null) {
	    handler.navigationStopped(event);
	}
    }

    //
    // UITransitionManager methods
    //

    public NavigationListener getHandler() {
	return handler;
    }

    public void setHandler(NavigationListener handler) {
	this.handler = handler;
    }
}

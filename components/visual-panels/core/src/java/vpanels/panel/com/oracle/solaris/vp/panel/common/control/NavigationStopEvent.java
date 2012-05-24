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

import java.util.*;

@SuppressWarnings({"serial"})
public class NavigationStopEvent extends EventObject {
    //
    // Instance data
    //

    private Navigable[] last;
    private List<Control> stopped;
    private List<Control> started;
    private NavigationException exception;

    //
    // Constructors
    //

    /**
     * Constructs a {@code NavigationStopEvent} for a failed navigation.
     *
     * @param	    source
     *		    the source {@link Navigator}
     *
     * @param	    last
     *		    a {@link Navigable} array that can be used to return to the
     *		    previously current {@link Navigator#getPath path} (with the
     *		    first element a {@link Control}, as required by the {@code
     *		    path} parameter of {@link Navigator#goTo})
     *
     * @param	    stopped
     *		    the {@link Control}s that were {@link #getStopped stopped}
     *		    during navigation
     *
     * @param	    started
     *		    the {@link Control}s that were {@link #getStarted started}
     *		    during navigation
     *
     * @param	    exception
     *		    the {@link NavigationException}, if non-{@code null}, that
     *		    caused the navigation to fail
     */
    public NavigationStopEvent(Navigator source, Navigable[] last,
	List<Control> stopped, List<Control> started, NavigationException
	exception) {

	super(source);
	this.last = last;
	this.stopped = stopped;
	this.started = started;
	this.exception = exception;
    }

    /**
     * Constructs a {@code NavigationStopEvent} for a successful navigation.
     *
     * @param	    source
     *		    the source {@link Navigator}
     *
     * @param	    stopped
     *		    the {@link Control}s that were {@link #getStopped stopped}
     *		    during navigation
     *
     * @param	    started
     *		    the {@link Control}s that were {@link #getStarted started}
     *		    during navigation
     */
    public NavigationStopEvent(Navigator source, Navigable[] last,
	List<Control> stopped, List<Control> started) {

	this(source, last, stopped, started, null);
    }

    //
    // EventObject methods
    //

    @Override
    public Navigator getSource() {
	return (Navigator)super.getSource();
    }

    //
    // NavigationStopEvent methods
    //

    /**
     * Gets the {@link NavigationException}, if any, that caused the navigation
     * to fail.
     *
     * @return	    a {@link NavigationException}, or {@code null} if the
     *		    navigation completed successfully
     */
    public NavigationException getNavigationException() {
	return exception;
    }

    /**
     * Indicates whether the navigation succeeded, based on whether this {@code
     * NavigationStopEvent}'s {@link #getNavigationException
     * NavigationException} is {@code null}.
     */
    public boolean getNavigationSuccessful() {
	return exception == null;
    }

    /**
     * Gets the {@link Navigable} array that can be used to return to the
     * previously current {@link Navigator#getPath path} (with the first element
     * a {@link Control}, as required by the {@code path} parameter of {@link
     * Navigator#goTo}).
     */
    public Navigable[] getPreviousPath() {
	return last;
    }

    /**
     * Gets the {@code Control}s that were started, in the order that they were
     * started, as part of the navigation.
     */
    public List<Control> getStarted() {
	return started;
    }

    /**
     * Gets the {@code Control}s that were stopped, in the order that they were
     * stopped, as part of the navigation.
     */
    public List<Control> getStopped() {
	return stopped;
    }
}

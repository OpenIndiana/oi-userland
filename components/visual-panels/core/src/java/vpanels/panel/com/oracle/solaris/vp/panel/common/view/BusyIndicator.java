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

package com.oracle.solaris.vp.panel.common.view;

import javax.swing.Action;

/**
 * The {@code BusyIndicator} displays a visual indication of work in progress
 * and blocks the user from interacting with the client.
 * <p>
 * A {@code BusyIndicator} should be shown whenever work is being done that must
 * preclude user interaction.  For brief tasks, however, the {@code
 * BusyIndicator} must be lightweight to avoid a "flicker" effect resulting from
 * quickly showing and hiding visual elements.
 * <p>
 * For this reason, the {@code BusyIndicator} supports two stages:
 * <p>
 * <ol>
 *   <li>
 *     the initial stage, where the user is blocked from interacting with the
 *     UI
 *   </li>
 *   <li>
 *     the secondary stage, where a {@link #setMessage status message} and other
 *     optional components (such as a progress bar) are shown
 *   </li>
 * </ol>
 * <p>
 * The {@code BusyIndicator} transitions through these stages automatically.
 * The delay between them can be set using the {@link #setDelay} method.  It is
 * typically under 5 seconds, but can vary by implementation.
 * <p>
 * When {@link #setBusyIndicatorDisplayed hidden}, the {@code BusyIndicator}
 * will revert back to its default settings.
 */
public interface BusyIndicator {
    //
    // BusyIndicator methods
    //

    /**
     * Gets any {@code Action}s to be presented to the user.
     */
    Action[] getActions();

    /**
     * Gets the delay (in milliseconds) to wait in the initial stage before
     * transitioning to the secondary stage.
     */
    int getDelay();

    /**
     * Gets a status message to display.
     *
     * @return	    the message to display, or {@code null} to display a default
     *		    message
     */
    String getMessage();

    /**
     * Returns a {@code boolean} indicating whether this {@code BusyIndicator}
     * is displayed.
     */
    boolean isBusyIndicatorDisplayed();

    /**
     * Sets any {@code Action}s to be presented to the user.
     */
    void setActions(Action... actions);

    /**
     * Sets the delay (in milliseconds) to wait in the initial stage before
     * transitioning to the secondary stage.
     */
    void setDelay(int delay);

    /**
     * Displays or hides this busy indicator.  If {@code displayed} is {@code
     * false}, all settings ({@link #setMessage message}, {@link #setDelay
     * delay}, {@link #getActions actions}, etc.) are reset to their defaults.
     *
     * @param	    displayed
     *		    whether to display/hide this {@code BusyIndicator}
     */
    void setBusyIndicatorDisplayed(boolean displayed);

    /**
     * Sets a status message to display.
     *
     * @param	    message
     *		    the message to display, or {@code null} to display a default
     *		    message
     */
    void setMessage(String message);
}

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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.Component;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.swing.HasComponent;

/**
 * The {@code CustomObjectsFilter} class encapsulates the state and view of an
 * {@link ObjectsFilter} with a custom component.  Any filter with its own UI,
 * such as a search or "advanced" filter, would need to subclass this class.
 */
public class CustomObjectsFilter<C extends ManagedObject>
    extends ObjectsFilter<C> implements HasComponent<Component> {

    //
    // Instance data
    //

    private Component comp;
    private CustomObjectsFilterAction action;

    //
    // Constructors
    //

    public CustomObjectsFilter(String text, Component comp) {
	super(text, null);
	this.comp = comp;
    }

    //
    // HasComponent methods
    //

    /**
     * Gets the {@code Component} to present to the user.  Note that standard
     * controls such as okay/cancel buttons, should not be part of this
     * component.
     */
    @Override
    public Component getComponent() {
	return comp;
    }

    //
    // CustomObjectsFilter methods
    //

    /**
     * Gets the {@link CustomObjectsFilterAction} for this {@code
     * CustomObjectsFilter}.
     */
    protected CustomObjectsFilterAction getObjectsFilterAction() {
	return action;
    }

    /**
     * Sets the value returned by {@link #getComponent}.
     */
    protected void setComponent(Component comp) {
	this.comp = comp;
    }

    /**
     * Indicates that this custom control is now being displayed; saves the
     * given {@link CustomObjectsFilterAction}.
     *
     * @param	    action
     *		    provides hooks that allow this filter to control the filter
     *		    process
     */
    public void start(CustomObjectsFilterAction action) {
	this.action = action;
    }

    /**
     * Indicates that this custom control is no longer being displayed; sets
     * this {@code CustomObjectsFilter}'s {@link CustomObjectsFilterAction} to
     * {@code null}.
     *
     * @param	    applied
     *		    {@code true} if the filter was applied, {@code false} if it
     *		    was cancelled
     */
    public void stop(boolean applied) {
	action = null;
    }
}

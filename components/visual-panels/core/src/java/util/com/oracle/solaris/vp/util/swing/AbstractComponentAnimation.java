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

package com.oracle.solaris.vp.util.swing;

import java.awt.Component;
import javax.swing.event.*;
import org.jdesktop.animation.timing.TimingTarget;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

public abstract class AbstractComponentAnimation<C extends Component>
    implements ComponentAnimation<C>, TimingTarget {

    //
    // Instance data
    //

    private String id;
    private ChangeListeners listeners = new ChangeListeners();
    private ChangeEvent event = new ChangeEvent(this);

    //
    // Constructors
    //

    public AbstractComponentAnimation(String id) {
	this.id = id;
    }

    //
    // HasId methods
    //

    @Override
    public String getId() {
	return id;
    }

    //
    // TimingTarget methods
    //

    /**
     * Empty implementation.
     */
    @Override
    public void begin() {
    }

    /**
     * Calls {@link #fireStateChanged} to notify listeners that the animation
     * has completed.
     */
    @Override
    public void end() {
	fireStateChanged();
    }

    /**
     * Empty implementation.
     */
    @Override
    public void repeat() {
    }

    /**
     * Empty implementation.
     */
    @Override
    public void timingEvent(float fraction) {
    }

    //
    // ComponentAnimation methods
    //

    @Override
    public void addChangeListener(ChangeListener listener) {
	listeners.add(listener);
    }

    @Override
    public boolean removeChangeListener(ChangeListener listener) {
	return listeners.remove(listener);
    }

    //
    // AbstractComponentAnimation methods
    //

    protected void fireStateChanged() {
	listeners.stateChanged(event);
    }
}

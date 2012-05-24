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


package com.oracle.solaris.vp.panel.common.model;

import java.beans.*;

/**
 * A {@code PropertyChangeListener} that forwards {@code PropertyChangeEvent}s
 * to the specified {@code AbstractManagedObject}'s listeners.
 */
public class PropertyChangeForwarder implements PropertyChangeListener
{
    private AbstractManagedObject managedObject_;
    private Object source_;

    /**
     * Constructs a {@code PropertyChangeForwarder} that forwards events
     * to the specified {@code AbstractManagedObject}'s listeners, rewriting
     * the events' source to be the specified {@code AbstractManagedObject}.
     *
     * @param mo the object's whose listeners are sent the event, and is
     * made the source of the event
     */
    public PropertyChangeForwarder(AbstractManagedObject mo) {
	this(mo, mo);
    }

    /**
     * Constructs a {@code PropertyChangeForwarder} that forwards events
     * to the specified {@code AbstractManagedObject}'s listeners, rewriting
     * the events' source.
     *
     * @param mo the object's whose listeners are sent the event
     * @param source the new source of the events, or {@code null} to
     * leave the source alone
     */
    public PropertyChangeForwarder(AbstractManagedObject mo, Object source) {
	managedObject_ = mo;
	source_ = source;
    }

    @Override
    public void propertyChange(PropertyChangeEvent e) {
	if (source_ != null)
	    e = new PropertyChangeEvent(source_, e.getPropertyName(),
		e.getOldValue(), e.getNewValue());
	managedObject_.firePropertyChange(e);
    }
}

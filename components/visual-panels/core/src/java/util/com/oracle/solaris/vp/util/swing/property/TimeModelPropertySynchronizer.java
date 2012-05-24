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

package com.oracle.solaris.vp.util.swing.property;

import java.beans.*;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.time.TimeModel;

/**
 * The {@code TimeModelPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code TimeModel} so that changes in one
 * will automatically be reflected in the other.
 */
public class TimeModelPropertySynchronizer
    extends PropertySynchronizer<Long, TimeModel> {

    //
    // Instance data
    //

    private PropertyChangeListener listener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public TimeModelPropertySynchronizer(MutableProperty<Long> property,
	TimeModel model, boolean initFromProp) {

	super(property, model, initFromProp);
	model.addPropertyChangeListener(TimeModel.PROPERTY_TIME_OFFSET,
	    listener);
    }

    /**
     * Constructs a {@code TimeModelPropertySynchronizer} with initial
     * synchronization from the property to the {@code TimeModel}.
     */
    public TimeModelPropertySynchronizer(MutableProperty<Long> property,
	TimeModel model) {

	this(property, model, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removePropertyChangeListener(listener);
    }

    @Override
    public Long getValue() {
	return getObject().getTimeOffset();
    }

    @Override
    public void setValue(Long timeOffset) {
	if (timeOffset == null) {
	    timeOffset = 0L;
	}
	getObject().setTimeOffset(timeOffset);
    }
}

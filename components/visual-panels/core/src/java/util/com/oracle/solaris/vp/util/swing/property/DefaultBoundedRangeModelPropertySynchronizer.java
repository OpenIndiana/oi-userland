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

import javax.swing.DefaultBoundedRangeModel;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code DefaultBoundedRangeModelPropertySynchronizer} class synchronizes a
 * {@link MutableProperty} with a {@code DefaultBoundedRangeModel} so that
 * changes in one will automatically be reflected in the other.
 */
public class DefaultBoundedRangeModelPropertySynchronizer
    extends PropertySynchronizer<Integer, DefaultBoundedRangeModel> {

    //
    // Instance data
    //

    private ChangeListener listener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public DefaultBoundedRangeModelPropertySynchronizer(
	MutableProperty<Integer> property, DefaultBoundedRangeModel model,
	boolean initFromProp) {

	super(property, model, initFromProp);
	model.addChangeListener(listener);
    }

    /**
     * Constructs a {@code DefaultBoundedRangeModelPropertySynchronizer} with
     * initial synchronization from the property to the
     * {@code DefaultBoundedRangeModel}.
     */
    public DefaultBoundedRangeModelPropertySynchronizer(
	MutableProperty<Integer> property, DefaultBoundedRangeModel model) {

	this(property, model, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeChangeListener(listener);
    }

    @Override
    public Integer getValue() {
	return getObject().getValue();
    }

    @Override
    public void setValue(Integer i) {
	if (i == null) {
	    i = 0;
	}

	getObject().setValue(i);
    }
}

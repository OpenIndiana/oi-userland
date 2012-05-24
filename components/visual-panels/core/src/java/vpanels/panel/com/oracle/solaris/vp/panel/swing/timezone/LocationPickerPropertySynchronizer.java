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

package com.oracle.solaris.vp.panel.swing.timezone;

import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code LocationPickerPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code LocationPicker} so that changes in one will
 * automatically be reflected in the other.
 */
public class LocationPickerPropertySynchronizer<T, O extends LocationPicker<T>>
    extends PropertySynchronizer<T, O> {

    //
    // Instance data
    //

    private LocationSelectionListener<T> listener =
	new LocationSelectionListener<T>() {
	    @Override
	    public void locationChanged(
		LocationSelectionEvent<T> event) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public LocationPickerPropertySynchronizer(MutableProperty<T> property,
	O picker, boolean initFromProp) {

	super(property, picker, initFromProp);
	picker.addSelectionListener(listener);
    }

    /**
     * Constructs a {@code LocationPickerPropertySynchronizer} with initial
     * synchronization from the property to the {@code LocationPicker}.
     */
    public LocationPickerPropertySynchronizer(MutableProperty<T> property,
	O picker) {

	this(property, picker, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeSelectionListener(listener);
    }

    @Override
    public T getValue() {
	return getObject().getSelection();
    }

    @Override
    public void setValue(T info) {
	getObject().setSelection(info);
    }
}

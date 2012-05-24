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

package com.oracle.solaris.vp.util.misc.property;

import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;

/**
 * The {@code PropertyPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with another {@link MutableProperty} so that changes in one
 * will automatically be reflected in the other.
 */
public class PropertyPropertySynchronizer<T>
    extends PropertySynchronizer<T, MutableProperty<T>> {

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

    public PropertyPropertySynchronizer(MutableProperty<T> property,
	MutableProperty<T> property2, boolean initFromProp) {

	super(property, property2, initFromProp);

	property2.addChangeListener(listener);
    }

    /**
     * Constructs a {@code PropertyPropertySynchronizer} with initial
     * synchronization from {@code property} to {@code property2}.
     */
    public PropertyPropertySynchronizer(MutableProperty<T> property,
	MutableProperty<T> property2) {

	this(property, property2, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    protected boolean differ() {
	return super.differ() || !ObjectUtil.equals(getSavedValue(),
	    getProperty().getSavedValue());
    }

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeChangeListener(listener);
    }

    @Override
    public T getValue() {
	return getObject().getValue();
    }

    @Override
    protected void syncObjectChanges() {
	super.syncObjectChanges();
	T value = getSavedValue();
	getProperty().setSavedValue(value);
    }

    @Override
    protected void syncPropertyChanges() {
	super.syncPropertyChanges();
	T value = getProperty().getSavedValue();
	setSavedValue(value);
    }

    @Override
    public void setValue(T value) {
	getObject().setValue(value);
    }

    //
    // PropertyPropertySynchronizer methods
    //

    public T getSavedValue() {
	return getObject().getSavedValue();
    }

    public void setSavedValue(T SavedValue) {
	getObject().setSavedValue(SavedValue);
    }
}

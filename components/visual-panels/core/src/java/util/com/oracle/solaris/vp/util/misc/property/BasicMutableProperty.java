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

import java.beans.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.converter.DualConverter;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

public class BasicMutableProperty<T> implements MutableProperty<T> {
    //
    // Instance data
    //

    private String name;
    private DualConverter<String, T> converter;
    private T value;
    private T saved;

    private ChangeListeners changeListeners = new ChangeListeners();
    private ChangeEvent event = new ChangeEvent(this);

    private PropertyChangeListeners propListeners =
	new PropertyChangeListeners();

    //
    // Constructors
    //

    public BasicMutableProperty(String name, DualConverter<String, T> converter)
    {
	this.name = name;
	this.converter = converter;
    }

    public BasicMutableProperty(String name) {
	this(name, null);
    }

    public BasicMutableProperty(DualConverter<String, T> converter) {
	this(null, converter);
    }

    public BasicMutableProperty() {
	this(null, null);
    }

    //
    // Changeable methods
    //

    @Override
    public void addChangeListener(ChangeListener listener) {
	changeListeners.add(listener);
    }

    @Override
    public boolean removeChangeListener(ChangeListener listener) {
	return changeListeners.remove(listener);
    }

    @Override
    public void reset() {
	setValue(getSavedValue());
    }

    @Override
    public void save() {
	setSavedValue(getValue());
    }

    //
    // MutableProperty methods
    //

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener) {
	propListeners.add(listener);
    }

    @Override
    public DualConverter<String, T> getConverter() {
	return converter;
    }

    @Override
    public String getPropertyName() {
	return name;
    }

    @Override
    public T getSavedValue() {
	return saved;
    }

    @Override
    public T getValue() {
	return value;
    }

    @Override
    public boolean isChanged() {
	return !ObjectUtil.equals(getValue(), getSavedValue());
    }

    @Override
    public boolean removePropertyChangeListener(PropertyChangeListener listener)
    {
	return propListeners.remove(listener);
    }

    @Override
    public void setSavedValue(T saved) {
	T old = this.saved;
	if (!ObjectUtil.equals(old, saved)) {
	    this.saved = saved;
	    propertyChange(old, saved);
	    stateChanged();
	}
    }

    @Override
    public void setValue(T value) {
	T old = this.value;
	if (!ObjectUtil.equals(old, value)) {
	    this.value = value;
	    propertyChange(old, value);
	    stateChanged();
	}
    }

    @Override
    public void update(T value, boolean force) {
	boolean changed = isChanged();
	setSavedValue(value);
	if (force || !changed) {
	    reset();
	}
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return String.format("%s: name=[%s] saved=[%s] value=[%s]",
	    DebugUtil.toBaseName(this), getPropertyName(), getSavedValue(),
	    getValue());
    }

    //
    // BasicMutableProperty methods
    //

    /**
     * Notifies registered {@code PropertyChangeListener}s of a change in the
     * current or saved value this {@code MutableProperty}.
     */
    protected void propertyChange(T old, T value) {
	PropertyChangeEvent event = new PropertyChangeEvent(this,
	    getPropertyName(), old, value);
	propListeners.propertyChange(event);
    }

    public void setConverter(DualConverter<String, T> converter) {
	this.converter = converter;
    }

    /**
     * Notifies registered {@code ChangeListener}s of a change in this {@code
     * MutableProperty}.
     */
    protected void stateChanged() {
	changeListeners.stateChanged(event);
    }
}

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

package com.oracle.solaris.vp.panel.common.smf;

import java.beans.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.converter.DualConverter;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

/**
 * The {@code SmfMutablePropertyWrapper} class provides allows a wrapped {@link
 * BasicSmfMutableProperty} to be accessed as a {@link MutableProperty} for its
 * property type.  This class is used for simple SMF properties that don't have
 * multiple values.  Specifically, the {@code [gs]etValue} methods of this class
 * are translated to the {@code [gs]etFirstValue} methods of the wrapped {@link
 * BasicSmfMutableProperty}.  Most other methods are passed straight through.
 */
public class SmfMutablePropertyWrapper<T> implements MutableProperty<T> {
    //
    // Instance data
    //

    private BasicSmfMutableProperty<T> property;

    private ChangeListeners changeListeners = new ChangeListeners();
    private ChangeEvent event = new ChangeEvent(this);

    private PropertyChangeListeners propListeners =
	new PropertyChangeListeners();

    private ChangeListener changeListener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		SmfMutablePropertyWrapper.this.stateChanged();
	    }
	};

    private PropertyChangeListener propListener =
	new PropertyChangeListener() {
	    @Override
	    @SuppressWarnings({"unchecked"})
	    public void propertyChange(PropertyChangeEvent e) {
		T oldValue = (T)e.getOldValue();
		T newValue = (T)e.getNewValue();
		SmfMutablePropertyWrapper.this.propertyChange(oldValue,
		    newValue);
	    }
	};

    //
    // Constructors
    //

    public SmfMutablePropertyWrapper(BasicSmfMutableProperty<T> property) {
	this.property = property;
	property.addChangeListener(changeListener);
	property.addPropertyChangeListener(propListener);
    }

    //
    // Changeable methods
    //

    @Override
    public void addChangeListener(ChangeListener listener) {
	changeListeners.add(listener);
    }

    @Override
    public boolean isChanged() {
	return property.isChanged();
    }

    @Override
    public boolean removeChangeListener(ChangeListener listener) {
	return changeListeners.remove(listener);
    }

    @Override
    public void reset() {
	property.reset();
    }

    @Override
    public void save() {
	property.save();
    }

    //
    // MutableProperty methods
    //

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener) {
	propListeners.add(listener);
    }

    @Override
    public boolean removePropertyChangeListener(PropertyChangeListener listener)
    {
	return propListeners.remove(listener);
    }

    @Override
    public DualConverter<String, T> getConverter() {
	return property.getPropertyConverter();
    }

    @Override
    public String getPropertyName() {
	return property.getPropertyName();
    }

    @Override
    public T getSavedValue() {
	return property.getFirstSavedValue();
    }

    @Override
    public T getValue() {
	return property.getFirstValue();
    }

    @Override
    public void setSavedValue(T saved) {
	property.setFirstSavedValue(saved);
    }

    @Override
    public void setValue(T t) {
	property.setFirstValue(t);
    }

    @Override
    public void update(T t, boolean force) {
	property.updateFirst(t, force);
    }

    //
    // SmfMutablePropertyWrapper methods
    //

    public BasicSmfMutableProperty<T> getProperty() {
	return property;
    }

    protected void propertyChange(T oldValue, T newValue) {
	PropertyChangeEvent event = new PropertyChangeEvent(this,
	    getPropertyName(), oldValue, newValue);
	propListeners.propertyChange(event);
    }

    protected void stateChanged() {
	changeListeners.stateChanged(event);
    }
}

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
 * The {@code PropertySynchronizer} class provides a base class for
 * synchronization between a {@link MutableProperty} and some other {@link
 * #getObject object}, so that changes in one will automatically be reflected in
 * the other.  Besides implementing the abstract methods, subclasses should call
 * {@link #objectChanged} whenever that object changes.
 */
public abstract class PropertySynchronizer<T, O> {
    //
    // Instance data
    //

    private MutableProperty<T> property;
    private O object;
    private boolean syncObjectChanges = true;
    private boolean syncPropertyChanges = true;

    private ChangeListener propListener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		propertyChanged();
	    }
	};

    //
    // Constructors
    //

    /**
     * Constructs a {@code PropertySynchronizer} and {@link #init initializes}
     * it.
     *
     * @param	    property
     *		    the property to synchronize with the secondary object
     *
     * @param	    object
     *		    the secondary object to synchronize with the property
     *
     * @param	    initFromProp
     *		    if {@code true}, initial synchronization will be from
     *		    the property to the secondary object; if {@code false},
     *		    initial synchronization will go in the other direction
     */
    public PropertySynchronizer(MutableProperty<T> property, O object,
	boolean initFromProp) {

	this.property = property;
	this.object = object;
	property.addChangeListener(propListener);

	init(initFromProp);
    }

    /**
     * Constructs a {@code PropertySynchronizer} with initial synchronization
     * from the property to the secondary object.
     */
    public PropertySynchronizer(MutableProperty<T> property, O object) {
	this(property, object, true);
    }

    //
    // PropertySynchronizer methods
    //

    /**
     * Removes the {@code ChangeListener} that keeps the secondary object
     * up-to-date with changes in the {@link MutableProperty}.	This method
     * should be overridden to additionally remove any listener that keeps the
     * {@link MutableProperty} up-to-date with changes in the secondary object.
     */
    public void desynchronize() {
	property.removeChangeListener(propListener);
    }

    /**
     * Indicates whether the {@link #getProperty property} differs from the
     * {@link #getObject secondary object}.
     * <p/>
     * This default implementation compares the property's value with the
     * secondary object's {@link #getValue value}.  Subclasses may wish to
     * compare other attributes.
     */
    protected boolean differ() {
	return !ObjectUtil.equals(getValue(), property.getValue());
    }

    /**
     * Initializes this {@code PropertySynchronizer}, calling {@link
     * #propertyChanged} if {@code initFromProp} is {@code true}, or {@link
     * #objectChanged} if {@code initFromProp} is {@code false}.
     */
    public void init(boolean initFromProp) {
	if (initFromProp) {
	    propertyChanged();
	} else {
	    objectChanged();
	}
    }

    public O getObject() {
	return object;
    }

    public MutableProperty<T> getProperty() {
	return property;
    }

    /**
     * Gets whether changes in the {@link #getObject secondary object}
     * are propagated to the {@link #getProperty property}.
     */
    protected boolean getSyncObjectChanges() {
	return syncObjectChanges;
    }

    /**
     * Gets whether changes in the {@link #getProperty property} are propagated
     * to the {@link #getObject secondary object}.
     */
    protected boolean getSyncPropertyChanges() {
	return syncPropertyChanges;
    }

    /**
     * Gets the value of the {@link #getObject secondary object}.
     */
    protected abstract T getValue();

    /**
     * {@link #syncObjectChanges Updates} the {@link #getProperty property} with
     * the value of the {@link #getObject secondary object}, if they {@link
     * #differ differ}. This method should be called by subclasses when the
     * secondary object changes.
     */
    protected void objectChanged() {
	if (syncObjectChanges) {
	    if (differ()) {
		boolean saved = getSyncPropertyChanges();
		// Disable property change syncs to avoid loops
		setSyncPropertyChanges(false);
		try {
		    syncObjectChanges();
		} finally {
		    setSyncPropertyChanges(saved);
		}
	    }
	}
    }

    /**
     * {@link #syncPropertyChanges Updates} the {@link #getObject secondary
     * object} with the value of the {@link #getProperty property}, if they
     * {@link #differ differ}.	This method is called whenever the property
     * changes.
     */
    protected void propertyChanged() {
	if (syncPropertyChanges) {
	    if (differ()) {
		boolean saved = getSyncObjectChanges();
		// Disable object change syncs to avoid loops
		setSyncObjectChanges(false);
		try {
		    syncPropertyChanges();
		} finally {
		    setSyncObjectChanges(saved);
		}
	    }
	}
    }

    /**
     * Sets whether changes in the {@link #getObject secondary object}
     * are propagated to the {@link #getProperty property}.
     */
    protected void setSyncObjectChanges(boolean syncObjectChanges) {
	if (this.syncObjectChanges != syncObjectChanges) {
	    this.syncObjectChanges = syncObjectChanges;
	}
    }

    /**
     * Sets whether changes in the {@link #getProperty property}
     * are propagated to the {@link #getObject secondary object}.
     */
    protected void setSyncPropertyChanges(boolean syncPropertyChanges) {
	if (this.syncPropertyChanges != syncPropertyChanges) {
	    this.syncPropertyChanges = syncPropertyChanges;
	}
    }

    /**
     * Sets the value in the {@link #getObject secondary object}.
     */
    protected abstract void setValue(T value);

    /**
     * Does the actual work of propagating changes in the {@code #getObject
     * secondary object} to the {@link #getProperty property}.	Called by {@link
     * #objectChanged} after verifing that the two {@link #differ differ} and
     * that such changes {@link #getSyncObjectChanges should be propagated}.
     * <p/>
     * This default implementation sets the {@link #getValue value} of the
     * secondary object in the property.
     */
    protected void syncObjectChanges() {
	T value = getValue();
	property.setValue(value);
    }

    /**
     * Does the actual work of propagating changes in the {@link #getProperty
     * property} to the {@code #getObject secondary object}.  Called by {@link
     * #propertyChanged} after verifing that the two {@link #differ differ} and
     * that such changes {@link #getSyncPropertyChanges should be propagated}.
     * <p/>
     * This default implementation {@link #setValue sets} the value of the
     * property in the secondary object.
     */
    protected void syncPropertyChanges() {
	T value = getProperty().getValue();
	setValue(value);
    }
}

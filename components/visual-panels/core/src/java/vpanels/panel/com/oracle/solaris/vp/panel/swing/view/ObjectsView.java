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
import java.beans.*;
import java.util.List;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.HasId;
import com.oracle.solaris.vp.util.misc.HasName;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;

/**
 * The {@code ObjectsView} class represents a unique view of a {@link
 * ManagedObject}.  Most implementations will display children or other
 * descendants thereof.
 */
public abstract class ObjectsView<C extends ManagedObject>
    implements HasId, HasName {

    //
    // Static data
    //

    public static final String PROPERTY_OBJECT_COUNT = "objectcount";
    public static final String PROPERTY_SELECTION = "selection";

    //
    // Instance data
    //

    private ManagedObject<C> pObject;
    private StructuredAction<List<C>, ?, ?>[] mActions;
    private StructuredAction<List<C>, ?, ?> dmAction;

    private int count;
    private List<C> selection;
    private PropertyChangeListeners listeners = new PropertyChangeListeners();

    // Notify PropertyChangeListeners of changes in a list's selection model
    protected ListSelectionListener updateActionSelectionListener =
	new ListSelectionListener() {
	    @Override
	    public void valueChanged(ListSelectionEvent e) {
		if (!e.getValueIsAdjusting()) {
		    fireSelectionChange();
		}
	    }
	};

    //
    // Constructors
    //

    public ObjectsView(ManagedObject<C> pObject,
	StructuredAction<List<C>, ?, ?>[] mActions,
	StructuredAction<List<C>, ?, ?> dmAction) {

	this.pObject = pObject;
	this.mActions = mActions;
	this.dmAction = dmAction;
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return getName();
    }

    //
    // ObjectsView methods
    //

    public void addPropertyChangeListener(PropertyChangeListener l) {
	listeners.add(l);
    }

    /**
     * If the {@link #getObjectCount object count} has changed, creates and
     * fires a {@code PropertyChangeEvent} for the {@link
     * #PROPERTY_OBJECT_COUNT} property.
     */
    protected void fireObjectCountChange() {
	int count = getObjectCount();
	if (count != this.count) {
	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_OBJECT_COUNT, this.count, count);
	    this.count = count;
	    firePropertyChange(e);
	}
    }

    protected void firePropertyChange(PropertyChangeEvent e) {
	listeners.propertyChange(e);
    }

    /**
     * If the {@link #getSelection object selection} has changed, creates and
     * fires a {@code PropertyChangeEvent} for the {@link #PROPERTY_SELECTION}
     * property.
     */
    protected void fireSelectionChange() {
	List<C> selection = getSelection();
	if (!selection.equals(this.selection)) {
	    PropertyChangeEvent e = new PropertyChangeEvent(
		this, PROPERTY_SELECTION, this.selection, selection);
	    this.selection = selection;
	    firePropertyChange(e);
	}
    }

    public StructuredAction<List<C>, ?, ?>[] getActions() {
	return mActions;
    }

    public abstract Component getComponent();

    public StructuredAction<List<C>, ?, ?> getDefaultAction() {
	return dmAction;
    }

    /**
     * Gets an identifier for this {@code ObjectsView}, sufficiently unique as
     * to distinguish itself from its peers.
     * <p>
     * This default implementation returns the class name.
     */
    public String getId() {
	return getClass().getName();
    }

    public ManagedObject<C> getManagedObject() {
	return pObject;
    }

    /**
     * Gets the selected {@code ManagedObject}s in this view.
     * <p>
     * Note: Implementations of this class <strong>must</strong> call {@link
     * #fireSelectionChange} whenever this value changes.
     */
    public abstract List<C> getSelection();

    /**
     * Gets the number of {@code ManagedObject}s displayed in this view.
     * <p>
     * Note: Implementations of this class <strong>must</strong> call {@link
     * #fireObjectCountChange} whenever this value changes.
     */
    public abstract int getObjectCount();

    public boolean removePropertyChangeListener(PropertyChangeListener l) {
	return listeners.remove(l);
    }
}

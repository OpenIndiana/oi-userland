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

import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.ListSelector;

/**
 * The {@code ListSelectorPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code ListSelector} so that changes in one will
 * automatically be reflected in the other.
 */
public class ListSelectorPropertySynchronizer<T>
    extends PropertySynchronizer<Set<T>, ListSelector> {

    //
    // Instance data
    //

    private Boolean leftListIsDest;

    private ListDataListener listener =
	new ListDataListener() {
	    @Override
	    public void contentsChanged(ListDataEvent e) {
		objectChanged();
	    }

	    @Override
	    public void intervalAdded(ListDataEvent e) {
		objectChanged();
	    }

	    @Override
	    public void intervalRemoved(ListDataEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    /**
     * Constructs a {@code ListSelectorPropertySynchronizer}.
     *
     * @param	    property
     *		    the {@link MutableProperty} to synchronize with {@code
     *		    selector}
     *
     * @param	    selector
     *		    the {@link ListSelector} to synchronize with {@code
     *		    property}
     *
     * @param	    initFromProp
     *		    if {@code true}, initial synchronization will be from
     *		    the property to the object; if {@code false},
     *		    initial synchronization will go in the other direction
     *
     * @param	    leftListIsDest
     *		    {@code true} if the {@link ListSelector}'s left list holds
     *		    the selection, {@code false} if the right list
     */
    public ListSelectorPropertySynchronizer(MutableProperty<Set<T>> property,
	ListSelector selector, boolean initFromProp, boolean leftListIsDest) {

	super(property, selector, initFromProp);
	this.leftListIsDest = leftListIsDest;

	// Re-initialize now that leftListIsDest has been set
	init(initFromProp);

	selector.getLeftList().getModel().addListDataListener(listener);
	selector.getRightList().getModel().addListDataListener(listener);
    }

    /**
     * Constructs a {@code ListSelectorPropertySynchronizer} with initial
     * synchronization from the property to the {@link ListSelector}.
     */
    public ListSelectorPropertySynchronizer(MutableProperty<Set<T>> property,
	ListSelector selector, boolean leftListIsDest) {

	this(property, selector, true, leftListIsDest);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	ListSelector selector = getObject();
	selector.getLeftList().getModel().addListDataListener(listener);
	selector.getRightList().getModel().addListDataListener(listener);
    }

    @Override
    public Set<T> getValue() {
	ListSelector selector = getObject();
	JList list = leftListIsDest ? selector.getLeftList() :
	    selector.getRightList();

	ListModel model = list.getModel();
	int size = model.getSize();

	Set<T> values = new HashSet<T>(size);
	for (int i = 0; i < size; i++) {
	    Object element = model.getElementAt(i);
	    T value = toT(element);
	    values.add(value);
	}

	return values;
    }

    @Override
    public void init(boolean initFromProp) {
	// Wait until leftListIsDest has been set to initialize
	if (leftListIsDest != null) {
	    super.init(initFromProp);
	}
    }

    @Override
    public void setValue(Set<T> values) {
	if (values == null) {
	    values = Collections.emptySet();
	}

	ListSelector selector = getObject();

	JList srcList = leftListIsDest ?
	    selector.getRightList() : selector.getLeftList();

	JList destList = leftListIsDest ?
	    selector.getLeftList() : selector.getRightList();

	DefaultListModel srcModel = (DefaultListModel)srcList.getModel();
	DefaultListModel destModel = (DefaultListModel)destList.getModel();

	for (int i = srcModel.getSize() - 1; i >= 0; i--) {
	    Object element = srcModel.getElementAt(i);
	    T value = toT(element);
	    if (values.contains(value)) {
		srcModel.removeElementAt(i);
		destModel.addElement(element);
	    }
	}

	for (int i = destModel.getSize() - 1; i >= 0; i--) {
	    Object element = destModel.getElementAt(i);
	    T value = toT(element);
	    if (!values.contains(value)) {
		destModel.removeElementAt(i);
		srcModel.addElement(element);
	    }
	}
    }

    //
    // ListSelectorPropertySynchronizer methods
    //

    /**
     * Gets the value from the given list item from the {@code ListModel} of the
     * {@code JList}s of the {@link ListSelector} of this {@code
     * ListSelectorPropertySynchronizer}.  This implementation returns {@code
     * item}, cast to a {@code T}.
     */
    @SuppressWarnings({"unchecked"})
    protected T toT(Object item) {
	return (T)item;
    }
}

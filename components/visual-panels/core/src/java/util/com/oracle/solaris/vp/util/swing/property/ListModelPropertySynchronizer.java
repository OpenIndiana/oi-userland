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

/**
 * The {@code ListModelPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code ListModel} so that changes in one will
 * automatically be reflected in the other.
 */
public class ListModelPropertySynchronizer<T>
    extends PropertySynchronizer<List<T>, DefaultListModel> {

    //
    // Instance data
    //

    private JList list;

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

    public ListModelPropertySynchronizer(MutableProperty<List<T>> property,
	DefaultListModel model, boolean initFromProp) {

	super(property, model, initFromProp);
	model.addListDataListener(listener);
    }

    /**
     * Constructs a {@code ListModelPropertySynchronizer} with initial
     * synchronization from the property to the {@code DefaultListModel}.
     */
    public ListModelPropertySynchronizer(MutableProperty<List<T>> property,
	DefaultListModel model) {

	this(property, model, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().addListDataListener(listener);
    }

    @Override
    @SuppressWarnings({"unchecked"})
    public List<T> getValue() {
	ListModel model = getObject();
	int nRows = model.getSize();
	List<T> values = new ArrayList<T>(nRows);

	for (int row = 0; row < nRows; row++) {
	    values.add((T)model.getElementAt(row));
	}

	return values;
    }

    @Override
    public void setValue(List<T> values) {
	if (values == null) {
	    values = Collections.emptyList();
	}

	DefaultListModel model = getObject();
	int nRows = model.getSize();
	int nVals = values.size();

	model.clear();
	for (Object value : values) {
	    model.addElement(value);
	}
    }
}

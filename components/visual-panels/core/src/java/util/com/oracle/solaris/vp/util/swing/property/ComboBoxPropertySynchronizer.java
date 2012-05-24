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

import java.awt.event.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code ComboBoxPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code JComboBox} so that changes in one will
 * automatically be reflected in the other.
 */
public class ComboBoxPropertySynchronizer<T>
    extends PropertySynchronizer<T, JComboBox> {

    //
    // Instance data
    //

    private ItemListener listener =
	new ItemListener() {
	    @Override
	    public void itemStateChanged(ItemEvent e) {
		objectChanged();
	    }
	};

    //
    // Constructors
    //

    public ComboBoxPropertySynchronizer(MutableProperty<T> property,
	JComboBox combo, boolean initFromProp) {

	super(property, combo, initFromProp);
	combo.addItemListener(listener);
    }

    /**
     * Constructs a {@code ComboBoxPropertySynchronizer} with initial
     * synchronization from the property to the {@code JComboBox}.
     */
    public ComboBoxPropertySynchronizer(MutableProperty<T> property,
	JComboBox combo) {

	this(property, combo, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeItemListener(listener);
    }

    @Override
    public T getValue() {
	return toT(getObject().getSelectedItem());
    }

    @Override
    public void setValue(T t) {
	Object selection = null;
	JComboBox combo = getObject();
	ComboBoxModel model = combo.getModel();
	for (int i = 0, n = model.getSize(); i < n; i++) {
	    Object element = model.getElementAt(i);
	    T item = toT(element);
	    if (ObjectUtil.equals(toT(element), t)) {
		selection = element;
		break;
	    }
	}
	combo.setSelectedItem(selection);
    }

    //
    // ComboBoxPropertySynchronizer methods
    //

    /**
     * Gets the value from the given item from the {@code ComboBoxModel} of the
     * {@code JComboBox}s of this {@code ComboBoxPropertySynchronizer}.  This
     * implementation returns {@code item}, cast to a {@code T}.
     */
    @SuppressWarnings({"unchecked"})
    protected T toT(Object item) {
	return (T)item;
    }
}

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

package com.oracle.solaris.vp.util.swing;

import javax.swing.DefaultComboBoxModel;
import com.oracle.solaris.vp.util.misc.NameValue;

@SuppressWarnings({"serial"})
public class NameValueComboBoxModel<V> extends DefaultComboBoxModel {
    //
    // Constructors
    //

    public NameValueComboBoxModel(NameValue<V>... items) {
	super(items);
    }

    public NameValueComboBoxModel() {
    }

    //
    // NameValueComboBoxModel methods
    //

    public void addElement(String name, V value) {
	addElement(new NameValue<V>(name, value));
    }

    @SuppressWarnings({"unchecked"})
    public V getSelectedValue() {
	V value = null;
	Object selected = getSelectedItem();
	if (selected != null) {
	    value = ((NameValue<V>)selected).getValue();
	}

	return value;
    }

    public NameValue<V> getNameValue(V value) {
	for (int i = 0, n = getSize(); i < n; i++) {
	    @SuppressWarnings({"unchecked"})
	    NameValue<V> nv = (NameValue<V>)getElementAt(i);
	    if (value.equals(nv.getValue())) {
		return nv;
	    }
	}
	return null;
    }

    @SuppressWarnings({"unchecked"})
    public V getValueAt(int index) {
	return ((NameValue<V>)getElementAt(index)).getValue();
    }

    public void setSelectedValue(V value) {
	setSelectedItem(getNameValue(value));
    }
}

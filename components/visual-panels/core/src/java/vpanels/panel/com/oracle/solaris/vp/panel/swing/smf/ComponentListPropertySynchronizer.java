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

package com.oracle.solaris.vp.panel.swing.smf;

import java.awt.Component;
import java.util.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.smf.BasicSmfMutableProperty;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code ComponentListPropertySynchronizer} class provides a base class to
 * synchronize a {@link MutableProperty} with a {@link ComponentList} so that
 * changes in one will automatically be reflected in the other.
 */
public abstract class ComponentListPropertySynchronizer<T, C extends Component,
    L extends ComponentList<C>> extends PropertySynchronizer<List<T>, L> {

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

    public ComponentListPropertySynchronizer(
	BasicSmfMutableProperty<T> property, L list) {

	super(property, list);
	list.addChangeListener(listener);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	getObject().removeChangeListener(listener);
    }

    @Override
    public List<T> getValue() {
	ComponentList<C> list = getObject();
	int nComps = list.getComponentCount();
	List<T> values = new ArrayList<T>(nComps);
	for (int i = 0; i < nComps; i++) {
	    C comp = list.getListComponent(i);
	    values.add(getValue(comp));
	}
	return values;
    }

    @Override
    public void setValue(List<T> values) {
	ComponentList<C> list = getObject();
	int nComps = list.getComponentCount();
	int nValues = values == null ? 0 : values.size();

	if (nValues > nComps) {
	    for (int i = 0; i < nValues - nComps; i++) {
		list.add();
	    }
	} else if (nValues < nComps) {
	    for (int i = 0; i < nComps - nValues; i++) {
		list.remove(0);
	    }
	}

	nComps = list.getComponentCount();
	assert nValues == nComps;

	for (int i = 0; i < nValues; i++) {
	    C comp = comp = list.getListComponent(i);
	    T value = values.get(i);
	    setValue(comp, value);
	}
    }

    //
    // ComponentListPropertySynchronizer methods
    //

    protected abstract T getValue(C comp);

    protected abstract void setValue(C comp, T value);
}

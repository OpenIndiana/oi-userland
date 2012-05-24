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
import java.util.Map;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code RadioButtonPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code Map} of {@code AbstractButton}s so that
 * changes in one will automatically be reflected in the other.
 */
public class RadioButtonPropertySynchronizer<T>
    extends PropertySynchronizer<T, Map<AbstractButton, T>> {

    //
    // Instance data
    //

    private ButtonGroup group = new ButtonGroup();

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

    /**
     * Constructs a {@code RadioButtonPropertySynchronizer}.  The buttons in the
     * given map will be added to a new {@link #getGroup ButtonGroup}.
     *
     * @param	    property
     *		    the property to synchronize with the button group
     *
     * @param	    map
     *		    a {@code Map} from buttons to the values they represent
     *
     * @param	    initFromProp
     *		    if {@code true}, initial synchronization will be from
     *		    the property to the buttons; if {@code false},
     *		    initial synchronization will go in the other direction
     */
    public RadioButtonPropertySynchronizer(MutableProperty<T> property,
	Map<AbstractButton, T> map, boolean initFromProp) {

	super(property, map, initFromProp);

	// Re-initialize now that group has been set
	init(initFromProp);

	for (AbstractButton button : map.keySet()) {
	    button.addItemListener(listener);
	    group.add(button);
	}
    }

    /**
     * Constructs a {@code RadioButtonPropertySynchronizer} with initial
     * synchronization from the property to the button map.
     */
    public RadioButtonPropertySynchronizer(MutableProperty<T> property,
	Map<AbstractButton, T> map) {

	this(property, map, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void desynchronize() {
	super.desynchronize();
	for (AbstractButton button : getObject().keySet()) {
	    button.removeItemListener(listener);
	}
    }

    @Override
    public T getValue() {
	ButtonModel selected = group.getSelection();
	if (selected != null) {
	    Map<AbstractButton, T> map = getObject();
	    for (AbstractButton button : map.keySet()) {
		if (button.getModel().equals(selected)) {
		    return map.get(button);
		}
	    }
	}
	return null;
    }

    @Override
    public void init(boolean initFromProp) {
	// Wait until group has been set to initialize
	if (group != null) {
	    super.init(initFromProp);
	}
    }

    @Override
    public void setValue(T value) {
	Map<AbstractButton, T> map = getObject();
	for (AbstractButton button : map.keySet()) {
	    Object mapValue = map.get(button);
	    if (ObjectUtil.equals(value, mapValue)) {
		button.setSelected(true);
		return;
	    }
	}
	group.clearSelection();
    }

    //
    // RadioButtonPropertySynchronizer methods
    //

    public ButtonGroup getGroup() {
	return group;
    }
}

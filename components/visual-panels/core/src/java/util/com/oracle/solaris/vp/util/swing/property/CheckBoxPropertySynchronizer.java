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
import javax.swing.JCheckBox;
import com.oracle.solaris.vp.util.misc.property.*;

/**
 * The {@code CheckBoxPropertySynchronizer} class synchronizes a {@link
 * MutableProperty} with a {@code JCheckBox} so that changes in one will
 * automatically be reflected in the other.
 */
public class CheckBoxPropertySynchronizer
    extends PropertySynchronizer<Boolean, JCheckBox> {

    //
    // Instance data
    //

    private Boolean negated;

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

    public CheckBoxPropertySynchronizer(MutableProperty<Boolean> property,
	JCheckBox checkBox, boolean initFromProp, boolean negated) {

	super(property, checkBox, initFromProp);
	this.negated = negated;

	// Re-initialize now that negated has been set
	init(initFromProp);

	checkBox.addItemListener(listener);
    }

    /**
     * Constructs a {@code CheckBoxPropertySynchronizer} with initial
     * synchronization from the property to the {@code JCheckBox}.
     */
    public CheckBoxPropertySynchronizer(MutableProperty<Boolean> property,
	JCheckBox checkBox) {

	this(property, checkBox, true, false);
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
    public Boolean getValue() {
	return negated != getObject().isSelected();
    }

    @Override
    public void init(boolean initFromProp) {
	// Wait until negated has been set to initialize
	if (negated != null) {
	    super.init(initFromProp);
	}
    }

    @Override
    public void setValue(Boolean value) {
	getObject().setSelected(value == null ? false : negated != value);
    }

    //
    // CheckBoxPropertySynchronizer methods
    //

    public boolean getNegated() {
	return negated;
    }
}

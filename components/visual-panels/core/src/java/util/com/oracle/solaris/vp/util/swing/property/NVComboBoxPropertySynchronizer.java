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

import javax.swing.JComboBox;
import com.oracle.solaris.vp.util.misc.NameValue;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

/**
 * The {@code NVComboBoxPropertySynchronizer} class is a {@link
 * ComboBoxPropertySynchronizer} whose {@link JComboBox}'s {@code
 * ComboBoxModel}s contain {@link NameValue}s.
 */
public class NVComboBoxPropertySynchronizer<T>
    extends ComboBoxPropertySynchronizer<T> {

    //
    // Constructors
    //

    public NVComboBoxPropertySynchronizer(MutableProperty<T> property,
	JComboBox combo, boolean initFromProp) {

	super(property, combo, initFromProp);
    }

    /**
     * Constructs a {@code NVComboBoxPropertySynchronizer} with initial
     * synchronization from the property to the {@code JComboBox}.
     */
    public NVComboBoxPropertySynchronizer(MutableProperty<T> property,
	JComboBox combo) {

	this(property, combo, true);
    }

    //
    // ComboBoxPropertySynchronizer methods
    //

    @Override
    protected T toT(Object item) {
	@SuppressWarnings({"unchecked"})
	NameValue<T> nv = (NameValue<T>)item;
	return nv == null ? null : nv.getValue();
    }
}

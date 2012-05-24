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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.util.Map;
import javax.swing.AbstractButton;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;
import com.oracle.solaris.vp.util.swing.property.
    RadioButtonPropertySynchronizer;

/**
 * The {@code CustomizedChoicePropertySynchronizer} class is a {@link
 * RadioButtonPropertySynchronizer} that permits selecting one-of-N predefined
 * choices but at the same time permits the wrapped datum to take on arbitrary
 * values, as indicated by a specified N+1st choice.  This N+1st choice is
 * normally greyed out and cannot be selected by the user; it is only activated
 * when the wrapped datum does not correspond to one of the other choices.
 */
public class CustomizedChoicePropertySynchronizer<T>
    extends RadioButtonPropertySynchronizer<T> {

    //
    // Instance data
    //

    private AbstractButton custom;

    //
    // Constructors
    //

    /**
     * Constructs a {@code CustomizedChoicePropertySynchronizer}.
     *
     * @param	    map
     *		    a {@code Map} from buttons to the values they represent
     *
     * @param	    custom
     *		    the button representing a custom configuration; this button
     *		    will be enabled and when a value is set that does not
     *		    correspond to any of the other buttons
     *
     * @param	    initFromProp
     *		    if {@code true}, initial synchronization will be from
     *		    the property to the buttons; if {@code false},
     *		    initial synchronization will go in the other direction
     */
    public CustomizedChoicePropertySynchronizer(MutableProperty<T> property,
	Map<AbstractButton, T> map, AbstractButton custom, boolean initFromProp)
    {
	super(property, map);
	this.custom = custom;

	// Re-init, now that custom has been set
	init(initFromProp);
    }

    /**
     * Constructs a {@code CustomizedChoicePropertySynchronizer} with initial
     * synchronization from the property to the button map.
     */
    public CustomizedChoicePropertySynchronizer(MutableProperty<T> property,
	Map<AbstractButton, T> map, AbstractButton custom) {

	this(property, map, custom, true);
    }

    //
    // PropertySynchronizer methods
    //

    @Override
    public void init(boolean initFromProp) {
	if (custom != null) {
	    super.init(initFromProp);
	}
    }

    @Override
    public void setValue(T value) {
	AbstractButton selected = null;

	Map<AbstractButton, T> map = getObject();
	for (AbstractButton button : map.keySet()) {
	    Object mapValue = map.get(button);
	    if (ObjectUtil.equals(value, mapValue)) {
		selected = button;
		break;
	    }
	}

	if (selected == null) {
	    map.put(custom, value);
	    selected = custom;
	}

	custom.setEnabled(selected == custom);
	selected.setSelected(true);
    }
}

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

import java.awt.event.*;
import java.util.*;
import javax.swing.JComboBox;

public class ComboBoxList extends ComponentList<JComboBox> {
    //
    // Instance data
    //

    private ItemListener listener =
	new ItemListener() {
	    @Override
	    public void itemStateChanged(ItemEvent e) {
		fireStateChanged();
	    }
	};

    private String defaultValue;
    private List<String> allowed;

    //
    // Constructors
    //

    public ComboBoxList(String defaultValue, List<String> allowed) {
	this.defaultValue = defaultValue;
	this.allowed = allowed;
    }

    //
    // ComponentList methods
    //

    @Override
    protected JComboBox createListComponent(int index) {
	Vector<String> data = new Vector<String>();
	data.addAll(allowed);
	JComboBox combo = new JComboBox(data);
	combo.setSelectedItem(defaultValue);
	combo.addItemListener(listener);

	return combo;
    }

    @Override
    protected void disposeListComponent(JComboBox combo) {
	combo.removeItemListener(listener);
    }

    //
    // ComboBoxList methods
    //

    public String getDefaultValue() {
	return defaultValue;
    }
}

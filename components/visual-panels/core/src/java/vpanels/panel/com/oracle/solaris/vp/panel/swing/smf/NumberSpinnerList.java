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

import javax.swing.*;
import javax.swing.event.*;

public class NumberSpinnerList extends ComponentList<JSpinner> {
    //
    // Instance data
    //

    private ChangeListener listener =
	new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		fireStateChanged();
	    }
	};

    private Integer defaultValue;
    private boolean isCount;

    //
    // Constructors
    //

    public NumberSpinnerList(Integer defaultValue, boolean isCount) {
	this.defaultValue = defaultValue;
	this.isCount = isCount;
    }

    //
    // ComponentList methods
    //

    @Override
    protected JSpinner createListComponent(int index) {
	SpinnerNumberModel model = new SpinnerNumberModel();

	if (isCount) {
	    model.setMinimum(0);
	}

	model.setValue(defaultValue);

	JSpinner spinner = new JSpinner(model);
	spinner.addChangeListener(listener);

	JComponent editor = spinner.getEditor();
	if (editor instanceof JSpinner.DefaultEditor) {
	    JTextField field = ((JSpinner.DefaultEditor)editor).getTextField();
	    field.setColumns(5);
	    field.setHorizontalAlignment(JTextField.RIGHT);
	}

	return spinner;
    }

    @Override
    protected void disposeListComponent(JSpinner spinner) {
	spinner.removeChangeListener(listener);
    }

    //
    // NumberSpinnerList methods
    //

    public Integer getDefaultValue() {
	return defaultValue;
    }
}

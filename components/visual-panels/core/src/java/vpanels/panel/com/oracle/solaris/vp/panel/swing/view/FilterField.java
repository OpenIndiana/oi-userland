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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.Color;
import javax.swing.*;
import javax.swing.event.DocumentEvent;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

/**
 * A simple live filter entry box.  Could be extended to track history,
 * sport a clear button, etc.  For now it is just a JTextField.
 */
public class FilterField extends Box
{
    private static final Color COLOR_UNMATCHED =
	ColorUtil.lighter(Color.RED, .9f);

    private JTextField field_;
    private String text_ = "";
    private FilterListener listener_ = null;

    public interface FilterListener
    {
	public void filterUpdate(FilterField field);
    }

    public FilterField(int columns)
    {
	super(BoxLayout.LINE_AXIS);

	setOpaque(false);

	JLabel label = new JLabel(Finder.getString(
	    "objects.header.filter.label"));
	field_ = new JTextField();
	field_.setColumns(columns);

	field_.getDocument().addDocumentListener(new DocumentAdapter() {
	    @Override
	    public void docUpdate(DocumentEvent e)
	    {
		text_ = field_.getText();
		update();
	    }
	});

	add(label);
	add(createHorizontalStrut(GUIUtil.getHalfGap()));
	add(field_);
    }

    public String getText()
    {
	return (text_);
    }

    public void setFilterListener(FilterListener listener)
    {
	listener_ = listener;
    }

    private void update()
    {
	if (listener_ != null)
	    listener_.filterUpdate(this);
    }

    public void setUnmatched(boolean unmatched)
    {
	if (unmatched)
	    field_.setBackground(COLOR_UNMATCHED);
	else
	    field_.setBackground(null);
    }
}

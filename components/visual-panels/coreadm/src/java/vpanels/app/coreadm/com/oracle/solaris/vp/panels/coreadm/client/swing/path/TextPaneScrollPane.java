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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.coreadm.client.swing.path;

import java.awt.*;
import java.beans.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class TextPaneScrollPane extends ExtScrollPane {
    //
    // Instance data
    //

    private JTextPane textPane;
    private int columns;
    private int columnWidth;
    private int height;

    //
    // Constructors
    //

    public TextPaneScrollPane(JTextPane textPane, int columns) {
	super(getPanel(textPane));
	this.textPane = textPane;
	this.columns = columns;

	// Schedule recalculation of column width when font changes
	textPane.addPropertyChangeListener("font",
	    new PropertyChangeListener() {
		@Override
		public void propertyChange(PropertyChangeEvent e) {
		    columnWidth = 0;
		    height = 0;
		}
	    });

	// Don't show scroll bars
	setVerticalScrollBarPolicy(
	    ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
	setHorizontalScrollBarPolicy(
	    ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
    }

    public TextPaneScrollPane(JTextPane textPane) {
	this(textPane, GUIUtil.getTextFieldWidth());
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	Dimension d = super.getPreferredSize();

	// Limit height of scroll pane to initial height of text pane
	if (height == 0) {
	    height = d.height;
	} else {
	    d.height = height;
	}

	int columns = getColumns();
	if (columns >= 0) {
	    int columnWidth = getColumnWidth();
	    Insets i = textPane.getInsets();
	    d.width = i.left + i.right + columns * columnWidth;
	}

	return d;
    }

    //
    // TextPaneScrollPane methods
    //

    protected int getColumnWidth() {
        if (columnWidth == 0) {
            FontMetrics metrics = textPane.getFontMetrics(textPane.getFont());
            columnWidth = metrics.charWidth('m');
        }
        return columnWidth;
    }

    public JTextPane getTextPane() {
	return textPane;
    }

    public int getColumns() {
	return columns;
    }

    public void setColumns(int columns) {
	this.columns = columns;

	invalidate();

	Container parent = getParent();
	if (parent != null && parent instanceof JComponent) {
	    ((JComponent)parent).revalidate();
	}
    }

    //
    // Static methods
    //

    private static JPanel getPanel(JTextPane textPane) {
	JPanel panel = new JPanel(new BorderLayout());
	panel.add(textPane);
	return panel;
    }
}

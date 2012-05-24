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

package com.oracle.solaris.vp.util.swing.layout;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.CollectionUtil;

public class TableLayout extends AbstractTableLayout<HasAnchors> {
    //
    // Static methods
    //

    public static final HorizontalAnchor DEFAULT_HORIZONTAL_ANCHOR =
	HorizontalAnchor.FILL;

    public static final VerticalAnchor DEFAULT_VERTICAL_ANCHOR =
	VerticalAnchor.FILL;

    public static final HasAnchors DEFAULT_CONSTRAINT =
	new SimpleHasAnchors(HorizontalAnchor.FILL, VerticalAnchor.FILL);

    //
    // Instance data
    //

    private List<AbstractTableConstraint> colConstraints =
	new ArrayList<AbstractTableConstraint>();
    private List<AbstractTableConstraint> rowConstraints =
	new ArrayList<AbstractTableConstraint>();

    //
    // Constructors
    //

    public TableLayout(AbstractTableConstraint[] rowConstraints,
	AbstractTableConstraint[] colConstraints) {

	super(DEFAULT_HORIZONTAL_ANCHOR, DEFAULT_VERTICAL_ANCHOR,
	    DEFAULT_CONSTRAINT);

	CollectionUtil.addAll(this.rowConstraints, rowConstraints);
	CollectionUtil.addAll(this.colConstraints, colConstraints);
    }

    public TableLayout(int rows, int cols, int hGap, int vGap) {
	this(createTableConstraints(rows, vGap),
	    createTableConstraints(cols, hGap));
    }

    public TableLayout(int rows, int cols) {
	this(rows, cols, 0, 0);
    }

    //
    // ConstrainedLayout methods
    //

    @Override
    public HasAnchors cloneConstraint(HasAnchors constraint) {
	return new SimpleHasAnchors(
	    constraint.getHorizontalAnchor(), constraint.getVerticalAnchor());
    }

    //
    // AbstractTableLayout methods
    //

    @Override
    public AbstractTableConstraint getColumnConstraint(
	Container container, int col) {

	return colConstraints.get(col);
    }

    @Override
    public AbstractTableConstraint getRowConstraint(
	Container container, int row) {

	int size = rowConstraints.size();

	if (row < size) {
	    return rowConstraints.get(row);
	}

	// Not enough rows were specified
	return rowConstraints.get(size - 1);
    }

    @Override
    protected int getColumnCount(Container container) {
	return colConstraints.size();
    }

    //
    // TableLayout methods
    //

    public void addRows(AbstractTableConstraint... constraints) {
	CollectionUtil.addAll(this.rowConstraints, constraints);
    }

    public void addRow() {
	AbstractTableConstraint constraint =
	    rowConstraints.get(rowConstraints.size() - 1);
	rowConstraints.add(constraint);
    }

    //
    // Static methods
    //

    private static SimpleTableConstraint[] createTableConstraints(
	int count, int gap) {

	if (count <= 0) {
	    throw new IllegalArgumentException(
		"invalid number of rows/columns: " + count);
	}

	SimpleTableConstraint constraint = new SimpleTableConstraint(gap);

	SimpleTableConstraint[] constraints = new SimpleTableConstraint[count];
	for (int i = 0; i < constraints.length; i++) {
	    constraints[i] = constraint;
	}

	return constraints;
    }

    public static void main(String[] args) {
	int rows = 6;
	int cols = 6;
	int gap = 5;
//	TableLayout layout = new TableLayout(rows, cols, gap, gap);

	AbstractTableConstraint[] rowConstraints =
	    new AbstractTableConstraint[rows];
	for (int row = 0; row < rows; row++) {
	    rowConstraints[row] = new SimpleTableConstraint(gap * row);
	    rowConstraints[row].setLayoutIfInvisible(false);
	}

	AbstractTableConstraint[] colConstraints =
	    new AbstractTableConstraint[cols];
	for (int col = 0; col < cols; col++) {
	    colConstraints[col] = new SimpleTableConstraint(gap * col);
	    colConstraints[col].setLayoutIfInvisible(false);
	}

	TableLayout layout = new TableLayout(rowConstraints, colConstraints);
	layout.setVerticalAnchor(VerticalAnchor.FILL);
	layout.setHorizontalAnchor(HorizontalAnchor.FILL);

	JPanel p = new JPanel(layout);

	SimpleHasAnchors constraint = new SimpleHasAnchors(
	    HorizontalAnchor.FILL, VerticalAnchor.FILL);

	for (int row = 0; row < rows; row++) {
	    for (int col = 0; col < cols; col++) {
		StringBuilder b = new StringBuilder("<html>");
		for (int i = 0; i <= row; i++) {
		    for (int j = 0; j <= col; j++) {
			b.append('m');
		    }
		    b.append("<br/>");
		}
		JButton button = new JButton(b.toString());
		if (col == 2 || row == 2) {
		    button.setVisible(false);
		}
		p.add(button, constraint);
	    }
	}

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(p, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}

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
import com.oracle.solaris.vp.util.swing.layout.AbstractLayout.SizedSet;
import com.oracle.solaris.vp.util.swing.layout.Anchor.AnchorType;

public abstract class AbstractTableLayout<C extends HasAnchors>
    extends ConstrainedLayout<C> implements HasAnchors {

    //
    // Inner classes
    //

    protected static class CellInfo {
	//
	// Instance data
	//

	private Component component;
	private Dimension size;
	private boolean preferred;
	private List<RowOrCol> parents = new ArrayList<RowOrCol>();

	//
	// Constructors
	//

	public CellInfo(Component component, boolean preferred) {
	    this.component = component;
	    this.preferred = preferred;
	}

	//
	// CellInfo methods
	//

	public void add(RowOrCol parent) {
	    parents.add(parent);
	}

	public Component getComponent() {
	    return component;
	}

	public Dimension getSize() {
	    // Deferred fetch
	    if (size == null) {
		size = preferred ?
		    component.getPreferredSize() : component.getMinimumSize();
	    }
	    return size;
	}

	public void remove() {
	    for (int i = parents.size() - 1; i >= 0; i--) {
		parents.get(i).childRemoved(this);
		parents.remove(i);
	    }
	}
    }

    protected static class RowOrCol {
	//
	// Instance data
	//

	private AbstractTableConstraint constraint;
	private boolean isRow;
	private int size = -1;
	private float weight = -1f;
	private List<CellInfo> children = new ArrayList<CellInfo>();
	private List<CellInfo> roChildren =
	    Collections.unmodifiableList(children);

	//
	// Constructors
	//

	public RowOrCol(AbstractTableConstraint constraint, boolean isRow) {
	    this.constraint = constraint;
	    this.isRow = isRow;
	}

	//
	// Instance data
	//

	public void add(CellInfo child) {
	    children.add(child);
	    child.add(this);
	}

	/**
	 * Called by the child when it is removed from layout.
	 */
	public boolean childRemoved(CellInfo child) {
	    boolean ret = children.remove(child);
	    if (ret) {
		size = -1;
	    }
	    return ret;
	}

	public AbstractTableConstraint getConstraint() {
	    return constraint;
	}

	public List<CellInfo> getChildren() {
	    return roChildren;
	}

	/**
	 * Get the maximum size (row height or column width) of every child
	 * {@code Component}.
	 */
	public int getSize() {
	    // Deferred fetch
	    if (size == -1) {
		for (CellInfo child : children) {
		    Dimension d = child.getSize();
		    int s = isRow ? d.height : d.width;
		    if (s > size) {
			size = s;
		    }
		}
	    }
	    return size;
	}

	public float getWeight() {
	    // Deferred fetch
	    if (weight == -1) {
		weight = constraint.getWeight();
	    }
	    return weight;
	}

	/**
	 * Remove all children in this row/column from layout (in any
	 * row/column).
	 */
	public void remove() {
	    for (int i = children.size() - 1; i >= 0; i--) {
		remove(children.get(i));
	    }
	}

	/**
	 * Remove the given child in this row/column from layout (in any
	 * row/column).
	 */
	public boolean remove(CellInfo child) {
	    if (children.contains(child)) {
		child.remove();
		return true;
	    }
	    return false;
	}

	public void setSize(int size) {
	    this.size = size;
	}

	public void setWeight(float weight) {
	    this.weight = weight;
	}
    }

    protected static class RowOrColSet implements SizedSet {
	//
	// Instance data
	//

	private int tSizes = -1;
	private int tGaps = -1;
	private List<RowOrCol> elements = new ArrayList<RowOrCol>();
	private List<RowOrCol> roElements =
	    Collections.unmodifiableList(elements);

	//
	// SizedSet methods
	//

	@Override
	public int getCount() {
	    return elements.size();
	}

	@Override
	public int getSize(int i) {
	    return elements.get(i).getSize();
	}

	@Override
	public float getWeight(int i) {
	    return elements.get(i).getWeight();
	}

	@Override
	public void setSize(int i, int size) {
	    elements.get(i).setSize(size);
	}

	@Override
	public void setWeight(int i, float weight) {
	    elements.get(i).setWeight(weight);
	}

	//
	// RowOrColSet methods
	//

	public void add(RowOrCol element) {
	    elements.add(element);
	}

	public void add(int i, RowOrCol element) {
	    elements.add(i, element);
	}

	public List<RowOrCol> getElements() {
	    return roElements;
	}

	public int getGap(int i) {
	    AbstractTableConstraint constraint =
		elements.get(i).getConstraint();

	    return (i == 0 && constraint.getIgnoreFirstGap()) ?
		0 : constraint.getGap();
	}

	public int getGapTotal() {
	    // Deferred fetch
	    if (tGaps == -1) {
		tGaps = 0;
		for (int i = 0, n = getCount(); i < n; i++) {
		    tGaps += getGap(i);
		}
	    }
	    return tGaps;
	}

	public int getSizeTotal() {
	    // Deferred fetch
	    if (tSizes == -1) {
		tSizes = 0;
		for (RowOrCol element : elements) {
		    tSizes += element.getSize();
		}
	    }
	    return tSizes;
	}

	public void remove(int i) {
	    RowOrCol element = elements.remove(i);
	    if (element != null) {
		element.remove();
		tSizes = -1;
		tGaps = -1;
	    }
	}
    }

    protected static class TableInfo {
	//
	// Instance data
	//

	private RowOrColSet cols;
	private RowOrColSet rows;

	//
	// Constructors
	//

	public TableInfo(RowOrColSet cols, RowOrColSet rows) {
	    this.cols = cols;
	    this.rows = rows;

	    // Remove rows/columns from layout if a) directed by constraints b)
	    // they contain only invisible Components
	    for (RowOrColSet set : new RowOrColSet[] {rows, cols}) {
		List<RowOrCol> elements = set.getElements();
		OUTER: for (int i = elements.size() - 1; i >= 0; i--) {
		    RowOrCol element = elements.get(i);
		    if (!element.getConstraint().getLayoutIfInvisible()) {
			for (CellInfo comp : element.getChildren()) {
			    if (comp.getComponent().isVisible()) {
				continue OUTER;
			    }
			}

			// Remove this row/column from layout
			set.remove(i);
		    }
		}
	    }
	}

	//
	// TableInfo methods
	//

	public RowOrColSet getColumns() {
	    return cols;
	}

	public RowOrColSet getRows() {
	    return rows;
	}
    }

    //
    // Instance data
    //

    public HorizontalAnchor hAnchor;
    public VerticalAnchor vAnchor;

    //
    // Constructors
    //

    public AbstractTableLayout(HorizontalAnchor hAnchor,
	VerticalAnchor vAnchor, C defaultElementConstraint) {

	super(defaultElementConstraint);
	this.hAnchor = hAnchor;
	this.vAnchor = vAnchor;
    }

    //
    // HasAnchors methods
    //

    @Override
    public HorizontalAnchor getHorizontalAnchor() {
	return hAnchor;
    }

    @Override
    public VerticalAnchor getVerticalAnchor() {
	return vAnchor;
    }

    //
    // LayoutManager methods
    //

    /**
     * Lay out Components in the given Container.
     */
    @Override
    public void layoutContainer(Container container) {
	TableInfo info = getTableInfo(container, true);

	RowOrColSet rows = info.getRows();
	int nRows = rows.getCount();
	if (nRows == 0) {
	    return;
	}

	RowOrColSet cols = info.getColumns();
	int nCols = cols.getCount();

	Insets insets = container.getInsets();
	Dimension aSize = container.getSize();

	// The amount of space we have to work with
	int cWidth = aSize.width - insets.left - insets.right;
	int cHeight = aSize.height - insets.top - insets.bottom;

	// Where to start drawing the first Component
	int top = insets.top;
	int tableLeft = insets.left;

	// First set heights of rows
	top += fitToSize(cHeight, rows, getVerticalAnchor());

	// Then set widths of columns
	tableLeft += fitToSize(cWidth, cols, getHorizontalAnchor());

	// Lay out components
	for (int r = 0; r < nRows; r++) {

	    RowOrCol row = rows.getElements().get(r);
	    int rSize = row.getSize();
	    top += rows.getGap(r);

	    List<CellInfo> children = row.getChildren();
	    int left = tableLeft;
	    for (int c = 0; c < nCols; c++) {

		RowOrCol col = cols.getElements().get(c);
		int cSize = col.getSize();
		left += cols.getGap(c);

		if (c < children.size()) {
		    CellInfo cInfo = children.get(c);
		    Component comp = cInfo.getComponent();
		    Dimension pSize = cInfo.getSize();

		    HasAnchors hasAnchors = compToConst.get(comp);

		    int[] yAndHeight = getOffsetAndSize(rSize,
			pSize.height, hasAnchors.getVerticalAnchor());

		    int[] xAndWidth = getOffsetAndSize(cSize,
			pSize.width, hasAnchors.getHorizontalAnchor());

		    comp.setBounds(left + xAndWidth[0], top + yAndHeight[0],
			xAndWidth[1], yAndHeight[1]);
		}

		left += cSize;
	    }

	    top += rSize;
	}
    }

    //
    // AbstractLayout methods
    //

    @Override
    protected Dimension getLayoutSize(Container container, boolean preferred) {
	TableInfo info = getTableInfo(container, preferred);

	RowOrColSet cols = info.getColumns();
	RowOrColSet rows = info.getRows();

	int width = cols.getSizeTotal() + cols.getGapTotal();
	int height = rows.getSizeTotal() + rows.getGapTotal();

	Insets insets = container.getInsets();
	width += insets.left + insets.right;
	height += insets.top + insets.bottom;

	return new Dimension(width, height);
    }

    protected TableInfo getTableInfo(Container container, boolean preferred) {
	Component[] comps = getLayoutComponents(container.getComponents());

	int nCols = getColumnCount(container);
	int nRows = 0;
	if (nCols != 0) {
	    nRows = comps.length / nCols;
	    if (comps.length % nCols > 0) {
		nRows++;
	    }
	}

	// Build cells
	CellInfo[] cInfo = new CellInfo[comps.length];
	for (int i = 0; i < comps.length; i++) {
	    cInfo[i] = new CellInfo(comps[i], preferred);
	}

	// Build columns
	RowOrColSet cols = new RowOrColSet();
	for (int c = 0; c < nCols; c++) {
	    AbstractTableConstraint constraint =
		getColumnConstraint(container, c);

	    RowOrCol col = new RowOrCol(constraint, false);

	    for (int r = 0; r < nRows; r++) {
		int index = r * nCols + c;
		if (index < cInfo.length) {
		    col.add(cInfo[index]);
		}
	    }

	    cols.add(col);
	}

	// Build rows
	RowOrColSet rows = new RowOrColSet();
	for (int r = 0; r < nRows; r++) {
	    AbstractTableConstraint constraint =
		getRowConstraint(container, r);

	    RowOrCol row = new RowOrCol(constraint, true);

	    for (int c = 0; c < nCols; c++) {
		int index = r * nCols + c;
		if (index < cInfo.length) {
		    row.add(cInfo[index]);
		}
	    }

	    rows.add(row);
	}

	return new TableInfo(cols, rows);
    }

    //
    // AbstractTableLayout methods
    //

    protected abstract AbstractTableConstraint getColumnConstraint(
	Container container, int col);

    protected abstract AbstractTableConstraint getRowConstraint(
	Container container, int row);

    /**
     * Gets the number of columns in this {@code AbstractTableLayout}.
     *
     * @param	    container
     *		    the {@code Container} being layed out
     */
    protected abstract int getColumnCount(Container container);

    public void setHorizontalAnchor(HorizontalAnchor hAnchor) {
	this.hAnchor = hAnchor;
    }

    public void setVerticalAnchor(VerticalAnchor vAnchor) {
	this.vAnchor = vAnchor;
    }

    //
    // Private methods
    //

    private int fitToSize(int aSize, RowOrColSet set, Anchor anchor) {
	int top = 0;
	int tSizes = set.getSizeTotal();
	int tGaps = set.getGapTotal();

	// Excess/insufficient space
	int extraSize = aSize - tSizes - tGaps;

	if (extraSize != 0) {

	    if (extraSize < 0 ||
		anchor.getAnchorType() == Anchor.AnchorType.FILL) {

		distributeSpace(extraSize, set);
	    } else {

		switch (anchor.getAnchorType()) {
		    case RIGHT_BOTTOM:
			top += (aSize - tSizes - tGaps);
			break;

		    case CENTER:
			top += (aSize - tSizes - tGaps) / 2;
			break;
		}
	    }
	}

	return top;
    }

    /**
     * Returns a two-element array consisting of the offset and size of a
     * resized {@code Component}.
     *
     * @param	    aSize
     *		    the available size in which to fit the {@code Component}
     *
     * @param	    pSize
     *		    the preferred size in which to fit the {@code Component}
     *
     * @param	    anchor
     *		    the Anchor of the {@code Component}
     */
    private int[] getOffsetAndSize(int aSize, int pSize, Anchor anchor) {
	// Excess/insufficient space
	int extra = aSize - pSize;

	int offset = 0;
	int size = pSize;
	Anchor.AnchorType type = anchor.getAnchorType();

	if (extra != 0) {

	    if (extra < 0 || type == Anchor.AnchorType.FILL) {
		size = aSize;
	    } else {

		switch (type) {
		    case RIGHT_BOTTOM:
			offset = (aSize - pSize);
			break;

		    case CENTER:
			offset = (aSize - pSize) / 2;
			break;
		}
	    }
	}

	return new int[] {offset, size};
    }
}

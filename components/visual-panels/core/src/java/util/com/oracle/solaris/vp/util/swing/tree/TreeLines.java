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

package com.oracle.solaris.vp.util.swing.tree;

import java.awt.*;
import java.util.List;
import javax.swing.*;
import javax.swing.plaf.PanelUI;
import com.oracle.solaris.vp.util.swing.GraphicsUtil;

@SuppressWarnings({"serial"})
public class TreeLines extends JPanel {
    //
    // Static data
    //

    // Amount of space between end of tree line and table cell
    protected static final int _LINE_CELL_GAP = 3;

    // Amount of space between vertical tree linees
    protected static final int _VERTICAL_LINE_GAP = 20;

    // Length of horizontal line
    protected static final int _HORIZONTAL_LINE_LENGTH = 9;

    // Width of line
    protected static final int _LINE_WIDTH = 1;

    private static final Icon ICON_COLLAPSED =
	getPaintedIcon(UIManager.getIcon("Tree.collapsedIcon"));

    private static final Icon ICON_EXPANDED =
	getPaintedIcon(UIManager.getIcon("Tree.expandedIcon"));

    //
    // Instance data
    //

    private TreeTable table;
    private ViewRowData data;
    private int lineCellGap = _LINE_CELL_GAP;
    private int verticalLineGap = _VERTICAL_LINE_GAP;
    private int horizontalLineLength = _HORIZONTAL_LINE_LENGTH;
    private int lineWidth = _LINE_WIDTH;
    private boolean paintLines;

    //
    // Constructors
    //

    public TreeLines(TreeTable table) {
	this.table = table;
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	List<Boolean> showLines = getRowData().getShowLines();
	int size = showLines == null ? 0 :
	    Math.max(0, showLines.size() - getIgnore());

	int verticalLineGap = getVerticalLineGap();
	int lineWidth = getLineWidth();
	int horizontalLineLength = getHorizontalLineLength();
	int lineCellGap = getLineCellGap();

	int width = verticalLineGap / 2 + lineWidth + size *
	    (verticalLineGap + lineWidth) + horizontalLineLength +
	    lineCellGap;
	int height = lineWidth;

	return new Dimension(width, height);
    }

    //
    // Component methods
    //

    @Override
    public void setForeground(Color c) {
	if (c == null) {
	    c = UIManager.getColor("Tree.line");
	}

	if (c == null) {
	    c = UIManager.getColor("Tree.dropLineColor");
	}

	super.setForeground(c);
    }

    //
    // JComponent methods
    //

    @Override
    public void paint(Graphics g) {
	int width = getWidth();
	int height = getHeight();

	int verticalLineGap = getVerticalLineGap();
	int lineWidth = getLineWidth();
	int horizontalLineLength = getHorizontalLineLength();

	((Graphics2D)g).setStroke(new BasicStroke(lineWidth));

	g.setColor(getForeground());

	ViewRowData vData = getRowData();
	int vRow = vData.getRow();
	ModelRowData mData = vData.getModelRow();
	Icon icon = mData.getTreeNode().isLeaf() ? null :
	    mData.isExpanded() ? ICON_EXPANDED : ICON_COLLAPSED;
	List<Boolean> showLines = vData.getShowLines();

	// Hack to ensure that tree lines between rows connect (this is not safe
	// outside the table)
	int rowMargin = table.getRowMargin();
	Rectangle clip = SwingUtilities.convertRectangle(
	    table, table.getVisibleRect(), this);
	g.setClip(clip);

	int y = - rowMargin / 2;
	int x = verticalLineGap / 2;
	boolean paintLines = getPaintLines();
	int ignore = getIgnore();

	for (int i = ignore - 1, n = showLines.size(); i < n; i++) {
	    if (paintLines) {
		int xCoord = x + lineWidth / 2;

		// Draw vertical bar
		if (showLines.get(i) || i == showLines.size() - 1) {
		    int startY = vRow == 0 ? height / 2 : y;
		    int endY = showLines.get(i) ?
			height + rowMargin - 1 : height / 2;

		    g.drawLine(xCoord, startY, xCoord, endY);
		}

		if (i == showLines.size() - 1) {
		    int yCoord = height / 2;

		    // Draw horizontal branch
		    g.drawLine(xCoord, yCoord, xCoord + horizontalLineLength,
			yCoord);
		}
	    }

	    if (i == showLines.size() - 1 && icon != null) {
		// Draw icon centered over beginning of horizontal branch
		int iX = x + (lineWidth - icon.getIconWidth()) / 2;
		int iY = (height - icon.getIconHeight()) / 2;
		icon.paintIcon(this, g, iX, iY);
	    }

	    x += lineWidth + verticalLineGap;
	}
    }

    //
    // JPanel methods
    //

    @Override
    public void setUI(PanelUI newUI) {
	super.setUI(newUI);
	Object value = UIManager.get("Tree.drawVerticalLines");
	if (value != null) {
	    paintLines = Boolean.valueOf(value.toString());
	} else {
	    paintLines = UIManager.getBoolean("Tree.paintLines");
	}

	setPaintLines(paintLines);
    }

    //
    // TreeLines methods
    //

    public int getHorizontalLineLength() {
	return horizontalLineLength;
    }

    protected Icon getIcon() {
	ViewRowData vData = getRowData();
	int vRow = vData.getRow();
	ModelRowData mData = vData.getModelRow();
	Icon icon = mData.getTreeNode().isLeaf() ? null :
	    mData.isExpanded() ? ICON_EXPANDED : ICON_COLLAPSED;

	return icon;
    }

    public int getLineCellGap() {
	return lineCellGap;
    }

    public int getLineWidth() {
	return lineWidth;
    }

    public boolean getPaintLines() {
	return paintLines;
    }

    public ViewRowData getRowData() {
	return data;
    }

    public TreeTable getTable() {
	return table;
    }

    public int getVerticalLineGap() {
	return verticalLineGap;
    }

    /**
     * Determines whether the given Point, relative to this component, is over a
     * turner icon.
     */
    boolean isOverTurner(Point p) {
	Icon icon = getIcon();
	if (icon != null) {
	    Dimension d = getPreferredSize();

	    int horizontalLineLength = getHorizontalLineLength();
	    int lineCellGap = getLineCellGap();

	    int xMin = d.width - lineCellGap - horizontalLineLength -
		icon.getIconWidth() / 2;

	    int xMax = xMin + icon.getIconWidth();

	    return (p.x >= xMin && p.x < xMax);
	}

	return false;
    }

    public void setHorizontalLineLength(int horizontalLineLength) {
	this.horizontalLineLength = horizontalLineLength;
    }

    public void setLineCellGap(int lineCellGap) {
	this.lineCellGap = lineCellGap;
    }

    public void setLineWidth(int lineWidth) {
	this.lineWidth = lineWidth;
    }

    private void setPaintLines(boolean paintLines) {
	this.paintLines = paintLines;
    }

    public void setRowData(ViewRowData data) {
	this.data = data;
    }

    public void setVerticalLineGap(int verticalLineGap) {
	this.verticalLineGap = verticalLineGap;
    }

    //
    // Private methods
    //

    private int getIgnore() {
	return table.isRootVisible() ? 1 : 2;
    }

    //
    // Static methods
    //

    /**
     * Synth icons cannot be painted without a synth context, so calling
     * paintIcon as within {@link #paintComponent} results in nothing actually
     * being painted.  As a hack/workaround, paint the icon onto a JLabel, then
     * paint the JLabel into an image.  This seems to be necessary only with
     * synth icons, but do it for all icons to be sure.
     */
    private static Icon getPaintedIcon(Icon icon) {
	if (icon != null) {
	    JLabel l = new JLabel(icon);
	    l.setSize(l.getPreferredSize());
	    Image image = GraphicsUtil.paintToImage(l);
	    icon = new ImageIcon(image);
	}
	return icon;
    }
}

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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.table.TableCellRenderer;
import javax.swing.tree.*;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.swing.layout.*;

public class SimpleCellRenderer<T> extends JPanel
    implements ListCellRenderer, TableCellRenderer, TreeCellRenderer {

    //
    // Static data
    //

    private static final int DEFAULT_ICON_HEIGHT_LIST = 24;
    private static final int DEFAULT_ICON_HEIGHT_TABLE = 16;
    private static final int DEFAULT_ICON_HEIGHT_TREE = 24;
    private static final int DEFAULT_CELL_WIDTH_LIST = 80;

    //
    // Instance data
    //

    private BorderLayout layout;
    private JLabel iconLabel;
    private JLabel textLabel;
    private JLabel statusLabel;
    private JPanel textPanel;

    private Border focusBorder;
    private Border noFocusBorder;

    private int iGap = 0;
    private int oGap = 2;
    private int hGap = 0;
    private int vGap = 0;
    private int cWidthMin = -1;
    private int cWidthMax = -1;
    private int iconHeight = -1;
    private boolean showStatus = true;
    private boolean styled = true;

    //
    // Constructors
    //

    public SimpleCellRenderer() {
	layout = new BorderLayout();
	setLayout(layout);

	iconLabel = new AutoHideLabel();
	textLabel = new AutoHideLabel();
	statusLabel = new AutoHideLabel();

	setIconTextGap(iconLabel.getIconTextGap());
	createBorders();

	Font font = statusLabel.getFont();
	float size = font.getSize() * .85f;
	font = font.deriveFont(Font.ITALIC, size);
	statusLabel.setFont(font);

	textPanel = new JPanel(new ColumnLayout(VerticalAnchor.FILL));
	textPanel.setOpaque(false);
	ColumnLayoutConstraint c = new ColumnLayoutConstraint();
	textPanel.add(new Spacer(), c.setWeight(1));
	textPanel.add(textLabel, c.setWeight(0));
	textPanel.add(statusLabel, c.setWeight(0));
	textPanel.add(new Spacer(), c.setWeight(1));

	setOrientation(false);
    }

    //
    // ListCellRenderer methods
    //

    @Override
    public Component getListCellRendererComponent(JList list, Object value,
	int index, boolean isSelected, boolean hasFocus) {

	return getCellRendererComponent(list, value, isSelected, hasFocus);
    }

    //
    // TableCellRenderer methods
    //

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
	boolean isSelected, boolean hasFocus, int row, int col) {

	return getCellRendererComponent(table, value, isSelected, hasFocus);
    }

    //
    // TreeCellRenderer methods
    //

    @Override
    public Component getTreeCellRendererComponent(JTree tree,
	Object value, boolean isSelected, boolean isExpanded,
	boolean isLeaf, int row, boolean hasFocus) {

	if (value instanceof DefaultMutableTreeNode) {
	    value = ((DefaultMutableTreeNode)value).getUserObject();
	}

	return getCellRendererComponent(tree, value, isSelected, hasFocus);
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	assert cWidthMin < 0 || cWidthMax < 0 || cWidthMin <= cWidthMax;
	Dimension d = super.getPreferredSize();
	if (cWidthMin >= 0 && d.width < cWidthMin) {
	    d.width = cWidthMin;
	} else if (cWidthMax >= 0 && d.width > cWidthMax) {
	    d.width = cWidthMax;
	}
	return d;
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	if (isOpaque()) {
	    Color bg = getBackground();
	    int w = getWidth() - hGap;
	    int h = getHeight() - vGap;

	    if (styled) {
		((Graphics2D)g).setRenderingHint(
		    RenderingHints.KEY_ANTIALIASING,
		    RenderingHints.VALUE_ANTIALIAS_ON);

		((Graphics2D)g).setPaint(new GradientPaint(
		    0, 0, ColorUtil.lighter(bg, .1f),
		    0, h, ColorUtil.darker(bg, .1f)));

		int arc = 10;
		g.fillRoundRect(0, 0, w, h, arc, arc);
	    } else {
		g.setColor(bg);
		g.fillRect(0, 0, w, h);
	    }
	}
    }

    //
    // SimpleCellRenderer methods
    //

    /**
     * Configures this renderer for the given {@code JList}.
     *
     * @param	    list
     *		    a {@code JList}, or {@code null} to make guesses about the
     *		    {@code JList} configuration
     */
    public void configureFor(JList list) {
	int orientation = list == null ? JList.VERTICAL :
	    list.getLayoutOrientation();

	switch (orientation) {
	    case JList.VERTICAL_WRAP:
	    case JList.HORIZONTAL_WRAP:
		setHorizontalCellSpacing(1);
		setVerticalCellSpacing(1);
		setOrientation(true);
		setMinimumCellWidth(DEFAULT_CELL_WIDTH_LIST);
		setMaximumCellWidth(DEFAULT_CELL_WIDTH_LIST);
		break;

	    case JList.VERTICAL:
		setHorizontalCellSpacing(0);
		setVerticalCellSpacing(1);
		setOrientation(false);
		setMinimumCellWidth(-1);
		setMaximumCellWidth(-1);
		break;
	}

	setIconHeight(DEFAULT_ICON_HEIGHT_LIST);
	setStyled(true);
	setShowStatus(true);
	setInnerGap(0);
	setOuterGap(2);
    }

    /**
     * Configures this renderer for the given {@code JTable}.
     *
     * @param	    table
     *		    a {@code JTable}, or {@code null} to make guesses about the
     *		    {@code JTable} configuration
     */
    public void configureFor(JTable table) {
	setHorizontalCellSpacing(0);
	setVerticalCellSpacing(0);
	setOrientation(false);
	setMinimumCellWidth(-1);
	setMaximumCellWidth(-1);
	setIconHeight(DEFAULT_ICON_HEIGHT_TABLE);
	setStyled(false);
	setShowStatus(false);
	setInnerGap(0);
	setOuterGap(0);
    }

    /**
     * Configures this renderer for the given {@code JTree}.
     *
     * @param	    tree
     *		    a {@code JTree}, or {@code null} to make guesses about the
     *		    {@code JTree} configuration
     */
    public void configureFor(JTree tree) {
	setHorizontalCellSpacing(0);
	setVerticalCellSpacing(1);
	setOrientation(false);
	setMinimumCellWidth(-1);
	setMaximumCellWidth(-1);
	setIconHeight(DEFAULT_ICON_HEIGHT_TREE);
	setStyled(true);
	setShowStatus(true);
	setInnerGap(0);
	setOuterGap(2);
    }

    /**
     * Get the backgound color of a cell.
     *
     * @return	    a {@code Color}, or {@code null} to use the parent {@code
     *		    Component}'s background
     */
    protected Color getBackground(Component comp, T value, boolean isSelected,
	boolean hasFocus) {

	Color color = null;

	if (isSelected) {
	    if (comp instanceof JList) {
		color = ((JList)comp).getSelectionBackground();
	    } else if (comp instanceof JTable) {
		color = ((JTable)comp).getSelectionBackground();
	    } else if (comp instanceof JTree) {
		color = UIManager.getColor("Tree.selectionBackground");
	    }
	}

	return color;
    }

    public Component getCellRendererComponent(Component comp, Object value,
	boolean isSelected, boolean hasFocus) {

	@SuppressWarnings("unchecked")
	T t = (T)value;

	boolean opaque = getOpaque(comp, t, isSelected, hasFocus);
	setOpaque(opaque);

	Color bg = getBackground(comp, t, isSelected, hasFocus);
	setBackground(bg);

	Color fg = getTextForeground(comp, t, isSelected, hasFocus);
	setForeground(fg);
	textLabel.setForeground(fg);

	Color sfg = getStatusTextForeground(comp, t, isSelected, hasFocus);
	statusLabel.setForeground(sfg);

	setBorder(hasFocus ? focusBorder : noFocusBorder);

	String text = getText(comp, t, isSelected, hasFocus);
	textLabel.setText(text);

	String status = getStatusText(comp, t, isSelected, hasFocus);
	statusLabel.setText(status);

	Icon icon = getSizedIcon(comp, t, isSelected, hasFocus);
	iconLabel.setIcon(icon);

	String toolTip = getToolTipText(comp, t, isSelected, hasFocus);
	setToolTipText(toolTip);

	return this;
    }

    /**
     * Gets the space (in pixels) to the right of this cell.  The default is 0.
     */
    public int getHorizontalCellSpacing() {
	return hGap;
    }

    /**
     * Gets an icon for the given value to display in the cell, or {@code null}
     * to display no icon for this value.
     * <br/>
     * This default implementation returns {@code null}.
     */
    public Icon getIcon(Component comp, T value, boolean isSelected,
	boolean hasFocus) {
	return null;
    }

    /**
     * Gets a static height for all icons returned from {@link #getIcon}.  Icons
     * returned from that method are resized as necessary.  The default is -1.
     *
     * @return	    a positive int, or -1 for no static icon height
     */
    public int getIconHeight() {
	return iconHeight;
    }

    protected JLabel getIconLabel() {
	return iconLabel;
    }

    public int getIconTextGap() {
	return layout.getHgap();
    }

    /**
     * Gets the the space (in pixels) between the contents of the cell and the
     * focus border.  The default is 0.
     */
    public int getInnerGap() {
	return iGap;
    }

    /**
     * Gets the maximum preferred width (in pixels) of the cell, or -1 if no
     * maximum preferred width is set.	The default is -1.
     */
    public int getMaximumCellWidth() {
	return cWidthMax;
    }

    /**
     * Gets the minimum preferred width (in pixels) of the cell, or -1 if no
     * minimum preferred width is set.	The default is -1.
     */
    public int getMinimumCellWidth() {
	return cWidthMin;
    }

    /**
     * Get the opacity of a cell.  This default implementation returns {@code
     * true} if selected, {@code false} otherwise.
     */
    protected boolean getOpaque(Component comp, T value, boolean isSelected,
	boolean hasFocus) {

	if (comp instanceof JTree) {
	    // JTrees under the GTKLookAndFeel present a variety of problems
	    // to using this renderer.	To start, they color the entire row
	    // of a selected node (handles, lines, and all), whereas most
	    // L&Fs only color the "data" portion of the node.	Next, they
	    // ignore the background color of the renderer and use the
	    // "Tree.selectionBackground" UI property.	Finally, the
	    // selection color actually changes when the tree doesn't have
	    // focus.  Thus setting any color or style in the renderer looks odd
	    // at best.  So, don't fight it and return false here.
	    LookAndFeel laf = UIManager.getLookAndFeel();
	    if (laf != null && laf.getClass().getName().contains(
		"GTKLookAndFeel")) {
		return false;
	    }
	}

	return isSelected;
    }

    /**
     * Gets the space (in pixels) between the focus border and the edge of the
     * cell.  The default is 2.
     */
    public int getOuterGap() {
	return oGap;
    }

    /**
     * Gets whether to display a status line.  The default is {@code true}.
     */
    public boolean getShowStatus() {
	return showStatus;
    }

    protected JLabel getTextLabel() {
	return textLabel;
    }

    protected JLabel getStatusLabel() {
	return statusLabel;
    }

    /**
     * Gets status text for the given value to display in the cell, or {@code
     * null} to display no status text for this value.
     * <br/>
     * This default implementation returns {@code null}.
     */
    public String getStatusText(Component comp, T value, boolean isSelected,
	boolean hasFocus) {
	return null;
    }

    /**
     * Get the foreground color of the status portion of the cell.
     *
     * @return	    a {@code Color}
     */
    public Color getStatusTextForeground(Component comp, T value,
	boolean isSelected, boolean hasFocus) {

	Color textColor = getTextForeground(comp, value, isSelected, hasFocus);
	return isSelected ? textColor : ColorUtil.lighter(textColor, .5f);
    }

    /**
     * Gets whether the background of this cell renderer is styled.  The default
     * is {@code true}.
     */
    public boolean getStyled() {
	return styled;
    }

    /**
     * Gets a text representation of the given value to display in the cell, or
     * {@code null} to display no text for this value.
     * <br/>
     * This default implementation returns {@code null}.
     */
    public String getText(Component comp, T value, boolean isSelected,
	boolean hasFocus) {
	return null;
    }

    /**
     * Gets a tool tip for the given value to display in the cell, or
     * {@code null} to display no tool tip for this value.
     * <br/>
     * This default implementation returns {@code null}.
     */
    public String getToolTipText(Component comp, T value, boolean isSelected,
	boolean hasFocus) {
	return null;
    }

    /**
     * Get the foreground color of the text portion of the cell.
     *
     * @return	    a non-null {@code Color}
     */
    protected Color getTextForeground(Component comp, T value,
	boolean isSelected, boolean hasFocus) {

	Color color = comp.getForeground();

	if (isSelected) {
	    if (comp instanceof JList) {
		color = ((JList)comp).getSelectionForeground();
	    } else if (comp instanceof JTable) {
		color = ((JTable)comp).getSelectionForeground();
	    } else if (comp instanceof JTree) {
		// XXX
		Color bg = getBackground();
		if (bg == null) {
		    bg = UIManager.getColor("Tree.selectionBackground");
		}

		if (bg != null) {
		    color = ColorUtil.isDark(bg) ? Color.white : Color.black;
		}
	    }
	}

	return color;
    }

    /**
     * Gets the the space (in pixels) at the bottom of this cell.  The default
     * is 0.
     */
    public int getVerticalCellSpacing() {
	return vGap;
    }

    /**
     * Sets the the space (in pixels) to the right of this cell.
     */
    public void setHorizontalCellSpacing(int hGap) {
	if (this.hGap != hGap) {
	    this.hGap = hGap;
	    createBorders();
	}
    }

    /**
     * Sets a static height for all icons returned from {@link #getIcon}.  Icons
     * returned from that method are resized as necessary.
     *
     * @param	    iconHeight
     *		    a positive int, or -1 for no static icon height
     */
    public void setIconHeight(int iconHeight) {
	this.iconHeight = iconHeight;
    }

    public void setIconTextGap(int gap) {
	layout.setHgap(gap);
	layout.setVgap(gap);
	revalidate();
	repaint();
    }

    /**
     * Sets the the space (in pixels) between the contents of the cell and the
     * focus border.
     */
    public void setInnerGap(int iGap) {
	if (this.iGap != iGap) {
	    this.iGap = iGap;
	    createBorders();
	}
    }

    /**
     * Sets the maximum preferred width (in pixels) of the cell, or -1 if no
     * maximum preferred width should be enforced.
     */
    public void setMaximumCellWidth(int cWidthMax) {
	this.cWidthMax = cWidthMax;
    }

    /**
     * Sets the minimum preferred width (in pixels) of the cell, or -1 if no
     * minimum preferred width should be enforced.
     */
    public void setMinimumCellWidth(int cWidthMin) {
	this.cWidthMin = cWidthMin;
    }

    /**
     * Sets whether this renderer's icon appears on top ({@code true}) or at
     * left ({@code false}).
     */
    public void setOrientation(boolean iconOnTop) {
	int orientation = iconOnTop ? SwingConstants.CENTER :
	    SwingConstants.LEFT;

	iconLabel.setHorizontalAlignment(orientation);
	textLabel.setHorizontalAlignment(orientation);
	statusLabel.setHorizontalAlignment(orientation);

	removeAll();
	add(iconLabel, iconOnTop ? BorderLayout.NORTH : BorderLayout.WEST);
	add(textPanel, BorderLayout.CENTER);
    }

    /**
     * Sets the space (in pixels) between the focus border and the edge of the
     * cell.
     */
    public void setOuterGap(int oGap) {
	if (this.oGap != oGap) {
	    this.oGap = oGap;
	    createBorders();
	}
    }

    /**
     * Sets whether to display a status line.
     */
    public void setShowStatus(boolean showStatus) {
	this.showStatus = showStatus;
    }

    /**
     * Sets whether the background of this cell renderer is styled.
     */
    public void setStyled(boolean styled) {
	this.styled = styled;
    }

    /**
     * Sets the the space (in pixels) at the bottom of this cell.
     */
    public void setVerticalCellSpacing(int vGap) {
	if (this.vGap != vGap) {
	    this.vGap = vGap;
	    createBorders();
	}
    }

    //
    // Private methods
    //

    private void createBorders() {
	Border dotted = new DottedBorder();

	Border oEmpty = BorderFactory.createEmptyBorder(
	    oGap, oGap, oGap + vGap, oGap + hGap);

	Border iEmpty = BorderFactory.createEmptyBorder(iGap, iGap, iGap, iGap);

	focusBorder = GUIUtil.createCompoundBorder(oEmpty, dotted, iEmpty);

	Insets i = focusBorder.getBorderInsets(this);
	noFocusBorder = BorderFactory.createEmptyBorder(
	    i.top, i.left, i.bottom, i.right);
    }

    private Icon getSizedIcon(Component comp, T value, boolean isSelected,
	boolean hasFocus) {

	Icon icon = getIcon(comp, value, isSelected, hasFocus);
	if (icon != null) {
	    int height = getIconHeight();
	    if (height != -1) {
		icon = IconUtil.ensureIconHeight(icon, height);
	    }
	}

	return icon;
    }
}

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
import java.awt.geom.Area;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.plaf.basic.BasicTabbedPaneUI;

public class SleekTabbedPaneUI extends BasicTabbedPaneUI {
    //
    // Static data
    //

    // Default color of the border
    static final Color _COLOR = new Color(163, 184, 203);

    // Default color of the selected tab
    static final Color _BORDER_COLOR = Color.DARK_GRAY;

    // Default color of the inactive tabs
    private static final Color _INACTIVE_COLOR =
	UIManager.getColor("TabbedPane.background");

    // Gap between tabs
    private static final int TAB_GAP = 2;

    // Arc of the tab corners
    private static final int TAB_ARC = 8;

    // Space around the contents of each tab, within the tab
    private static final Insets TAB_INSETS = new Insets(2, 10, 0, 10);

    // Additional space around selected tab
    private static final Insets SELECTED_TAB_INSETS = new Insets(0, 0, 0, 0);

    // Space around tab group
    private static final int TAB_AREA_GAP = TAB_GAP;
    private static final Insets TAB_AREA_INSETS_NO_BORDER =
	new Insets(0, TAB_AREA_GAP, 0, TAB_AREA_GAP);
    private static final Insets TAB_AREA_INSETS_BORDER =
	new Insets(0, 0, 0, 0);

    // Height of the solid bar running underneath tabs, above the content area
    private static final int CONTENT_TOP_HEIGHT = 5;
    private static final Insets CONTENT_INSETS_NO_BORDER =
	new Insets(CONTENT_TOP_HEIGHT, 0, 0, 0);
    private static final Insets CONTENT_INSETS_BORDER =
	new Insets(CONTENT_TOP_HEIGHT, 1, 1, 1);

    //
    // Instance data
    //

    private Color color = _COLOR;
    private Color borderColor = _BORDER_COLOR;
    private Color contentBorderColor = _BORDER_COLOR;
    private Color inactiveColor = _INACTIVE_COLOR;

    private boolean drawContentBorder = false;

    //
    // BasicTabbedPaneUI methods
    //

    @Override
    protected int calculateTabWidth(
	int tabPlacement, int tabIndex, FontMetrics metrics) {

	// Uniform tab widths
	int width = 0;
	for (int i = 0, n = tabPane.getTabCount(); i < n; i++) {
	    width = Math.max(width,
		super.calculateTabWidth(tabPlacement, i, metrics));
	}

	return width + TAB_GAP + 1;
    }

    @Override
    protected Insets getContentBorderInsets(int tabPlacement) {
	return getDrawContentBorder() ?
	    CONTENT_INSETS_BORDER : CONTENT_INSETS_NO_BORDER;
    }

    @Override
    protected int getTabLabelShiftY(
	int tabPlacement, int tabIndex, boolean isSelected) {

	// Don't offset the label of the selected tab
	return 0;
    }

    @Override
    protected void installDefaults() {
	super.installDefaults();

	// Let the JTabbedPane determine it's own opacity
        UIManager.put("TabbedPane.contentOpaque", false);

	tabAreaInsets = getDrawContentBorder() ?
	    TAB_AREA_INSETS_BORDER : TAB_AREA_INSETS_NO_BORDER;

	tabInsets = TAB_INSETS;
	selectedTabPadInsets = SELECTED_TAB_INSETS;

	// Embolden font
	tabPane.setFont(tabPane.getFont().deriveFont(Font.BOLD));
    }

    @Override
    protected void paintContentBorderBottomEdge(Graphics g, int tabPlacement,
	int selectedIndex, int x, int y, int w, int h) {

	if (getDrawContentBorder()) {
	    Graphics2D g2 = (Graphics2D)g;
	    g2.setPaint(getContentBorderColor());
	    g2.drawLine(x, y + h - 1, x + w - 1, y + h - 1);
	}
    }

    @Override
    protected void paintContentBorderLeftEdge(Graphics g, int tabPlacement,
	int selectedIndex, int x, int y, int w, int h) {

	if (getDrawContentBorder()) {
	    Graphics2D g2 = (Graphics2D)g;
	    g2.setPaint(getContentBorderColor());
	    g2.drawLine(x, y, x, y + h - 1);
	}
    }

    @Override
    protected void paintContentBorderRightEdge(Graphics g, int tabPlacement,
	int selectedIndex, int x, int y, int w, int h) {

	if (getDrawContentBorder()) {
	    Graphics2D g2 = (Graphics2D)g;
	    g2.setPaint(getContentBorderColor());
	    g2.drawLine(x + w - 1, y, x + w - 1, y + h - 1);
	}
    }

    @Override
    protected void paintContentBorderTopEdge(Graphics g, int tabPlacement,
	int selectedIndex, int x, int y, int w, int h) {

        Graphics2D g2 = (Graphics2D)g;

	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	    RenderingHints.VALUE_ANTIALIAS_ON);

	h = CONTENT_TOP_HEIGHT;

	if (h > 0) {
	    Color color = getColor();

	    // Paint the background
	    g2.setPaint(color);
	    g2.fillRect(x, y, w, h - 1);

	    if (h > 2) {
		// Paint a light gradient
		g2.setComposite(AlphaComposite.getInstance(
		    AlphaComposite.SRC_OVER, .25f));
		Paint paint = new GradientPaint(
		    x, y, color, x, y + h - 1, Color.white, false);
		g2.setPaint(paint);
		g2.fillRect(x, y, w, h - 1);

		// Reset alpha
		g2.setPaintMode();
	    }

	    g2.setColor(getBorderColor());

	    // Draw top line
	    if (selectedIndex >= 0) {
		Rectangle selectedRect = getTabBounds(selectedIndex, calcRect);
		int sWidth = selectedRect.width - TAB_GAP - 1;

		g2.drawLine(x, y, selectedRect.x, y);
		g2.drawLine(selectedRect.x + sWidth, y, x + w - 1, y);
	    } else {
		g2.drawLine(x, y, x + w - 1, y);
	    }

	    if (h > 1) {
		// Draw bottom line
		g2.drawLine(x, y + h - 1, x + w - 1, y + h - 1);
	    }
	}
    }

    @Override
    protected void paintFocusIndicator(Graphics g, int tabPlacement,
	Rectangle[] rects, int tabIndex, Rectangle iconRect, Rectangle textRect,
	boolean isSelected) {

        Rectangle tabRect = rects[tabIndex];
	Rectangle tmp = (Rectangle)tabRect.clone();

	tmp.width -= TAB_GAP;
	rects[tabIndex] = tmp;

	super.paintFocusIndicator(
	    g, tabPlacement, rects, tabIndex, iconRect, textRect, isSelected);

	rects[tabIndex] = tabRect;
    }

    @Override
    protected void paintIcon(Graphics g, int tabPlacement,
	int tabIndex, Icon icon, Rectangle iconRect, boolean isSelected) {
        if (icon != null) {
	    Rectangle tmp = (Rectangle)iconRect.clone();

	    // The superclass centers the icon, so restore insets
	    tmp.x -= (tabInsets.right - tabInsets.left) / 2;
	    tmp.y -= (tabInsets.bottom - tabInsets.top) / 2;

	    // The superclass centers the icon, so account for gap
	    tmp.x -= (TAB_GAP + 1) / 2;

	    super.paintIcon(g, tabPlacement, tabIndex, icon, tmp, isSelected);
        }
    }

    @Override
    protected void paintTabBackground(Graphics g, int tabPlacement,
	int tabIndex, int x, int y, int w, int h, boolean isSelected) {

        Graphics2D g2 = (Graphics2D)g;

	Color color = isSelected ? getColor() : getInactiveColor();

	Shape clip = g2.getClip();
	Area aClip = new Area(clip);
	aClip.intersect(new Area(new Rectangle(x, y, w, h)));
	g2.setClip(aClip);

	// Paint the background of the tab
	g2.setColor(color);
	g2.fillRoundRect(x, y, w - TAB_GAP - 1, (3 * h) / 2, TAB_ARC, TAB_ARC);

	// Paint the light (top) gradient of the tab
	g2.setComposite(AlphaComposite.getInstance(
	    AlphaComposite.SRC_OVER, .8f));
	Paint paint = new GradientPaint(
	    x, y, Color.WHITE, x, y + ((float)h / 2f), color, false);
	g2.setPaint(paint);
	g2.fillRoundRect(x, y, w - TAB_GAP - 1, (3 * h) / 2, TAB_ARC, TAB_ARC);

	g2.setClip(clip);
    }

    @Override
    protected void paintTabBorder(Graphics g, int tabPlacement, int tabIndex,
	int x, int y, int w, int h, boolean isSelected) {

        Graphics2D g2 = (Graphics2D)g;

        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
	    RenderingHints.VALUE_ANTIALIAS_ON);

	Shape clip = g2.getClip();
	Area aClip = new Area(clip);
	aClip.intersect(new Area(new Rectangle(x, y, w, h)));
	g2.setClip(aClip);

	g2.setColor(getBorderColor());
	g2.drawRoundRect(x, y, w - TAB_GAP - 1, (3 * h) / 2, TAB_ARC, TAB_ARC);

	// Paint a shadow on the sides
	g2.setComposite(AlphaComposite.getInstance(
	    AlphaComposite.SRC_OVER, .25f));
	g2.setColor(Color.BLACK);
	g2.drawRoundRect(
	    x + 1, y, w - TAB_GAP - 3, (3 * h) / 2, TAB_ARC, TAB_ARC);

	// Reset alpha
	g2.setPaintMode();
	g2.setClip(clip);
    }

    @Override
    protected void paintText(Graphics g, int tabPlacement, Font font,
	FontMetrics metrics, int tabIndex, String title, Rectangle textRect,
	boolean isSelected) {

	Rectangle tmp = (Rectangle)textRect.clone();

	// The superclass centers the text, so restore insets
	tmp.x -= (tabInsets.right - tabInsets.left) / 2;
	tmp.y -= (tabInsets.bottom - tabInsets.top) / 2;

	// The superclass centers the text, so account for gap
	tmp.x -= (TAB_GAP + 1) / 2;

	super.paintText(g, tabPlacement, font, metrics,
	    tabIndex, title, tmp, isSelected);
    }

    //
    // SleekTabbedPaneUI methods
    //

    public Color getBorderColor() {
	return borderColor;
    }

    public Color getContentBorderColor() {
	return contentBorderColor;
    }

    public Color getColor() {
	return color;
    }

    public boolean getDrawContentBorder() {
	return drawContentBorder;
    }

    public Color getInactiveColor() {
	return inactiveColor;
    }

    public void setBorderColor(Color borderColor) {
	this.borderColor = borderColor;
    }

    public void setContentBorderColor(Color contentBorderColor) {
	this.contentBorderColor = contentBorderColor;
    }

    public void setColor(Color color) {
	this.color = color;
    }

    public void setDrawContentBorder(boolean drawContentBorder) {
	this.drawContentBorder = drawContentBorder;
    }

    public void setInactiveColor(Color inactiveColor) {
	this.inactiveColor = inactiveColor;
    }

    //
    // Static methods
    //

    public static ComponentUI createUI(JComponent c) {
	return new SleekTabbedPaneUI();
    }

    public static void main(String[] args) {
	Class[] uis = {
	    null, SleekTabbedPaneUI.class
	};

	int[] placements = {
	    JTabbedPane.TOP,
	    JTabbedPane.LEFT,
	};

	for (int k = 0; k < uis.length; k++) {
	    for (int i = 0; i < placements.length; i++) {
		JTabbedPane tabs = new JTabbedPane();

		if (uis[k] != null) {
		    try {
			tabs.setUI((TabbedPaneUI)uis[k].newInstance());
		    } catch (Throwable e) {
			e.printStackTrace();
		    }
		}

		tabs.setTabPlacement(placements[i]);

		for (int j = 0; j < 5; j++) {
		    tabs.addTab("Tab " + j, new JLabel("Label " + j));
		}

		JFrame frame = new JFrame();
		Container c = frame.getContentPane();
		c.setLayout(new BorderLayout());
		c.add(tabs, BorderLayout.CENTER);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);

		frame.setSize(new Dimension(300, 300));
	    }
	}
    }
}

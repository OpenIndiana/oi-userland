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
import java.awt.event.*;
import java.awt.geom.Area;
import java.util.Vector;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.swing.glass.BlockingGlassPane;

@SuppressWarnings({"serial"})
public class OverlayTable extends ExtTable {
    //
    // Instance data
    //

    private ShadowPanel shadowPanel;
    private JPanel contentPane;
    private JPanel rendererPane;
    private OverlayComponentFactory factory;
    private int vRow = -1;
    private boolean overlaySpansFullWidth = true;

    private ListSelectionListener selectionListener =
	new ListSelectionListener() {
	    @Override
	    public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting()) {
		    hideOverlay();
		} else {
		    int[] rows = getSelectedRows();
		    if (rows.length == 1) {
			if (isEnabled()) {
			    showOverlay(rows[0]);
			}
		    }
		}
	    }
	};

    private MouseListener clickListener =
	new MouseAdapter() {
	    @Override
	    public void mouseClicked(MouseEvent e) {
		if (GUIUtil.isUnmodifiedClick(e, 2)) {
		    int vRow = rowAtPoint(e.getPoint());
		    if (vRow >= 0) {
			if (isEnabled()) {
			    showOverlay(vRow);
			}
		    }
		}
	    }
	};

    //
    // Constructors
    //

    public OverlayTable() {
	init();
    }

    public OverlayTable(int numRows, int numColumns) {
	super(numRows, numColumns);
	init();
    }

    public OverlayTable(Object[][] rowData, Object[] columnNames) {
	super(rowData, columnNames);
	init();
    }

    public OverlayTable(TableModel model) {
	super(model);
	init();
    }

    public OverlayTable(TableModel model, TableColumnModel cModel) {
	super(model, cModel);
	init();
    }

    public OverlayTable(TableModel model, TableColumnModel cModel,
	ListSelectionModel sModel) {

	super(model, cModel, sModel);
	init();
    }

    public OverlayTable(Vector rowData, Vector columnNames) {
	super(rowData, columnNames);
	init();
    }

    //
    // Container methods
    //

    @Override
    public void doLayout() {
	super.doLayout();

	if (vRow != -1) {
	    Dimension tSize = getSize();
	    shadowPanel.setBounds(0, 0, tSize.width, tSize.height);

	    // Build renderer pane bounds
	    Rectangle rBounds = getCellRect(vRow, 0, true);
	    int rowHeight = rBounds.height;

	    rBounds.height = rendererPane.getPreferredSize().height + rowHeight;

	    Dimension cPrefSize = contentPane.getPreferredSize();

	    // Renderer pane overlaps the content pane's left border
	    Insets cInsets = contentPane.getInsets();
	    rBounds.width += cInsets.left;

	    // Build content pane bounds
	    Rectangle cBounds = getCellRect(vRow, 1, true);

	    // Adjust bounds to align with vertical grid line
	    rBounds.width--;
	    cBounds.x--;
	    cBounds.width++;

	    // Span the remaining width of the table
	    cBounds.width = tSize.width - cBounds.x;
	    if (!overlaySpansFullWidth) {
		cBounds.width = Math.min(cBounds.width, cPrefSize.width);
	    }

	    // Use preferred height, adjust downward if necessary
	    cBounds.height = Math.min(cPrefSize.height, tSize.height);

	    // At least as high as the renderer pane
	    cBounds.height = Math.max(cBounds.height, rBounds.height);

	    // Do bounds span beyond the bottom of the table?
	    if (rBounds.y + rBounds.height > tSize.height ||
		cBounds.y + cBounds.height > tSize.height) {

		// Align bottom edges instead
		rBounds.y += rowHeight - rBounds.height;
		cBounds.y += rowHeight - cBounds.height;

		// Do bounds span beyond the top of the table?
		if (cBounds.y < 0) {
		    cBounds.y = 0;
		}

		if (rBounds.y < 0) {
		    rBounds.y = 0;
		}
	    }

	    rendererPane.setBounds(rBounds);
	    contentPane.setBounds(cBounds);
	    rendererPane.repaint();
	    contentPane.repaint();

	    repaint();
	}
    }

    //
    // JComponent methods
    //

    @Override
    public boolean isOptimizedDrawingEnabled() {
	return false;
    }

    //
    // OverlayTable methods
    //

    public void configureOverlayOnRowSelection() {
	setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

	ListSelectionModel sModel = getSelectionModel();

	// Ensure listener only added once
	sModel.removeListSelectionListener(selectionListener);
	sModel.addListSelectionListener(selectionListener);
    }

    public void configureOverlayOnDoubleClick() {
	// Ensure listener only added once
	removeMouseListener(clickListener);
	addMouseListener(clickListener);
    }

    protected JPanel getContentPane() {
	return contentPane;
    }

    public OverlayComponentFactory getFactory() {
	return factory;
    }

    public Color getOverlayBackground() {
	return contentPane.getBackground();
    }

    public Border getOverlayBorder() {
	return contentPane.getBorder();
    }

    public Component getOverlayComponent(int vRow) {
	if (factory != null) {
	    return factory.getOverlayComponent(this, vRow);
	}
	return null;
    }

    public boolean getOverlaySpansFullWidth() {
	return overlaySpansFullWidth;
    }

    protected JPanel getRenderPane() {
	return rendererPane;
    }

    public void hideOverlay() {
	if (isOverlayVisible()) {
	    vRow = -1;
	    contentPane.setVisible(false);
	    rendererPane.setVisible(false);
	    revalidate();
	    repaint();
	}
    }

    public boolean isOverlayShadowEnabled() {
	return shadowPanel.isShadowEnabled();
    }

    public boolean isOverlayVisible() {
	return vRow != -1;
    }

    public Component prepareOverlayRenderer(
	TableCellRenderer renderer, int row, int column) {
	Object value = getValueAt(row, column);

	boolean isSelected = false;
	boolean hasFocus = false;

	Component comp = renderer.getTableCellRendererComponent(
	    this, value, isSelected, hasFocus, row, column);

	if (comp instanceof JComponent) {
	    ((JComponent)comp).setOpaque(false);
	}

	return comp;
    }

    public void setFactory(OverlayComponentFactory factory) {
	this.factory = factory;
    }

    public void setOverlayBackground(Color color) {
	contentPane.setBackground(color);
	rendererPane.setBackground(color);
    }

    public void setOverlayBorder(final Border border) {
	Border rendererBorder = border == null ?
	    null : new ClippedBorder(border, true, true, true, false);

	rendererPane.setBorder(rendererBorder);

	Border contentBorder = null;
	if (border != null) {
	    contentBorder = new Border() {
		@Override
		public Insets getBorderInsets(Component c) {
		    return border.getBorderInsets(c);
		}

		@Override
		public boolean isBorderOpaque() {
		    return border.isBorderOpaque();
		}

		@Override
		public void paintBorder(Component c, Graphics g, int x, int y,
		    int width, int height)  {

		    Shape clip = g.getClip();

		    Area newClip = new Area(clip);

		    Rectangle cBounds = c.getBounds();
		    Rectangle rBounds = rendererPane.getBounds();

		    // Account for insets
		    Insets rInsets = rendererPane.getInsets();
		    rBounds.translate(rInsets.left, rInsets.top);
		    rBounds.width -= rInsets.left + rInsets.right;
		    rBounds.height -= rInsets.top + rInsets.bottom;

		    // Translate to clip coordinates
		    rBounds.translate(-cBounds.x, -cBounds.y);

		    newClip.subtract(new Area(rBounds));
		    g.setClip(newClip);

		    border.paintBorder(c, g, x, y, width, height);

		    g.setClip(clip);
		}
	    };
	}

	contentPane.setBorder(contentBorder);
    }

    public void setOverlayShadowEnabled(boolean enabled) {
	shadowPanel.setShadowEnabled(enabled);
    }

    public void setOverlaySpansFullWidth(boolean overlaySpansFullWidth) {
	this.overlaySpansFullWidth = overlaySpansFullWidth;
    }

    public void showOverlay(int vRow) {
	if (vRow != this.vRow) {
	    // Hide any existing overlay
	    hideOverlay();

	    if (vRow != -1) {
		Component oComp = getOverlayComponent(vRow);
		if (oComp != null) {
		    if (oComp.getParent() != contentPane) {
			contentPane.removeAll();
			contentPane.add(oComp, BorderLayout.CENTER);
		    }

		    this.vRow = vRow;
		    contentPane.setVisible(true);
		    rendererPane.setVisible(true);

		    revalidate();
		    repaint();

		    EventQueue.invokeLater(
			new Runnable() {
			    @Override
			    public void run() {
				scrollRectToVisible(contentPane.getBounds());
			    }
			});
		}
	    }
	}
    }

    //
    // Private methods
    //

    private Component getOverlayCellRenderer() {
	TableCellRenderer renderer = getCellRenderer(vRow, 0);
	return prepareOverlayRenderer(renderer, vRow, 0);
    }

    private void init() {
	contentPane = new JPanel();
	contentPane.setLayout(new BorderLayout());
	contentPane.setOpaque(true);

	// Prevent clicks from passing through to table
	BlockingGlassPane.addConsumeEventListeners(contentPane);

	final CellRendererPane cellRendererPane = new CellRendererPane();
	rendererPane = new JPanel() {
	    @Override
	    public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Dimension spacing = getIntercellSpacing();
		Insets insets = getInsets();
		insets.top += spacing.height / 2;
		insets.bottom -= 1 - spacing.height / 2;
		insets.left += spacing.width / 2;
		insets.right -= 1 - spacing.width / 2;

		Dimension cSize = getSize();

		// The amount of space we have to work with
		int cWidth = cSize.width - insets.left - insets.right;
		int cHeight = cSize.height - insets.top - insets.bottom;

		Component renderer = getOverlayCellRenderer();

		cellRendererPane.paintComponent(g, renderer, this, insets.left,
		    insets.top, cWidth, cHeight);
	    }
	};

	rendererPane.setOpaque(true);
	rendererPane.setLayout(new BorderLayout());
	rendererPane.add(cellRendererPane, BorderLayout.CENTER);

	// Prevent clicks from passing through to table
	BlockingGlassPane.addConsumeEventListeners(rendererPane);

	shadowPanel = new ShadowPanel();
	shadowPanel.setLayout(null);
	shadowPanel.setOpaque(false);

	shadowPanel.add(contentPane);
	shadowPanel.add(rendererPane);
	add(shadowPanel);

	Border border = BorderFactory.createLineBorder(Color.BLACK, 1);
	setOverlayBorder(border);

	getColumnModel().addColumnModelListener(
	    new TableColumnModelListener() {
		//
		// TableColumnModelListener methods
		//

		@Override
		public void columnAdded(TableColumnModelEvent e) {
		    revalidateIfOverlayVisible();
		}

		@Override
		public void columnMarginChanged(ChangeEvent e) {
		}

		@Override
		public void columnMoved(TableColumnModelEvent e) {
		    revalidateIfOverlayVisible();
		}

		@Override
		public void columnRemoved(TableColumnModelEvent e) {
		    revalidateIfOverlayVisible();
		}

		@Override
		public void columnSelectionChanged(ListSelectionEvent e) {
		}

		//
		// Private methods
		//

		private void revalidateIfOverlayVisible() {
		    if (isOverlayVisible()) {
			revalidate();
		    }
		}
	    });
    }

    //
    // Static methods
    //

    // XXX Unit test -- remove
    public static void main(String[] args) {
	JFrame f = new JFrame();

	Object[][] data = {
	    new Object[] {"0 0", "0 1", "0 2"},
	    new Object[] {"1 0", "1 1", "1 2"},
	    new Object[] {"2 0", "2 1", "2 2"},
	    new Object[] {"3 0", "3 1", "3 2"},
	    new Object[] {"4 0", "4 1", "4 2"},
	    new Object[] {"5 0", "5 1", "5 2"},
	    new Object[] {"6 0", "6 1", "6 2"},
	    new Object[] {"7 0", "7 1", "7 2"},
	    new Object[] {"8 0", "8 1", "8 2"},
	    new Object[] {"9 0", "9 1", "9 2"},
	    new Object[] {"10 0", "10 1", "10 2"},
	    new Object[] {"11 0", "11 1", "11 2"},
	    new Object[] {"12 0", "12 1", "12 2"},
	    new Object[] {"13 0", "13 1", "13 2"},
	    new Object[] {"14 0", "14 1", "14 2"},
	    new Object[] {"15 0", "15 1", "15 2"},
	    new Object[] {"16 0", "16 1", "16 2"},
	    new Object[] {"17 0", "17 1", "17 2"},
	    new Object[] {"18 0", "18 1", "18 2"},
	    new Object[] {"19 0", "19 1", "19 2"},
	    new Object[] {"20 0", "20 1", "20 2"},
	    new Object[] {"21 0", "21 1", "21 2"},
	};

	DefaultTableModel model = new DefaultTableModel(
	    data, new String[] {"String", "String", "2"});

	final JLabel label = new JLabel("Hello Hello Hello");
	label.setBorder(null);
//	label.setOpaque(true);
	label.setFont(label.getFont().deriveFont(60f));
	label.setForeground(Color.green);
	label.setBackground(Color.yellow);

	OverlayTable t = new OverlayTable(model) {
	    @Override
	    public Component getOverlayComponent(int vRow) {
		return label;
	    }
	};
	t.configureOverlayOnRowSelection();

	t.setOverlayShadowEnabled(true);
//	t.setOverlayBorder(GUIUtil.BORDER_LINE_SHADOW);
//	t.setOverlayBackground(Color.red);
//	t.setBackground(Color.blue.brighter());
//	t.setStripeColor(Color.orange);
//	t.setIntercellSpacing(new Dimension(20, 20));
//	t.setRowHeight(40);
//	t.setGridColor(Color.cyan);
//	t.setShowGrid(true);

	JScrollPane scroll = new JScrollPane(t);

	JPanel c = (JPanel)f.getContentPane();
	c.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
	c.setLayout(new BorderLayout());
	c.add(t.getTableHeader(), BorderLayout.NORTH);
//	c.add(t, BorderLayout.CENTER);
	c.add(scroll, BorderLayout.CENTER);

	f.pack();
//	f.setSize(500, 500);
	f.setVisible(true);
    }
}

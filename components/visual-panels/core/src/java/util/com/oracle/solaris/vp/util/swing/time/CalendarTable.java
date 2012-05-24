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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import java.awt.event.*;
import java.text.DateFormat;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class CalendarTable extends ExtTable {
    //
    // Inner classes
    //

    public static class CellRenderer extends SimpleCellRenderer<Calendar> {
	//
	// Instance data
	//

	private DateFormat format;

	//
	// Constructors
	//

	public CellRenderer() {
	    getTextLabel().setHorizontalAlignment(SwingConstants.CENTER);
	    setLocale(Locale.getDefault());
	}

	//
	// TableCellRenderer methods
	//

	@Override
	public Component getTableCellRendererComponent(JTable table,
	    Object value, boolean isSelected, boolean hasFocus, int row,
	    int col) {

            Calendar cal = null;

            // value may be null if called by some JTable infrastructure
            // routines
            if (value != null) {
                cal = (Calendar)value;
                CalendarTable mTable = (CalendarTable)table;
                CalendarTableModel model = mTable.getModel();
                boolean isInMainRange = model.isInMainRange(cal);

                if (!mTable.getShowOutliers() && !isInMainRange) {
                    cal = null;
                }
            }

	    return super.getTableCellRendererComponent(
		table, cal, isSelected, hasFocus, row, col);
	}

	//
	// Component methods
	//

	@Override
	public void setLocale(Locale locale) {
	    super.setLocale(locale);
	    format = DateFormat.getDateInstance(DateFormat.FULL, locale);
	}

	//
	// SimpleCellRenderer methods
	//

	@Override
	public String getText(Component comp, Calendar cal, boolean isSelected,
	    boolean hasFocus) {
	    return cal == null ? null :
		((CalendarTable)comp).getModel().toString(cal);
	}

	@Override
	public Color getTextForeground(Component comp, Calendar cal,
	    boolean isSelected, boolean hasFocus) {

	    CalendarTable table = (CalendarTable)comp;
	    CalendarTableModel model = table.getModel();
	    boolean isInMainRange = cal == null ? false :
                model.isInMainRange(cal);

	    Color fg;

	    if (isSelected) {
		fg = table.getSelectionForeground();
	    } else {
		fg = table.getForeground();

		if (!isInMainRange) {
		    Color bg = getBackground(comp, cal, isSelected, hasFocus);
		    if (bg == null) {
			bg = table.getBackground();
		    }
		    fg = ColorUtil.blend(fg, bg, .65f);
		}
	    }

	    return fg;
	}

	@Override
	public String getToolTipText(Component comp, Calendar cal,
	    boolean isSelected, boolean hasFocus) {

	    return cal == null ? null : CalendarTableModel.format(format, cal);
	}
    }

    public static class HeaderRenderer extends DefaultTableCellRenderer {
	@Override
	public Component getTableCellRendererComponent(JTable table,
	    Object value, boolean isSelected, boolean hasFocus, int row,
	    int col) {

	    Component comp = super.getTableCellRendererComponent(table, value,
		isSelected, hasFocus, row, col);

	    Color fg = table.getForeground();

	    setOpaque(false);
	    setForeground(fg);
	    setHorizontalAlignment(SwingConstants.CENTER);

	    return comp;
	}
    }

    //
    // Instance data
    //

    private TimeModel timeModel;
    private boolean showOutliers = true;
    private int prefRowHeight;

    //
    // Constructors
    //

    public CalendarTable(CalendarTableModel model) {
	super(model);

	setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

	setCellSelectionEnabled(true);
	setAutoResizeMode(AUTO_RESIZE_OFF);
	setDefaultRenderer(Object.class, new CellRenderer());
	setShowGrid(false);
	setStripeColor(null);

	JTableHeader header = getTableHeader();
	header.setReorderingAllowed(false);
	header.setResizingAllowed(false);
	header.setBackground(getBackground());
	header.setDefaultRenderer(new HeaderRenderer());

	Dimension spacing = new Dimension(5, 5);
	setPreferredRowHeight(getRowHeight() + spacing.height);
	setIntercellSpacing(spacing);

	// Do this last to minimize redundant work
	setAutoFitColumns(ColumnWidthPolicy.EQUAL);

	// Override left/right arrows to move up/down row at ends

	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "select previous cell",
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    incSelection(-1);
		}
	    }, KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0));

	GUIUtil.installKeyBinding(this, JComponent.WHEN_FOCUSED,
	    "select next cell",
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    incSelection(1);
		}
	    }, KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0));

	// Make tab/shift-tab handle focus as most components do
	GUIUtil.setUseStandardFocusTraversalKeys(this, true);
    }

    public CalendarTable() {
	this(new MonthTableModel());
    }

    //
    // Component methods
    //

    @Override
    public Dimension getPreferredSize() {
	Dimension d = super.getPreferredSize();
	d.height = getPreferredRowHeight() * getRowCount();
	return d;
    }

    @Override
    public void setLocale(Locale locale) {
	super.setLocale(locale);

	((CellRenderer)getDefaultRenderer(Object.class)).setLocale(locale);
	getModel().setLocale(locale);
    }

    //
    // Container methods
    //

    /**
     * Overridden to size each row equally, and to fill the table vertically.
     */
    @Override
    public void doLayout() {
	int rowHeight = getHeight() / getRowCount();
	if (rowHeight < 1) {
	    rowHeight = 1;
	}
	setRowHeight(rowHeight);
	super.doLayout();
    }

    //
    // JTable methods
    //

    @Override
    public CalendarTableModel getModel() {
	return (CalendarTableModel)super.getModel();
    }

    //
    // CalendarTable methods
    //

    /**
     * Gets the preferred row height for this {@code CalendarTable}.
     */
    public int getPreferredRowHeight() {
	return prefRowHeight;
    }

    /**
     * Gets a {@code Calendar} encapsulating the selected date in this {@code
     * CalendarTable}.
     *
     * @return	    a {@code Calendar}, or {@code null} if no date is selected
     */
    public Calendar getSelectedCalendar() {
	Calendar cal = null;
	int vRow = getSelectedRow();
	int vCol = getSelectedColumn();
	if (vRow != -1 && vCol != -1) {
	    cal = (Calendar)getValueAt(vRow, vCol);
	}
	return cal;
    }

    /**
     * Selects the given {@code Calendar} in the model.
     *
     * @exception   NoSuchElementException
     *		    if the given {@code Calendar} does not exist in the model
     */
    public void setSelectedCalendar(Calendar cal) {
	Point mPos = getModel().getPosition(cal);

	if (mPos == null) {
	    throw new NoSuchElementException("not in model: " +
		DateFormat.getDateInstance(DateFormat.FULL, getLocale()).format(
		cal.getTime()));
	}

	int vRow = convertRowIndexToView(mPos.y);
	int vCol = convertColumnIndexToView(mPos.x);

	if (vRow != -1 && vCol != -1 &&
	    (vRow != getSelectedRow() || vCol != getSelectedColumn())) {
	    changeSelection(vRow, vCol, false, false);
	}
    }

    /**
     * Gets whether to display outlying dates that don't occur within the main
     * range of this calendar.
     *
     * @see	    CalendarTableModel#isInMainRange
     */
    public boolean getShowOutliers() {
	return showOutliers;
    }

    /**
     * Sets the preferred row height for this {@code CalendarTable}.  This
     * affects the {@link #getPreferredSize preferred size}, but rows will
     * always be sized to fill the allotted vertical space of the table.
     */
    public void setPreferredRowHeight(int prefRowHeight) {
	this.prefRowHeight = prefRowHeight;
    }

    /**
     * Sets whether to display outlying dates that don't occur within the main
     * range of this calendar.
     *
     * @see	    CalendarTableModel#isInMainRange
     */
    public void setShowOutliers(boolean showOutliers) {
	if (this.showOutliers != showOutliers) {
	    this.showOutliers = showOutliers;
	    repaint();
	}
    }

    //
    // Private methods
    //

    private void incSelection(final int offset) {
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    int vRow = getSelectedRow();
		    int vCol = getSelectedColumn();
		    if (vRow != -1 && vCol != -1) {
			int nRows = getRowCount();
			int nCols = getColumnCount();

			int pos = vRow * nCols + vCol + offset;
			if (pos < 0) {
			    pos = 0;
			} else if (pos >= nRows * nCols) {
			    pos = nRows * nCols - 1;
			}

			int newVRow = pos / nCols;
			int newVCol = pos % nCols;
			if (newVRow != vRow || newVCol != vCol) {
			    ListSelectionModel rsm = getSelectionModel();
			    ListSelectionModel csm =
				getColumnModel().getSelectionModel();

			    rsm.setValueIsAdjusting(true);
			    csm.setValueIsAdjusting(true);
			    changeSelection(newVRow, newVCol, false, false);
			    rsm.setValueIsAdjusting(false);
			    csm.setValueIsAdjusting(false);
			}
		    }
		}
	    });
    }

    //
    // Static methods
    //

    public static void main(String args[]) {
	CalendarTableModel tableModel = new DecadeTableModel();

	CalendarTable table = new CalendarTable(tableModel);

//	table.setSelectionBackground(Color.red);
//	table.setForeground(Color.red.brighter());
//	table.setBackground(Color.blue.darker());
//	table.setLocale(Locale.JAPANESE);
//	tableModel.setFirstDayOfWeek(Calendar.WEDNESDAY);
//	table.setShowOutliers(false);

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(table.getTableHeader(), BorderLayout.NORTH);
	c.add(table, BorderLayout.CENTER);

	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}

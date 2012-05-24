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
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import javax.swing.plaf.TableUI;
import javax.swing.table.*;

/**
 * The {@code ExtTable} class is a {@code JTable} with the following extras:
 *
 * <h4>Striping</h4>
 *
 * The {@code ExtTable} is decorated by default with alternating colored rows:
 * 1) the table's background, and 2) {@link #setStripeColor the stripe color}.
 * To turn this behavior off, call {@link #setStripeColor setStripeColor}{@code
 * (null)}.
 *
 * <h4>Caching</h4>
 *
 * The {@code ExtTable} can optionally cache the values it finds in its
 * {@code TableModel}.	This can speed performance when the model's {@code
 * getValueAt} method is time-consuming.  This feature is off by default, but
 * can be enabled by {@link #setCacheSize setting the size of the cache} to a
 * non-zero number of rows.
 *
 * <h4>Specifiable visible row count</h4>
 *
 * This feature, found in the {@code JList} API, {@link #setVisibleRowCount
 * sets} the preferred number of rows to display without requiring
 * scrolling.  This feature is off by default.
 *
 * <h4>Automatically-sized column widths</h4>
 *
 * Columns in an {@code ExtTable} can be easily sized to fit their content,
 * overriding the constant column widths set by {@code JTable}.  This can be
 * done {@link #fitColumns on demand} or {@link #setAutoFitColumns
 * automatically} whenever the table changes.  This feature is off by default.
 */
@SuppressWarnings({"serial"})
public class ExtTable extends JTable {
    //
    // Enums
    //

    public enum ColumnWidthPolicy {
	/**
	 * Column width is the maximum preferred width of each cell and
	 * header in the column.
	 */
	PREFERRED,

	/**
	 * Columns widths are sized equally, based on the maximum value of all
	 * columns' preferred widths.
	 */
	EQUAL
    }

    //
    // Inner classes
    //

    private static class CachedColumn<T> {
	//
	// Instance data
	//

	public int col;
	public T value;

	//
	// Constructors
	//

	public CachedColumn(int col, T value) {
	    this.col = col;
	    this.value = value;
	}
    }

    private static class CachedRow<T> {
	//
	// Instance data
	//

	public int row;
	public List<CachedColumn<T>> cols = new LinkedList<CachedColumn<T>>();

	//
	// Constructors
	//

	public CachedRow(int row) {
	    this.row = row;
	}
    }

    //
    // Static data
    //

    public static final Color DEFAULT_STRIPE_COLOR =
	new Color(242, 242, 242);
//	new Color(237, 243, 254);

    //
    // Instance data
    //

    private int visibleRowCount = -1;
    private Color stripeColor = DEFAULT_STRIPE_COLOR;

    private List<CachedRow<Object>> valueCache =
	new LinkedList<CachedRow<Object>>();
    private int valueCacheSize = 0;

    private Map<TableColumn, ArrayList<Integer>> widthCache =
	new HashMap<TableColumn, ArrayList<Integer>>();
    private ColumnWidthPolicy colWidthPolicy;

    private TableModelListener modelListener;
    private TableColumnModelListener columnListener;
    private RowSorterListener sorterListener;

    //
    // Constructors
    //

    public ExtTable() {
	init();
    }

    public ExtTable(int numRows, int numColumns) {
	super(numRows, numColumns);
	init();
    }

    public ExtTable(Object[][] rowData, Object[] columnNames) {
	super(rowData, columnNames);
	init();
    }

    public ExtTable(TableModel model) {
	super(model);
	init();
    }

    public ExtTable(TableModel model, TableColumnModel cModel) {
	super(model, cModel);
	init();
    }

    public ExtTable(TableModel model, TableColumnModel cModel,
	ListSelectionModel sModel) {

	super(model, cModel, sModel);
	init();
    }

    public ExtTable(Vector rowData, Vector columnNames) {
	super(rowData, columnNames);
	init();
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	Rectangle clip = g.getClipBounds();
	int rHeight = getRowHeight();
	int fRow = clip.y / rHeight;
	int lRow = (clip.y + clip.height) / rHeight + 1;

	if (isOpaque()) {
	    g.setColor(getBackground());
	    g.fillRect(clip.x, clip.y, clip.width, clip.height);
	}

	if (stripeColor != null) {
	    g.setColor(stripeColor);
	    if ((fRow & 1) == 1) {
		fRow++;
	    }

	    for (int row = fRow; row < lRow; row += 2) {
		g.fillRect(clip.x, rHeight * row, clip.width, rHeight);
	    }
	}

	if (getShowHorizontalLines()) {
	    g.setColor(getGridColor());
	    for (int row = fRow; row < lRow; row++) {
		int y = rHeight * row - 1;
		g.drawLine(clip.x, y, clip.width - 1, y);
	    }
	}

	if (getShowVerticalLines()) {
	    g.setColor(getGridColor());

	    TableColumnModel model = getColumnModel();
	    int x = -1;
	    for (int col = 0, n = model.getColumnCount(); col < n; col++) {
		x += model.getColumn(col).getWidth();

		if (x >= clip.x) {
		    if (x > clip.x + clip.width) {
			break;
		    }
		    g.drawLine(x, clip.y, x, clip.y + clip.height - 1);
		}
	    }
	}

	getUI().paint(g, this);
    }

    //
    // JTable methods
    //

    @Override
    public Dimension getPreferredScrollableViewportSize() {
	if (visibleRowCount < 0) {
	    return super.getPreferredScrollableViewportSize();
	}

	Insets insets = getInsets();
	Dimension d = getPreferredSize();
	d.height = visibleRowCount * getRowHeight() + insets.top +
	    insets.bottom;

	return d;
    }

    @Override
    public Object getValueAt(int vRow, int vCol) {
	if (valueCacheSize > 0) {
	    CachedRow<Object> row = null;
	    ListIterator<CachedRow<Object>> rowIter = valueCache.listIterator();

	    while (rowIter.hasNext()) {
		CachedRow<Object> r = rowIter.next();

		if (r.row == vRow) {
		    row = r;
		    break;
		}

		if (r.row > vRow) {
		    rowIter.previous();
		    break;
		}
	    }

	    if (row == null) {
		row = new CachedRow<Object>(vRow);

		rowIter.add(row);

		if (valueCache.size() > valueCacheSize) {
		    // Trim cached row farthest from the new one
		    int index = rowIter.previousIndex();
		    int lastIndex = valueCache.size() - 1;
		    valueCache.remove(lastIndex - index > index - 0 ?
			lastIndex : 0);
		}
	    }

	    CachedColumn<Object> col = null;
	    ListIterator<CachedColumn<Object>> colIter =
		row.cols.listIterator();

	    while (colIter.hasNext()) {
		CachedColumn<Object> c = colIter.next();

		if (c.col == vCol) {
		    col = c;
		    break;
		}

		if (c.col > vCol) {
		    colIter.previous();
		    break;
		}
	    }

	    if (col == null) {
		Object value = super.getValueAt(vRow, vCol);
		col = new CachedColumn<Object>(vCol, value);
		colIter.add(col);
	    }

	    return col.value;
	}

	return super.getValueAt(vRow, vCol);
    }

    @Override
    public Component prepareRenderer(TableCellRenderer renderer, int row,
        int col) {

        Component comp = super.prepareRenderer(renderer, row, col);
        if (comp instanceof JComponent) {
            ((JComponent)comp).setOpaque(isCellSelected(row, col));
        }

        return comp;
    }

    @Override
    public void setColumnModel(TableColumnModel columnModel) {
	TableColumnModel old = super.getColumnModel();
	if (old != columnModel) {
	    if (columnListener == null) {
		// Create this here since object members haven't yet been
		// initialized if this method is being called from a superclass
		// constructor
		columnListener = new TableColumnModelListener() {
		    @Override
		    public void columnAdded(TableColumnModelEvent e) {
			fitColumnsIfRequested();
		    }

		    @Override
		    public void columnMarginChanged(ChangeEvent e) {
		    }

		    @Override
		    public void columnMoved(TableColumnModelEvent e) {
		    }

		    @Override
		    public void columnRemoved(TableColumnModelEvent e) {
			deleteUnusedColumnsFromWidthCache();
		    }

		    @Override
		    public void columnSelectionChanged(ListSelectionEvent e) {
		    }
		};
	    }

	    if (old != null) {
		old.removeColumnModelListener(columnListener);
	    }

	    if (columnModel != null) {
		columnModel.addColumnModelListener(columnListener);
	    }

	    super.setColumnModel(columnModel);

	    clearWidthCache();
	    fitColumnsIfRequested();
	}
    }

    @Override
    public void setTableHeader(JTableHeader header) {
	JTableHeader old = super.getTableHeader();
	if (old != header) {
	    super.setTableHeader(header);

	    clearWidthCache();
	    fitColumnsIfRequested();
	}
    }

    @Override
    public void setModel(TableModel model) {
	TableModel old = super.getModel();
	if (old != model) {
	    if (modelListener == null) {
		// Create this here since object members haven't yet been
		// initialized if this method is being called from a superclass
		// constructor
		modelListener = new TableModelListener() {
		    @Override
		    public void tableChanged(TableModelEvent e) {
			valueCache.clear();
			updateWidthCache(e);
		    }
		};
	    }

	    if (old != null) {
		old.removeTableModelListener(modelListener);
	    }

	    if (model != null) {
		model.addTableModelListener(modelListener);
	    }

	    super.setModel(model);

	    clearWidthCache();
	    fitColumnsIfRequested();
	}
    }

    @Override
    public void setRowSorter(RowSorter<? extends TableModel> sorter) {
	RowSorter<? extends TableModel> oldSorter = getRowSorter();
	if (sorter != oldSorter) {
	    if (sorterListener == null) {
		// Create this here since object members haven't yet been
		// initialized if this method is being called from a superclass
		// constructor
		sorterListener = new RowSorterListener() {
		    @Override
		    public void sorterChanged(RowSorterEvent e) {
			valueCache.clear();

			switch (e.getType()) {
			case SORT_ORDER_CHANGED:
			    break;

			default:
			case SORTED:
			    fitColumnsIfRequested();
			}
		    }
		};

		if (oldSorter != null) {
		    oldSorter.removeRowSorterListener(sorterListener);
		}

		if (sorter != null) {
		    sorter.addRowSorterListener(sorterListener);
		}
	    }

	    super.setRowSorter(sorter);
	    fitColumnsIfRequested();
	}
    }

    //
    // ExtTable methods
    //

    /**
     * Calculates and sets the preferred widths for each {@code TableColumn} in
     * the {@code TableColumnModel}.
     * <p/>
     * This operation has a performance cost that increases with the number of
     * rows or columns in the table, since each cell must be examined to
     * determine its column's preferred width.	However, this should be a
     * one-time cost, since these values can be cached for subsequent or {@link
     * #setAutoFitColumns automatic} calls to this routine.
     *
     * @param	    colWidthPolicy
     *		    how to automatically fit columns
     *
     * @param	    useCache
     *		    {@code true} to cache and reuse the values, {@code false}
     *		    if this is a one-time operation
     *
     * @see	    #setAutoFitColumns
     */
    public void fitColumns(ColumnWidthPolicy colWidthPolicy, boolean useCache) {
	if (colWidthPolicy == null) {
	    return;
	}

	synchronized (widthCache) {
	    TableModel model = getModel();
	    TableColumnModel cModel = getColumnModel();
	    int cMargin = getColumnModel().getColumnMargin();
	    int nvRows = getRowCount();
	    int maxColWidth = 0;
	    int n = getColumnCount();

	    for (int vCol = 0; vCol < n; vCol++) {
		int mCol = convertColumnIndexToModel(vCol);
		TableColumn column = cModel.getColumn(vCol);

		TableCellRenderer renderer = column.getCellRenderer();
		if (renderer == null) {
		    Class<?> cClass = model.getColumnClass(mCol);
		    renderer = getDefaultRenderer(cClass);
		}

		ArrayList<Integer> colWidthCache = null;

		if (useCache) {
		    colWidthCache = widthCache.get(column);
		    if (colWidthCache == null) {
			colWidthCache = new ArrayList<Integer>(0);
			colWidthCache.ensureCapacity(nvRows);
			for (int i = 0; i < nvRows; i++) {
			    colWidthCache.add(-1);
			}
			widthCache.put(column, colWidthCache);
		    }
		}

		int width = 0;

		for (int vRow = 0; vRow < nvRows; vRow++) {
		    int mRow = convertRowIndexToModel(vRow);
		    int cellWidth = 0;
		    try {
			cellWidth = colWidthCache == null ?
			    -1 : colWidthCache.get(mRow);
		    } catch (IndexOutOfBoundsException ignore) {
			// This method has probably been called (perhaps by the
			// RowSorter) before insertWidthCache could react to a
			// tableChange in the TableModel.  That same change will
			// ultimately make its way to our own modelListener, and
			// this method will be called again (after
			// insertWidthCache has been run) so we can abort now.
			return;
		    }

		    if (cellWidth == -1) {
			Object value = getValueAt(vRow, vCol);

			Component comp = renderer.getTableCellRendererComponent(
			    this, value, true, true, vRow, vCol);

			cellWidth = comp.getPreferredSize().width;

			if (colWidthCache != null) {
			    colWidthCache.set(mRow, cellWidth);
			}
		    }

		    width = Math.max(width, cellWidth);
		}

		// Account for header
		renderer = column.getHeaderRenderer();
		if (renderer == null) {
		    JTableHeader header = getTableHeader();
		    if (header != null) {
			renderer = header.getDefaultRenderer();
		    }
		}

		if (renderer != null) {
		    Object value = column.getHeaderValue();

		    Component comp = renderer.getTableCellRendererComponent(
			this, value, true, true, -1, vCol);

		    int cellWidth = comp.getPreferredSize().width;
		    width = Math.max(width, cellWidth);
		}

		width += cMargin;

		maxColWidth = Math.max(maxColWidth, width);
		setPreferredWidth(column, width);
	    }

	    if (colWidthPolicy == ColumnWidthPolicy.EQUAL) {
		for (int vCol = 0; vCol < n; vCol++) {
		    int mCol = convertColumnIndexToModel(vCol);
		    TableColumn column = cModel.getColumn(vCol);
		    setPreferredWidth(column, maxColWidth);
		}
	    }
	}
    }

    /**
     * Indicates whether {@link #fitColumns} is called automatically whenever
     * the table is changed in a significant way.
     *
     * @return	    how to automatically fit columns, or {@code null} to not
     *		    automatically call {@link #fitColumns}
     */
    public ColumnWidthPolicy getAutoFitColumns() {
	return colWidthPolicy;
    }

    /**
     * Gets the number of rows in the cache of cell values.  A higher value may
     * speed up rendering of the table if the table model must do expensive
     * calculations to determine the value in each cell.
     * <p>
     * The default value is 0, effectively disabling the cache.
     */
    public int getCacheSize() {
	return valueCacheSize;
    }

    public Color getStripeColor() {
	return stripeColor;
    }

    /**
     * Gets the number of rows used to calculate the preferred size of an
     * enclosing viewport.
     *
     * @return	    the number of rows to show in an enclosing viewport, or -1
     *		    to rely on the default calculation for preferred viewport
     *		    size
     */
    public int getVisibleRowCount() {
	return visibleRowCount;
    }

    /**
     * Indicates whether this table has a non-{@code null} {@link
     * #getStripeColor stripe color}.
     */
    public boolean isStriped() {
	return getStripeColor() != null;
    }

    /**
     * Sets whether {@link #fitColumns} is called automatically whenever the
     * table is changed in a significant way.
     *
     * @param	    colWidthPolicy
     *		    how to automatically fit columns, or {@code null} to not
     *		    automatically call {@link #fitColumns}
     */
    public void setAutoFitColumns(ColumnWidthPolicy colWidthPolicy) {
	if (this.colWidthPolicy != colWidthPolicy) {
	    this.colWidthPolicy = colWidthPolicy;
	    fitColumnsIfRequested();
	}
    }

    /**
     * Sets the number of rows in the cache of cell values.  See {@link
     * #getCacheSize}.
     */
    public void setCacheSize(int valueCacheSize) {
	if (this.valueCacheSize != valueCacheSize) {
	    if (this.valueCacheSize > valueCacheSize) {
		try {
		    // Trim if necessary
		    ListIterator<CachedRow<Object>> rowIter =
			valueCache.listIterator(valueCacheSize);

		    while (rowIter.hasNext()) {
			rowIter.next();
			rowIter.remove();
		    }
		} catch (IndexOutOfBoundsException ignore) {
		}
	    }

	    this.valueCacheSize = valueCacheSize;
	}
    }

    public void setStripeColor(Color stripeColor) {
	if (this.stripeColor != stripeColor) {
	    this.stripeColor = stripeColor;
	    repaint();
	}
    }

    /**
     * Sets the number of rows used to calculate the preferred size of an
     * enclosing viewport.
     *
     * @param	    visibleRowCount
     *		    the number of rows to show in an enclosing viewport, or -1
     *		    to rely on the default calculation for preferred viewport
     *		    size
     */
    public void setVisibleRowCount(int visibleRowCount) {
	this.visibleRowCount = visibleRowCount;
    }

    //
    // Private methods
    //

    private void init() {
	setTableHeader(new ExtTableHeader(getColumnModel()));
	setFillsViewportHeight(true);

	addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mousePressed(MouseEvent e) {
		    int vRow = rowAtPoint(e.getPoint());
		    if (vRow == -1) {
			clearSelection();
		    }
		}
	    });

	setShowHorizontalLines(false);
	setShowVerticalLines(true);

	// Accommodate a 16-pixel icon + a 1-pixel focus border
	setRowHeight(18);
    }

    private void clearWidthCache() {
	if (widthCache != null) {
	    synchronized (widthCache) {
		widthCache.clear();
	    }
	}
    }

    private void deleteUnusedColumnsFromWidthCache() {
	TableColumnModel cModel = getColumnModel();
	synchronized (widthCache) {
	    CACHED: for (Iterator<TableColumn> i =
		widthCache.keySet().iterator(); i.hasNext();) {

		TableColumn column = i.next();
		for (int j = 0, n = cModel.getColumnCount(); j < n; j++) {
		    if (cModel.getColumn(j) == column) {
			continue CACHED;
		    }
		}
		i.remove();
	    }
	}
    }

    private void deleteWidthCache(int fmRow, int lmRow) {
	synchronized (widthCache) {
	    for (TableColumn column : widthCache.keySet()) {
		ArrayList<Integer> colWidthCache = widthCache.get(column);
		for (int mRow = lmRow; mRow >= fmRow; mRow--) {
		    colWidthCache.remove(mRow);
		}
	    }
	}
    }

    private void fitColumnsIfRequested() {
	if (colWidthPolicy != null) {
	    fitColumns(colWidthPolicy, true);
	}
    }

    private void insertWidthCache(int fmRow, int lmRow) {
	synchronized (widthCache) {
	    for (TableColumn column : widthCache.keySet()) {
		ArrayList<Integer> colWidthCache = widthCache.get(column);
		for (int mRow = fmRow; mRow <= lmRow; mRow++) {
		    colWidthCache.add(mRow, -1);
		}
	    }
	}
    }

    private void resetWidthCache(int fmRow, int lmRow, int fmCol, int lmCol) {
	synchronized (widthCache) {
	    TableColumnModel cModel = getColumnModel();

	    for (int mCol = fmCol; mCol <= lmCol; mCol++) {
		int vCol = convertColumnIndexToView(mCol);
		TableColumn column = cModel.getColumn(vCol);

		ArrayList<Integer> colWidthCache = widthCache.get(column);
		if (colWidthCache != null) {
		    for (int mRow = fmRow; mRow <= lmRow; mRow++) {
			try {
			    colWidthCache.set(mRow, -1);
			} catch (IndexOutOfBoundsException ignore) {
			}
		    }
		}
	    }
	}
    }

    private void setPreferredWidth(TableColumn column, int width) {
	column.setPreferredWidth(width);
	column.setMinWidth(Math.min(column.getMinWidth(), width));
    }

    private void updateWidthCache(TableModelEvent e) {
	synchronized (widthCache) {
	    int fmRow = e.getFirstRow();
	    int lmRow = e.getLastRow();

	    int nRows = getModel().getRowCount();
	    if (lmRow >= nRows) {
		lmRow = nRows - 1;
	    }

	    switch (e.getType()) {
	    case TableModelEvent.UPDATE:
		int fmCol = e.getColumn();
		int lmCol = fmCol;

		if (fmCol == TableModelEvent.ALL_COLUMNS) {
		    fmCol = 0;
		    lmCol = getColumnModel().getColumnCount() - 1;
		}

		resetWidthCache(fmRow, lmRow, fmCol, lmCol);
		break;


	    case TableModelEvent.DELETE:
		deleteWidthCache(fmRow, lmRow);
		break;

	    case TableModelEvent.INSERT:
		insertWidthCache(fmRow, lmRow);
		break;
	    }

	    fitColumnsIfRequested();
	}
    }

    //
    // Static methods
    //

    // XXX Unit test -- remove
    public static void main(String[] args) {
	JFrame f = new JFrame();

	JPanel c = (JPanel)f.getContentPane();
	c.setLayout(new BorderLayout());
	c.setBorder(GUIUtil.getEmptyBorder());

	Object[][] data = {
	    new Object[] {"0 zero", "0 zero", "blah"},
	    new Object[] {"1 one", "1 one", "blah"},
	    new Object[] {"2 two", "2 two", "blah"},
	    new Object[] {"3 three", "3 three", "blah"},
	    new Object[] {"4 four", "4 four", "blah"},
	    new Object[] {"5 five", "5 five", "blah"},
	};

	final DefaultTableModel model = new DefaultTableModel(
	    data, new String[] {"Column 0", "Column 1", "Column 2"});

	final ExtTable t = new ExtTable(model);
	t.setAutoFitColumns(ColumnWidthPolicy.PREFERRED);
//	t.setOpaque(false);
//	t.setBackground(Color.green);
//	t.setStripeColor(null);
//	t.setShowGrid(true);

	t.addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mouseClicked(MouseEvent e) {
		    if (e.getButton() == 3) {
			Point p = e.getPoint();
			int vCol = t.columnAtPoint(p);
			int mCol = t.convertColumnIndexToModel(vCol);

			Object[] row = {"new", "new", "new"};
			row[mCol] = "loooooooooooooooooooooooooong";
			model.addRow(row);
		    } else

		    if (e.getButton() == 2) {
			Point p = e.getPoint();
			int vRow = t.rowAtPoint(p);
			int mRow = t.convertRowIndexToModel(vRow);
			model.removeRow(mRow);
		    }
		}
	    });

	JScrollPane scroll = new ExtScrollPane(t);
	c.add(scroll, BorderLayout.CENTER);

	JButton b = new JButton("Remove column");
	b.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    TableColumn column = t.getColumnModel().getColumn(1);
		    System.out.printf("Removing column: %s\n",
			column.getIdentifier());
		    t.removeColumn(column);
		}
	    });
	c.add(b, BorderLayout.SOUTH);

	f.pack();
	f.setVisible(true);
    }
}

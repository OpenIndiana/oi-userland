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
import java.awt.event.MouseEvent;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.swing.ExtTable;

@SuppressWarnings({"serial"})
public class TreeTable extends ExtTable {
    //
    // Instance data
    //

    protected class RenderPanel extends JPanel {
	//
	// Instance data
	//

	private TreeLines lines;

	//
	// Constructors
	//

	public RenderPanel(TreeLines lines) {
	    super(new BorderLayout());
	    this.lines = lines;
	    setBackground(UIManager.getColor("Table.selectionBackground"));
	    setOpaque(false);
	}

	//
	// Component methods
	//

	@Override
	public boolean isEnabled() {
	    try {
		return getComponent(1).isEnabled();
	    } catch (IndexOutOfBoundsException e) {
		return false;
	    }
	}

	@Override
	public void setEnabled(boolean enabled) {
	    try {
		getComponent(1).setEnabled(enabled);
	    } catch (IndexOutOfBoundsException ignore) {
	    }
	}

	//
	// RenderPanel methods
	//

	public TreeLines getTreeLines() {
	    return lines;
	}

	public void setComponent(Component c) {
	    removeAll();
	    add(lines, BorderLayout.WEST);
	    add(c, BorderLayout.CENTER);
	}
    }

    //
    // Static data
    //

    private RowFilter<TreeTableModelAdapter, Integer> ROOT_VISIBLE_FILTER =
	new RowFilter<TreeTableModelAdapter, Integer>() {
	    @Override
	    public boolean include(RowFilter.Entry<
		? extends TreeTableModelAdapter, ? extends Integer> entry) {

		if (isRootVisible()) {
		    return true;
		}

		int index = entry.getIdentifier();
		ModelRowData row = entry.getModel().getRow(index);

		return row.getLevel() != 0;
	    }
	};

    private RowFilter<TreeTableModelAdapter, Integer>
	ANCESTOR_COLLAPSED_FILTER =
	new RowFilter<TreeTableModelAdapter, Integer>() {
	    @Override
	    public boolean include(RowFilter.Entry<
		? extends TreeTableModelAdapter, ? extends Integer> entry) {

		TreeTableModelAdapter adapter = entry.getModel();
		int index = entry.getIdentifier();
		ModelRowData row = adapter.getRow(index);

		ModelRowData parent = adapter.getParent(row);
		while (parent != null) {
		    if (!parent.isExpanded()) {
			return false;
		    }
		    parent = adapter.getParent(parent);
		}

		return true;
	    }
	};

    //
    // Instance data
    //

    private List<ViewRowData> rowData = new ArrayList<ViewRowData>();

    private TreeLines renderTreeLines = new TreeLines(this);
    private RenderPanel renderPanel = new RenderPanel(renderTreeLines);

    private TreeLines editorTreeLines = new TreeLines(this);
    private RenderPanel editPanel = new RenderPanel(editorTreeLines);

    private boolean rootVisible = true;
    private boolean turnerPressed;

    private List<RowFilter<TreeTableModelAdapter, Integer>> filters =
	new ArrayList<RowFilter<TreeTableModelAdapter, Integer>>();

    //
    // Constructors
    //

    public TreeTable(TreeTableModel model) {
	super(new TreeTableModelAdapter(model));

	// Set up sorting
	setAutoCreateRowSorter(false);

	final TableRowSorter<TreeTableModelAdapter> sorter =
	    new TableRowSorter<TreeTableModelAdapter>(getModel());

	// By default, sorting is disabled
	for (int i = 0, n = model.getColumnCount(); i < n; i++) {
	    sorter.setSortable(i, false);
	}

	getColumnModel().addColumnModelListener(
	    new TableColumnModelListener() {
		@Override
		public void columnAdded(TableColumnModelEvent e) {
		    sorter.setSortable(e.getToIndex(), false);
		}

		@Override
		public void columnMarginChanged(ChangeEvent e) {
		}

		@Override
		public void columnMoved(TableColumnModelEvent e) {
		}

		@Override
		public void columnRemoved(TableColumnModelEvent e) {
		}

		@Override
		public void columnSelectionChanged(ListSelectionEvent e) {
		}
	    });

	sorter.setRowFilter(
	    new RowFilter<TreeTableModelAdapter, Integer>() {
		@Override
		public boolean include(
		    RowFilter.Entry<? extends TreeTableModelAdapter,
		    ? extends Integer> entry) {

		    synchronized (filters) {
			for (RowFilter<TreeTableModelAdapter, Integer> filter :
			    filters) {

			    if (!filter.include(entry)) {
				return false;
			    }
			}
			return true;
		    }
		}
	    });
	addRowFilter(ROOT_VISIBLE_FILTER);
	addRowFilter(ANCESTOR_COLLAPSED_FILTER);

	setRowSorter(sorter);
    }

    //
    // Component methods
    //

    @Override
    protected void processMouseEvent(MouseEvent e) {
	if (e.getButton() == 1) {
	    switch (e.getID()) {
		case MouseEvent.MOUSE_PRESSED:
		    Point p = e.getPoint();
		    int vRow = rowAtPoint(p);
		    if (vRow != -1) {
			int vCol = columnAtPoint(p);
			int mCol = convertColumnIndexToModel(vCol);
			TreeTableModelAdapter adapter = getModel();
			if (adapter.getTreeTableModel().isTreeColumn(mCol)) {

			    Rectangle cellRect = getCellRect(vRow, vCol, false);
			    Point relPoint = new Point(
				p.x - cellRect.x, p.y - cellRect.y);

			    ViewRowData data = getRowData(vRow);
			    renderTreeLines.setRowData(data);

			    if (renderTreeLines.isOverTurner(relPoint)) {
//				TableCellEditor editor =
//				    getTable().getCellEditor();
//				if (editor != null) {
//				    editor.stopCellEditing();
//				}

				ModelRowData row = data.getModelRow();
				row.setExpanded(!row.isExpanded());
				((TableRowSorter)getRowSorter()).sort();
				turnerPressed = true;
				e.consume();
				return;
			    }
			}
		    }
		    break;

		case MouseEvent.MOUSE_RELEASED:
		    turnerPressed = false;
		    break;
	    }
	}

	super.processMouseEvent(e);
    }

    @Override
    protected void processMouseMotionEvent(MouseEvent e) {
	switch (e.getID()) {
	    case MouseEvent.MOUSE_DRAGGED:
		if (turnerPressed) {
		    e.consume();
		    return;
		}
		break;
	}

	super.processMouseMotionEvent(e);
    }

    //
    // JComponent methods
    //

    @Override
    protected void paintComponent(Graphics g) {
	// This recalculation really should only be done when 1) a sort occurs,
	// 2) the model changes, or 3) the visible rows change.  Lacking hooks
	// into the latter, do it every time.
	synchronized (rowData) {
	    Rectangle clip = getVisibleRect();
	    int rHeight = getRowHeight();
	    int fVRow = clip.y / rHeight;
	    int lVRow = (clip.y + clip.height) / rHeight;
	    lVRow = Math.min(lVRow, getRowCount() - 1);

	    int nVRows = lVRow - fVRow + 1;

	    rowData.clear();

	    TreeTableModelAdapter adapter = getModel();
	    List<Boolean> showLines = null;

	    ViewRowData data = null;
	    for (int vRow = lVRow; vRow >= fVRow; vRow--) {
		data = createRowData(adapter, vRow,
		    data == null ? null : data.getShowLines());

		rowData.add(data);
	    }

	    Collections.reverse(rowData);
	}

	super.paintComponent(g);
    }

    //
    // JTable methods
    //

    @Override
    public TreeTableModelAdapter getModel() {
	return (TreeTableModelAdapter)super.getModel();
    }

    @Override
    public Component prepareEditor(TableCellEditor editor, int vRow, int vCol) {
	Component comp = super.prepareEditor(editor, vRow, vCol);
	return prepare(editPanel, comp, vRow, vCol);
    }

    @Override
    public Component prepareRenderer(TableCellRenderer renderer, int vRow,
	int vCol) {

	Component comp = super.prepareRenderer(renderer, vRow, vCol);
	return prepare(renderPanel, comp, vRow, vCol);
    }

    //
    // TreeTable methods
    //

    public void addRowFilter(RowFilter<TreeTableModelAdapter, Integer> filter) {
	synchronized (filters) {
	    filters.add(filter);
	}
    }

    public TreeLines getEditorTreeLines() {
	return editorTreeLines;
    }

    public TreeLines getRenderTreeLines() {
	return renderTreeLines;
    }

    public boolean isRootVisible() {
	return rootVisible;
    }

    public void removeRowFilter(
	RowFilter<TreeTableModelAdapter, Integer> filter) {

	synchronized (filters) {
	    filters.remove(filter);
	}
    }

    public void setRootVisible(boolean rootVisible) {
	this.rootVisible = rootVisible;
	((TableRowSorter)getRowSorter()).sort();
	repaint();
    }

    //
    // Private methods
    //

    private ViewRowData createRowData(TreeTableModelAdapter adapter, int vRow,
	List<Boolean> templateShowLines) {

	int mRow = convertRowIndexToModel(vRow);
	ModelRowData row = adapter.getRow(mRow);
	int level = row.getLevel();

	// Ensure sufficient size
	List<Boolean> showLines = new ArrayList<Boolean>();
	for (int i = 0; i < level; i++) {
	    Boolean value = null;
	    try {
		value = templateShowLines.get(i);
	    } catch (IndexOutOfBoundsException ignore) {
	    } catch (NullPointerException ignore) {
	    }
	    showLines.add(value);
	}
	showLines.add(null);

	ViewRowData data = new ViewRowData(vRow, row, showLines);

	int nRows = getRowCount();
	for (vRow++; level >= 0 && showLines.get(level) == null; vRow++) {
	    int curLevel = -1;
	    if (vRow < nRows) {
		mRow = convertRowIndexToModel(vRow);
		row = adapter.getRow(mRow);
		curLevel = row.getLevel();
	    }

	    if (curLevel == level) {
		showLines.set(level, true);
		level--;
	    } else

	    if (curLevel < level) {
		for (int i = level; i > curLevel; i--) {
		    showLines.set(level, false);
		    level--;
		}

		if (level != -1) {
		    showLines.set(level, true);
		    level--;
		}
	    }
	}

	return data;
    }

    private ViewRowData getRowData(int vRow) throws IndexOutOfBoundsException {
	synchronized (rowData) {
	    int offset = rowData.get(0).getRow();
	    return rowData.get(vRow - offset);
	}
    }

    private Component prepare(RenderPanel panel, Component comp, int vRow,
	int vCol) {

	TreeTableModelAdapter model = getModel();
	int mCol = convertColumnIndexToModel(vCol);

	if (model.getTreeTableModel().isTreeColumn(mCol)) {
	    try {
		ViewRowData data = getRowData(vRow);
		panel.getTreeLines().setRowData(data);
		panel.setComponent(comp);

		if (isCellSelected(vRow, vCol)) {
		    panel.setOpaque(true);
		    panel.getTreeLines().setForeground(
			UIManager.getColor("Table.selectionForeground"));
		} else {
		    panel.setOpaque(false);
		    panel.getTreeLines().setForeground(null);
		}

		comp = panel;
	    } catch (IndexOutOfBoundsException ignore) {
	    }
	}

	return comp;
    }
}

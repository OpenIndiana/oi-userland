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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class ManagedObjectTable extends ExtTable {
    //
    // Instance data
    //

    private JPopupMenu popup;
    private Action dAction;

    //
    // Constructors
    //

    public ManagedObjectTable(ManagedObjectTableModel model, JPopupMenu popup,
	Action dAction) {

	super(model);

	this.popup = popup;
	setDefaultAction(dAction);

	ListSelectionModel tsModel = new ExtListSelectionModel();
	setSelectionModel(tsModel);
	tsModel.setSelectionMode(
	    ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

	for (int i = 0, n = model.getColumnCount(); i < n; i++) {
	    setCustomRendererEditor(i);
	}

	getColumnModel().addColumnModelListener(
	    new TableColumnModelListener() {
		@Override
		public void columnAdded(TableColumnModelEvent e) {
		    setCustomRendererEditor(e.getToIndex());
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

	// Set up sorting
	setAutoCreateRowSorter(false);

	TableRowSorter<ManagedObjectTableModel> sorter =
	    new TableRowSorter<ManagedObjectTableModel>(model) {

	    @Override
	    public void rowsUpdated(int firstRow, int endRow) {
		super.rowsUpdated(firstRow, endRow);
		// Workaround for 6592461: JTable repaints incorrectly when a
		// RowSorter with setSortsOnUpdate as true is set
		repaint();
	    }
	};

	sorter.setSortsOnUpdates(true);

	for (int i = 0, n = model.getColumnCount(); i < n; i++) {
	    sorter.setSortable(i, model.isSortable(i));
	    sorter.setComparator(i, model.getComparator(i));
	}

	setRowSorter(sorter);

	addMouseListener(
	    new MouseAdapter() {
		//
		// MouseListener methods
		//

		@Override
		public void mouseClicked(MouseEvent e) {
		    final Action dAction = getDefaultAction();

		    // Invoke default action (if non-null) on double-click
		    if (dAction != null && GUIUtil.isUnmodifiedClick(e, 2) &&
			dAction.isEnabled()) {

			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    ActionEvent ae = new ActionEvent(
					ManagedObjectTable.this,
					ActionEvent.ACTION_PERFORMED,
					"default");
				    dAction.actionPerformed(ae);
				}
			    });
		    }
		}

		@Override
		public void mousePressed(final MouseEvent e) {
		    if (e.isPopupTrigger()) {
			// By default, the JTable doesn't select on
			// right-clicks.  If right-clicks are a popup trigger,
			// modify selection before popping up the menu.
			if (e.getButton() == MouseEvent.BUTTON3) {
			    int index = rowAtPoint(e.getPoint());
			    if (index >= 0) {
				ListSelectionModel model = getSelectionModel();
				if (!model.isSelectedIndex(index)) {
				    model.clearSelection();
				    model.setSelectionInterval(index, index);
				};
			    }
			}

			// Invoke later so that events resulting from any
			// change in selection above can be processed before the
			// popup is shown.
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    showPopup(e.getX(), e.getY());
				}
			    });
		    }
		}

		@Override
		public void mouseReleased(final MouseEvent e) {
		    if (e.isPopupTrigger()) {
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    showPopup(e.getX(), e.getY());
				}
			    });
		    }
		}
	    });

	setAutoFitColumns(ColumnWidthPolicy.PREFERRED);
    }

    //
    // JTable methods
    //

    @Override
    public Component prepareRenderer(TableCellRenderer renderer, int vRow,
	int vCol) {

	Component c = super.prepareRenderer(renderer, vRow, vCol);

	boolean enabled = isCellSelected(vRow, vCol);
	if (!enabled) {
	    int mRow = convertRowIndexToModel(vRow);
	    int mCol = convertColumnIndexToModel(vCol);
	    ManagedObjectTableModel model = (ManagedObjectTableModel)getModel();

	    enabled = model.isCellEnabled(mRow, mCol);
	}

	c.setEnabled(enabled);

	return c;
    }

    //
    // ManagedObjectTable methods
    //

    public Action getDefaultAction() {
	return dAction;
    }

    public JPopupMenu getPopupMenu() {
	return popup;
    }

    public void setDefaultAction(Action dAction) {
	this.dAction = dAction;
    }

    public void showPopup(int x, int y) {
	JPopupMenu popup = getPopupMenu();
	if (popup != null) {
	    popup.show(this, x, y);
	}
    }

    //
    // Private methods
    //

    private void setCustomRendererEditor(int col) {
	ManagedObjectTableModel model = (ManagedObjectTableModel)getModel();
	TableColumnModel cModel = getColumnModel();

	TableCellEditor editor = model.getTableCellEditor(col);
	if (editor != null) {
	    cModel.getColumn(col).setCellEditor(editor);
	}

	TableCellRenderer renderer = model.getTableCellRenderer(col);
	if (renderer != null) {
	    cModel.getColumn(col).setCellRenderer(renderer);
	}
    }
}

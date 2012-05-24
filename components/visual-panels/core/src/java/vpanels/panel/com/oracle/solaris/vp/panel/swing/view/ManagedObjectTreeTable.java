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
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.tree.*;

@SuppressWarnings({"serial"})
public class ManagedObjectTreeTable extends TreeTable {
    //
    // Instance data
    //

    private JPopupMenu popup;

    //
    // Constructors
    //

    public ManagedObjectTreeTable(ManagedObjectTreeTableModel model,
	JPopupMenu popup, final Action dAction) {

	super(model);

	this.popup = popup;

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

	addMouseListener(
	    new MouseAdapter() {
		//
		// MouseListener methods
		//

		@Override
		public void mouseClicked(MouseEvent e) {
		    // Invoke default action (if non-null) on double-click
		    if (dAction != null && GUIUtil.isUnmodifiedClick(e, 2) &&
			dAction.isEnabled()) {

			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    ActionEvent ae = new ActionEvent(
					ManagedObjectTreeTable.this,
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
	    TreeTableModelAdapter adapter = getModel();

	    int mRow = convertRowIndexToModel(vRow);
	    int mCol = convertColumnIndexToModel(vCol);

	    ManagedObjectTreeNode node =
		(ManagedObjectTreeNode)adapter.getTreeNode(mRow);

	    ManagedObjectTreeTableModel model =
		(ManagedObjectTreeTableModel)adapter.getTreeTableModel();

	    enabled = model.isCellEnabled(node, mCol);
	}

	c.setEnabled(enabled);

	return c;
    }

    //
    // ManagedObjectTreeTable methods
    //

    public List<ManagedObject> getSelectedObjects() {
        TreeTableModelAdapter adapter = getModel();
        int[] sRows = getSelectedRows();

        List<ManagedObject> objects =
	    new ArrayList<ManagedObject>(sRows.length);

        for (int i = 0; i < sRows.length; i++) {
            int index = convertRowIndexToModel(sRows[i]);
            ManagedObjectTreeNode node =
                (ManagedObjectTreeNode)adapter.getTreeNode(index);
            objects.add(node.getUserObject());
        }

        return objects;
    }

    public JPopupMenu getPopupMenu() {
	return popup;
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
	ManagedObjectTreeTableModel model =
	    (ManagedObjectTreeTableModel)getModel().getTreeTableModel();
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

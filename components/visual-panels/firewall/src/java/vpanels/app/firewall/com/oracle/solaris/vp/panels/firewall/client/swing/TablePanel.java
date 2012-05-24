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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class TablePanel extends JPanel implements DescendantEnabler {
    //
    // Inner classes
    //

    protected class Table extends JTable {
	//
	// Constructors
	//

	public Table(TableModel model) {
	    super(model);

	    setFillsViewportHeight(true);
	    setRowSelectionAllowed(true);
	    getSelectionModel().setSelectionMode(
		ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

	    setShowGrid(false);
	    setDragEnabled(true);
	    setDropMode(DropMode.INSERT_ROWS);

	    ActionMap aMap = getActionMap();

	    // JTable doesn't call cancelCellEditing on a TableCellEditor when
	    // the user hits escape; it simply removes the editor.  Override
	    // this behavior by calling cancelCellEditing directly.
	    // Unfortunately this action name is not publicly exposed by the
	    // API.
	    aMap.put("cancel",
		new AbstractAction() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			Object source = e.getSource();
			if (source instanceof JTable) {
			    JTable table = (JTable)source;
			    TableCellEditor editor = table.getCellEditor();
			    if (editor != null) {
				editor.cancelCellEditing();
			    }
			}
		    }
		});

	    String actionKey = "deleteSelection";

	    getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(
		KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0), actionKey);

	    aMap.put(actionKey,
		new AbstractAction() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			getDeleteButton().doClick(0);
		    }
		});

	    // Setting this property to TRUE would almost work, but wouldn't
	    // allow the Cancel button to cancel an edit.
	    putClientProperty("terminateEditOnFocusLost", Boolean.FALSE);

	    // This isn't a spreadsheet
	    putClientProperty("JTable.autoStartsEdit", Boolean.FALSE);
	}
    }

    //
    // Static data
    //

    private static final String BUTTONS_EDIT = "edit";
    private static final String BUTTONS_ACCEPT = "accept";

    //
    // Instance data
    //

    private boolean enabled = true;
    private JTable table;
    private TableModel tableModel;
    private JButton addButton;
    private JButton editButton;
    private JButton deleteButton;
    private JPanel buttonPanel;
    private JScrollPane scroll;
    private int prevVisRows = -1;

    private ListSelectionListener buttonEnableListener =
	new ListSelectionListener() {
	    @Override
	    public void valueChanged(ListSelectionEvent e) {
		setButtonsEnabledState();
	    }
	};

    //
    // Constructors
    //

    public TablePanel(DefaultTableModel model) {
	setOpaque(false);

	scroll = createTable(model);

	createAddButton();
	createEditButton();
	createDeleteButton();

	// Set initial button states
	setEnabled(true);

	table.getSelectionModel().addListSelectionListener(
	    buttonEnableListener);

	int gap = GUIUtil.getHalfGap();
	RowLayoutConstraint r = new RowLayoutConstraint().setGap(gap);

	JPanel editPanel = new JPanel(new RowLayout());
	editPanel.setOpaque(false);
	editPanel.add(addButton, r);
	editPanel.add(editButton, r);
	editPanel.add(deleteButton, r);

	buttonPanel = new JPanel(new RowLayout());
	buttonPanel.setOpaque(false);
	buttonPanel.add(editPanel, r);

	setLayout(new BorderLayout(gap, gap));
	add(scroll, BorderLayout.CENTER);
	add(buttonPanel, BorderLayout.SOUTH);
    }

    public TablePanel() {
	this(new DefaultTableModel());
    }

    //
    // Component methods
    //

    @Override
    public boolean isEnabled() {
	return enabled;
    }

    @Override
    public void setEnabled(boolean enabled) {
	JTable table = getTable();

	if (enabled != this.enabled) {
	    table.clearSelection();
	}

	for (Component component : getComponents()) {
	    GUIUtil.setEnabledRecursive(component, enabled);
	}

	if (enabled) {
	    // Set appropriate enabled/disabled button status
	    buttonEnableListener.valueChanged(null);
	}

	this.enabled = enabled;
    }

    //
    // TablePanel methods
    //

    protected void createAddButton() {
	addButton = new JButton(Finder.getString("list.button.add"));
    }

    protected void createEditButton() {
	editButton = new JButton(Finder.getString("list.button.edit"));
    }

    protected void createDeleteButton() {
	deleteButton = new JButton(Finder.getString("list.button.delete"));
	deleteButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    JTable table = getTable();
		    int[] selected = table.getSelectedRows();
		    for (int i = 0; i < selected.length; i++)
			selected[i] = table.convertRowIndexToModel(selected[i]);

		    Arrays.sort(selected);
		    DefaultTableModel model =
			(DefaultTableModel) table.getModel();

		    for (int i = selected.length - 1; i >= 0; i--) {
			model.removeRow(selected[i]);
		    }
		}
	    });
    }

    protected JScrollPane createTable(DefaultTableModel model) {
	table = new Table(model);

	JScrollPane scroll = new ExtScrollPane(table,
	    JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
	    JScrollPane.HORIZONTAL_SCROLLBAR_NEVER) {

	    @Override
	    public Dimension getPreferredSize() {
		JTable table = getTable();
		Dimension d = table.getPreferredSize();

		int prefRows = getPreferredVisibleRows();
		if (prefRows >= 0) {
		    d.height -= table.getRowHeight() *
			(table.getRowCount() - getPreferredVisibleRows());
		}

		// XXX Better way?
		d.width += getVerticalScrollBar().getPreferredSize().width * 2;

		return d;
	    }
	};

	scroll.setOpaque(false);
	return scroll;
    }

    public JButton getAddButton() {
	return addButton;
    }

    public JButton getDeleteButton() {
	return deleteButton;
    }

    public JButton getEditButton() {
	return editButton;
    }

    public JPanel getButtonPanel() {
	return buttonPanel;
    }

    public JScrollPane getScrollPane() {
	return scroll;
    }

    public int getPreferredVisibleRows() {
	return prevVisRows;
    }

    public JTable getTable() {
	return table;
    }

    protected void setButtonsEnabledState() {
	JTable table = getTable();
	int[] selected = table.getSelectedRows();
	Arrays.sort(selected);
	boolean isSelected = selected.length != 0;

	editButton.setEnabled(isSelected && selected.length == 1);
	deleteButton.setEnabled(isSelected);
    }

    public void setPreferredVisibleRows(int prevVisRows) {
	if (prevVisRows < 0) {
	    prevVisRows = -1;
	}
	this.prevVisRows = prevVisRows;
    }
}

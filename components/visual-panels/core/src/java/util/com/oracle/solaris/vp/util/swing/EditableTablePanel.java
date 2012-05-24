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
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class EditableTablePanel extends JPanel implements DescendantEnabler {
    //
    // Inner classes
    //

    protected class Table extends ExtTable {
	//
	// Constructors
	//

	public Table(TableModel model) {
	    super(model);

	    setFillsViewportHeight(true);
	    setRowSelectionAllowed(true);
	    getSelectionModel().setSelectionMode(
		ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

	    if (model.getColumnCount() == 1) {
		setStripeColor(null);
		setTableHeader(null);
		setShowVerticalLines(false);
	    }

	    setDragEnabled(true);
	    setDropMode(DropMode.INSERT_ROWS);
	    setTransferHandler(new EditableTableTransferHandler());

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

	//
	// JTable methods
	//

	@Override
	protected void configureEnclosingScrollPane() {
	    // Do nothing
	}

	@Override
	public boolean editCellAt(int row, int column, EventObject e) {
	    boolean success = super.editCellAt(row, column, e);
	    if (success) {
		TableCellEditor editor = getCellEditor();
		if (editor != null) {
		    ((CardLayout)buttonPanel.getLayout()).show(
			buttonPanel, BUTTONS_ACCEPT);
		}
	    }
	    return success;
	}

	@Override
	public Component prepareEditor(
	    TableCellEditor editor, int row, int column) {

	    Component c = super.prepareEditor(editor, row, column);

	    // Make sure there's only one instance
	    c.removeFocusListener(stopEditFocusListener);
	    c.addFocusListener(stopEditFocusListener);

	    return c;
	}

	@Override
	public Component prepareRenderer(
	    TableCellRenderer renderer, int row, int column) {

	    Component c = super.prepareRenderer(renderer, row, column);
	    c.setEnabled(isEnabled());

	    return c;
	}

	@Override
	public void removeEditor() {
	    int row = getEditingRow();
	    int column = getEditingColumn();

	    super.removeEditor();
	    ((CardLayout)buttonPanel.getLayout()).show(
		buttonPanel, BUTTONS_EDIT);
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
    private ExtTable table;
    private JButton moveUpButton;
    private JButton moveDownButton;
    private JButton addButton;
    private JButton editButton;
    private JButton deleteButton;
    private JButton okayButton;
    private JButton cancelButton;
    private JPanel buttonPanel;
    private JScrollPane scroll;

    private ListSelectionListener buttonEnableListener =
	new ListSelectionListener() {
	    @Override
	    public void valueChanged(ListSelectionEvent e) {
		setButtonsEnabledState();
	    }
	};

    private FocusListener stopEditFocusListener =
	new FocusAdapter() {
	    @Override
	    public void focusLost(FocusEvent e) {
		// If the table is in the middle of a cell edit, and the
		// Component that just got focus is not part of this
		// EditableTablePanel, stop the edit.

		TableCellEditor editor = getTable().getCellEditor();
		if (editor != null) {
		    Component c = e.getOppositeComponent();
		    if (c != null) {
			Container parent;
			while ((parent = c.getParent()) != null) {
			    if (parent == EditableTablePanel.this) {
				return;
			    }
			    c = parent;
			}
			editor.stopCellEditing();
		    }
		}
	    }
	};

    //
    // Constructors
    //

    public EditableTablePanel(EditableTableModel model) {
	setOpaque(false);

	scroll = createTable(model);

	createAddButton();
	createEditButton();
	createDeleteButton();
	createOkayButton();
	createCancelButton();
	createMoveDownButton();
	createMoveUpButton();

	// Set initial button states
	setEnabled(true);

	table.getSelectionModel().addListSelectionListener(
	    buttonEnableListener);

	int gap = GUIUtil.getHalfGap();

	JPanel movePanel = new JPanel(new GridLayout(2, 0, 0, gap));
	movePanel.setOpaque(false);
	movePanel.add(moveUpButton);
	movePanel.add(moveDownButton);

	JPanel moveNorthPanel = new JPanel(new BorderLayout());
	moveNorthPanel.setOpaque(false);
	moveNorthPanel.add(movePanel, BorderLayout.NORTH);

	RowLayoutConstraint r = new RowLayoutConstraint().setGap(gap);

	JPanel editPanel = new JPanel(new RowLayout());
	editPanel.setOpaque(false);
	editPanel.add(addButton, r);
	editPanel.add(editButton, r);
	editPanel.add(deleteButton, r);

	JPanel acceptPanel = new JPanel(new RowLayout());
	acceptPanel.setOpaque(false);
	acceptPanel.add(cancelButton, r);
	acceptPanel.add(okayButton, r);

	buttonPanel = new JPanel(new CardLayout());
	buttonPanel.setOpaque(false);
	buttonPanel.add(editPanel, BUTTONS_EDIT);
	buttonPanel.add(acceptPanel, BUTTONS_ACCEPT);

	setLayout(new BorderLayout(gap, gap));
	add(scroll, BorderLayout.CENTER);
	add(moveNorthPanel, BorderLayout.EAST);
	add(buttonPanel, BorderLayout.SOUTH);
    }

    public EditableTablePanel() {
	this(new DefaultEditableTableModel());
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
    // EditableTablePanel methods
    //

    protected void createAddButton() {
	addButton = new JButton(Finder.getString("list.button.add"));
	addButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    JTable table = getTable();
		    final EditableTableModel model =
			(EditableTableModel)table.getModel();

		    final int index = model.getRowCount();
		    Object[] row = model.getTemplateRow();
		    if (model.attemptAddRow(row)) {

			int col = model.getAutoEditedColumn();
			if (col != -1) {

			    table.scrollRectToVisible(
				table.getCellRect(index, col, false));

			    if (table.editCellAt(index, col)) {
				table.getEditorComponent().
				    requestFocusInWindow();

				final CellEditor editor = table.getCellEditor();
				editor.addCellEditorListener(
				    new  CellEditorListener() {
					@Override
					public void editingCanceled(
					    ChangeEvent e) {
					    editor.removeCellEditorListener(
						this);
					    model.removeRow(index);
					}

					@Override
					public void editingStopped(
					    ChangeEvent e) {
					    editor.removeCellEditorListener(
						this);
					}
				    });
			    }
			}
		    }
		}
	    });
    }

    protected void createCancelButton() {
	cancelButton = new JButton(Finder.getString("list.button.cancel"));
	cancelButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    TableCellEditor editor = getTable().getCellEditor();
		    if (editor != null) {
			editor.cancelCellEditing();
		    }
		}
	    });
    }

    protected void createDeleteButton() {
	deleteButton = new JButton(Finder.getString("list.button.delete"));
	deleteButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    JTable table = getTable();
		    int[] selected = table.getSelectedRows();
		    Arrays.sort(selected);

		    EditableTableModel model =
			(EditableTableModel)table.getModel();
		    for (int i = selected.length - 1; i >= 0; i--) {
			model.removeRow(selected[i]);
		    }
		}
	    });
    }

    protected void createEditButton() {
	editButton = new JButton(Finder.getString("list.button.edit"));
	editButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    JTable table = getTable();
		    int row = table.getSelectedRow();

		    if (row != -1) {
			EditableTableModel model =
			    (EditableTableModel)table.getModel();
			int col = model.getAutoEditedColumn();

			if (col != -1) {
			    if (table.editCellAt(row, col)) {
				table.getEditorComponent().
				    requestFocusInWindow();
			    }
			}
		    }
		}
	    });
    }

    protected void createOkayButton() {
	okayButton = new JButton(Finder.getString("list.button.okay"));
	okayButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    TableCellEditor editor = getTable().getCellEditor();
		    if (editor != null) {
			editor.stopCellEditing();
		    }
		}
	    });
    }

    protected void createMoveDownButton() {
	moveDownButton = new JButton(Finder.getString("list.button.movedown"),
	    Finder.getIcon("images/button/movedown.png"));

	moveDownButton.addMouseListener(
	    new MouseHeldHandler() {
		@Override
		public void mouseHeld(MouseEvent e) {
		    JTable table = getTable();
		    int[] selected = table.getSelectedRows();
		    if (selected.length != 0) {
			Arrays.sort(selected);

			if (selected[selected.length - 1] !=
			    table.getRowCount() - 1) {

			    EditableTableModel model =
				(EditableTableModel)table.getModel();

			    for (int i = selected.length - 1; i >= 0; i--) {
				int row = selected[i];
				table.removeRowSelectionInterval(row, row);
				model.moveRow(row, row, row + 1);
				table.addRowSelectionInterval(row + 1, row + 1);
			    }

			    table.scrollRectToVisible(table.getCellRect(
				selected[selected.length - 1] + 1, 0, false));
			}
		    }
		}
	    });
    }

    protected void createMoveUpButton() {
	moveUpButton = new JButton(Finder.getString("list.button.moveup"),
	    Finder.getIcon("images/button/moveup.png"));

	moveUpButton.addMouseListener(
	    new MouseHeldHandler() {
		@Override
		public void mouseHeld(MouseEvent e) {
		    JTable table = getTable();
		    int[] selected = table.getSelectedRows();
		    if (selected.length != 0) {
			Arrays.sort(selected);

			if (selected[0] != 0) {
			    EditableTableModel model =
				(EditableTableModel)table.getModel();

			    for (int i = 0; i < selected.length; i++) {
				int row = selected[i];
				table.removeRowSelectionInterval(row, row);
				model.moveRow(row, row, row - 1);
				table.addRowSelectionInterval(row - 1, row - 1);
			    }

			    table.scrollRectToVisible(table.getCellRect(
				selected[0] - 1, 0, false));
			}
		    }
		}
	    });
    }

    protected JScrollPane createTable(EditableTableModel model) {
	table = new Table(model);
	JScrollPane scroll = new ExtScrollPane(table);
	scroll.setColumnHeaderView(table.getTableHeader());
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

    public JButton getMoveDownButton() {
	return moveDownButton;
    }

    public JButton getMoveUpButton() {
	return moveUpButton;
    }

    public boolean getOrderable() {
	return moveUpButton.isVisible() && moveDownButton.isVisible();
    }

    public JPanel getButtonPanel() {
	return buttonPanel;
    }

    public JScrollPane getScrollPane() {
	return scroll;
    }

    public ExtTable getTable() {
	return table;
    }

    protected void setButtonsEnabledState() {
	JTable table = getTable();
	int[] selected = table.getSelectedRows();
	Arrays.sort(selected);
	boolean isSelected = selected.length != 0;

	moveUpButton.setEnabled(isSelected && selected[0] != 0);

	moveDownButton.setEnabled(isSelected &&
	    selected[selected.length - 1] !=
	    table.getRowCount() - 1);

	editButton.setEnabled(isSelected && selected.length == 1);
	deleteButton.setEnabled(isSelected);
    }

    public void setOrderable(boolean orderable) {
	moveUpButton.setVisible(orderable);
	moveDownButton.setVisible(orderable);
    }

    //
    // Static methods
    //

    // XXX - Remove
    public static void main(String[] args) {
	Object[][] data = {
	    new Object[] {"0 zero"},
	    new Object[] {"1 one"},
	    new Object[] {"2 two"},
	    new Object[] {"3 three"},
	    new Object[] {"4 four"},
	    new Object[] {"5 five"},
	};

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new GridLayout());

	for (int i = 0; i < 2; i++) {
	    DefaultEditableTableModel model = new DefaultEditableTableModel(
		data, new String[] {"String"});

	    EditableTablePanel panel = new EditableTablePanel(model);
	    panel.setEnabled(false);
	    panel.setEnabled(true);
	    c.add(panel);
	}

	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}

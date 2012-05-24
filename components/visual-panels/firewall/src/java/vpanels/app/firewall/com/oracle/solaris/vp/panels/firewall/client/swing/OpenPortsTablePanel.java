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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class OpenPortsTablePanel extends TablePanel implements ActionListener {

    //
    // Inner class
    //

    protected class Entry implements PropertyChangeListener {

	//
	// Instance data
	//

	public JOptionPane pane;
	public JDialog dialog;
	public JPanel formPanel;

	private PortFormatter portFormat;
	private JComboBox protoOption;
	private JFormattedTextField portF1;
	private JFormattedTextField portF2;

	private JLabel protoLabel = new JLabel(
	    Finder.getString("dialog.port.proto.label"));
	private JLabel portRangeLabel = new JLabel(
	    Finder.getString("dialog.port.range.label"));
	private JLabel separator = new JLabel(
	    Finder.getString("dialog.port.range.separator"));

	//
	// Constructor
	//

	public Entry(String label) {
	    protoOption = new JComboBox(options);

	    portFormat = new PortFormatter();
	    portF1 = new JFormattedTextField(portFormat);
	    portF2 = new JFormattedTextField(portFormat);
	    portF1.setColumns(5);
	    portF2.setColumns(5);

	    ActionListener alistener =
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			Object o = e.getSource();
			if (o instanceof JTextField) {
			    pane.setValue(JOptionPane.OK_OPTION);
			    return;
			}
		    }
		};

	    int hGap = GUIUtil.getHalfGap();
	    int sGap = hGap * 2;
	    RowLayoutConstraint r = new RowLayoutConstraint(
		VerticalAnchor.CENTER, hGap);
	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, hGap);
	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    JPanel pPanel = new JPanel();
	    pPanel.setOpaque(false);
	    Form pform = new Form(pPanel, VerticalAnchor.FILL);
	    pform.addRow(HorizontalAnchor.LEFT, c);
	    pform.add(portF1, r);
	    pform.add(separator, r);
	    pform.add(portF2, r);

	    formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.FILL);

	    form.addTable(2, hGap, 1, HorizontalAnchor.LEFT,
		c.clone().setGap(sGap));
	    form.add(protoLabel, a);
	    form.add(portRangeLabel, a);
	    form.add(protoOption, a);
	    form.add(pPanel, a);
	    form.addRow(HorizontalAnchor.LEFT, c);

	    pane = new JOptionPane(formPanel, JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);
	    createDialog(getTable(), label);
	    pane.addPropertyChangeListener(this);
	}

	public void createDialog(Component parentComp, String title)
	    throws HeadlessException {

	    Frame f = JOptionPane.getFrameForComponent(parentComp);
	    dialog = new JDialog(f, title, true);

	    dialog.setComponentOrientation(pane.getComponentOrientation());
	    Container contentPane = dialog.getContentPane();

	    contentPane.setLayout(new BorderLayout());
	    contentPane.add(pane, BorderLayout.CENTER);
	    dialog.setResizable(false);

	    dialog.pack();
	    dialog.setLocationRelativeTo(parentComp);
	    dialog.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
	}

	public void showDialog() {
	    dialog.setVisible(true);
	}

	/**
	 * PropertyChangeListener method
	 *
	 * Validate user input when appropriate
	 */

	public void propertyChange(PropertyChangeEvent e) {
	    String prop = e.getPropertyName();

	    if (dialog.isVisible() && (e.getSource() == pane) &&
		prop.equals(JOptionPane.VALUE_PROPERTY)) {

		Object val = pane.getValue();
		if (val == null) {
		    dialog.setVisible(false);
		    return;
		}

		if (val == JOptionPane.UNINITIALIZED_VALUE)
		    return;

		if (((Integer)val).intValue() != JOptionPane.OK_OPTION) {
		    dialog.setVisible(false);
		    return;
		}

		//
		// Close dialog and continue iff we have valid input
		//
		if (inputCheckValue()) {
		    dialog.setVisible(false);
		} else {
		    // reset value so we can catch the next property change
		    pane.setValue(JOptionPane.UNINITIALIZED_VALUE);
		}
	    }
	}

	public String getSelectedOption() {
	    return ((String) protoOption.getSelectedItem());
	}

	public String getInput() {
	    String text1 = portF1.getText();
	    String text2 = portF2.getText();

	    if (text2.isEmpty() && text1.isEmpty())
		return null;

	    if (!text2.isEmpty() && !text1.isEmpty())
		return (text1 + "-" + text2);
	    else if (!text1.isEmpty())
		return text1;
	    else
		return text2;
	}

	//
	// Obtain input string appropriate for committing to repository
	//
	public String getSavingInput() {
	    // Input text is already verified in inputCheckValue
	    String text1 = portF1.getText();
	    String text2 = portF2.getText();

	    if (text1.isEmpty())
		return text2;

	    if (text2.isEmpty())
		return text1;

	    int p1 = Integer.parseInt(text1);
	    int p2 = Integer.parseInt(text2);
	    return (p1 < p2 ? text1 + "-" + text2 : text2 + "-" + text1);
	}

	public boolean inputCheckValue() {
	    String in = getInput();

	    if (!AccessPolicyUtil.validatePort(in)) {
		GUIUtil.showError(dialog, null, Finder.getString(
		    "port.entry.invalid", in));
		return false;
	    }
	    return true;
	}

	public String getEntry() {
	    String opt = getSelectedOption();
	    String in = getSavingInput();

	    if (opt.equals(TCP_OPT))
		return (TCP_PREFIX.concat(in));
	    else if (opt.equals(UDP_OPT))
		return (UDP_PREFIX.concat(in));
	    else
		return (TCP_UDP_PREFIX.concat(in));
	}

	public void initValue(String v) {
	    if (v.startsWith(TCP_PREFIX)) {
		protoOption.setSelectedIndex(1);
		portSetValue(v.substring(TCP_PREFIX.length()));

	    } else if (v.startsWith(UDP_PREFIX)) {
		protoOption.setSelectedIndex(2);
		portSetValue(v.substring(UDP_PREFIX.length()));

	    } else if (v.startsWith(TCP_UDP_PREFIX)) {
		protoOption.setSelectedIndex(0);
		portSetValue(v.substring(TCP_UDP_PREFIX.length()));
	    }
	}

	private void portSetValue(String str) {
	    String values[] = str.split("\\-");

	    portF1.setValue(values[0].trim());
	    if (values.length > 1)
		portF2.setValue(values[1].trim());
	}
    }


    //
    // Inner column renderer classes
    //

    protected class PortRenderer extends DefaultTableCellRenderer {
	public PortRenderer() {
	    setHorizontalAlignment(SwingConstants.LEFT);
	}
    }

    //
    // Static data
    //

    private static final String TABLE_TITLE =
	Finder.getString("openports.table.title");
    private static final String TCP_COL_TITLE =
	Finder.getString("openports.table.title.tcpcol");
    private static final String UDP_COL_TITLE =
	Finder.getString("openports.table.title.udpcol");
    private static final String PORT_COL_TITLE =
	Finder.getString("openports.table.title.portcol");

    private static final String PORT_ENTRY_REGEX =
	"(tcp|udp)?:(\\d{1,5}){1}(\\s*-\\s*\\d{1,5})?";

    private static final String BUTTONS_EDIT = "edit";

    private static final String TCP_PREFIX = "tcp:";
    private static final String UDP_PREFIX = "udp:";
    private static final String TCP_UDP_PREFIX = ":";

    private static final String ADD_DIALOG_LABEL =
	Finder.getString("dialog.add.entry.label");
    private static final String EDIT_DIALOG_LABEL =
	Finder.getString("dialog.edit.entry.label");

    private static String ADD_CMD = "Add";
    private static String EDIT_CMD = "Edit";

    public static String TCP_OPT = Finder.getString("openports.proto.tcp");
    public static String UDP_OPT = Finder.getString("openports.proto.udp");
    public static String TCP_UDP_OPT = Finder.getString("openports.proto.both");
    public static String[] options = { TCP_UDP_OPT, TCP_OPT, UDP_OPT };

    //
    //
    // Constructors
    //

    public OpenPortsTablePanel() {
	super(new OpenPortsTableModel(new String[0],
	    new String [] {TCP_COL_TITLE, UDP_COL_TITLE, PORT_COL_TITLE}));

	getTable().setAutoCreateRowSorter(true);
	setPreferredVisibleRows(12);
	setColumnsRenderer();
	resetButtonPanel();
    }

    //
    // ActionListener methods
    //

    @Override
    public void actionPerformed(ActionEvent e) {
	String aCmd = e.getActionCommand();

	if (aCmd.equals(ADD_CMD))
	    addEntry();
	else if (aCmd.equals(EDIT_CMD))
	    editEntry();
    }

    //
    // OpenPortsTablePanel methods
    //

    public void clearButtonPanel() {
	getButtonPanel().removeAll();
    }

    public void setColumnsRenderer() {
	JTable table = getTable();
	TableColumnModel model = table.getColumnModel();
	TableColumn column;

	column = model.getColumn(2);
	column.setCellRenderer(new PortRenderer());
	Component r = column.getCellRenderer().getTableCellRendererComponent(
	    table, " 00000-00000 ", false, false, 0, 0);
	column.setPreferredWidth(r.getPreferredSize().width);
    }

    public void resetButtonPanel() {
	clearButtonPanel();
	JButton add = new JButton(Finder.getString("table.button.add"));
	JButton edit =  new JButton(Finder.getString("table.button.edit"));
	add.setActionCommand(ADD_CMD);
	edit.setActionCommand(EDIT_CMD);

	add.addActionListener(this);
	edit.addActionListener(this);

	int gap = GUIUtil.getHalfGap();
	RowLayoutConstraint r = new RowLayoutConstraint().setGap(gap);

	JPanel editPanel = new JPanel(new RowLayout());
	editPanel.setOpaque(false);
	editPanel.add(add, r);
	editPanel.add(edit, r);
	editPanel.add(getDeleteButton(), r);

	getButtonPanel().add(editPanel, r);
    }

    public void addEntry() {
	Entry e = new Entry(ADD_DIALOG_LABEL);
	e.showDialog();

	Object o = e.pane.getValue();
	if (o == null ||
	    ((Integer)o).intValue() == JOptionPane.CLOSED_OPTION ||
	    ((Integer)o).intValue() == JOptionPane.CANCEL_OPTION)
	    return;

	//
	// Add new entry to table
	//
	String entry = e.getEntry();
	if (entry == null || entry.isEmpty())
	    return;

	JTable table = getTable();
	OpenPortsTableModel model = (OpenPortsTableModel)table.getModel();
	int index = model.getRowCount();

	model.addRow(model.getTemplateRow());
	table.scrollRectToVisible(table.getCellRect(index, 0, false));
	model.setValueAt(entry, index);
    }

    public void editEntry() {
	JTable table = getTable();
	int row = table.getSelectedRow();
	if (row == -1)
	    return;

	int modelRow = table.convertRowIndexToModel(table.getSelectedRow());

	//
	// Don't allow to edit malformed entry.
	// User should delete and add new entry instead.
	//
	OpenPortsTableModel model = (OpenPortsTableModel)table.getModel();
	String curEntry = (String) model.getValueAt(modelRow);
	if (!validateEntry(curEntry)) {
	    GUIUtil.showError(getTable(), null,
		Finder.getString("table.entry.invalid", curEntry));
	    return;
	}


	Entry e = new Entry(EDIT_DIALOG_LABEL);
	e.initValue(curEntry);
	e.showDialog();

	Object o = e.pane.getValue();
	if (o == null || ((Integer)o).intValue() == JOptionPane.CANCEL_OPTION)
	    return;

	//
	// Replace existing entry
	//
	String entry = e.getEntry();
	if (entry == null || entry.isEmpty())
	    return;

	table.clearSelection();
	if (!entry.equals(curEntry))
	    model.setValueAt(entry, modelRow);
    }

    private boolean validateEntry(String entry) {
	if (!entry.matches(PORT_ENTRY_REGEX))
	    return false;

	int index = entry.indexOf(":");
	if (index == -1)
	    return (AccessPolicyUtil.validatePort(entry));
	else
	    return (AccessPolicyUtil.validatePort(entry.substring(index + 1)));
    }
}

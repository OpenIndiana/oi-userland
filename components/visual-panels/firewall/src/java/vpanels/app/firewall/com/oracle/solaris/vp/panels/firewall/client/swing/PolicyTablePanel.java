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
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.table.DefaultTableCellRenderer;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.api.network.NetworkMXBean;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class PolicyTablePanel extends EditableTablePanel
    implements ActionListener {

    //
    // Static data
    //

    private static final String BUTTONS_EDIT = "edit";

    private static final String HOST_ADDR_PREFIX = "host:";
    private static final String NET_ADDR_PREFIX = "network:";
    private static final String IF_PREFIX = "if:";

    public static String HOST_LABEL =
	Finder.getString("table.button.host.label");
    public static String NET_LABEL =
	Finder.getString("table.button.net.label");
    public static String IF_LABEL =
	Finder.getString("table.button.interface.label");

    public static String HOST_CMD = "Host";
    public static String NET_CMD = "Network";
    public static String IF_CMD = "Interface";

    private static final String ADD_DIALOG_LABEL =
	Finder.getString("dialog.add.entry.label");
    private static final String EDIT_DIALOG_LABEL =
	Finder.getString("dialog.edit.entry.label");

    private static String ADD_CMD = "Add";
    private static String EDIT_CMD = "Edit";

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

	public JRadioButton hostButton = new JRadioButton(HOST_LABEL);
	public JRadioButton netButton = new JRadioButton(NET_LABEL);
	public JRadioButton ifButton = new JRadioButton(IF_LABEL);

	public HostMaskFormatter fmtHost = new HostMaskFormatter();
	public IPMaskFormatter fmtNet = new IPMaskFormatter();

	public JFormattedTextField hField = new JFormattedTextField(fmtHost);
	public JFormattedTextField nField = new JFormattedTextField(fmtNet);
	public JComboBox iField;

	private Map<JRadioButton, JComponent> bmap;

	//
	// Constructor
	//

	public Entry(String label) {
	    hField.setColumns(10);
	    nField.setColumns(10);
	    iField = new JComboBox(getNetworkInterfaces().toArray());

	    bmap = new HashMap<JRadioButton, JComponent>();
	    bmap.put(hostButton, hField);
	    bmap.put(netButton, nField);
	    bmap.put(ifButton, iField);

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

	    ItemListener iListener =
		new ItemListener() {
		    @Override
		    public void itemStateChanged(ItemEvent e) {
			JRadioButton b = (JRadioButton) e.getItem();
			JComponent c = bmap.get(b);
			if (b.isSelected()) {
			    c.setEnabled(true);
			    c.requestFocus();
			} else {
			    c.setEnabled(false);
			}
		    }
		};

	    hostButton.setActionCommand(HOST_CMD);
	    netButton.setActionCommand(NET_CMD);
	    ifButton.setActionCommand(IF_CMD);

	    ButtonGroup bgroup = new ButtonGroup();
	    bgroup.add(hostButton);
	    bgroup.add(netButton);
	    bgroup.add(ifButton);

	    //
	    // Gray out input fields initially
	    //
	    hField.setEnabled(false);
	    nField.setEnabled(false);
	    iField.setEnabled(false);

	    hostButton.addItemListener(iListener);
	    netButton.addItemListener(iListener);
	    ifButton.addItemListener(iListener);

	    int gap = GUIUtil.getHalfGap();
	    int hGap = gap * 3;
	    int sGap = gap * 2;
	    RowLayoutConstraint r = new RowLayoutConstraint(
		VerticalAnchor.CENTER, gap);
	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, hGap);
	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.FILL);

	    form.addTable(2, gap, gap, HorizontalAnchor.LEFT,
		c.clone().setGap(sGap));
	    form.add(hostButton, a);
	    form.add(hField, a);
	    form.add(netButton, a);
	    form.add(nField, a);
	    form.add(ifButton, a);
	    form.add(iField, a);

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
	 * Before closing dialog, validate user input when appropriate
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

	public JRadioButton getSelected() {
	    JRadioButton b = null;

	    for (Iterator iter = bmap.keySet().iterator(); iter.hasNext(); ) {
		b = (JRadioButton) iter.next();
		if (b.isSelected())
		    break;
	    }
	    return b;
	}

	public String getInput() {
	    Object obj = bmap.get(getSelected());

	    return (obj instanceof JFormattedTextField ?
		((JFormattedTextField)obj).getText() :
		((String) ((JComboBox)obj).getSelectedItem()));
	}

	public boolean inputCheckValue() {
	    String in = getInput();
	    String cmd = getSelected().getActionCommand();
	    boolean ret = true;

	    if (cmd.equals(HOST_CMD) && !validateHostName(in)) {

		ret = false;
		GUIUtil.showError(dialog, null, Finder.getString(
		    "host.entry.invalid", in));

	    } else if (cmd.equals(NET_CMD) &&
		!AccessPolicyUtil.validateSubnetIP(in)) {
		ret = false;
		GUIUtil.showError(dialog, null, Finder.getString(
		    "network.entry.invalid", in));
	    }

	    return ret;
	}

	public List<String> getEntry() {
	    List<String> rvals = new ArrayList<String>();
	    JRadioButton b = getSelected();
	    Object obj = bmap.get(b);

	    String s = (obj instanceof JFormattedTextField ?
		((JFormattedTextField)obj).getText() :
		(String) ((JComboBox)obj).getSelectedItem());

	    String cmd = b.getActionCommand();
	    if (cmd.equals(HOST_CMD)) {
		List<String> IPs = hostGetIPs(s);
		for (int i = 0; i < IPs.size(); i++)
		    rvals.add(HOST_ADDR_PREFIX.concat(IPs.get(i)));

	    } else if (cmd.equals(NET_CMD)) {
		String str = AccessPolicyUtil.cleanSubnet(s);
		if (str != null)
		    rvals.add(NET_ADDR_PREFIX.concat(str));
	    } else
		rvals.add(IF_PREFIX.concat(s));

	    return rvals;
	}

	public void initValue(String v) {
	    if (v.startsWith(HOST_ADDR_PREFIX)) {
		hostButton.setSelected(true);
		JFormattedTextField f =
		    (JFormattedTextField) bmap.get(hostButton);

		String ip = v.substring(HOST_ADDR_PREFIX.length());
		f.setValue(getHostNameForIP(ip));

	    } else if (v.startsWith(NET_ADDR_PREFIX)) {
		netButton.setSelected(true);
		JFormattedTextField f =
		    (JFormattedTextField) bmap.get(netButton);

		f.setValue(v.substring(NET_ADDR_PREFIX.length()));

	    } else {
		ifButton.setSelected(true);
		JComboBox cBox = (JComboBox) bmap.get(ifButton);
		cBox.setSelectedItem(v.substring(IF_PREFIX.length()));
	    }
	}
    }

    //
    // Inner EntryRenderer
    //
    protected class EntryRenderer extends DefaultTableCellRenderer {
	public void setValue(Object value) {

	    if (value == null)
		return;

	    String array[] = ((String) value).split("\\:");
	    if (array.length != 2) {
		setText((String) value);
		setToolTipText((String) value);
		return;
	    }

	    String text, tooltip;

	    // If this is a host entry, try to get a hostname
	    if (((String) value).startsWith(HOST_ADDR_PREFIX)) {
		text = getHostNameForIP(array[1]);
		tooltip = (text.equals(array[1]) ? text :
		    text + "(" + array[1] + ")");

	    } else {
		tooltip = text = array[1];
	    }

	    setIconTextGap(6);
	    if (((String) value).startsWith(HOST_ADDR_PREFIX)) {
		setIcon(Finder.getIcon(
		    "images/server-16.png"));
	    } else if (((String) value).startsWith(NET_ADDR_PREFIX)) {
		setIcon(Finder.getIcon(
		    "images/network-workgroup-16.png"));
	    } else if (((String) value).startsWith(IF_PREFIX)) {
		setIcon(Finder.getIcon(
		    "images/audio-card-16.png"));
	    }

	    setText(text);
	    setToolTipText(tooltip);
	}
    }

    //
    // Instance data
    //

    private FirewallPanelDescriptor descriptor;

    //
    // Constructors
    //

    public PolicyTablePanel(String title) {
	super(new PolicyTableModel());
	addTitle(title);
	resetButtonPanel();
	getTable().setDefaultRenderer(String.class, new EntryRenderer());
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
    // PolicyTablePanel methods
    //

    public void addTitle(String title) {
	ExtScrollPane scroll = (ExtScrollPane) getScrollPane();

	Border empty = BorderFactory.createEmptyBorder();
	Border titled = BorderFactory.createTitledBorder(empty, title);
	scroll.setBorder(titled);
    }

    public void clearButtonPanel() {
	getButtonPanel().removeAll();
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

	getButtonPanel().add(editPanel, BUTTONS_EDIT);
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
	List<String> entry = e.getEntry();
	if (entry.size() == 0)
	    return;

	JTable table = getTable();
	EditableTableModel model = (EditableTableModel)table.getModel();

	int selectStart = model.getRowCount();
	for (int i = 0; i < entry.size(); i++) {
	    int index = model.getRowCount();
	    Object[] row = model.getTemplateRow();

	    if (model.attemptAddRow(row)) {
		table.scrollRectToVisible(table.getCellRect(index, 0, false));
		table.setValueAt(entry.get(i), index, 0);
	    }
	}
	int selectEnd = model.getRowCount() - 1;
	table.setRowSelectionInterval(selectStart, selectEnd);
    }

    public void editEntry() {
	JTable table = getTable();
	int row = table.getSelectedRow();
	if (row == -1)
	    return;

	//
	// Don't allow to edit malformed entry.
	// User should delete and add new entry instead.
	//
	String curEntry = (String) table.getValueAt(row, 0);
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
	List<String> entry = e.getEntry();
	if (entry.size() == 0)
	    return;

	//
	// Edit should only affect one entry, so use the first value in list
	//
	if (!entry.equals(curEntry))
	    table.setValueAt(entry.get(0), row, 0);
    }

    //
    // Methods for interaction with NetworkMXBean from
    // FirewallPanelDescriptor
    //

    public void setPanelDescriptor(FirewallPanelDescriptor descriptor) {
	this.descriptor = descriptor;
    }

    public String getHostNameForIP(String ip) {
	try {
	    return (descriptor == null ? ip :
		descriptor.getNetworkMXBean().getHostNameForIP(ip));
	} catch (ObjectException e) {
	    return ip;
	}
    }

    public List<String> getNetworkInterfaces() {
	try {
	    return descriptor.getNetworkMXBean().getnetworkInterfaces();
	} catch (ObjectException e) {
	    return Collections.emptyList();
	}
    }

    public List<String> hostGetIPs(String hostName) {
	try {
	    return descriptor.getNetworkMXBean().hostGetIPs(hostName);
	} catch (ObjectException e) {
	    return Collections.emptyList();
	}
    }

    public boolean validateHostName(String hostName) {
	return (!hostGetIPs(hostName).isEmpty());
    }

    public boolean validateIF(String iface) {
	return (getNetworkInterfaces().contains(iface));
    }

    //
    // Private methods
    //

    private boolean validateEntry(String entry) {
	boolean rval = false;
	int index;

	if ((index = entry.indexOf(":")) == -1)
	    return false;

	if (entry.startsWith(HOST_ADDR_PREFIX)) {
	    return (AccessPolicyUtil.validateIP(entry.substring(index + 1)));

	} else if (entry.startsWith(NET_ADDR_PREFIX)) {
	    return (AccessPolicyUtil.validateSubnetIP(
		entry.substring(index + 1)));

	} else if (entry.startsWith(IF_PREFIX)) {
	    return (validateIF(entry.substring(index + 1)));

	} else {
	    rval = false;
	}

	return rval;
    }
}

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

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

/**
 * User Manager Basic panel
 */
@SuppressWarnings({"serial"})
public class UserMgrBasicPanel extends SettingsPanel
    implements ActionListener {
    private static final String ACTION_ADV_SETTINGS = "settings";

    //
    // Inner class
    //
    private JLabel nameLabel;
    private JLabel nameField;
    private JLabel uidLabel;
    private JLabel uidField;
    private JLabel descLabel;
    private JTextField findField;
    private JTextField descField;
    private JComboBox groupCombo;
    private HintTextField homeField;
    private JComboBox shellCombo;
    private UserManagedObject umo;
    private AdvancedSettingsDialog advDialog = null;
    private ActionString actString = null;
    ChangeIndicator settingsChange;
    String changepassStr;

    public class PasswordPanel extends LinkCollapsiblePane {

	//
	// Instance data
	//

	private JLabel passLabel;
	private JPasswordField passField;
	private JLabel passConfirmLabel;
	private JPasswordField passConfirmField;

	private MutableProperty<char[]> passProperty =
	    new BasicMutableProperty<char[]>();
	private MutableProperty<char[]> passConfirmProperty =
	    new BasicMutableProperty<char[]>();

	//
	// Constructors
	//

	public PasswordPanel() {
	    super(GUIUtil.getHalfGap());

	    changepassStr = Finder.getString("usermgr.basic.label.changepass");

	    int width = GUIUtil.getTextFieldWidth();
	    actString = new ActionString("usermgr.basic.label.pass");
            passLabel = new JLabel(actString.getString());
            passLabel.setDisplayedMnemonic(actString.getMnemonic());

	    passField = new JPasswordField(width);
	    new PasswordFieldPropertySynchronizer(passProperty, passField);
	    ChangeIndicator passChange = new ChangeIndicator();
	    passProperty.addChangeListener(passChange);
	    passLabel.setLabelFor(passField);

	    actString = new ActionString("usermgr.basic.label.passconfirm");
            passConfirmLabel = new JLabel(actString.getString());
            passConfirmLabel.setDisplayedMnemonic(actString.getMnemonic());

	    passConfirmField = new JPasswordField(width);
	    new PasswordFieldPropertySynchronizer(
		passConfirmProperty, passConfirmField);
	    ChangeIndicator passConfirmChange = new ChangeIndicator();
	    passConfirmProperty.addChangeListener(passConfirmChange);

	    passConfirmLabel.setLabelFor(passConfirmField);

	    // Create the form and the form elements
	    JPanel formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.TOP);

	    int hGap = GUIUtil.getHalfGap();
	    ColumnLayoutConstraint col = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, hGap);
	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    form.addTable(3, hGap, hGap, HorizontalAnchor.LEFT, col);

	    form.add(passLabel, a);
	    form.add(passField, a);
	    form.add(passChange, a);

	    form.add(passConfirmLabel, a);
	    form.add(passConfirmField, a);
	    form.add(passConfirmChange, a);

	    getContentPane().add(formPanel);
	}

	//
	// LinkCollapsiblePane methods
	//

	@Override
	public void setCollapsed(boolean collapsed) {
	    super.setCollapsed(collapsed);

	    if (!collapsed) {
		passField.requestFocusInWindow();
	    }
	}

	@Override
	public String getLinkText(boolean collapsed) {
	    return (changepassStr);
	}

	//
	// PasswordPanel methods
	//

	public MutableProperty<char[]> getPassProperty() {
	    return passProperty;
	}

	public MutableProperty<char[]> getPassConfirmProperty() {
	    return passConfirmProperty;
	}
    }

    //
    // Instance data
    //
    private ChangeableAggregator aggregator;
    private PasswordPanel passPanel;

    private MutableProperty<String> descProperty = new StringProperty();
    private MutableProperty<String> groupProperty = new StringProperty();
    private MutableProperty<String> homeProperty = new StringProperty();
    private MutableProperty<String> shellProperty = new StringProperty();
    private MutableProperty<Boolean> settingsProperty = new BooleanProperty();

    private UserMgrPanelDescriptor descriptor;

    //
    // Constructors
    //

    public UserMgrBasicPanel(UserMgrPanelDescriptor descriptor) {
        this.descriptor = descriptor;
	JPanel form = createForm();
	setContent(form, false, false);

        aggregator = getChangeableAggregator();
	aggregator.addChangeables(descProperty);
	aggregator.addChangeables(groupProperty);
	aggregator.addChangeables(homeProperty);
	aggregator.addChangeables(shellProperty);
	aggregator.addChangeables(settingsProperty);
	aggregator.addChangeables(getPassProperty());
	aggregator.addChangeables(getPassConfirmProperty());
    }

    //
    // UserMgrBasicPanel methods
    //

    public MutableProperty<String> getDescProperty() {
	return descProperty;
    }

    public MutableProperty<String> getGroupProperty() {
	return groupProperty;
    }

    public MutableProperty<String> getHomeProperty() {
	return homeProperty;
    }

    public MutableProperty<String> getShellProperty() {
	return shellProperty;
    }

    public MutableProperty<Boolean> getSettingsProperty() {
	return settingsProperty;
    }

    public MutableProperty<char[]> getPassProperty() {
	return passPanel.passProperty;
    }

    public MutableProperty<char[]> getPassConfirmProperty() {
	return passPanel.passConfirmProperty;
    }

    public void init(UserMgrPanelDescriptor paneldesc, UserManagedObject umo) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();


	this.umo = umo;
	descriptor = paneldesc;

	// Set the current and saved values for each property
	nameField.setText(umo.getName());
	Long uidValue = new Long(umo.getUserId());
	uidField.setText(uidValue.toString());

	descProperty.update(umo.getUserDescProperty().getSavedValue(), false);
	descField.setText(umo.getUserDescription());

	// group
	long gid = umo.getGroupId();
	String gname = null;
	long savedGid = umo.getGroupIdProperty().getSavedValue();
	String savedGname = null;
	if (groupCombo.getItemCount() > 0)
	    groupCombo.removeAllItems();
	for (Group g : descriptor.getGroups()) {
	    groupCombo.addItem(g.getGroupName());
	    if (gid == g.getGroupID())
		gname = g.getGroupName();
	    if (savedGid == g.getGroupID())
		savedGname = g.getGroupName();
	}
	groupProperty.update(savedGname, false);
	groupCombo.setSelectedItem(gname);

	// homedir
 	if (!umo.isNewUser()) {
	    homeField.setText(umo.getHomedir());
 	}
	homeProperty.update(umo.getHomeDirProperty().getSavedValue(), false);

	// shell
	if (shellCombo.getItemCount() > 0)
	    shellCombo.removeAllItems();
	for (String s : descriptor.getShells())
	    shellCombo.addItem(s);
	shellProperty.update(umo.getShellProperty().getSavedValue(), false);
	shellCombo.setSelectedItem(umo.getShell());

	// Password
	getPassProperty().update(umo.getPassProperty().getSavedValue(), false);
	getPassConfirmProperty().update(
	    umo.getPassProperty().getSavedValue(), false);

	if (umo.hasPassword()) {
	    changepassStr = Finder.getString("usermgr.basic.label.changepass");
	} else {
	    changepassStr = Finder.getString("usermgr.basic.label.initialpass");
	}

	passPanel.setCollapsed(true);

	settingsProperty.update(false, true);
    }

    //
    // Private methods
    //

    private JPanel createForm() {
	JPanel form = new JPanel(new GridBagLayout());
	GridBagConstraints gbc = new GridBagConstraints();
	int width = GUIUtil.getTextFieldWidth();
        int hGap = GUIUtil.getHalfGap();

	gbc.weightx = 1.0;
	gbc.anchor = GridBagConstraints.LINE_START;
	gbc.fill = GridBagConstraints.NONE;
	gbc.insets = new Insets(0, 0, hGap, hGap);

	// User name
	actString = new ActionString("usermgr.basic.name." +
	    descriptor.getTypeString());
        nameLabel = new JLabel(actString.getString());

	nameField = new JLabel();

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy = 0;
        form.add(nameLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(nameField, gbc);
	form.add(new Spacer(), gbc);

	// Description
	actString = new ActionString("usermgr.basic.desc." +
	    descriptor.getTypeString());
        descLabel = new JLabel(actString.getString());
        descLabel.setDisplayedMnemonic(actString.getMnemonic());
	descField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextField>(
	    descProperty, descField);
	ChangeIndicator descChange = new ChangeIndicator();
	descProperty.addChangeListener(descChange);

	// Connect the label to the field
	descLabel.setLabelFor(descField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(descLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(descField, gbc);
        form.add(descChange, gbc);

	// User ID
	actString = new ActionString("usermgr.basic.uid." +
	    descriptor.getTypeString());
        uidLabel = new JLabel(actString.getString());
	uidField = new JLabel();

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(uidLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(uidField, gbc);
	form.add(new Spacer(), gbc);

	// Group Name
	actString = new ActionString("usermgr.basic.label.group");
        JLabel groupLabel = new JLabel(actString.getString());
        groupLabel.setDisplayedMnemonic(actString.getMnemonic());
	groupCombo = new JComboBox();
	new ComboBoxPropertySynchronizer<String>(groupProperty, groupCombo);

	for (Group g : descriptor.getGroups()) {
	    groupCombo.addItem(g.getGroupName());
	}
	ChangeIndicator groupChange = new ChangeIndicator();
	groupProperty.addChangeListener(groupChange);

	// Connect the label to the field
	groupLabel.setLabelFor(groupCombo);

	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(groupLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(groupCombo, gbc);
        form.add(groupChange, gbc);

	// Home Directory
	actString = new ActionString("usermgr.basic.label.home");
        JLabel homeLabel = new JLabel(actString.getString());
        homeLabel.setDisplayedMnemonic(actString.getMnemonic());

	homeField = new HintTextField(width);
	homeField.setHintText(Finder.getString("usermgr.new.value.auto"));
	new HintTextPropertySynchronizer<String>(homeProperty, homeField, "");

	ChangeIndicator homeChange = new ChangeIndicator();
	homeProperty.addChangeListener(homeChange);

	// Connect the label to the field
	homeLabel.setLabelFor(homeField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(homeLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(homeField, gbc);
        form.add(homeChange, gbc);

	// Login Shell
	actString = new ActionString("usermgr.basic.label.shell");
        JLabel shellLabel = new JLabel(actString.getString());
        shellLabel.setDisplayedMnemonic(actString.getMnemonic());
	shellCombo = new JComboBox();
	new ComboBoxPropertySynchronizer<String>(shellProperty, shellCombo);
	for (String s : descriptor.getShells())
	    shellCombo.addItem(s);
	ChangeIndicator shellChange = new ChangeIndicator();
	shellProperty.addChangeListener(shellChange);

	// Connect the label to the field
	shellLabel.setLabelFor(shellCombo);

	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(shellLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(shellCombo, gbc);
        form.add(shellChange, gbc);

	// Change Password
	gbc.gridx = 0;
	gbc.gridy++; // next row
	gbc.weightx = 0.0;
	gbc.gridwidth = GridBagConstraints.REMAINDER;
	passPanel = new PasswordPanel();
        form.add(passPanel, gbc);

	// Advanced Settings
	actString = new ActionString("usermgr.advanced.settings");
	JButton advSettings = new JButton(actString.getString());
	advSettings.setActionCommand(ACTION_ADV_SETTINGS);
	advSettings.addActionListener(this);
	advSettings.setMnemonic(actString.getMnemonic());
	settingsChange = new ChangeIndicator();
	settingsProperty.addChangeListener(settingsChange);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++;
	gbc.gridwidth = 1; // GridBagConstraints.RELATIVE;
	gbc.weighty = 1.0;
	gbc.anchor = GridBagConstraints.LAST_LINE_START;
	form.add(advSettings, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
	gbc.gridwidth = 0;
        form.add(settingsChange, gbc);

	return form;
    }

    /**
     * ActionListener for Advanced Settings
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        String actionCmd = e.getActionCommand();
	if (actionCmd == ACTION_ADV_SETTINGS) {
		if (advDialog == null ||
			descriptor.isTypeRole() != advDialog.isTypeRole()) {
		    advDialog = new AdvancedSettingsDialog(this,
			descriptor, umo);
		} else {
			advDialog.setUser(umo);
		}
		advDialog.show();
		if (advDialog.getValue() == JOptionPane.OK_OPTION) {
		    advDialog.update();
		    settingsProperty.setValue(advDialog.isChanged());
		}
	}
    }

    /**
     * Clear the advanced settings change state.
     */
    public void clearChanges() {
        settingsProperty.update(false, true);
    }
}

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
import java.util.List;
import javax.swing.*;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.AddManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.view.ChangeIndicator;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;

/*
 * Add a new user or role
 */

@SuppressWarnings({"serial"})
public class AddUserAction extends AddManagedObjectAction
    <UserManagedObject, AddUserAction.Data, UserManagedObject> {

    private UserManagedObject umo = null;
    private UserImpl user = null;

    //
    // Inner classes
    //

    protected class Data implements ActionListener {
	//
	// Instance data
	//

	private JLabel uidLabel;
	private HintTextField uidField;
	private JLabel descLabel;
	private JComboBox groupCombo;
	private HintTextField homeField;
	private JComboBox shellCombo;
	public MutableProperty<String> typeProperty = new StringProperty();
	public StringProperty nameProperty = new StringProperty();
	public LongProperty uidProperty = new LongProperty();
	public MutableProperty<String> descProperty = new StringProperty();
	public MutableProperty<String> groupProperty = new StringProperty();
	public MutableProperty<String> homeProperty = new StringProperty();
	public MutableProperty<String> shellProperty = new StringProperty();
	public MutableProperty<char[]> passProperty =
	    new BasicMutableProperty<char[]>();
	public MutableProperty<char[]> passConfirmProperty =
	    new BasicMutableProperty<char[]>();

	private JOptionPane pane;
	private JDialog dialog;
        private static final String ACTION_ADV_SETTINGS = "settings";
        private AdvancedSettingsDialog advDialog = null;
	private UserMgrPanelDescriptor descriptor = null;
	private ActionString actString = null;

	//
	// Constructors
	//

	public Data() {
	    pane = new JOptionPane(createForm(), JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);
	    UserMgrUtils.removeIcons(pane);

	    String title = Finder.getString("usermgr.new.title." +
		descriptor.getTypeString());
	    dialog = pane.createDialog(getHasComponent().getComponent(),
		title);
	}

    private JPanel createForm() {
	    ActionListener listener =
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			pane.setValue(JOptionPane.OK_OPTION);
		    }
		};

	descriptor = control.getPanelDescriptor();
	user = descriptor.getDefaultUser();

	JPanel form = new JPanel(new GridBagLayout());
	GridBagConstraints gbc = new GridBagConstraints();
	int width = GUIUtil.getTextFieldWidth();

	gbc.gridx = 0;
	gbc.gridy = 0;
	gbc.weightx = 1.0;
	gbc.anchor = GridBagConstraints.LINE_START;
        int hGap = GUIUtil.getHalfGap();
	gbc.insets = new Insets(0, 0, hGap, hGap);

	// Intro text
	JLabel introLabel = new JLabel(
	Finder.getString("usermgr.new.label." +
		descriptor.getTypeString()));
	form.add(introLabel, gbc);

	// User name
	actString = new ActionString("usermgr.basic.name." +
		descriptor.getTypeString());
        JLabel nameLabel = new JLabel(actString.getString());
        nameLabel.setDisplayedMnemonic(actString.getMnemonic());

	JTextField nameField = GUIUtil.createTextField();
	nameField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String, JTextComponent>
		(nameProperty, nameField, false);

	// Connect the label to the field
	nameLabel.setLabelFor(nameField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(nameLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(nameField, gbc);
	form.add(new Spacer(), gbc);

	// Description
	actString = new ActionString("usermgr.basic.desc." +
		descriptor.getTypeString());
        descLabel = new JLabel(actString.getString());
        descLabel.setDisplayedMnemonic(actString.getMnemonic());
	JTextField descField = GUIUtil.createTextField();
	new TextComponentPropertySynchronizer<String, JTextField>(
	    descProperty, descField);

	// Connect the label to the field
	descLabel.setLabelFor(descField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(descLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(descField, gbc);

	// User ID
	actString = new ActionString("usermgr.basic.uid." +
		descriptor.getTypeString());
        uidLabel = new JLabel(actString.getString());
        uidLabel.setDisplayedMnemonic(actString.getMnemonic());


	uidField = new HintTextField(width);
	uidField.setHintText(
	    Finder.getString("usermgr.new.value.auto"));
	uidField.setDocument(new NumericDocument());
	new HintTextPropertySynchronizer<Long>(uidProperty,
	    uidField, 0L);
	ChangeIndicator uidChange = new ChangeIndicator();
	uidProperty.addChangeListener(uidChange);
	uidProperty.save();
	// uidField.addActionListener(listener);

	// Connect the label to the field
	uidLabel.setLabelFor(uidField);

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
	    if (user.getGroupID() == g.getGroupID()) {
		groupCombo.setSelectedItem(g.getGroupName());
	    }
	}

	// Connect the label to the field
	groupLabel.setLabelFor(groupCombo);

	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(groupLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(groupCombo, gbc);

	// Home Directory
	actString = new ActionString("usermgr.basic.label.home");
        JLabel homeLabel = new JLabel(actString.getString());
        homeLabel.setDisplayedMnemonic(actString.getMnemonic());

	homeField = new HintTextField(width);
	homeField.setHintText(Finder.getString("usermgr.new.value.auto"));
	new HintTextPropertySynchronizer<String>(homeProperty, homeField, "");
	ChangeIndicator homeChange = new ChangeIndicator();
	homeProperty.addChangeListener(homeChange);
	homeProperty.save();

	// Connect the label to the field
	homeLabel.setLabelFor(homeField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(homeLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(homeField, gbc);

	// Login Shell
	actString = new ActionString("usermgr.basic.label.shell");
        JLabel shellLabel = new JLabel(actString.getString());
        shellLabel.setDisplayedMnemonic(actString.getMnemonic());
	shellCombo = new JComboBox();
	new ComboBoxPropertySynchronizer<String>(shellProperty, shellCombo);
	for (String s : descriptor.getShells())
	    shellCombo.addItem(s);

	shellCombo.setSelectedItem(user.getDefaultShell());
	// Connect the label to the field
	shellLabel.setLabelFor(shellCombo);

	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(shellLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(shellCombo, gbc);

	    // Password
	actString = new ActionString("usermgr.basic.label.pass");
        JLabel passLabel = new JLabel(actString.getString());
        passLabel.setDisplayedMnemonic(actString.getMnemonic());

	    JPasswordField passField = new JPasswordField(width);
	    passField.addActionListener(listener);
	new PasswordFieldPropertySynchronizer(passProperty, passField, false);

	// Connect the label to the field
	passLabel.setLabelFor(passField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(passLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(passField, gbc);

	// Password Confirm
	actString = new ActionString("usermgr.basic.label.passconfirm");
        JLabel passConfirmLabel = new JLabel(actString.getString());
        passConfirmLabel.setDisplayedMnemonic(actString.getMnemonic());

	JPasswordField passConfirmField = new JPasswordField(width);
	new PasswordFieldPropertySynchronizer(
		passConfirmProperty, passConfirmField, false);

	// Connect the label to the field
	passConfirmLabel.setLabelFor(passConfirmField);

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(passConfirmLabel, gbc);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(passConfirmField, gbc);

	// Advanced Settings
	actString = new ActionString("usermgr.advanced.settings");
	JButton advSettings = new JButton(actString.getString());
	advSettings.setActionCommand(ACTION_ADV_SETTINGS);
	advSettings.addActionListener(this);
	advSettings.setMnemonic(actString.getMnemonic());

	// Add to the layout
	gbc.gridx = 0;
	gbc.gridy++;
	gbc.gridwidth = GridBagConstraints.REMAINDER;
	gbc.anchor = GridBagConstraints.SOUTHWEST;
	form.add(advSettings, gbc);

	return form;
    }

	/**
	 * action listener for Adv settings button
	 */
        @Override
        public void actionPerformed(ActionEvent e)  {
            String actionCmd = e.getActionCommand();
	    if (actionCmd == ACTION_ADV_SETTINGS) {
		UserMgrPanelDescriptor descriptor =
			control.getPanelDescriptor();
		if (umo == null || user == null) {
		    user = new UserImpl();
		    umo = new UserManagedObject(descriptor, user, null);
		}

		if (advDialog == null ||
		    descriptor.isTypeRole() != advDialog.isTypeRole()) {
		    advDialog = new AdvancedSettingsDialog(
			getHasComponent().getComponent(), descriptor, umo);
		} else {
		    advDialog.setUser(umo);
		}
		advDialog.show();
		if (advDialog.getValue() == JOptionPane.OK_OPTION) {
		    advDialog.update();
    		}
	    }
        }
    }

    //
    // Static data
    //

    private static final String ADD_TEXT = Finder.getString(
	"usermgr.action.add.button");

    //
    // Instance data
    //

    private MainControl control;

    //
    // Constructors
    //

    public AddUserAction(MainControl control) {
	super(ADD_TEXT, null, control);
        ActionString actStr = new ActionString(
	    "usermgr.action.add.button");
	putValue(Action.NAME, actStr.getString());
	putValue(Action.MNEMONIC_KEY, actStr.getMnemonic());
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public Data getRuntimeInput(List<UserManagedObject> selection,
    	Data uData) throws ActionAbortedException {

	// Since this action navigates to the new object once created, we must
	// first navigate to control so that any outstanding changes in the
	// current Control are handled.
	try {
	    control.getNavigator().goToAsyncAndWait(false, control);
	} catch (NavigationException e) {
	    throw new ActionAbortedException(e);
	}

	if (uData == null) {
	    uData = new Data();
	}

	// Blocks until dismissed
	uData.dialog.setVisible(true);

	if (!ObjectUtil.equals(uData.pane.getValue(), JOptionPane.OK_OPTION)) {
	    throw new ActionAbortedException();
	}

	return uData;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public UserManagedObject workBusy(List<UserManagedObject> selection,
	Data uData) throws ActionFailedException,
		ActionAbortedException,
	ActionUnauthorizedException {


	UserMgrPanelDescriptor descriptor = control.getPanelDescriptor();

	String username = uData.nameProperty.getValue();
	UserMgrUtils.validateUsername(descriptor, username);

	String description = uData.descProperty.getValue();
	UserMgrUtils.validateUserDesc(description);

	String group = uData.groupProperty.getValue();
	String shell = uData.shellProperty.getValue();
	String homedir = uData.homeProperty.getValue();

	char[] password = uData.passProperty.getValue();
	char[] password2 = uData.passConfirmProperty.getValue();
	UserMgrUtils.validatePassword(true, password, password2);

	UserMgrUtils.clearPassword(password2);

	user.setUsername(username);
	if (uData.uidProperty.isChanged()) {
	    long uid = uData.uidProperty.getValue();
	    user.setUserID(uid);
	}

	user.setDescription(description);
	user.setDefaultShell(shell);
	user.setHomeDirectory(homedir);

	if (umo == null) {
	    umo = new UserManagedObject(descriptor,
	    user, password);
	} else {
	    umo.setUser(user, password);
	}

	descriptor.addToAddList(umo);
	descriptor.saveAddedUsers();

	// Navigate to the newly created user
	Navigable navigable = new SimpleNavigable(
	    UserMgrBasicControl.ID, umo.getName(),
	    UserMgrBasicControl.PARAM_USER, umo.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return umo;
    }
}

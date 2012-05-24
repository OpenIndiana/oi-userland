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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.List;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.SwingManagedObjectAction;
import com.oracle.solaris.rad.usermgr.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.*;

/**
 * Filter users based on the scope (files or ldap)
 * and type (user or role). The search string provides
 * additional filtering.
 */
@SuppressWarnings({"serial"})
public class FilterUserAction extends SwingManagedObjectAction
    <UserManagedObject, FilterUserAction.Data, UserManagedObject> {

    private UserManagedObject umo = null;
    private UserImpl user = null;

    //
    // Inner classes
    //

    protected class Data { // implements ActionListener
	//
	// Instance data
	//

	private ButtonGroup scopeGroup;
	private ButtonGroup typeGroup;
	private JTextField matchField;
	private JOptionPane pane;
	private JDialog dialog;

	private UserMgrPanelDescriptor descriptor = null;

	public MutableProperty<String> matchProperty = new StringProperty();
	public MutableProperty<String> typeProperty = new StringProperty();


	//
	// Constructors
	//

	public Data()   {
	    pane = new JOptionPane(CreateGui(),
		JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);
	    UserMgrUtils.removeIcons(pane);

	    dialog = pane.createDialog(getHasComponent().getComponent(),
		Finder.getString("usermgr.filter.title"));
	}

        private JPanel CreateGui() {
	    ActionListener listener =
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			pane.setValue(JOptionPane.OK_OPTION);
		    }
		};

	ActionString actString = null;
	JRadioButton scopeButton = null;
	descriptor = control.getPanelDescriptor();
	JPanel form = new JPanel(new GridBagLayout());
	GridBagConstraints gbc = new GridBagConstraints();
	int width = GUIUtil.getTextFieldWidth();

	gbc.gridx = 0;
	gbc.gridy = 0;
	// gbc.weightx = 1.0;
	gbc.fill = GridBagConstraints.REMAINDER;
	gbc.anchor = GridBagConstraints.LINE_START;
        int hGap = GUIUtil.getHalfGap();
	gbc.insets = new Insets(0, 0, hGap, hGap);

	// Label for the dialog
	JLabel introLabel = new JLabel(
	    Finder.getString("usermgr.filter.label"));
	form.add(introLabel, gbc);

	//
	// Scope: files or ldap
	//
        JLabel scopeLabel = new JLabel(
		Finder.getString("usermgr.filter.scope"));
	JPanel scopePanel = new JPanel();

	scopeGroup = new ButtonGroup();
	List<String> scopes = descriptor.getScopes();
	JRadioButton[] buttons = new JRadioButton[scopes.size()];
	for (int i = 0; i < scopes.size(); i++) {
		String scope = scopes.get(i);
		scopeButton = new JRadioButton(scope);
		scopeButton.setActionCommand(scope);
		int mnemonic = scope.toUpperCase().charAt(0);
		scopeButton.setMnemonic(mnemonic);
		scopeGroup.add(scopeButton);
		scopePanel.add(scopeButton);
		buttons[i] = scopeButton;
	}

	// For single scope, disable the button
	if (scopes.size() == 1) {
	    buttons[0].setEnabled(false);
	}

	gbc.gridy++;
	gbc.gridwidth = 1;
	gbc.fill = GridBagConstraints.NONE;
        form.add(scopeLabel, gbc);
	gbc.fill = GridBagConstraints.REMAINDER;
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(scopePanel, gbc);

	//
	// Type: User or Role
	//
        JLabel typeLabel = new JLabel(
		Finder.getString("usermgr.filter.type"));
	JPanel typePanel = new JPanel();

	typeGroup = new ButtonGroup();
	actString = new ActionString("usermgr.filter.type.user");
	JRadioButton userButton = new JRadioButton(actString.getString());
	userButton.setMnemonic(actString.getMnemonic());
        userButton.setSelected(true);
        userButton.setActionCommand("normal");
	typeGroup.add(userButton);
	typePanel.add(userButton);

	actString = new ActionString("usermgr.filter.type.role");
	JRadioButton roleButton = new JRadioButton(actString.getString());
	roleButton.setMnemonic(actString.getMnemonic());
        roleButton.setActionCommand("role");
	typeGroup.add(roleButton);
	typePanel.add(roleButton);

	gbc.gridy++;
	gbc.gridwidth = 1;
	gbc.fill = GridBagConstraints.NONE;
        form.add(typeLabel, gbc);
	gbc.fill = GridBagConstraints.REMAINDER;
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(typePanel, gbc);

	// Match String
	actString = new ActionString("usermgr.filter.match");
	JLabel matchLabel = new JLabel(actString.getString());
	matchLabel.setDisplayedMnemonic(actString.getMnemonic());
	gbc.gridx = 0;
	gbc.gridy++; // next row
        form.add(matchLabel, gbc);

	matchField = GUIUtil.createTextField();
	matchField.addActionListener(listener);
	new TextComponentPropertySynchronizer<String, JTextComponent>
		(matchProperty, matchField, false);

	matchLabel.setLabelFor(matchField);
	gbc.gridx = GridBagConstraints.RELATIVE;
        form.add(matchField, gbc);

	//
	// Start with previously selected filter entries
	//
	if (userButton.getActionCommand().equals(descriptor.getType())) {
	    userButton.setSelected(true);
	} else {
	    roleButton.setSelected(true);
	}
	matchField.setText(descriptor.getMatch());

	for (int j = 0; j < buttons.length; j++) {
	    if (buttons[j].getActionCommand().equals(descriptor.getScope())) {
		buttons[j].setSelected(true);
		break;
	    }
	}

	return form;
    }

    public String getScope() {
    	ButtonModel bm = scopeGroup.getSelection();
	return bm.getActionCommand();
    }

    public String getType() {
    	ButtonModel bm = typeGroup.getSelection();
	return bm.getActionCommand();
    }

    public String getString() {
	return matchField.getText();
    }
    }

    //
    // Static data
    //

    private static final String FILTER_TEXT = Finder.getString(
	"usermgr.action.filter.button");

    //
    // Instance data
    //

    private MainControl control;

    //
    // Constructors
    //

    public FilterUserAction(MainControl control) {
	super(FILTER_TEXT, null, control);
        ActionString actStr = new ActionString(
	    "usermgr.action.filter.button");
	putValue(Action.NAME, actStr.getString());
	putValue(Action.MNEMONIC_KEY, actStr.getMnemonic());
	// putValue(Action.MNEMONIC_KEY, KeyEvent.VK_F);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    // @Override
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

    // @Override
    public UserManagedObject workBusy(List<UserManagedObject> selection,
	Data uData) throws ActionFailedException,
		ActionAbortedException,
		ActionUnauthorizedException {

	UserMgrPanelDescriptor descriptor = control.getPanelDescriptor();
	descriptor.initUsers(uData.getScope(),
		uData.getType(), uData.getString());

	return null; // umo;
    }

}

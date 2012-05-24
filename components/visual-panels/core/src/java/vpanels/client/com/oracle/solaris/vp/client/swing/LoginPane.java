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

package com.oracle.solaris.vp.client.swing;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.JTextComponent;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.util.misc.DialogMessage;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class LoginPane extends DialogPane {
    //
    // Inner classes
    //

    private static interface LoginField<T> {
	T getValue();

	void requestEditFocus();

	void setEditable(boolean editable);

	void setValue(T text);

	void setVisible(boolean visible);
    }

    private static abstract class DualLoginField<T, C extends Component>
	extends JPanel implements LoginField<T> {

	//
	// Instance data
	//

	private JLabel label;
	private C field;

	//
	// Constructors
	//

	public DualLoginField() {
	    super(new BorderLayout());
	    setOpaque(false);

	    label = new JLabel();
	    add(label, BorderLayout.WEST);

	    field = createField();
	    add(field, BorderLayout.NORTH);
	}

	//
	// LoginField methods
	//

	@Override
	public void requestEditFocus() {
	    field.requestFocusInWindow();
	}

	@Override
	public void setEditable(boolean editable) {
	    label.setVisible(!editable);
	    field.setVisible(editable);
	}

	//
	// DualLoginField methods
	//

	public abstract C createField();

	public JLabel getLabel() {
	    return label;
	}

	public C getField() {
	    return field;
	}

	public String toDisplayableText(T value) {
	    return value == null ? null : value.toString();
	}

	protected void updateLabel() {
	    getLabel().setText(toDisplayableText(getValue()));
	}
    }

    private static class LoginTextField
	extends DualLoginField<String, JTextField> {

	//
	// LoginField methods
	//

	@Override
	public String getValue() {
	    String value = getField().getText();
	    if (value.isEmpty()) {
		value = null;
	    }
	    return value;
	}

	@Override
	public void requestEditFocus() {
	    getField().selectAll();
	    super.requestEditFocus();
	}

	@Override
	public void setValue(String text) {
	    getField().setText(text);
	}

	//
	// DualLoginField methods
	//

	@Override
	public JTextField createField() {
	    JTextField field = new JTextField(GUIUtil.getTextFieldWidth());

	    field.getDocument().addDocumentListener(
		new DocumentAdapter() {
		    @Override
		    public void docUpdate(DocumentEvent e) {
			updateLabel();
		    }
		});

	    return field;
	}
    }

    private static class LoginComboBox
	extends DualLoginField<String, JComboBox> {

	//
	// Instance data
	//

	private String nullText;

	//
	// Constructors
	//

	public LoginComboBox(String nullText) {
	    this.nullText = nullText;
	    updateLabel();
	}

	//
	// LoginField methods
	//

	@Override
	public String getValue() {
	    return (String)getField().getSelectedItem();
	}

	@Override
	public void setValue(String text) {
	    getField().getModel().setSelectedItem(text);
	}

	//
	// DualLoginField methods
	//

	@Override
	public JComboBox createField() {
	    JComboBox field = new JComboBox();
	    if (!(field.getModel() instanceof DefaultComboBoxModel)) {
		field.setModel(new DefaultComboBoxModel());
	    }

	    final ListCellRenderer renderer = field.getRenderer();

	    // Handle null values in the model
	    field.setRenderer(
		new ListCellRenderer() {
		    @Override
                    public Component getListCellRendererComponent(JList list,
			Object value, int index, boolean isSelected,
			boolean cellHasFocus) {

                        return renderer.getListCellRendererComponent(list,
			    toDisplayableText((String)value), index, isSelected,
			    cellHasFocus);
		    }
                });

	    field.getModel().addListDataListener(
		new ListDataListener() {
		    @Override
		    public void contentsChanged(ListDataEvent e) {
			updateLabel();
		    }

		    @Override
		    public void intervalAdded(ListDataEvent e) {
			updateLabel();
		    }

		    @Override
		    public void intervalRemoved(ListDataEvent e) {
			updateLabel();
		    }
		});

	    return field;
	}

	@Override
	public String toDisplayableText(String value) {
	    return value == null ? nullText : value;
	}
    }

    private static class LoginCheckBox extends JCheckBox
	implements LoginField<Boolean> {

	//
	// Instance data
	//

	private UneditableToggleButtonModel model;

	//
	// Constructors
	//

	public LoginCheckBox() {
	    model = new UneditableToggleButtonModel();
	    setModel(model);
	}

	//
	// LoginField methods
	//

	@Override
	public Boolean getValue() {
	    return isSelected();
	}

	@Override
	public void requestEditFocus() {
	    requestFocusInWindow();
	}

	@Override
	public void setEditable(boolean editable) {
	    model.setEditable(editable);
	}

	@Override
	public void setValue(Boolean checked) {
	    model.setSelectedForced(checked != null && checked);
	}
    }

    //
    // Static data
    //

    private static final Color COLOR_LABEL_ERROR = Color.red.darker();

    private static final String LABEL_HOST =
	Finder.getString("login.label.host");

    private static final String LABEL_USER =
	Finder.getString("login.label.user");

    private static final String LABEL_ROLE =
	Finder.getString("login.label.role");

    private static final String LABEL_ZONEPROMPT =
	Finder.getString("login.label.zoneprompt");

    private static final String LABEL_ZONE =
	Finder.getString("login.label.zone");

    private static final String LABEL_ZONEUSER =
	Finder.getString("login.label.zoneuser");

    private static final String LABEL_ZONEROLE =
	Finder.getString("login.label.zonerole");

    //
    // Instance data
    //

    private JPanel fieldPanel;
    private int nCoreFields;

    private JLabel hostLabel;
    private LoginTextField hostField;

    private JLabel userLabel;
    private LoginTextField userField;

    private JLabel roleLabel;
    private LoginComboBox roleField;

    private LoginCheckBox zonePromptField;

    private JLabel zoneLabel;
    private LoginComboBox zoneField;

    private JLabel zoneUserLabel;
    private LoginTextField zoneUserField;

    private JLabel zoneRoleLabel;
    private LoginComboBox zoneRoleField;

    //
    // Constructors
    //

    public LoginPane() {
	createFieldPanel();

	zonePromptField = new LoginCheckBox();

	int gap = GUIUtil.getHalfGap();
	JPanel panel = new JPanel(new BorderLayout(gap, gap));
	panel.setOpaque(false);
	panel.add(fieldPanel, BorderLayout.CENTER);
	panel.add(zonePromptField, BorderLayout.SOUTH);

	setContent(panel, false, false);

	SettingsButtonBar buttonBar = getButtonBar();

	JButton cancel = buttonBar.getCancelButton();
	cancel.addActionListener(setClickedButtonActionListener);

	// Move to left side of dialog
	buttonBar.remove(cancel);
	buttonBar.add(cancel, 0);

	JButton close = buttonBar.getCloseButton();
	close.addActionListener(setClickedButtonActionListener);

	JButton back = buttonBar.getBackButton();
	back.addActionListener(setClickedButtonActionListener);

	JButton forward = buttonBar.getForwardButton();
	forward.addActionListener(setClickedButtonActionListener);
	forward.setText(Finder.getString("login.button.forward"));
    }

    //
    // LoginPane methods
    //

    public void promptForAck(LoginRequest request)
	throws ActionAbortedException {

	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<String> role = request.getRole();
	final LoginProperty<String> zone = request.getZone();
	final LoginProperty<String> zoneUser = request.getZoneUser();
	final LoginProperty<String> zoneRole = request.getZoneRole();
	final List<DialogMessage> messages = request.getMessages();

	addMessage(request, "login.message.ack");

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    clear();
		    setHostInUI(host, false);
		    setUserInUI(user, false);

		    if (role.getValue() != null) {
			setRoleInUI(role, false);
		    }

		    if (zone.getValue() != null) {
			setZoneInUI(zone, false);
			if (zoneUser.getValue() != null) {
			    setZoneUserInUI(zoneUser, false);
			    if (zoneRole.getValue() != null) {
				setZoneRoleInUI(zoneRole, false);
			    }
			}
		    }

		    getButtonBar().getBackButton().setEnabled(false);
		}
	});

	try {
	    awaitForward();
	} catch (ActionRegressedException impossible) {
	}
    }

    public void promptForAuth(LoginRequest request,
        final List<LoginProperty> properties, final boolean isZone,
	final boolean isUserAuth, boolean isFirst)
	throws ActionAbortedException, ActionRegressedException {

	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<Boolean> zonePrompt = request.getZonePrompt();
	final LoginProperty<String> role = request.getRole();
	final LoginProperty<String> zone = request.getZone();
	final LoginProperty<String> zoneUser = request.getZoneUser();
	final LoginProperty<String> zoneRole = request.getZoneRole();
	final List<DialogMessage> messages = request.getMessages();

	if (isFirst) {
	    String message = "login.message.auth.";
	    if (isZone) {
		message += "zone.";
	    }
	    message += isUserAuth ? "user" : "role";
	    addMessage(request, message);
	}

	final Map<LoginProperty, JTextComponent> map =
	    new HashMap<LoginProperty, JTextComponent>();

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    clear();
		    setHostInUI(host, false);

		    if (isZone) {
			setZoneInUI(zone, false);
			setZoneUserInUI(zoneUser, false);
			if (!isUserAuth) {
			    setZoneRoleInUI(zoneRole, false);
			}
		    } else {
			setUserInUI(user, false);
			if (!isUserAuth) {
			    setRoleInUI(role, false);
			}
		    }

		    boolean editable = host.isEditable() || user.isEditable() ||
                        zonePrompt.isEditable();
		    if (isZone) {
                        editable |= role.isEditable() || zone.isEditable() ||
                            zoneUser.isEditable() || (!isUserAuth &&
                            zoneRole.isEditable());
		    } else {
                        editable |= !isUserAuth && role.isEditable();
		    }

                    getButtonBar().getBackButton().setEnabled(editable);

		    int cols = GUIUtil.getTextFieldWidth();

		    if (properties != null) {
			for (LoginProperty property : properties) {
			    JLabel label = new JLabel(property.getName());
			    JTextComponent field = null;
			    Object value = property.getValue();
			    String text;
			    if (property instanceof PasswordLoginProperty) {
				field = new JPasswordField(cols);
				text = new String((char[])value);
			    } else {
				field = new JTextField(cols);
				text = (String)value;
			    }

			    field.setText(text);
			    fieldPanel.add(label);
			    fieldPanel.add(field);
			    map.put(property, field);
			}
		    }
		}
	    });

	final boolean[] success = {false};
	try {
	    awaitForward();
	    success[0] = true;
	} finally {
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			for (Map.Entry<LoginProperty, JTextComponent> entry :
			    map.entrySet()) {

			    JTextComponent field = entry.getValue();

			    if (success[0]) {
				if (field instanceof JPasswordField) {
				    @SuppressWarnings({"unchecked"})
				    LoginProperty<char[]> prop =
					(LoginProperty<char[]>)entry.getKey();
				    prop.setValue(
					((JPasswordField)field).getPassword());
				} else {
				    @SuppressWarnings({"unchecked"})
				    LoginProperty<String> prop =
					(LoginProperty<String>)entry.getKey();
				    prop.setValue(field.getText());
				}
			    }

			    // Remove any sensitive information
			    field.setText(null);
			}
		    }
		});
	}
    }

    public void promptForFailedRequest(LoginRequest request) {
	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<String> role = request.getRole();
	final LoginProperty<String> zone = request.getZone();
	final LoginProperty<String> zoneUser = request.getZoneUser();
	final LoginProperty<String> zoneRole = request.getZoneRole();
	final List<DialogMessage> messages = request.getMessages();

	if (messages.isEmpty()) {
	    addMessage(request, "login.message.fail");
	}

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    clear();
		    if (host.getValue() != null) {
			setHostInUI(host, false);
			if (user.getValue() != null) {
			    setUserInUI(user, false);
			    if (role.getValue() != null) {
				setRoleInUI(role, false);
			    }
			    if (zone.getValue() != null) {
				setZoneInUI(zone, false);
				if (zoneUser.getValue() != null) {
				    setZoneUserInUI(zoneUser, false);
				    if (zoneRole.getValue() != null) {
					setZoneRoleInUI(zoneRole, false);
				    }
				}
			    }
			}
		    }
		}
	});

	awaitClose();
    }

    public void promptForHostAndUser(LoginRequest request)
	throws ActionAbortedException {

	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<Boolean> zonePrompt = request.getZonePrompt();
	final List<DialogMessage> messages = request.getMessages();

	String resource = "login.message.hostuser";
	if (host.isEditable()) {
	    resource += ".host";
	}
	if (user.isEditable()) {
	    resource += ".user";
	}
	addMessage(request, resource);

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    clear();
		    setHostInUI(host, true);
		    setUserInUI(user, true);

		    Boolean zonePromptValue = zonePrompt.getValue();
                    if ((zonePromptValue != null && zonePromptValue) ||
			zonePrompt.isEditable()) {
			setZonePromptInUI(zonePrompt, true);
		    }

		    getButtonBar().getBackButton().setEnabled(false);
		}
	});

	try {
	    awaitForward();
	} catch (ActionRegressedException impossible) {
	}

	setInProperty(host, hostField);
	setInProperty(user, userField);
	setInProperty(zonePrompt, zonePromptField);
    }

    public void promptForRole(LoginRequest request,
        final List<String> roles, final boolean isZone)
	throws ActionAbortedException, ActionRegressedException {

	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<Boolean> zonePrompt = request.getZonePrompt();
	final LoginProperty<String> role = request.getRole();
	final LoginProperty<String> zone = request.getZone();
	final LoginProperty<String> zoneUser = request.getZoneUser();
	final LoginProperty<String> zoneRole = request.getZoneRole();
	final List<DialogMessage> messages = request.getMessages();

        addMessage(request, isZone ? "login.message.zonerole" :
	    "login.message.role");

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    LoginComboBox field = isZone ? zoneRoleField : roleField;
		    DefaultComboBoxModel model =
			(DefaultComboBoxModel)field.getField().getModel();

		    model.removeAllElements();
		    model.addElement(null);
		    for (String r : roles) {
			model.addElement(r);
		    }

		    clear();
		    setHostInUI(host, false);

		    if (isZone) {
			setZoneInUI(zone, false);
			setZoneUserInUI(zoneUser, false);
			setZoneRoleInUI(zoneRole, true);
		    } else {
			setUserInUI(user, false);
			setRoleInUI(role, true);
		    }

		    getButtonBar().getBackButton().setEnabled(
			host.isEditable() || user.isEditable() ||
			zonePrompt.isEditable() ||
			(isZone && zone.isEditable() || zoneUser.isEditable()));
		}
	    });

	awaitForward();
	if (isZone) {
	    setInProperty(zoneRole, zoneRoleField);
	} else {
	    setInProperty(role, roleField);
	}
    }

    public void promptForZoneAndUser(LoginRequest request,
        final List<String> zones) throws ActionAbortedException,
        ActionRegressedException {

	assert !EventQueue.isDispatchThread();

	final LoginProperty<String> host = request.getHost();
	final LoginProperty<String> user = request.getUser();
	final LoginProperty<Boolean> zonePrompt = request.getZonePrompt();
	final LoginProperty<String> role = request.getRole();
	final LoginProperty<String> zone = request.getZone();
	final LoginProperty<String> zoneUser = request.getZoneUser();
	final List<DialogMessage> messages = request.getMessages();

	String resource = "login.message.zoneuser";
	if (zone.isEditable()) {
	    resource += ".zone";
	}
	if (zoneUser.isEditable()) {
	    resource += ".user";
	}
	addMessage(request, resource);

	if (zoneUser.getValue() == null) {
	    // Prepopulate with sensible default if unset
	    zoneUser.setValue(user.getValue());
	}

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    getMessagePanel().setMessages(messages);

		    DefaultComboBoxModel model =
			(DefaultComboBoxModel)zoneField.getField().getModel();

		    model.removeAllElements();
		    model.addElement(null);
		    for (String z : zones) {
			model.addElement(z);
		    }

		    clear();
		    setHostInUI(host, false);
		    setZoneInUI(zone, true);
		    setZoneUserInUI(zoneUser, true);

                    getButtonBar().getBackButton().setEnabled(
                        host.isEditable() || user.isEditable() ||
                        zonePrompt.isEditable() || role.isEditable());
		}
	    });

	awaitForward();
	setInProperty(zone, zoneField);
	setInProperty(zoneUser, zoneUserField);
    }

    //
    // Private methods
    //

    private void addMessage(LoginRequest request, String resource) {
	DialogMessage message = new DialogMessage(Finder.getString(
            resource, request.getHost().getValue(),
            request.getUser().getValue(), request.getRole().getValue(),
            request.getZone().getValue(), request.getZoneUser().getValue(),
            request.getZoneRole().getValue()));
	request.getMessages().add(message);
    }

    private void awaitClose() {
	SettingsButtonBar bar = getButtonBar();
	AbstractButton closeButton = bar.getCloseButton();

	for (AbstractButton button : bar.getButtons()) {
	    button.setVisible(button == closeButton);
	}

	while (awaitClickedButton() != closeButton);
    }

    private void awaitForward() throws ActionAbortedException,
	ActionRegressedException {

	SettingsButtonBar bar = getButtonBar();
	AbstractButton backButton = bar.getBackButton();
	AbstractButton forwardButton = bar.getForwardButton();
	AbstractButton cancelButton = bar.getCancelButton();

	for (AbstractButton button : bar.getButtons()) {
	    button.setVisible(button == backButton ||
		button == forwardButton || button == cancelButton);
	}

	JButton clicked = null;
	while (clicked != forwardButton) {
	    clicked = awaitClickedButton();

	    if (clicked == backButton) {
		throw new ActionRegressedException();
	    }

	    if (clicked == cancelButton) {
		throw new ActionAbortedException();
	    }
	}
    }

    private void createFieldPanel() {
	hostField = new LoginTextField();
	hostLabel = new JLabel();
	hostLabel.setLabelFor(hostField);

	userField = new LoginTextField();
	userLabel = new JLabel();
	userLabel.setLabelFor(userField);

        roleField = new LoginComboBox(
	    Finder.getString("login.field.role.none"));
	roleLabel = new JLabel();
	roleLabel.setLabelFor(roleField);

        zoneField = new LoginComboBox(
	    Finder.getString("login.field.zone.select"));
	zoneLabel = new JLabel();
	zoneLabel.setLabelFor(zoneField);

	zoneUserField = new LoginTextField();
	zoneUserLabel = new JLabel();
	zoneUserLabel.setLabelFor(zoneUserField);

        zoneRoleField = new LoginComboBox(
	    Finder.getString("login.field.zonerole.none"));
	zoneRoleLabel = new JLabel();
	zoneRoleLabel.setLabelFor(zoneRoleField);

	int gap = GUIUtil.getHalfGap();

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	TableLayout layout = new TableLayout(1, 2, gap, gap);
	layout.setHorizontalAnchor(HorizontalAnchor.LEFT);
	layout.setDefaultConstraint(a);

	fieldPanel = new JPanel(layout);
	fieldPanel.setOpaque(false);

	fieldPanel.add(hostLabel);
	fieldPanel.add(hostField);

	fieldPanel.add(userLabel);
	fieldPanel.add(userField);

	fieldPanel.add(roleLabel);
	fieldPanel.add(roleField);

	fieldPanel.add(zoneLabel);
	fieldPanel.add(zoneField);

	fieldPanel.add(zoneUserLabel);
	fieldPanel.add(zoneUserField);

	fieldPanel.add(zoneRoleLabel);
	fieldPanel.add(zoneRoleField);

	nCoreFields = fieldPanel.getComponentCount();
    }

    private void clear() {
	assert EventQueue.isDispatchThread();

	hostLabel.setVisible(false);
	hostField.setVisible(false);

	roleLabel.setVisible(false);
	roleField.setVisible(false);

	userLabel.setVisible(false);
	userField.setVisible(false);

	zoneLabel.setVisible(false);
	zoneField.setVisible(false);

	zonePromptField.setVisible(false);

	zoneUserLabel.setVisible(false);
	zoneUserField.setVisible(false);

	zoneRoleLabel.setVisible(false);
	zoneRoleField.setVisible(false);

	// Remove all but the "core" fields (host, user, role, etc.)
	while (fieldPanel.getComponentCount() > nCoreFields) {
	    fieldPanel.remove(nCoreFields);
	}
    }

    private void setHostInUI(LoginProperty<String> property, boolean allowEdit)
    {
	setInUI(property, hostLabel, hostField, LABEL_HOST, allowEdit);
    }

    private <T> void setInProperty(LoginProperty<T> property,
	LoginField<T> field) {

	if (property.isEditable()) {
	    property.setValue(field.getValue());
	}
	property.setErrored(false);
    }

    private <T> void setInUI(LoginProperty<T> property, Component label,
        final LoginField<T> field, String defaultLabel, boolean allowEdit) {

	assert EventQueue.isDispatchThread();

	String labelText = property.getName();
	if (labelText == null) {
	    labelText = defaultLabel;
	}
	if (label instanceof JLabel) {
	    ((JLabel)label).setText(labelText);
	} else if (label instanceof JCheckBox) {
	    ((JCheckBox)label).setText(labelText);
	}

	boolean editable = allowEdit && property.isEditable();
	Color foreground = null;
	int style = Font.PLAIN;
	if (property.isErrored()) {
	    foreground = COLOR_LABEL_ERROR;
	    style = Font.BOLD;
	    if (editable) {
		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    field.requestEditFocus();
			}
		    });
	    }
	}
	label.setForeground(foreground);
	label.setFont(label.getFont().deriveFont(style));
	label.setVisible(true);

	field.setValue(property.getValue());
	field.setEditable(editable);
	field.setVisible(true);
    }

    private void setRoleInUI(LoginProperty<String> property, boolean allowEdit)
    {
	setInUI(property, roleLabel, roleField, LABEL_ROLE, allowEdit);
    }

    private void setUserInUI(LoginProperty<String> property, boolean allowEdit)
    {
	setInUI(property, userLabel, userField, LABEL_USER, allowEdit);
    }

    private void setZoneInUI(LoginProperty<String> property, boolean allowEdit)
    {
	setInUI(property, zoneLabel, zoneField, LABEL_ZONE, allowEdit);
    }

    private void setZonePromptInUI(LoginProperty<Boolean> property,
	boolean allowEdit) {
        setInUI(property, zonePromptField, zonePromptField, LABEL_ZONEPROMPT,
	    allowEdit);
    }

    private void setZoneRoleInUI(LoginProperty<String> property,
	boolean allowEdit) {

        setInUI(property, zoneRoleLabel, zoneRoleField, LABEL_ZONEROLE,
	    allowEdit);
    }

    private void setZoneUserInUI(LoginProperty<String> property,
	boolean allowEdit) {
        setInUI(property, zoneUserLabel, zoneUserField, LABEL_ZONEUSER,
	    allowEdit);
    }
}

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

import java.awt.BorderLayout;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.predicate.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class DialogPane extends SettingsPanel {
    //
    // Inner classes
    //

    protected static class MessagePanel extends AutoHidePanel {
	//
	// Instance data
	//

	private Map<DialogMessagePanel, DialogMessage> map =
	    new HashMap<DialogMessagePanel, DialogMessage>();

	//
	// Constructors
	//

	public MessagePanel() {
	    int gap = GUIUtil.getGap();

	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, gap);

	    ColumnLayout layout = new ColumnLayout(VerticalAnchor.TOP);
	    layout.setDefaultConstraint(c);
	    setLayout(layout);
	}

	//
	// MessagePanel methods
	//

	public void setMessages(List<DialogMessage> messages) {
	    // Strip nulls
	    Predicate<DialogMessage> matcher = NonNullPredicate.getInstance();
	    messages = CollectionUtil.filter(messages, matcher);

	    int nMessages = messages.size();
	    int nComps = getComponentCount();

	    // Find index of first message not already shown
	    int i;
	    for (i = 0; i < nMessages && i < nComps; i++) {
		DialogMessagePanel pane = (DialogMessagePanel)getComponent(i);
		DialogMessage message = messages.get(i);
		if (map.get(pane) != message) {
		    break;
		}
	    }

	    // Remove following DialogMessagePanels
	    for (int j = nComps - 1; j >= i; j--) {
		map.remove((DialogMessagePanel)getComponent(j));
		remove(j);
	    }

	    // Add new messages
	    for (; i < nMessages; i++) {
		DialogMessage message = messages.get(i);
		DialogMessagePanel pane = new DialogMessagePanel(message);
		add(pane);
		map.put(pane, message);
	    }
	}
    }

    //
    // Static data
    //

    public static final String PROPERTY_PROMPTING = "prompting";

    //
    // Instance data
    //

    private MessagePanel messagePanel;
    private JButton[] clickedButton = {null};

    protected ActionListener setClickedButtonActionListener =
	new ActionListener() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		setClickedButton((JButton)e.getSource());
	    }
	};

    //
    // Constructors
    //

    public DialogPane() {
	setBorder(GUIUtil.getEmptyBorder());

	messagePanel = new MessagePanel();
	JPanel helpPane = getHelpPane();
	helpPane.removeAll();
	helpPane.add(messagePanel, BorderLayout.CENTER);

	getButtonBar().setChanged(true);
    }

    //
    // DialogPane methods
    //

    /**
     * Blocks the current thread until a button has been clicked.
     *
     * @return	    the last clicked button, or {@code null} no button has been
     *		    clicked
     */
    public JButton awaitClickedButton() {
	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    firePropertyChange(PROPERTY_PROMPTING, false, true);
		}
	    });

	synchronized (clickedButton) {
	    clickedButton[0] = null;
	    try {
		while (clickedButton[0] == null) {
		    clickedButton.wait();
		}
	    } catch (InterruptedException e) {
	    }
	}

	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    firePropertyChange(PROPERTY_PROMPTING, true, false);
		}
	    });

	return clickedButton[0];
    }

    /**
     * Blocks the current thread until a button has been clicked, then throws an
     * {@code ActionAbortedException} if the clicked button is not the okay
     * button.
     */
    protected void awaitOkay() throws ActionAbortedException {
	JButton clicked = awaitClickedButton();
	if (clicked != getButtonBar().getOkayButton()) {
	    throw new ActionAbortedException();
	}
    }

    /**
     * Returns the last clicked button, or {@code null} no button has been
     * clicked.
     */
    public JButton getClickedButton() {
	synchronized (clickedButton) {
	    return clickedButton[0];
	}
    }

    protected MessagePanel getMessagePanel() {
	return messagePanel;
    }

    protected void setClickedButton(JButton button) {
	synchronized (clickedButton) {
	    clickedButton[0] = button;
	    // Wake up any waiting threads
	    clickedButton.notifyAll();
	}
    }
}

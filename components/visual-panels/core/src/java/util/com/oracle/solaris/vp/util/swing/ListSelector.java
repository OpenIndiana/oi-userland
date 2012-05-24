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
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class ListSelector extends JPanel {
    //
    // Inner classes
    //

    protected class DragDropList extends ExtList {
	//
	// Constructors
	//

	public DragDropList(ListModel dataModel) {
	    super(dataModel);
	    setDragEnabled(true);
	    setDropMode(DropMode.INSERT);
	    setTransferHandler(handler);
	    setFillsViewportHeight(true);
	}

	//
	// DragDropList methods
	//

	public Boolean getMove() {
	    return true;
	}

	public void setMove(Boolean move) {
	    moveSelection(this == rightList);
	}
    }

    //
    // Static data
    //

    private static final int LIST_VISIBLE_ROWS = 4;

    //
    // Instance data
    //

    private JList leftList;
    private JList rightList;
    private JLabel leftLabel;
    private JLabel rightLabel;
    private JButton moveLeftButton;
    private JButton moveRightButton;
    private JButton defaultsButton;
    private Object[] leftData;
    private Object[] rightData;

    private TransferHandler handler = new TransferHandler("move") {
	@Override
	public int getSourceActions(JComponent c) {
	    return MOVE;
	}
    };

    //
    // Constructors
    //

    public ListSelector(DefaultListModel leftModel, DefaultListModel rightModel,
	String leftLabelText, String rightLabelText) {

	JPanel buttonPanel = createButtonPanel();

	leftList = createList(leftModel, moveRightButton);
	JScrollPane leftListScroll = new ExtScrollPane(leftList);

	rightList = createList(rightModel, moveLeftButton);
	JScrollPane rightListScroll = new ExtScrollPane(rightList);

	saveAsDefaults();

	leftLabel = new JLabel();
	setLeftLabel(leftLabelText);

	rightLabel = new JLabel();
	setRightLabel(rightLabelText);

	int gap = GUIUtil.getHalfGap();

	AbstractTableConstraint unweighted = new SimpleTableConstraint(gap, 0);
	AbstractTableConstraint weighted = new SimpleTableConstraint(gap, 1);

	AbstractTableConstraint[] rowConstraints = {
	    unweighted, weighted.clone().setGap(0), // unweighted
	};

	AbstractTableConstraint[] colConstraints = {
	    weighted, unweighted, weighted,
	};

	TableLayout layout = new TableLayout(rowConstraints, colConstraints) {
	    @Override
	    protected TableInfo getTableInfo(
		Container container, boolean preferred) {

		TableInfo info = super.getTableInfo(container, preferred);
		RowOrColSet set = info.getColumns();

		// Make sure columns 0 and 2 are always laid out with the same
		// width (the maximum of the two widths)
		if (set.getSize(0) < set.getSize(2)) {
		    set.setSize(0, set.getSize(2));
		} else {
		    set.setSize(2, set.getSize(0));
		}

		return info;
	    }
	};

	setLayout(layout);

	HasAnchors a = new SimpleHasAnchors(
	    HorizontalAnchor.FILL, VerticalAnchor.FILL);

	add(leftLabel, a);
	add(createSpacer(), a);
	add(rightLabel, a);

	add(leftListScroll, a);
	add(buttonPanel, a);
	add(rightListScroll, a);

//	add(createSpacer(), a);
//	add(createSpacer(), a);
//	add(defaultsButton, new SimpleHasAnchors(
//	    HorizontalAnchor.CENTER, VerticalAnchor.CENTER));
    }

    public ListSelector(Object[] leftData, Object[] rightData,
	String leftLabelText, String rightLabelText) {

	this(toModel(leftData), toModel(rightData), leftLabelText,
	    rightLabelText);
    }

    public ListSelector(DefaultListModel leftModel,
	DefaultListModel rightModel) {

	this(leftModel, rightModel, null, null);
    }

    public ListSelector(Object[] leftData, Object[] rightData) {
	this(leftData, rightData, null, null);
    }

    //
    // ListSelector methods
    //

    public JButton getDefaultsButton() {
	return defaultsButton;
    }

    public String getLeftLabel() {
	return leftLabel.getText();
    }

    public JList getLeftList() {
	return leftList;
    }

    public JButton getMoveLeftButton() {
	return moveLeftButton;
    }

    public String getRightLabel() {
	return rightLabel.getText();
    }

    public JList getRightList() {
	return rightList;
    }

    public JButton getMoveRightButton() {
	return moveRightButton;
    }

    public void moveSelection(boolean leftToRight) {
	JList srcList, destList;
	if (leftToRight) {
	    srcList = leftList;
	    destList = rightList;
	} else {
	    srcList = rightList;
	    destList = leftList;
	}

	DefaultListModel srcModel = (DefaultListModel)srcList.getModel();
	DefaultListModel destModel = (DefaultListModel)destList.getModel();

	int[] selected = srcList.getSelectedIndices();
	if (selected.length != 0) {
	    destList.clearSelection();

	    for (int i = selected.length - 1; i >= 0; i--) {
		int index = selected[i];
		Object datum = srcModel.getElementAt(index);
		destModel.addElement(datum);
		srcModel.removeElementAt(index);

		index = destModel.indexOf(datum);
		if (index != -1) {
		    destList.addSelectionInterval(index, index);
		    destList.ensureIndexIsVisible(index);
		}
	    }
	}
    }

    /**
     * Reverts the lists to the default state.
     */
    public void revertToDefaults() {
	DefaultListModel leftModel = (DefaultListModel)getLeftList().getModel();
	leftModel.clear();
	for (Object datum : leftData) {
	    leftModel.addElement(datum);
	}

	DefaultListModel rightModel =
	    (DefaultListModel)getRightList().getModel();
	rightModel.clear();
	for (Object datum : rightData) {
	    rightModel.addElement(datum);
	}
    }

    /**
     * Saves the current state of the lists, which can be reverted back to using
     * the the "defaults" button.
     */
    public void saveAsDefaults() {
	leftData = ((DefaultListModel)getLeftList().getModel()).toArray();
	rightData = ((DefaultListModel)getRightList().getModel()).toArray();
    }

    public void setLeftLabel(String text) {
	leftLabel.setText(text);
	leftLabel.setVisible(text != null);
    }

    public void setRightLabel(String text) {
	rightLabel.setText(text);
	rightLabel.setVisible(text != null);
    }

    /**
     * Sets the prototype cell for each list to be the widest cell of either
     * list.  Helps to maintain a consistent width between each list.
     */
    public void setWidestCellAsPrototype() {
	int mWidth = 0;
	Object mObject = null;
	JList[] lists = new JList[] {getLeftList(), getRightList()};

	for (JList list : lists) {
	    ListModel model = list.getModel();
	    ListCellRenderer renderer = list.getCellRenderer();

	    for (int i = 0, n = model.getSize(); i < n; i++) {
		Object object = model.getElementAt(i);
		Component c = renderer.getListCellRendererComponent(
		    list, object, i, false, false);
		int width = c.getPreferredSize().width;

		if (width > mWidth) {
		    mWidth = width;
		    mObject = object;
		}
	    }

	}

	for (JList list : lists) {
	    // May be null
	    list.setPrototypeCellValue(mObject);
	}
    }

    //
    // Private methods
    //

    private JPanel createButtonPanel() {
	int gap = GUIUtil.getHalfGap();

	moveLeftButton = new JButton(Finder.getString("list.button.moveleft"),
	    Finder.getIcon("images/button/moveleft.png"));
	moveLeftButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    moveSelection(false);
		}
	    });

	moveRightButton = new JButton(Finder.getString("list.button.moveright"),
	    Finder.getIcon("images/button/moveright.png"));
	moveRightButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    moveSelection(true);
		}
	    });

	defaultsButton = new JButton(Finder.getString("list.button.defaults"));
	defaultsButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    revertToDefaults();
		}
	    });

	ColumnLayout buttonLayout = new ColumnLayout(VerticalAnchor.CENTER);
	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.CENTER, gap);
	JPanel buttonPanel = new JPanel(buttonLayout);
	buttonPanel.setOpaque(false);
	buttonPanel.add(moveRightButton, c);
	buttonPanel.add(moveLeftButton, c);
	buttonPanel.add(defaultsButton, c);

	return buttonPanel;
    }

    private JList createList(ListModel model, final JButton moveButton) {
	final JList list = new DragDropList(model);
	list.setVisibleRowCount(LIST_VISIBLE_ROWS);

	ListSelectionListener moveButtonEnabler =
	    new ListSelectionListener() {
		@Override
		public void valueChanged(ListSelectionEvent e) {
		    moveButton.setEnabled(list.getSelectedIndex() != -1);
		}
	    };

	// Initialize button state
	moveButtonEnabler.valueChanged(null);

	list.addListSelectionListener(moveButtonEnabler);

	list.addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mouseClicked(MouseEvent e) {
		    if (GUIUtil.isUnmodifiedClick(e, 2)) {
			moveButton.doClick(0);
		    }
		}
	    });

	return list;
    }

    private Component createSpacer() {
	Spacer s = new Spacer();
	s.setVisible(false);

	return s;
    }

    //
    // Static methods
    //

    private static DefaultListModel toModel(Object[] data) {
	DefaultListModel model = new SortedListModel();

	if (data != null) {
	    for (Object datum : data) {
		model.addElement(datum);
	    }
	}

	return model;
    }

    // XXX Unit test -- remove
    public static void main(String args[]) {
	String[] data1 = {
	    "one", "two", "three",
	    "four", "five", "six",
	    "seven", "eight", "nine",
	    "ten", "eleven", "twelve",
	};

	String[] data2 = {
	    "1", "2", "3",
	    "4", "5", "6",
	    "7", "8", "9",
	    "10", "11", "12",
	};

	ListSelector selector =
//	    new ListSelector(data1, data2, null, null);
	    new ListSelector(data1, data2, "Unselected", "Selected");

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(selector, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}

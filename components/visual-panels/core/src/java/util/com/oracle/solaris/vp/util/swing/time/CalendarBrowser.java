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

package com.oracle.solaris.vp.util.swing.time;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import javax.swing.table.JTableHeader;
import com.oracle.solaris.vp.util.misc.finder.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class CalendarBrowser extends JPanel {
    //
    // Static data
    //

    private static final Icon zoomOutIcon;
    private static final Icon zoomInIcon;

    static {
	Icon tmp = GnomeUtil.getIcon("zoom-out", 16, true);
	if (tmp == null) {
	    tmp = Finder.getIcon("images/calendar/zoom-out.png");
	}
	zoomOutIcon = tmp;

	tmp = GnomeUtil.getIcon("zoom-in", 16, true);
	if (tmp == null) {
	    tmp = Finder.getIcon("images/calendar/zoom-in.png");
	}
	zoomInIcon = tmp;
    }

    //
    // Instance data
    //

    private CalendarTable[] tables;
    private int tableIndex;
    private TimeModel timeModel;
    private boolean selectionInProgress;
    private JButton titleButton;
    private JLabel titleLabel;
    private JPanel titlePanel;
    private JButton prevButton;
    private JButton nextButton;
    private AnimationPanel animPanel;
    private ScrollComponentAnimation scrollAnim;
    private JPanel tablesPanel;

    private Action nextAction =
	new AbstractAction() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		addIfTableVisible(1);
	    }
	};

    private Action prevAction =
	new AbstractAction() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		addIfTableVisible(-1);
	    }
	};

    private PropertyChangeListener timeListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		timeModelChanged();
	    }
	};

    //
    // Constructors
    //

    public CalendarBrowser(TimeModel timeModel, CalendarTableModel... models) {
	JPanel navPanel = createNavPanel();
	createAnimPanel(models);

	int gap = 5;

	setLayout(new BorderLayout(gap, gap));
	add(navPanel, BorderLayout.NORTH);
	add(animPanel, BorderLayout.CENTER);

	setBorder(BorderFactory.createLineBorder(
	    ColorUtil.darker(getBackground(), .3f)));
	setBackground(Color.white);

	// Initialize
	modelChanged();

	setTimeModel(timeModel);
    }

    public CalendarBrowser(CalendarTableModel... models) {
	this(new SimpleTimeModel(), models);
    }

    public CalendarBrowser() {
	this(new MonthTableModel(),
	    new YearTableModel(),
	    new DecadeTableModel());
    }

    //
    // CalendarBrowser methods
    //

    public void add(int intervals) {
	long millis = getSelectedTable().getModel().getMillis(intervals);
	long timeOffset = timeModel.getTimeOffset();
	timeModel.setTimeOffset(timeOffset + millis);
    }

    public JButton getNextButton() {
	return nextButton;
    }

    public JButton getPreviousButton() {
	return prevButton;
    }

    public CalendarTable getSelectedTable() {
	return tables[tableIndex];
    }

    public TimeModel getTimeModel() {
	return timeModel;
    }

    /**
     * Sets the {@link #getTimeModel time model}'s time offset to fall on the
     * same date as the given calendar.  The time portions of the given {@code
     * Calendar} are ignored.
     */
    public void setCalendar(Calendar cal) {
	Calendar oldCal = timeModel.getCalendar();
	Calendar newCal = (Calendar)cal.clone();

	int[] fields = {Calendar.HOUR_OF_DAY, Calendar.MINUTE, Calendar.SECOND,
	    Calendar.MILLISECOND};

	for (int field : fields) {
	    newCal.set(field, oldCal.get(field));
	}

	long millis = newCal.getTimeInMillis() - oldCal.getTimeInMillis();

	if (millis != 0) {
	    timeModel.setTimeOffset(millis + timeModel.getTimeOffset());
	}
    }

    protected void setSelectedTableIndex(int tableIndex) {
	if (this.tableIndex != tableIndex) {
	    CalendarTable curTable = tables[this.tableIndex];
	    CalendarTable nextTable = tables[tableIndex];

	    animPanel.stop();

	    ScrollComponentAnimation.Direction direction =
		tableIndex < this.tableIndex ?
		ScrollComponentAnimation.Direction.SOUTH :
		ScrollComponentAnimation.Direction.NORTH;

	    scrollAnim.setDirection(direction);
	    animPanel.init(scrollAnim.getId());

	    ((CardLayout)tablesPanel.getLayout()).show(tablesPanel,
		Integer.toString(tableIndex));

	    this.tableIndex = tableIndex;
	    timeModelChanged(false);

	    ((CardLayout)titlePanel.getLayout()).show(titlePanel,
		(tableIndex < tables.length - 1 ? titleButton : titleLabel).
		getName());

	    modelChanged();
	    animPanel.start();
	}
    }

    public void setTimeModel(TimeModel timeModel) {
	if (this.timeModel != timeModel) {
	    if (this.timeModel != null) {
		this.timeModel.removePropertyChangeListener(timeListener);
	    }

	    timeModel.addPropertyChangeListener(TimeModel.PROPERTY_TIME,
		timeListener);

	    this.timeModel = timeModel;
	    timeModelChanged();
	}
    }

    public boolean zoomIn() {
	if (tableIndex > 0) {
	    setSelectedTableIndex(tableIndex - 1);
	    return true;
	}
	return false;
    }

    public boolean zoomOut() {
	if (tableIndex < tables.length - 1) {
	    setSelectedTableIndex(tableIndex + 1);
	    return true;
	}
	return false;
    }

    //
    // Private methods
    //

    private void addIfTableVisible(final int offset) {
	if (getSelectedTable().isShowing()) {
	    add(offset);
	}
    }

    private JButton createButton() {
	JButton b = new JButton();
	new RolloverHandler(b);
	return b;
    }

    private void createNavButtons() {
	prevButton = createButton();
	prevButton.setIcon(ArrowIcon.LEFT);
	prevButton.setFocusable(false);
	prevButton.addMouseListener(
	    new MouseHeldHandler() {
		@Override
		public void mouseHeld(MouseEvent e) {
		    prevAction.actionPerformed(null);
		}
	    });

	nextButton = createButton();
	nextButton.setIcon(ArrowIcon.RIGHT);
	nextButton.setFocusable(false);
	nextButton.addMouseListener(
	    new MouseHeldHandler() {
		@Override
		public void mouseHeld(MouseEvent e) {
		    nextAction.actionPerformed(null);
		}
	    });
    }

    private void createTitle() {
	titleButton = createButton();
	titleButton.setName("button");
	titleButton.setIcon(zoomOutIcon);
	titleButton.setHorizontalTextPosition(SwingConstants.LEFT);
	titleButton.setFont(titleButton.getFont().deriveFont(Font.BOLD));
	titleButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    zoomOut();
		}
	    });

	titleLabel = new JLabel();
	titleLabel.setName("label");
	titleLabel.setHorizontalAlignment(SwingConstants.CENTER);
	titleLabel.setFont(titleButton.getFont());

	titlePanel = new JPanel(new CardLayout());
	titlePanel.setOpaque(false);
	titlePanel.add(titleButton, titleButton.getName());
	titlePanel.add(titleLabel, titleLabel.getName());
    }

    private JPanel createNavPanel() {
	createNavButtons();
	createTitle();

	JPanel navPanel = new JPanel(new RowLayout(
	    HorizontalAnchor.FILL));
	navPanel.setOpaque(false);
	RowLayoutConstraint r = new RowLayoutConstraint(VerticalAnchor.FILL);
	navPanel.add(prevButton, r);
	navPanel.add(titlePanel, r.clone().setWeight(1).
	    setHorizontalAnchor(HorizontalAnchor.CENTER));
	navPanel.add(nextButton, r);

	return navPanel;
    }

    private void createTables(CalendarTableModel[] models) {
	MouseListener mouseListener =
	    new MouseAdapter() {
		@Override
		public void mouseReleased(MouseEvent e) {
		    if (!GUIUtil.isModifierKeyPressed(e)) {
			// Allow selection to propagate before changing tables
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    zoomIn();
				}
			    });
		    }
		}
	    };

	TableModelListener modelListener =
	    new TableModelListener() {
		@Override
		public void tableChanged(TableModelEvent e) {
		    modelChanged();
		}
	    };

	ListSelectionListener rowSelectionListener =
	    new ListSelectionListener() {
		@Override
		public void valueChanged(ListSelectionEvent e) {
		    selectionChanged(e);
		}
	    };

	TableColumnModelListener colSelectionListener =
	    new TableColumnModelListener() {
		@Override
		public void columnAdded(TableColumnModelEvent e) {
		}

		@Override
		public void columnMarginChanged(ChangeEvent e) {
		}

		@Override
		public void columnMoved(TableColumnModelEvent e) {
		}

		@Override
		public void columnRemoved(TableColumnModelEvent e) {
		}

		@Override
		public void columnSelectionChanged(ListSelectionEvent e) {
		    selectionChanged(e);
		}
	    };

	KeyStroke ctrlUp = KeyStroke.getKeyStroke(KeyEvent.VK_UP,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlDown = KeyStroke.getKeyStroke(KeyEvent.VK_DOWN,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlLeft = KeyStroke.getKeyStroke(KeyEvent.VK_LEFT,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlRight = KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlMinus = KeyStroke.getKeyStroke(KeyEvent.VK_MINUS,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlPlus = KeyStroke.getKeyStroke(KeyEvent.VK_PLUS,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlSubtract = KeyStroke.getKeyStroke(KeyEvent.VK_SUBTRACT,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlAdd = KeyStroke.getKeyStroke(KeyEvent.VK_ADD,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke ctrlEquals = KeyStroke.getKeyStroke(KeyEvent.VK_EQUALS,
	    InputEvent.CTRL_DOWN_MASK);
	KeyStroke space = KeyStroke.getKeyStroke(KeyEvent.VK_SPACE, 0);

	Action zoomInAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    zoomIn();
		    tables[tableIndex].requestFocusInWindow();
		}
	    };

	Action zoomOutAction =
	    new AbstractAction() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    zoomOut();
		    tables[tableIndex].requestFocusInWindow();
		}
	    };

	tables = new CalendarTable[models.length];
	for (int i = 0; i < models.length; i++) {
	    CalendarTable table = new CalendarTable(models[i]);
	    tables[i] = table;

	    table.setOpaque(false);

	    table.addMouseListener(mouseListener);
	    table.getSelectionModel().addListSelectionListener(
		rowSelectionListener);
	    table.getColumnModel().addColumnModelListener(colSelectionListener);

	    table.getModel().addTableModelListener(modelListener);

	    GUIUtil.installKeyBinding(table, JComponent.WHEN_FOCUSED,
		"previous period", prevAction, ctrlLeft);

	    GUIUtil.installKeyBinding(table, JComponent.WHEN_FOCUSED,
		"next period", nextAction, ctrlRight);

	    GUIUtil.installKeyBinding(table, JComponent.WHEN_FOCUSED,
		"zoom in", zoomInAction, ctrlUp, ctrlPlus, ctrlAdd, ctrlEquals,
		space);

	    GUIUtil.installKeyBinding(table, JComponent.WHEN_FOCUSED,
		"zoom out", zoomOutAction, ctrlDown, ctrlMinus, ctrlSubtract);
	}
    }

    private void createTablesPanel(CalendarTableModel[] models) {
	createTables(models);

	tablesPanel = new JPanel(new CardLayout());
	tablesPanel.setOpaque(false);

	for (int i = 0; i < tables.length; i++) {
	    CalendarTable table = tables[i];
	    JComponent comp;
	    boolean showHeader = table.getModel().getColumnName(0) != null;
	    if (!showHeader) {
		comp = table;
	    } else {
		JTableHeader header = table.getTableHeader();
		header.setOpaque(false);

		JSeparator separator = new JSeparator();
		separator.setOpaque(false);

		JPanel tablePanel = new JPanel(new ColumnLayout(
		    VerticalAnchor.FILL));
		tablePanel.setOpaque(false);

		ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		    HorizontalAnchor.FILL);

		tablePanel.add(header, c);
		tablePanel.add(separator, c);
		tablePanel.add(table, c.setWeight(1));

		comp = tablePanel;
	    }

	    tablesPanel.add(comp, Integer.toString(i));
	}
    }

    private void createAnimPanel(CalendarTableModel[] models) {
	createTablesPanel(models);

	animPanel = new AnimationPanel(tablesPanel) {
	    boolean hasFocus;

	    @Override
	    public void start() {
		// If the table has focus...
		hasFocus = getSelectedTable().hasFocus();
		super.start();
	    }

	    @Override
	    public void stateChanged(ChangeEvent e) {
		super.stateChanged(e);
		if (hasFocus) {
		    // ...then request it again after the transition
		    getSelectedTable().requestFocusInWindow();
		}
	    }
	};
	animPanel.setOpaque(false);

	scrollAnim = new ScrollComponentAnimation("scroll");
	animPanel.addAnimation(scrollAnim);
    }

    private void modelChanged() {
	String title = getSelectedTable().getModel().getTitle();
	titleButton.setText(title);
	titleLabel.setText(title);
    }

    private void selectionChanged(ListSelectionEvent e) {
	selectionInProgress = e.getValueIsAdjusting();
	if (!selectionInProgress) {
	    // Invoke asynchronously, since we shouldn't change the selection in
	    // the middle of the notification process for the last selection
	    // change.
	    EventQueue.invokeLater(
		new Runnable() {
		    @Override
		    public void run() {
			Calendar cal = getSelectedTable().getSelectedCalendar();

			if (cal != null) {
			    setCalendar(cal);
			}
		    }
		});
	}
    }

    private void timeModelChanged() {
	timeModelChanged(true);
    }

    private void timeModelChanged(boolean animate) {
	CalendarTable table = getSelectedTable();
	CalendarTableModel model = table.getModel();
	Calendar cal = timeModel.getCalendar();

	// Will this cause the model to be rebuilt?
	animate = animate && !model.isInMainRange(cal);

	if (animate) {
	    animPanel.stop();
	    Calendar old = model.getCalendar();

	    ScrollComponentAnimation.Direction direction =
		old.before(cal) ?
		ScrollComponentAnimation.Direction.WEST :
		ScrollComponentAnimation.Direction.EAST;

	    scrollAnim.setDirection(direction);
	    animPanel.init(scrollAnim.getId());
	}

	model.setCalendar(cal);

	if (!selectionInProgress) {
	    table.setSelectedCalendar(cal);
	}

	if (animate) {
	    animPanel.start();
	}
    }

    //
    // Static methods
    //

    public static void main(String args[]) {
	SimpleTimeModel model = new SimpleTimeModel();
	Calendar cal = new GregorianCalendar(2009, 0, 10, 23, 59, 55);
	model.setTimeOffset(cal.getTimeInMillis() - System.currentTimeMillis());

	AnalogClock clock = new AnalogClock(model);
	clock.setInteractive(true);
	clock.setPreferredDiameter(300);

	TimeSpinnerModel spinModel = new TimeSpinnerModel(model);
	spinModel.setTimeSelectionModel(clock.getTimeSelectionModel());
	TimeSpinner spinner = new TimeSpinner(spinModel);

	CalendarBrowser browser = new CalendarBrowser(model,
	    new MonthTableModel(), new YearTableModel(),
	    new DecadeTableModel());

	JFrame frame = new JFrame();
	Container cont = frame.getContentPane();
	cont.setLayout(new FlowLayout());
	cont.add(browser);
	cont.add(spinner);
	cont.add(clock);

	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}

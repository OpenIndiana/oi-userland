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

package com.oracle.solaris.vp.util.swing.layout;

import java.awt.*;
import java.util.ArrayList;

public abstract class AbstractLayout implements LayoutManager {
    //
    // Inner classes
    //

    public interface SizedSet {
	/**
	 * Gets the number of elements in the set.
	 */
	int getCount();

	/**
	 * Gets the size of the {@code i}th element.
	 */
	int getSize(int i);

	/**
	 * Gets the weight of the {@code i}th element.
	 */
	float getWeight(int i);

	/**
	 * Sets the size of the {@code i}th element.
	 */
	void setSize(int i, int size);

	/**
	 * Sets the weight of the {@code i}th element.
	 */
	void setWeight(int i, float weight);
    }

    protected static class ArrayBasedSizedSet implements SizedSet {
	//
	// Instance data
	//

	private int[] sizes;
	private float[] weights;

	//
	// Constructors
	//

	public ArrayBasedSizedSet(int[] sizes, float[] weights) {
	    if (weights == null) {
		weights = new float[sizes.length];
	    } else

	    // Check for differing array lengths
	    if (sizes.length != weights.length) {
		throw new IllegalArgumentException(String.format(
		    "sizes (%d) and weights (%d) arrays differ in length",
		    sizes.length, weights.length));
	    }

	    this.sizes = sizes;
	    this.weights = weights;
	}

	//
	// SizedSet methods
	//

	@Override
	public int getCount() {
	    return sizes.length;
	}

	@Override
	public int getSize(int i) {
	    return sizes[i];
	}

	@Override
	public float getWeight(int i) {
	    return weights[i];
	}

	@Override
	public void setSize(int i, int size) {
	    sizes[i] = size;
	}

	@Override
	public void setWeight(int i, float weight) {
	    weights[i] = weight;
	}
    }

    //
    // LayoutManager methods
    //

    @Override
    public void addLayoutComponent(String name, Component comp) {
    }

    @Override
    public Dimension minimumLayoutSize(Container container) {
	return getLayoutSize(container, false);
    }

    @Override
    public Dimension preferredLayoutSize(Container container) {
	return getLayoutSize(container, true);
    }

    @Override
    public void removeLayoutComponent(Component comp) {
    }

    //
    // AbstractLayout methods
    //

    /**
     * Distribute the given extra space among the given sizes, subject to the
     * given weights.
     *
     * @param	    space
     *		    the excess space (may be negative) to distribute
     *
     * @param	    set
     *		    encapsulates the sizes/weights of the elements to distribute
     *		    {@code space} to
     *
     * @return	    the amount of space that could not be distributed
     */
    protected int distributeSpace(int space, SizedSet set) {
	int length = set.getCount();

	// Check for negative weights
	for (int i = 0; i < length; i++) {
	    float weight = set.getWeight(i);
	    if (weight < 0) {
		throw new IllegalArgumentException(
		    "negative weight: " + weight);
	    }
	}

	// Check for negative sizes
	for (int i = 0; i < length; i++) {
	    int size = set.getSize(i);
	    if (size < 0) {
		space -= size;
		set.setSize(i, 0);
	    }
	}

	if (space == 0) {
	    return space;
	}

	// If weights are all zeros, weight each size equally
	for (int i = 0; i < length; i++) {
	    if (set.getWeight(i) != 0) {
		break;
	    }

	    if (i == length - 1) {
		for (int j = 0; j < length; j++) {
		    set.setWeight(j, 1);
		}
	    }
	}

	// Verify that no non-zero weight is associated with a zero size
	boolean zeroedWeight = false;
	for (int i = 0; i < length; i++) {
	    if (set.getWeight(i) != 0 && set.getSize(i) == 0) {
		if (space <= 0) {
		    // Zero out weights corresponding to zero sizes (resulting
		    // sizes should not be negative)
		    set.setWeight(i, 0);
		    zeroedWeight = true;
		} else {
		    set.setSize(i, 1);
		    space--;
		}
	    }
	}

	// If we zeroed out a weight...
	if (zeroedWeight) {
	    for (int i = 0; i < length; i++) {
		if (set.getWeight(i) != 0) {
		    break;
		}

		// If all weights are now zeros
		if (i == length - 1) {
		    // Weight each non-zero size equally
		    for (int k = 0; k < length; k++) {
			if (set.getSize(k) != 0) {
			    set.setWeight(k, 1);
			}
		    }
		}
	    }
	}

	float sum = 0;
	for (int i = 0; i < length; i++) {
	    float weight = set.getWeight(i);
	    weight *= (float)set.getSize(i);
	    set.setWeight(i, weight);
	    sum += weight;
	}

	int notDistributed = 0;

	// Avoid divide-by-zero
	if (sum != 0) {
	    float remainder = 0;
	    int total = 0;

	    for (int i = 0; i < length; i++) {
		float weight = set.getWeight(i);
		weight /= sum;
		set.setWeight(i, weight);

		float delta = weight * (float)space;
		int trunc = (int)delta;

		// Keep track of truncated portion
		remainder += delta - trunc;

		int round = Math.round(remainder);
		if (round != 0) {
		    trunc += round;
		    remainder -= round;
		}

		total += trunc;

		int newSize = set.getSize(i) + trunc;
		if (newSize < 0) {
		    notDistributed += newSize;
		    newSize = 0;
		}

		set.setSize(i, newSize);
	    }
	}

	if (notDistributed != 0) {
	    for (int i = 0; i < length; i++) {
		if (set.getSize(i) != 0) {
		    notDistributed = distributeSpace(notDistributed, set);
		    break;
		}
	    }
	}

	return notDistributed;
    }

    /**
     * Distribute the given extra space among the given sizes, subject to the
     * given weights.
     *
     * @param	    space
     *		    the excess space (may be negative) to distribute
     *
     * @param	    sizes
     *		    the sizes to modify -- if any are negative, they will be
     *		    initially set to zero and the excess will be added to the
     *		    {@code space}
     *
     * @param	    weights
     *		    the weighting of each size, or {@code null} to apply
     *		    weightings equally across all sizes
     *
     * @exception   IllegalArgumentException
     *		    if the lengths of the two arrays are not equal, or a weight
     *		    is negative
     *
     * @return	    the amount of space that could not be distributed
     */
    protected int distributeSpace(int space, int[] sizes, float[] weights) {
	SizedSet set = new ArrayBasedSizedSet(sizes, weights);
	return distributeSpace(space, set);
    }

    public Component[] getLayoutComponents(Component[] comps) {
	// Weed out Components that don't need to be layed out
	ArrayList<Component> list = new ArrayList<Component>();
	for (Component comp : comps) {
	    if (needsLayout(comp)) {
		list.add(comp);
	    }
	}
	return list.toArray(new Component[list.size()]);
    }

    /**
     * Convenience method called by {@link
     * #minimumLayoutSize(java.awt.Container)} and {@link
     * #preferredLayoutSize(java.awt.Container)}.  This default implementation
     * returns {@code null}, in case subclasses choose to override those methods
     * directly.
     */
    protected Dimension getLayoutSize(Container container, boolean preferred) {
	return null;
    }

    /**
     * Called by {@code #getLayoutComponents(Component[])}, determines whether
     * the given {@code Component} should be layed out.  This default
     * implmentation returns {@code true} iff the {@code Component} is
     * non-{@code null}.
     */
    protected boolean needsLayout(Component c) {
	return c != null;
    }
}

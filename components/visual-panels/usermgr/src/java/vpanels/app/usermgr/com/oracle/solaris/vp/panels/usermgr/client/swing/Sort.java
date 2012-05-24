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
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */


/**
 * SMC code adapted for Visual Panels
 *
 * Sort: a class that uses the quicksort algorithm to sort an
 *         array of objects.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.util.Vector;
import java.util.Random;
import java.lang.Math;

@SuppressWarnings("unchecked")
public class Sort {

    private static Random rn = null;

    private static int MAX_ELEMENTS_FOR_COPY = 15000;

    static final int ASCENDING_SORT = 0;
    static final int DESCENDING_SORT = 0;

    private static void swap(Object arr[], int i, int j) {
        Object tmp;

        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    /**
     * quicksort the array of objects.
     *
     * @param arr[] - an array of objects
     * @param left - the start index - from where to begin sorting
     * @param right - the last index
     * @param comp - object that implemnts the Compare interface
     */
    private static void quicksort(Object arr[], int left, int right,
	Compare comp) {

        int i, last;

        if (left >= right) { /* do nothing if array contains fewer than two */
	    return;    /* two elements */
        }

        swap(arr, left, left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (comp.doCompare(arr[i], arr[left]) < 0) {
                swap(arr, ++last, i);
            }
        }
        swap(arr, left, last);

        quicksort(arr, left, last-1, comp);
        quicksort(arr, last+1, right, comp);
    }

    /**
     * quicksort the array of strings.
     *
     * @param arr[] - an array of strings
     * @param left - the start index - from where to begin sorting
     * @param right - the last index.
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    private static void quicksort(String arr[], int left, int right,
	int order) {

        int i, last;

        if (left >= right) { /* do nothing if array contains fewer than two */
	    return;	/* two elements */
        }
        swap(arr, left, left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (order == ASCENDING_SORT) {
                if (arr[i].compareTo(arr[left]) < 0) {
                    swap(arr, ++last, i);
                }
            } else {
                if (arr[i].compareTo(arr[left]) > 0) {
                    swap(arr, ++last, i);
                }
            }
        }
        swap(arr, left, last);
        quicksort(arr, left, last-1, order);
        quicksort(arr, last+1, right, order);
    }

    private static void swap(Vector vec, int i, int j) {
        Object tmp;

        tmp = vec.elementAt(i);
        vec.setElementAt(vec.elementAt(j), i);
        vec.setElementAt(tmp, j);
    }

    /**
     * quicksort the vector of objects.
     *
     * @param vec - a vector of objects
     * @param left - the start index - from where to begin sorting
     * @param right - the last index
     * @param comp - object that implements the Compare interface
     */
    private static void quicksort(Vector vec, int left, int right,
	Compare comp) {

        int i, last;

        if (left >= right) { /* do nothing if vector contains fewer than two */
	    return;	/* two elements */
        }
        swap(vec, left, left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (comp.doCompare(vec.elementAt(i), vec.elementAt(left)) < 0) {
                swap(vec, ++last, i);
            }
        }
        swap(vec, left, last);
        quicksort(vec, left, last-1, comp);
        quicksort(vec, last+1, right, comp);
    }

    /**
     * quicksort the vector of strings.
     *
     * @param vec - a vector of strings
     * @param left - the start index - from where to begin sorting
     * @param right - the last index.
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    private static void quicksort(Vector vec, int left, int right, int order) {
        int i, last;

        if (left >= right) { /* do nothing if vector contains fewer than two */
	    return;		/* two elements */
        }
        swap(vec, left, left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (order == ASCENDING_SORT) {
               if (((String)(vec.elementAt(i))).compareTo(
				(String)vec.elementAt(left)) < 0) {
                   swap(vec, ++last, i);
               }
            } else {
               if (((String)(vec.elementAt(i))).compareTo(
				(String)vec.elementAt(left)) > 0) {
                   swap(vec, ++last, i);
               }
            }
        }
        swap(vec, left, last);
        quicksort(vec, left, last-1, order);
        quicksort(vec, last+1, right, order);
    }

    /**
     * quicksort the vector of objects.
     *
     * @param vec - a vector of objects
     * @param left - the start index - from where to begin sorting
     * @param right - the last index
     * @param comp - object that implemnts the Compare interface
     */
    private static void quicksort(QuickVector vec, int left, int right,
	Compare comp) {

        int i, last;

        if (left >= right) { /* do nothing if vector contains fewer than two */
	    return;		/* two elements */
        }
        vec.quickSwapElementsAt(left,
				left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (comp.doCompare(vec.quickElementAt(i),
				vec.quickElementAt(left)) < 0) {
                vec.quickSwapElementsAt(++last, i);
            }
        }
        vec.quickSwapElementsAt(left, last);
        quicksort(vec, left, last-1, comp);
        quicksort(vec, last+1, right, comp);
    }

    /**
     * quicksort the vector of strings.
     *
     * @param vec - a vector of strings
     * @param left - the start index - from where to begin sorting
     * @param right - the last index.
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    private static void quicksort(QuickVector vec, int left, int right,
	int order) {

        int i, last;

        if (left >= right) { /* do nothing if vector contains fewer than two */
	    return;		/* two elements */
        }
        vec.quickSwapElementsAt(left,
				left+(Math.abs(rn.nextInt())%(right-left)+1));
        last = left;
        for (i = left+1; i <= right; i++) {
            if (order == ASCENDING_SORT) {
               if (((String)(vec.quickElementAt(i))).compareTo(
				(String)vec.quickElementAt(left)) < 0) {
                   vec.quickSwapElementsAt(++last, i);
               }
            } else {
               if (((String)(vec.quickElementAt(i))).compareTo(
				(String)vec.quickElementAt(left)) > 0) {
                   vec.quickSwapElementsAt(++last, i);
               }
            }
        }
        vec.quickSwapElementsAt(left, last);
        quicksort(vec, left, last-1, order);
        quicksort(vec, last+1, right, order);
    }

    /**
     * sort the array of objects.
     *
     * @param arr - a array of objects
     * @param comp - object that implemnts the Compare interface
     */
    public static void sort(Object arr[], Compare comp) {
        if (rn == null)
            rn = new Random();
        quicksort(arr, 0, arr.length-1, comp);
    }

    /**
     * sort the array of strings.
     *
     * @param arr - an array of strings
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    public static void sort(String arr[], int order) {
        if (rn == null)
            rn = new Random();
        quicksort(arr, 0, arr.length-1, order);
    }

    /**
     * sort the array of strings in ascending order
     *
     * @param arr - an array of strings
     */
    public static void sort(String arr[]) {
        sort(arr, ASCENDING_SORT);
    }

    /**
     * sort the vector of objects.
     *
     * @param vec - a vector of objects
     * @param comp - object that implemnts the Compare interface
     */
    public static void sort(Vector vec, Compare comp) {
        if (rn == null)
            rn = new Random();
        if (vec.size() > MAX_ELEMENTS_FOR_COPY) {
            // Would use up too much memory, so have to do an in place sort
            quicksort(vec, 0, vec.size()-1, comp);
        } else {
            // For small vector, optimize the sort by copying to an array
            // first
            Object[] arr = new Object[vec.size()];
            vec.copyInto(arr);
            quicksort(arr, 0, arr.length-1, comp);
            for (int i = 0; i < arr.length; i++) {
                vec.setElementAt(arr[i], i);
            }
        }
    }

    /**
     * sort the vector of strings.
     *
     * @param vec - a vector of strings
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    public static void sort(Vector vec, int order) {
        if (rn == null)
            rn = new Random();
        if (vec.size() > MAX_ELEMENTS_FOR_COPY) {
            // Would use up too much memory, so have to do an in place sort
            quicksort(vec, 0, vec.size()-1, order);
        } else {
            // For small vector, we can optimize the sort by copying to an array
            // first
            String[] arr = new String[vec.size()];
            vec.copyInto(arr);
            vec.removeAllElements();
            quicksort(arr, 0, arr.length-1, order);
            vec.setSize(arr.length);
            for (int i = 0; i < arr.length; i++) {
                vec.setElementAt(arr[i], i);
            }
        }
    }

    /**
     * sort the vector of strings in ascending order
     *
     * @param vec - a vector of strings
     */
    public static void sort(Vector vec) {
        sort(vec, ASCENDING_SORT);
    }

    /**
     * sort the vector of objects.
     *
     * @param vec - a vector of objects
     * @param comp - object that implemnts the Compare interface
     */
    public static void sort(QuickVector vec, Compare comp) {
        if (rn == null)
            rn = new Random();
        quicksort(vec, 0, vec.size()-1, comp);
    }

    /**
     * sort the vector of strings.
     *
     * @param vec - a vector of strings
     * @param order - ASCENDING_SORT or DESCENDING_SORT
     */
    public static void sort(QuickVector vec, int order) {
        if (rn == null)
            rn = new Random();
        quicksort(vec, 0, vec.size()-1, order);
    }

    /**
     * sort the vector of strings in ascending order
     *
     * @param vec - a vector of strings
     */
    public static void sort(QuickVector vec) {
        sort(vec, ASCENDING_SORT);
    }

}

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
 *
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/* A Solaris implementation of the Itanium C++ ABI __cxa_atexit
 * and __cxa_finalize functions.
 */

#include <stdlib.h>
#include <pthread.h>

#include "cxa_finalize.h"

#define __CXA_FUNC_CALLBACK 0
#define __CXA_FUNC_DONE     1
#define __CXA_ATEXIT_CHUNK  64

#define __DSO_TYPE_DESTRUCTOR 1
#define __DSO_TYPE_DLCLOSE    2

#define __DSO_SCOPE_LOCAL  4
#define __DSO_SCOPE_GLOBAL 8

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __cxxabi_atexit {
  void (*cxa_func)(void*);
  uint32_t type;
  uint32_t dso_type;
  uint32_t dso_scope;
  void* arg;
  void* dso;
} cxxabi_atexit;

typedef struct __cxxabi_atexit_list {
  uint32_t size;
  uint32_t nelem;
  cxxabi_atexit* list;
} cxxabi_atexit_list;

__attribute__((__visibility__("hidden")))
extern void* __dso_handle;

static cxxabi_atexit_list _list;
static pthread_mutex_t _mtx = PTHREAD_MUTEX_INITIALIZER;
static uint32_t _registered = 0;
static uint32_t _initialized = 0;

static int __register_with_atexit(const cxxabi_atexit* cxa);
static int __init_cxxabi_list(cxxabi_atexit** list);
static int __resize_cxxabi_list(const cxxabi_atexit* oldlist, uint32_t nelem,
                                cxxabi_atexit** newlist, uint32_t newsize);
void __cxa_atexit_callback(void);
static void __attribute__((destructor)) __do_cleanup(void);

int __init_cxxabi_list(cxxabi_atexit** list) {
  cxxabi_atexit* __p =
    (cxxabi_atexit *) malloc (__CXA_ATEXIT_CHUNK * sizeof(cxxabi_atexit));

  if (__p == NULL)
    return -1;

  *list = __p;
  return 0;
}

int __resize_cxxabi_list(const cxxabi_atexit* oldlist, uint32_t nelem,
                         cxxabi_atexit** newlist, uint32_t newsize) {
  register cxxabi_atexit* __p =
    (cxxabi_atexit *) malloc (newsize * sizeof(cxxabi_atexit));

  if (__p == NULL)
    return -1;

  const cxxabi_atexit* __l = oldlist;

  for (uint32_t i = 0; i < nelem; ++i)
    *(__p + i) = *(__l + i);

  *newlist = __p;

  return 0;
}

int __register_with_atexit(const cxxabi_atexit* cxa) {
  int ret = 0;

  if (cxa == NULL)
    return -1;

  pthread_mutex_lock(&_mtx);

  if (_initialized == 0) {
    _list.nelem = 0;

    ret = __init_cxxabi_list(&_list.list);

    if (ret == -1) {
      pthread_mutex_unlock(&_mtx);
      return ret;
    }

    _list.size = __CXA_ATEXIT_CHUNK;
    _initialized = 1;
  }

  if (_list.nelem == _list.size) {
    uint32_t newsize = _list.size * 2;
    cxxabi_atexit* __p;

    ret = __resize_cxxabi_list(_list.list, _list.nelem, &__p, newsize);

    if (ret == -1) {
      free (_list.list);
      _list.list = NULL;
      _list.size = 0;
      _list.nelem = 0;
      pthread_mutex_unlock(&_mtx);
      return ret;
    }

    _list.list = __p;
    _list.size = newsize;
  }

  if (_registered == 0) {
    ret = atexit(__cxa_atexit_callback);
    _registered = (ret == 0);
  }

  if (_registered != 1) {
    free (_list.list);
    _list.list = NULL;
    _list.size = 0;
    _list.nelem = 0;
    pthread_mutex_unlock(&_mtx);
    return ret;
  }

  register cxxabi_atexit* __p = _list.list + _list.nelem;
  *__p = *cxa;
  ++_list.nelem;

  pthread_mutex_unlock(&_mtx);
  return ret;
}

void __cxa_atexit_callback(void) {
  cxxabi_atexit* __e = _list.list + (_list.nelem - 1);
  cxxabi_atexit* __p = __e;

  if (__p == NULL)
    return;

  /* destroy local scope objects first */
  for (int i = _list.nelem; i > 0; --i) {
    if ((__p->type == __CXA_FUNC_CALLBACK) && 
        (__p->dso_scope == __DSO_SCOPE_LOCAL)) {
      __p->type = __CXA_FUNC_DONE;
      __p->cxa_func(__p->arg);
    }
    --__p;
  }

  __p = __e;

  /* destroy global scope objects last */
  for (int i = _list.nelem; i > 0; --i) {
    if ((__p->type == __CXA_FUNC_CALLBACK) &&
        (__p->dso_scope == __DSO_SCOPE_GLOBAL)) {
      __p->type = __CXA_FUNC_DONE;
      __p->cxa_func(__p->arg);
    }
    --__p;
  }
}

int __cxa_atexit(void (*destructor)(void*), void* arg, void* dso) {
  cxxabi_atexit cxa;

  cxa.type = __CXA_FUNC_CALLBACK;

  /* get dso_type from dso object itself */
  cxa.dso_type = __DSO_TYPE_DESTRUCTOR;

  /* get dso scope from dso object */
  cxa.dso_scope = __DSO_SCOPE_GLOBAL;
  cxa.cxa_func = destructor;
  cxa.arg = arg;
  cxa.dso = dso;

  return __register_with_atexit(&cxa);
}

int __cxa_finalize(void* dso) {
  uint32_t i;
  pthread_mutex_lock(&_mtx);

  if (_initialized == 0) {
    pthread_mutex_unlock(&_mtx);
    return -1;
  }

  cxxabi_atexit* __p = _list.list;
  pthread_mutex_unlock(&_mtx);

  if (__p == NULL)
    return -1;

  if (dso == NULL) {
    __p = _list.list + (_list.nelem - 1);

    pthread_mutex_lock(&_mtx);

    for (i = _list.nelem; i > 0; --i) {
      if (__p->type == __CXA_FUNC_DONE) {
        --__p;
        continue;
      }

      uint32_t __type = __p->type;
      __p->type = __CXA_FUNC_DONE;
      pthread_mutex_unlock(&_mtx);

      if (__type == __CXA_FUNC_CALLBACK)
        __p->cxa_func(__p->arg);

      --__p;
      pthread_mutex_lock(&_mtx);
    }

    pthread_mutex_unlock(&_mtx);
  } else {
    i = 0;
    do {
      if (__p->dso == dso) {
        pthread_mutex_lock(&_mtx);
        uint32_t __type = __p->type;
        __p->type = __CXA_FUNC_DONE;
        pthread_mutex_unlock(&_mtx);

        if (__type == __CXA_FUNC_CALLBACK)
          __p->cxa_func(__p->arg);
      }
      ++__p; ++i;
    } while (i < _list.nelem);
  }

  return 0;
}

void __attribute__((destructor)) __do_cleanup(void) {
  __cxa_finalize(__dso_handle);
}

#ifdef __cplusplus
}
#endif


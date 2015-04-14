/*
  This file is part of t8code.
  t8code is a C library to manage a collection (a forest) of multiple
  connected adaptive space-trees of general element classes in parallel.

  Copyright (C) 2015 the developers

  t8code is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  t8code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with t8code; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "t8_default_common.h"
#include "t8_default_tet.h"
#include "t8_dtet_bits.h"

typedef t8_dtet_t t8_default_tet_t;

static              size_t
t8_default_tet_size (void)
{
  return sizeof (t8_default_tet_t);
}

static int
t8_default_tet_maxlevel (void)
{
  return T8_DTET_MAXLEVEL;
}

static void
t8_default_tet_parent (const t8_element_t * elem, t8_element_t * parent)
{
  const t8_default_tet_t *t = (const t8_default_tet_t *) elem;
  t8_default_tet_t   *p = (t8_default_tet_t *) parent;

  t8_dtet_parent (t, p);
}

static void
t8_default_tet_sibling (const t8_element_t * elem,
                        int sibid, t8_element_t * sibling)
{
  const t8_default_tet_t *t = (const t8_default_tet_t *) elem;
  t8_default_tet_t   *s = (t8_default_tet_t *) sibling;

  t8_dtet_sibling (t, sibid, s);
}

static void
t8_default_tet_child (const t8_element_t * elem,
                      int childid, t8_element_t * child)
{
  const t8_default_tet_t *t = (const t8_default_tet_t *) elem;
  t8_default_tet_t   *c = (t8_default_tet_t *) child;

  t8_dtet_child (t, childid, c);
}

static void
t8_default_tet_nca (const t8_element_t * elem1,
                    const t8_element_t * elem2,
                    t8_element_t * nca){
    const t8_default_tet_t *t1 = (const t8_default_tet_t *) elem1;
    const t8_default_tet_t *t2 = (const t8_default_tet_t *) elem1;
    t8_default_tet_t   *c = (t8_default_tet_t *) nca;

    t8_dtet_nearest_common_ancestor(t1,t2,c);
}

t8_eclass_scheme_t *
t8_default_scheme_new_tet (void)
{
  t8_eclass_scheme_t *ts;

  ts = T8_ALLOC_ZERO (t8_eclass_scheme_t, 1);
  ts->eclass = T8_ECLASS_TET;

  ts->elem_size = t8_default_tet_size;
  ts->elem_maxlevel = t8_default_tet_maxlevel;

  ts->elem_parent = t8_default_tet_parent;
  ts->elem_sibling = t8_default_tet_sibling;
  ts->elem_child = t8_default_tet_child;
  ts->elem_nca = t8_default_tet_nca;

  ts->elem_new = t8_default_mempool_alloc;
  ts->elem_destroy = t8_default_mempool_free;

  ts->ts_destroy = t8_default_scheme_mempool_destroy;
  ts->ts_context = sc_mempool_new (sizeof (t8_default_tet_t));

  return ts;
}

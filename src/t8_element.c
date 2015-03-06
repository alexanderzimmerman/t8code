/*
  This file is part of t8code.
  t8code is a C library to manage a collection (a forest) of multiple
  connected adaptive space-trees of general element types in parallel.

  Copyright (C) 2010 The University of Texas System
  Written by Carsten Burstedde, Lucas C. Wilcox, and Tobin Isaac

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

#include <t8_element_quad.h>

t8_escheme_t *t8_escheme_vertex_default;
t8_escheme_t *t8_escheme_line_default;
t8_escheme_t *t8_escheme_quad_default;
t8_escheme_t *t8_escheme_triangle_default;
t8_escheme_t *t8_escheme_hex_default;
t8_escheme_t *t8_escheme_tet_default;
t8_escheme_t *t8_escheme_prism_default;
t8_escheme_t *t8_escheme_pyramid_default;

void
t8_escheme_new_defaults (void)
{
  t8_escheme_quad_default = t8_escheme_new_quad ();
}

void
t8_escheme_destroy_defaults (void)
{
  t8_escheme_destroy (t8_escheme_quad_default);
}

void
t8_escheme_destroy (t8_escheme_t * escheme)
{
  T8_ASSERT (escheme != NULL);

  if (escheme->escheme_destroy != NULL) {
    escheme->escheme_destroy (escheme->context);
  }
  T8_FREE (escheme);
}

void
t8_element_new (t8_escheme_t * scheme,
                int length, t8_element_t ** elems)
{
  T8_ASSERT (scheme != NULL && scheme->elem_new != NULL);
  scheme->elem_new (scheme->context, length, elems);
}

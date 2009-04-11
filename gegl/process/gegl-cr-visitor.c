/* This file is part of GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2006 Øyvind Kolås
 */

#include "config.h"

#include <glib-object.h>
#include <string.h>

#include "gegl.h"
#include "gegl-types-internal.h"
#include "gegl-cr-visitor.h"
#include "operation/gegl-operation.h"
#include "operation/gegl-operation-context.h"
#include "graph/gegl-node.h"
#include "graph/gegl-pad.h"
#include "graph/gegl-visitable.h"
#include "gegl-utils.h"


static void gegl_cr_visitor_class_init (GeglCRVisitorClass *klass);
static void gegl_cr_visitor_visit_node (GeglVisitor        *self,
                                        GeglNode           *node);


G_DEFINE_TYPE (GeglCRVisitor, gegl_cr_visitor, GEGL_TYPE_VISITOR)


static void
gegl_cr_visitor_class_init (GeglCRVisitorClass *klass)
{
  GeglVisitorClass *visitor_class = GEGL_VISITOR_CLASS (klass);

  visitor_class->visit_node = gegl_cr_visitor_visit_node;
}

static void
gegl_cr_visitor_init (GeglCRVisitor *self)
{
}

/* sets the context's result_rect and refs */
static void
gegl_cr_visitor_visit_node (GeglVisitor *self,
                            GeglNode    *node)
{
  GeglOperationContext *context = gegl_node_get_context (node, self->context_id);

  GEGL_VISITOR_CLASS (gegl_cr_visitor_parent_class)->visit_node (self, node);

  gegl_operation_calc_source_regions (node->operation, self->context_id);
  if (!context->cached)
    {
      gegl_rectangle_intersect (&context->result_rect, &node->have_rect, &context->need_rect);
      /* here we expand to the size requested by the operation to be cached */
      context->result_rect = gegl_operation_get_cached_region (node->operation, &context->result_rect);
    }
  context->refs = gegl_node_get_num_sinks (node);
}

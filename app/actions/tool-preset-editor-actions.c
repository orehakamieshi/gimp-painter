/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <gtk/gtk.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "actions-types.h"

#include "core/gimp.h"
#include "core/gimpcontext.h"

#include "widgets/gimpactiongroup.h"
#include "widgets/gimpdataeditor.h"
#include "widgets/gimphelp-ids.h"

#include "data-editor-commands.h"
#include "tool-preset-editor-actions.h"

#include "gimp-intl.h"


static const GimpActionEntry tool_preset_editor_actions[] =
{
  { "tool-preset-editor-popup", GIMP_STOCK_TOOL_PRESET,
    NC_("tool-preset-editor-action", "Tool Preset Editor Menu"), NULL, NULL, NULL,
    GIMP_HELP_BRUSH_EDITOR_DIALOG }
};


static const GimpToggleActionEntry tool_preset_editor_toggle_actions[] =
{
  { "tool-preset-editor-edit-active", GIMP_STOCK_LINKED,
    NC_("tool-preset-editor-action", "Edit Active Tool Preset"), NULL, NULL,
    G_CALLBACK (data_editor_edit_active_cmd_callback),
    FALSE,
    GIMP_HELP_BRUSH_EDITOR_EDIT_ACTIVE }
};


void
tool_preset_editor_actions_setup (GimpActionGroup *group)
{
  gimp_action_group_add_actions (group, "tool-preset-editor-action",
                                 tool_preset_editor_actions,
                                 G_N_ELEMENTS (tool_preset_editor_actions));

  gimp_action_group_add_toggle_actions (group, "tool-preset-editor-action",
                                        tool_preset_editor_toggle_actions,
                                        G_N_ELEMENTS (tool_preset_editor_toggle_actions));

}

void
tool_preset_editor_actions_update (GimpActionGroup *group,
                                   gpointer         user_data)
{
  GimpDataEditor *data_editor = GIMP_DATA_EDITOR (user_data);
  gboolean        edit_active = FALSE;

  edit_active = gimp_data_editor_get_edit_active (data_editor);

#define SET_SENSITIVE(action,condition) \
        gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
#define SET_ACTIVE(action,condition) \
        gimp_action_group_set_action_active (group, action, (condition) != 0)

  SET_ACTIVE ("tool-preset-editor-edit-active", edit_active);

#undef SET_SENSITIVE
#undef SET_ACTIVE
}

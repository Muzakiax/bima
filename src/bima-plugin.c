/***************************************************************************
 *            bima-plugin.c
 *
 *  Copyright  2006  Anas Muzakir
 *  anas.muzakir@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string.h> /* memset() */

#include "bima-plugin.h"

/* here are local prototypes */
static void bima_plugin_init (BimaPlugin * o) ;
static void bima_plugin_class_init (BimaPluginClass * c) ;

/* pointer to the class of our parent */
static GObjectClass *parent_class = NULL;

GType
bima_plugin_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (BimaPluginClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) bima_plugin_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (BimaPlugin),
			0 /* n_preallocs */,
			(GInstanceInitFunc) bima_plugin_init,
			NULL
		};

		type = g_type_register_static (G_TYPE_OBJECT, "BimaPlugin", &info, (GTypeFlags)0);
	}

	return type;
}

static void
___finalize(GObject *obj_self)
{

	//BimaPlugin *self  = BMA_PLUGIN (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);

}

static void 
bima_plugin_init (BimaPlugin * o )
{
	/* Empty */
}

static void 
bima_plugin_class_init (BimaPluginClass * c)
{

	GObjectClass *g_object_class  = (GObjectClass*) c;

	parent_class = g_type_class_ref (G_TYPE_OBJECT);

	g_object_class->finalize = ___finalize;
	
}

void  
bima_plugin_activate (BimaPlugin * self, BimaAppGui * appgui)
{
	g_return_val_if_fail (self != NULL, (void * )0);
	g_return_val_if_fail (BIMA_IS_PLUGIN (self), (void * )0);
	BIMA_PLUGIN_GET_CLASS (self)->activate(self, appgui);
	return;
}

void  
bima_plugin_deactivate (BimaPlugin * self, BimaAppGui * appgui)
{
	g_return_val_if_fail (self != NULL, (void * )0);
	g_return_val_if_fail (BIMA_IS_PLUGIN (self), (void * )0);
	BIMA_PLUGIN_GET_CLASS (self)->deactivate(self, appgui);
	return;
}

int  
bima_plugin_generate (BimaPlugin * self, FILE * ofile, gchar * token, BimaAppGui * appgui)
{
	int errCode;
	//g_printf("plugin parent call generate child\n");
	errCode = BIMA_PLUGIN_GET_CLASS (self)->generate(ofile, token, appgui);
	return errCode;
}

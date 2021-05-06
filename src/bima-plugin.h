/***************************************************************************
 *            bima-plugin.h
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

#ifndef __BIMA_PLUGIN_H__
#define __BIMA_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>

#include <stdio.h>
#include <stdlib.h>
#include "bima-app-gui.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Type checking and casting macros
 */
#define BIMA_TYPE_PLUGIN	(bima_plugin_get_type())
#define BIMA_PLUGIN(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_plugin_get_type(), BimaPlugin)
#define BIMA_PLUGIN_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), bima_plugin_get_type(), BimaPlugin const)
#define BIMA_PLUGIN_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), bima_plugin_get_type(), BimaPluginClass)
#define BIMA_IS_PLUGIN(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), bima_plugin_get_type ())

#define BIMA_PLUGIN_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), bima_plugin_get_type(), BimaPluginClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_BIMA_PLUGIN__
#define __TYPEDEF_BIMA_PLUGIN__
typedef struct _BimaPlugin BimaPlugin;
#endif
struct _BimaPlugin {
	GObject __parent__;
	/*< public >*/
};

/*
 * Class definition
 */
typedef struct _BimaPluginClass BimaPluginClass;
struct _BimaPluginClass {
	GObjectClass __parent__;

	/* virtual function */
	void (*activate)	(BimaPlugin * self,
						BimaAppGui * appgui);
	void (*deactivate)	(BimaPlugin * self,
						BimaAppGui * appgui);
	int (*generate)	(FILE * ofile,
						gchar * token,
						BimaAppGui * appgui);	
};


/*
 * Public methods
 */
GType	bima_plugin_get_type	(void);
void  	bima_plugin_activate	(BimaPlugin * self,
					BimaAppGui * appgui);
void  	bima_plugin_deactivate	(BimaPlugin * self,
					BimaAppGui * appgui);
int  	bima_plugin_generate	(BimaPlugin * self, FILE * ofile,
					gchar * token,
					BimaAppGui * appgui);

/* Macro for easy plugin builder 
 *
 */
#define BIMA_PLUGIN_REGISTER_TYPE(ClassName, plugin_name) 	\
															\
G_MODULE_EXPORT GType														\
get_plugin_type (void)								\
{															\
	static GType type = 0;									\
															\
	if (type == 0) {										\
		static const GTypeInfo info = {						\
			sizeof (ClassName##Class),						\
			(GBaseInitFunc) NULL,							\
			(GBaseFinalizeFunc) NULL,						\
			(GClassInitFunc) plugin_name##_class_init,		\
			(GClassFinalizeFunc) NULL,						\
			NULL /* class_data */,							\
			sizeof (ClassName),								\
			0 /* n_preallocs */,							\
			(GInstanceInitFunc) plugin_name##_init,			\
			NULL											\
		};													\
															\
		type = g_type_register_static (BIMA_TYPE_PLUGIN, #ClassName, &info, (GTypeFlags)0);		\
	}														\
															\
	return type;											\
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

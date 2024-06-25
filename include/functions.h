#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <webkit2/webkit2.h>
#include <gtk/gtk.h>
#include <string.h>

#include "resources.h"



const gchar			  * get_file_extension(const gchar *);
void					list_resources(const gchar*); 
const gchar			  * Check_resources(const gchar *, const gchar *);


#endif
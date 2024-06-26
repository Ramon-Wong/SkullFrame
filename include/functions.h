#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
#include <string.h>

#include "resources.h"



const gchar			  * get_file_extension(const gchar *);
void					list_resources( GResource *, const gchar*); 
const gchar			  * Check_resources( GResource *, const gchar *, const gchar *);


void                    C_HelloWorld();
void                    inject_js_functions(WebKitWebView *);

void                    inject_Hook_functions(WebKitWebView *);

#endif
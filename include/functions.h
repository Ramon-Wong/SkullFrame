#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
#include <string.h>

#include "resources.h"


extern WebKitWebView	* webview;
const gchar				* get_file_extension(const gchar *);
void					  list_resources( GResource *, const gchar*); 
const gchar				* Check_resources( GResource *, const gchar *, const gchar *);

void					  inject_Hook_functions(WebKitWebView *);
void					  initialize_C_Function(WebKitWebView *, const gchar *, GCallback, gpointer);
#endif
#include "functions.h"



// gboolean dispatch_custom_event(gpointer user_data) {
//     // WebKitWebView* webview = WEBKIT_WEB_VIEW(user_data);
    // const gchar* message = "Hello from C!";
    // gchar* js_code = g_strdup_printf("var event = new CustomEvent('hello_world', { detail: '%s' }); window.dispatchEvent(event);", message);
    // webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

    // g_free(js_code);
//     return TRUE;
// }


void on_load_changed(WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data) {

	if(load_event == WEBKIT_LOAD_STARTED){
		g_print("on_load_changed >>> New Data Source Request has been made.\n");

		const gchar* message = "WEBKIT_LOAD_FINISHED";
		gchar* js_code = g_strdup_printf("var event = new CustomEvent('WEBKIT_LOAD_FINISHED', { detail: '%s' }); window.dispatchEvent(event);", message);
		webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

		g_free(js_code);
	}

	if(load_event == WEBKIT_LOAD_REDIRECTED){
		g_print("on_load_changed >>> Data Source received a server redirect.\n");

		const gchar* message = "WEBKIT_LOAD_REDIRECTED";
		gchar* js_code = g_strdup_printf("var event = new CustomEvent('WEBKIT_LOAD_REDIRECTED', { detail: '%s' }); window.dispatchEvent(event);", message);
		webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

		g_free(js_code);
	}

	if(load_event == WEBKIT_LOAD_COMMITTED){
		g_print("on_load_changed >>> Data Source requirements are stabilished and the load is being performed.\n");

		const gchar* message = "WEBKIT_LOAD_COMMITTED";
		gchar* js_code = g_strdup_printf("var event = new CustomEvent('WEBKIT_LOAD_COMMITTED', { detail: '%s' }); window.dispatchEvent(event);", message);
		webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

		g_free(js_code);
	}

	if(load_event == WEBKIT_LOAD_FINISHED){
		g_print("on_load_changed >>> Data Source requirements are fully loaded and executed.  \n");

		const gchar* message = "WEBKIT_LOAD_FINISHED";
		gchar* js_code = g_strdup_printf("var event = new CustomEvent('WEBKIT_LOAD_FINISHED', { detail: '%s' }); window.dispatchEvent(event);", message);
		webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

		g_free(js_code);

	}	
}



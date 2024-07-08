#include "functions.h"



// gboolean dispatch_custom_event(gpointer user_data) {
//     // WebKitWebView* webview = WEBKIT_WEB_VIEW(user_data);
    // const gchar* message = "Hello from C!";
    // gchar* js_code = g_strdup_printf("var event = new CustomEvent('hello_world', { detail: '%s' }); window.dispatchEvent(event);", message);
    // webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);

    // g_free(js_code);
//     return TRUE;
// }



void SendEventMessage(  const gchar * event_name, const gchar * event_data){
	gchar* js_code = g_strdup_printf("var event = new CustomEvent('%s', { detail: '%s' }); window.dispatchEvent(event);", event_name, event_data);
	webkit_web_view_evaluate_javascript( webview, js_code, -1, NULL, NULL, NULL, NULL, NULL);
	g_free(js_code);
}


void on_load_changed( WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data) {

	if(load_event == WEBKIT_LOAD_STARTED){
		// seems like we only get this event
		g_print("on_load_changed >>> New Data Source Request has been made.\n");
		SendEventMessage( "WEBKIT_LOAD_STARTED", "WEBKIT_LOAD_STARTED");
	}

	if(load_event == WEBKIT_LOAD_REDIRECTED){
		// Javascript seems to be redirected, so it was never processed by our script
		g_print("on_load_changed >>> Data Source received a server redirect.\n");
		SendEventMessage( "WEBKIT_LOAD_REDIRECTED", "WEBKIT_LOAD_REDIRECTED");
	}

	if(load_event == WEBKIT_LOAD_COMMITTED){
		// Javascript seems to be committed, before execution
		g_print("on_load_changed >>> Data Source requirements are stabilished and the load is being performed.\n");
		SendEventMessage( "WEBKIT_LOAD_COMMITED", "WEBKIT_LOAD_COMMITED");
	}

	if(load_event == WEBKIT_LOAD_FINISHED){
		// Javascript seems to be finished, after it's finished
		g_print("on_load_changed >>> Data Source requirements are fully loaded and executed.  \n");
		SendEventMessage( "WEBKIT_LOAD_FINISHES", "WEBKIT_LOAD_FINISHES");
	}	
}


gboolean quit_main_loop(gpointer user_data) {
    // gtk_main_quit();
    return FALSE; // Return FALSE to remove the idle function
}


void on_destroy_window(GtkWidget* widget, gpointer user_data) {
    g_print("Window is being destroyed\n");

	SendEventMessage( "MAIN_THREAD_DESTROY_REQUEST", "MAIN_THREAD_DESTROY_REQUEST");
	// g_idle_add(quit_main_loop, NULL);
    gtk_main_quit();
}
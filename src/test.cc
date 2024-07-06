#include <webkit2/webkit2.h>
#include <gtk/gtk.h>

WebKitWebView *global_webview;

void SendEventMessage(const gchar *msg, const gchar *data) {
    gchar *js_code = g_strdup_printf(
        "var event = new CustomEvent('%s', { detail: '%s' }); window.dispatchEvent(event);",
        msg, data);
    webkit_web_view_run_javascript(global_webview, js_code, NULL, NULL, NULL);
    g_free(js_code);
}

void on_js_message(WebKitUserContentManager *manager, WebKitJavascriptResult *result, gpointer user_data) {
    JSGlobalContextRef js_context = webkit_javascript_result_get_global_context(result);
    JSValueRef js_value = webkit_javascript_result_get_value(result);

    if (JSValueIsString(js_context, js_value)) {
        JSStringRef js_string = JSValueToStringCopy(js_context, js_value, NULL);
        size_t buffer_size = JSStringGetMaximumUTF8CStringSize(js_string);
        gchar *buffer = g_new(gchar, buffer_size);
        JSStringGetUTF8CString(js_string, buffer, buffer_size);

        g_print("Received message from JavaScript: %s\n", buffer);

        // Process the message and send back a response
        SendEventMessage("CFunctionReturn_js_Call", "42");

        JSStringRelease(js_string);
        g_free(buffer);
    }
}

void initialize_C_Function(WebKitWebView *_webview, const gchar *js_function_name, GCallback cback, gpointer user_data) {
    WebKitUserContentManager *contentManager = webkit_web_view_get_user_content_manager(_webview);
    gchar *detailed_signal = g_strdup_printf("script-message-received::%s", js_function_name);

    g_signal_connect(contentManager, detailed_signal, cback, user_data);
    webkit_user_content_manager_register_script_message_handler(contentManager, js_function_name);
    g_free(detailed_signal);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    global_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(global_webview));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    initialize_C_Function(global_webview, "js_Call", G_CALLBACK(on_js_message), global_webview);

    webkit_web_view_load_uri(global_webview, "file:///path/to/your/file.html");

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

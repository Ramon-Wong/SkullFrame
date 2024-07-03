#include <webkit2/webkit2.h>
#include <gtk/gtk.h>

gboolean dispatch_custom_event(gpointer user_data) {
    WebKitWebView* webview = WEBKIT_WEB_VIEW(user_data);
    const gchar* message = "Hello from C!";
    gchar* js_code = g_strdup_printf("var event = new CustomEvent('hello_world', { detail: '%s' }); window.dispatchEvent(event);", message);
    webkit_web_view_evaluate_javascript(webview, js_code, NULL, NULL, NULL);
    g_free(js_code);

    // Return TRUE to keep the timer running
    return TRUE;
}

void on_window_destroy(GtkWidget* widget, gpointer user_data) {
    g_print("Window is being destroyed\n");
    gtk_main_quit();
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    WebKitWebContext* context = webkit_web_context_new();
    WebKitWebView* webview = WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(context));
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "WebView Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), webview);

    webkit_web_view_load_uri(webview, "file:///path/to/your/html/file.html");

    // Set up a timer to dispatch the custom event every 5 seconds (5000 milliseconds)
    g_timeout_add(5000, dispatch_custom_event, webview);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

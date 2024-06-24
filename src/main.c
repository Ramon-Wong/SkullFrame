#include "functions.h"




// gcc -o test src/TestFinal.c resources.c -I include `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    WebKitWebContext* context = webkit_web_context_new();
    const gchar* scheme = "resources";
    webkit_web_context_register_uri_scheme(context, scheme, my_uri_scheme_request_callback, NULL, NULL);

    WebKitWebView* webview = WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(context));
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

    // Get WebKit settings and optimize them
    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
	webkit_settings_set_enable_developer_extras(settings, TRUE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    webkit_web_view_load_uri(webview, "resources:///myapp/web/main.html");               // use "resources:///myapp/web/Cow.html" to get /web/Cow.html

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
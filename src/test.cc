#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

typedef struct {
    const char *name;
    int width;
    int height;
    int developerEnabled;
    const char *uriPath;
} Config;

Config Global_Config;

void inject_Hook_functions(WebKitWebView *webview) {
    // Your existing hook functions
}

void my_uri_scheme_request_callback(WebKitURISchemeRequest *request, gpointer user_data) {
    // Your existing URI scheme request callback code
}

// Function to run JavaScript code
void run_js_code(WebKitWebView *webview, const gchar *js_code) {
    webkit_web_view_run_javascript(webview, js_code, NULL, NULL, NULL);
}

// Custom signal handler
void on_custom_signal(WebKitWebView *webview, gpointer user_data) {
    const gchar *js_code = "sayHello()";
    run_js_code(webview, js_code);
}

// Callback for load-changed signal
void on_load_changed(WebKitWebView *webview, WebKitLoadEvent load_event, gpointer user_data) {
    if (load_event == WEBKIT_LOAD_FINISHED) {
        g_signal_emit_by_name(webview, "custom-signal");
    }
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    if (argc >= 2) {
        printf("\n\nArgument: %s\n", argv[1]);
        // Initialize Global_Config with the provided argument
    } else {
        printf("\n\nNo arguments provided.\n");
    }

    WebKitWebContext *context = webkit_web_context_new();
    const gchar *scheme = "resources";
    webkit_web_context_register_uri_scheme(context, scheme, my_uri_scheme_request_callback, NULL, NULL);

    WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(context));
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), Global_Config.name);
    gtk_window_set_default_size(GTK_WINDOW(window), Global_Config.width, Global_Config.height);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

    // Check if Developer mode is enabled
    if (Global_Config.developerEnabled == 1) {
        WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
        webkit_settings_set_enable_developer_extras(settings, TRUE);
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(webview, "load-changed", G_CALLBACK(on_load_changed), NULL);

    // Register and connect the custom signal
    g_signal_new("custom-signal", G_TYPE_FROM_CLASS(webkit_web_view_get_type()),
                 G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL, G_TYPE_NONE, 0);
    g_signal_connect(webview, "custom-signal", G_CALLBACK(on_custom_signal), NULL);

    inject_Hook_functions(webview);
    webkit_web_view_load_uri(webview, Global_Config.uriPath);
    g_timeout_add(5000, dispatch_custom_event, webview);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}



<!DOCTYPE html>
<html>
<head>
    <title>WebKit2GTK Example</title>
    <script type="text/javascript">
        function sayHello() {
            alert("Hello from C!");
        }

        window.onload = function() {
            if (window.webkit && window.webkit.messageHandlers && window.webkit.messageHandlers.customSignalHandler) {
                window.webkit.messageHandlers.customSignalHandler.postMessage = function(message) {
                    if (message === 'custom-signal') {
                        sayHello();
                    }
                };
            }
        };
    </script>
</head>
<body>
    <h1>WebKit2GTK Example</h1>
    <p>This is a simple WebKit2GTK browser.</p>
</body>
</html>

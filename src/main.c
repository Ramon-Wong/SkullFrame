#include "functions.h"



// gcc -o test src/TestFinal.c resources.c -I include `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`









void my_uri_scheme_request_callback(WebKitURISchemeRequest* request, gpointer user_data) {
    const gchar* uri = webkit_uri_scheme_request_get_uri(request);
    const gchar* path = webkit_uri_scheme_request_get_path(request);
    
    g_print("Request URI: %s\n", uri);
    g_print("Request Path: %s\n", path);
    
    const gchar* data = NULL;
    gsize data_length = 0;
    const gchar* mime_type = "text/html";

    if( g_strcmp0( Check_resources("/", path), path) == 0){
        g_print("found: %s \n\n", path); 

        GResource *resources = resources_get_resource();
        GBytes *bytes = g_resource_lookup_data ( resources,  path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);       

        if(bytes){
            data = (const gchar*) g_bytes_get_data( bytes, &data_length);
            // g_print("%s", data);
            g_bytes_unref(bytes);

            const gchar* file_extension = get_file_extension(path);
            if (g_strcmp0(file_extension, "html") == 0) {               mime_type = "text/html";                g_print(" HTML");   data_length = strlen(data);
                } else if (g_strcmp0(file_extension, "js") == 0) {      mime_type = "application/javascript";   g_print(" JS");     data_length = strlen(data);
                } else if (g_strcmp0(file_extension, "css") == 0) {     mime_type = "text/css";                 g_print(" CSS");    data_length = strlen(data);
                } else if (g_strcmp0(file_extension, "jpg") == 0 || g_strcmp0(file_extension, "jpeg") == 0) {   g_print(" JPEG");
                } else if (g_strcmp0(file_extension, "png") == 0) {     g_print(" PNG");
                } else if (g_strcmp0(file_extension, "gif") == 0) {     g_print(" GIF");
            }

        }else{
            g_print("Failed to load resource.\n");
        }
    }else{

        if (g_strcmp0(path, "/Cow.html") == 0) {
            data = "<html><script type='text/javascript' src='resources://example/script/Cow.js'></script><body>Hello, this is Cow!</body></html>";
            data_length = strlen(data);
        } else if (g_strcmp0(path, "/Chicken.html") == 0) {
            data = "<html><script type='text/javascript' src='resources://example/script/Chicken.js'></script><body>Hello, this is Chicken!</body></html>";
            data_length = strlen(data);
        } else if (g_strcmp0(path, "/script/Cow.js") == 0) {
            data = "console.log('Cow script loaded, eat more cow');";
            g_print("Loading cow script");        
            data_length = strlen(data);
            mime_type = "application/javascript";
        } else if (g_strcmp0(path, "/script/Chicken.js") == 0) {
            data = "console.log('Chicken script loaded');";
            g_print("Loading chicken script");
            data_length = strlen(data);
            mime_type = "application/javascript";
        } else {
            data = "<html><body>Resource not found.</body></html>";
            data_length = strlen(data);
        }
    }

    if (data) {
        GInputStream* stream = g_memory_input_stream_new_from_data(data, data_length, NULL);
        webkit_uri_scheme_request_finish(request, stream, data_length, mime_type);
        g_object_unref(stream);
    }
}


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    WebKitWebContext* context = webkit_web_context_new();
    const gchar* scheme = "resources";
    webkit_web_context_register_uri_scheme(context, scheme, my_uri_scheme_request_callback, NULL, NULL);

    WebKitWebView* webview      = WEBKIT_WEB_VIEW(webkit_web_view_new_with_context(context));
    GtkWidget* window           = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "My WebKitGTK Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

    // Get WebKit settings and optimize them
    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
	webkit_settings_set_enable_developer_extras(settings, TRUE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    webkit_web_view_load_uri(webview, "resources:///myapp/web/main.html");               // use "resources:///myapp/web/Cow.html" to get /web/Cow.html

    list_resources("/");

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

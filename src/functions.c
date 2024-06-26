#include "functions.h"





WebKitJavascriptResult * g_result;

static void web_view_javascript_finished(GObject * object, GAsyncResult * result, gpointer user_data){

    JSCValue               *value;
    GError                 *error = NULL;

    value = webkit_web_view_evaluate_javascript_finish( webview, result, &error);
    if (!value) {
        g_warning ("Error running javascript: %s", error->message);
        g_error_free (error);
        return;
    }

    if(jsc_value_is_string(value)){
        gchar        *str_value = jsc_value_to_string (value);
        JSCException *exception = jsc_context_get_exception (jsc_value_get_context (value));
        if (exception)
            g_warning ("Error running javascript(Exception): %s", jsc_exception_get_message (exception));
        else
            g_print ("Script result: %s\n", str_value);
        g_free (str_value);
    } else {
        // g_warning ("Error running javascript(jsc_value_is_string): unexpected return value %s", jsc_value_to_string (value));
    }
    webkit_javascript_result_unref (g_result);
}



// window.webkit.messageHandlers.js_Call.postMessage("test");
void C_HelloWorld1(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    g_print("Hello world, got your call from JavaScript\n");

    g_result = result;

    gchar *script = g_strdup_printf("window.onCFunctionReturn('Happy Motherfucking Every Day');");
    webkit_web_view_evaluate_javascript( webview, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);        
    g_free(script);    
}


// window.webkit.messageHandlers.js_Call.postMessage("test");
void  C_HelloWorld2(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    JSCValue * value = webkit_javascript_result_get_js_value(result);

    // Check if the value is a string
    if (jsc_value_is_string(value)) {
        gchar *message = jsc_value_to_string(value);
        g_print("Received message: %s\n", message);
        g_free(message);
    } else {
        g_print("Message is not a string.\n");
    }
}


// window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);
void C_HelloWorld3(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    JSCValue * value = webkit_javascript_result_get_js_value(result);

    // Check if the value is an array
    if (jsc_value_is_array(value)) {
        JSCValue *item1 = jsc_value_object_get_property_at_index(value, 0);
        JSCValue *item2 = jsc_value_object_get_property_at_index(value, 1);
        JSCValue *item3 = jsc_value_object_get_property_at_index(value, 2);

        if (jsc_value_is_string(item1)) {
            gchar *message = jsc_value_to_string(item1);
            g_print("Received message: %s\n", message);
            g_free(message);
        } else { g_print("First item is not a string.\n"); }

        if (jsc_value_is_number(item2)) {
            int number = jsc_value_to_int32(item2);
            g_print("Received number: %d\n", number);
        } else { g_print("Second item is not a number.\n");}

        if (jsc_value_is_boolean(item3)) {
            gboolean flag = jsc_value_to_boolean(item3);
            g_print("Received boolean: %s\n", flag ? "true" : "false");
        } else { g_print("Third item is not a boolean.\n"); }
    } else {
        g_print("Message is not an array.\n");
    }

    webkit_javascript_result_unref(result);
}


void initialize_C_Function(WebKitWebView* webView) {
    WebKitUserContentManager* contentManager = webkit_web_view_get_user_content_manager(webView);
    // Add a script message handler

    g_signal_connect(contentManager, "script-message-received::js_Call", G_CALLBACK(C_HelloWorld1), NULL);
    webkit_user_content_manager_register_script_message_handler(contentManager, "js_Call");
}



void inject_Hook_functions(WebKitWebView * webview){

    g_print("injecting Hook Functions");
    initialize_C_Function(webview);
}


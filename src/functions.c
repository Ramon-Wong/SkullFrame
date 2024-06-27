#include "functions.h"




// window.webkit.messageHandlers.js_Call.postMessage("test");
void C_HelloWorld1(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    g_print("Hello world, got your call from JavaScript\n");
}


// window.webkit.messageHandlers.js_Call.postMessage("test");
void  C_HelloWorld2(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    JSCValue *value = webkit_javascript_result_get_js_value(result);

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
    JSCValue *value = webkit_javascript_result_get_js_value(result);

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
}


void initialize_C_Function(WebKitWebView* webView) {
    WebKitUserContentManager* contentManager = webkit_web_view_get_user_content_manager(webView);

    // Create a user script
    const gchar* script =
        "window.js_Call = function(message) {"
        "    return window.webkit.messageHandlers.js_Call.postMessage(message);"
        "};";
    WebKitUserScript* userScript = webkit_user_script_new(script, WEBKIT_USER_CONTENT_INJECT_TOP_FRAME, WEBKIT_USER_SCRIPT_INJECT_AT_DOCUMENT_START, NULL, NULL);
    webkit_user_content_manager_add_script(contentManager, userScript);

    // Add a script message handler
    g_signal_connect(contentManager, "script-message-received::js_Call", G_CALLBACK(C_HelloWorld3), NULL);
    webkit_user_content_manager_register_script_message_handler(contentManager, "js_Call");
}


void inject_Hook_functions(WebKitWebView * webview){

    g_print("injecting Hook Functions");
    initialize_C_Function(webview);
}



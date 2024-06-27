#include "functions.h"




void C_HelloWorld(){
    g_print("Hello world, got your call from JavaScript\n");
}


// JSValueRef js_C_HelloWorld(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
//     C_HelloWorld();
//     return JSValueMakeUndefined(context);
// }

void inject_js_functions(WebKitWebView* webview) {
    WebKitUserContentManager* manager = webkit_web_view_get_user_content_manager(webview);
    webkit_user_content_manager_register_script_message_handler(manager, "C_HelloWorld");

    g_signal_connect(manager, "script-message-received::C_HelloWorld", G_CALLBACK(C_HelloWorld), NULL);
}







JSValueRef js_C_Hello(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if (argumentCount == 1 && JSValueIsString(context, arguments[0])) {
        JSStringRef jsString = JSValueToStringCopy(context, arguments[0], exception);
        size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
        char* name = (char*)g_malloc(maxBufferSize);
        JSStringGetUTF8CString(jsString, name, maxBufferSize);
        JSStringRelease(jsString);

        g_print("\n >> %s << \n", name);

        g_free(name);
    } else {
        g_print("Invalid argument passed from JavaScript\n");
    }

    return JSValueMakeUndefined(context);
}



// static gboolean js_Call_new(WebKitUserContentManager* manager, JSCValue* value, WebKitScriptMessageReply* reply, gpointer user_data) {
//     // Check if the value is a string
//     if (jsc_value_is_string(value)) {
//         gchar* message = jsc_value_to_string(value);
//         g_print("Received string message: %s\n", message);
//         g_free(message);

//         // Reply with a message
//         JSCValue* returnValue = jsc_value_new_string(jsc_value_get_context(value), "Reply from C");
//         webkit_script_message_reply_return_value(reply, returnValue);
//     } else if (jsc_value_is_number(value)) {
//         double number = jsc_value_is_number(value);
//         g_print("Received number message: %f\n", number);

//         // Reply with a number
//         JSCValue* returnValue = jsc_value_new_number(jsc_value_get_context(value), number * 2);
//         webkit_script_message_reply_return_value(reply, returnValue);
//     } else {
//         g_print("Received unknown type message\n");

//         // Reply with an error message
//         webkit_script_message_reply_return_error_message(reply, "Unsupported message type");
//     }

//     return TRUE;
// }


JSValueRef js_Call(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, 
                        size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception){
    g_print("Function called with %zu arguments.\n", (size_t)argumentCount);

    if (argumentCount == 1) {
        g_print("Correct number of arguments.\n");

        // Check if the argument is a string
        if (JSValueIsString(context, arguments[0])) {
            g_print("Argument is a string.\n");

            // Convert JS string to C string
            JSStringRef jsString = JSValueToStringCopy(context, arguments[0], exception);
            size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
            char* name = (char*)g_malloc(maxBufferSize);
            JSStringGetUTF8CString(jsString, name, maxBufferSize);
            JSStringRelease(jsString);

            g_print("\n >> %s << \n", name);

            // Clean up
            g_free(name);
        } else {
            g_print("Argument is not a string.\n");
        }
    } else {
        g_print("Invalid argument count.\n");
    }

    return JSValueMakeUndefined(context);
}


void C_teststring(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
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


void C_HelloWorld2(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
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



// WebKitWebView *view = webkit_web_view_new ();
// WebKitUserContentManager *manager = webkit_web_view_get_user_content_manager ();
// g_signal_connect (manager, "script-message-received::foobar", G_CALLBACK (handle_script_message), NULL);
// webkit_user_content_manager_register_script_message_handler (manager, "foobar");


void initialize_webkit(WebKitWebView* webView) {
    WebKitUserContentManager* contentManager = webkit_web_view_get_user_content_manager(webView);

    // Create a user script
    const gchar* script =
        "window.js_Call = function(message) {"
        "    return window.webkit.messageHandlers.js_Call.postMessage(message);"
        "};";
    WebKitUserScript* userScript = webkit_user_script_new(script, WEBKIT_USER_CONTENT_INJECT_TOP_FRAME, WEBKIT_USER_SCRIPT_INJECT_AT_DOCUMENT_START, NULL, NULL);
    webkit_user_content_manager_add_script(contentManager, userScript);

    // Add a script message handler
    g_signal_connect(contentManager, "script-message-received::js_Call", G_CALLBACK(C_HelloWorld2), NULL);
    webkit_user_content_manager_register_script_message_handler(contentManager, "js_Call");
}



void inject_Hook_functions(WebKitWebView * webview){

    g_print("injecting Hook Functions");
    inject_js_functions(webview);
    initialize_webkit(webview);
}



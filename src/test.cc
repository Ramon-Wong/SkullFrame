#include <webkit2/webkit2.h>

void C_HelloWorld1(WebKitUserContentManager* manager, WebKitJavascriptResult* result, gpointer user_data) {
    g_print("Hello world, got your call from JavaScript\n");

    const char *message = "TOP SECRET";

    // Create the JavaScript snippet that calls the JavaScript function with the data
    char jsSnippet[256];
    snprintf(jsSnippet, sizeof(jsSnippet), "handleDataFromC('%s');", message);

    // Get the WebView from the user_data (assuming user_data is your WebView)
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(user_data);

    // Evaluate the JavaScript code
    webkit_web_view_run_javascript(web_view, jsSnippet, NULL, NULL, NULL);
}


well, at least you were able to remember, without me inserting text to you, sweet, but anyway.

so from what I understand, to send data back to javascript, and as a function return value.
You have to literally execute a javascript function named handleDataFromC(..), maybe this piece will be embedded into the larger js function.

Problem I have is, like always previously with gtk, that there are not much of info here and to get the proper working function.
I've to do some research myself and feed that to you for processing. 

Thus, I was digging up some info regarding these functions.

gint    g_snprintf (gchar *string, gulong n, gchar const *format,...);
void    webkit_web_view_run_javascript ( WebKitWebView* web_view, const gchar* script, GCancellable * cancellable, GAsyncReadyCallback callback, gpointer user_data)

based on the examples you or aka chatgpt gave me.

    char jsSnippet[256];
    snprintf(jsSnippet, sizeof(jsSnippet), "handleDataFromC('%s');", message);
    webkit_web_view_run_javascript( WEBKIT_WEB_VIEW(user_data), jsSnippet, NULL, NULL, NULL);

second problem is creating the needed callback required for webkit_web_view_run_javascript
So lets talk about and analyse the functions necessary for this to work and don't forget the GAsyncReadyCallback callback for webkit_web_view_run_javascript






webkit_web_view_evaluate_javascript( WebKitWebView* web_view, const char* script, gssize length, const char* world_name, 
                                        const char* source_uri, GCancellable* cancellable, GAsyncReadyCallback callback,  gpointer user_data
)

static void
web_view_javascript_finished (GObject * object, GAsyncResult *result, gpointer user_data){
    JSCValue               *value;
    GError                 *error = NULL;

    value = webkit_web_view_evaluate_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
    if (!value) {
        g_warning ("Error running javascript: %s", error->message);
        g_error_free (error);
        return;
    }

    if (jsc_value_is_string (value)) {
        gchar        *str_value = jsc_value_to_string (value);
        JSCException *exception = jsc_context_get_exception (jsc_value_get_context (value));
        if (exception)
            g_warning ("Error running javascript: %s", jsc_exception_get_message (exception));
        else
            g_print ("Script result: %s\n", str_value);
        g_free (str_value);
    } else {
        g_warning ("Error running javascript: unexpected return value");
    }
    webkit_javascript_result_unref (js_result);
}

static void
web_view_get_link_url (WebKitWebView *web_view, const gchar   *link_id) {
    gchar *script = g_strdup_printf ("window.document.getElementById('%s').href;", link_id);
    webkit_web_view_evaluate_javascript (web_view, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);
    g_free (script);
}






Hey ChatGPT. Good morning
I'm trying to work on this function, which I got from the man page of webview/webkit2gtk.
What I'm trying to do is run a piece of javascript from C and in the future I wanna use this experience to return results from C functions to JS.
And from the looks of it, I need these two functions below to work, also these are from the man page and it gives me lots of warning.

Description of webkit_web_view_evaluate_javascript
Asynchronously evaluate script in the script world with name world_name of the main frame current context in web_view. If world_name is NULL, the default world is used. Any value that is not NULL is a distinct world. The source_uri will be shown in exceptions and doesn’t affect the behavior of the script. When not provided, the document URL is used.
Note that if WebKitSettings:enable-javascript is FALSE, this method will do nothing. If you want to use this method but still prevent web content from executing its own JavaScript, then use WebKitSettings:enable-javascript-markup.
When the operation is finished, callback will be called. You can then call webkit_web_view_evaluate_javascript_finish() to get the result of the operation.
This is an example of using webkit_web_view_evaluate_javascript() with a script returning a string:

static void
web_view_javascript_finished (GObject * object, GAsyncResult *result, gpointer user_data){
    JSCValue               *value;
    GError                 *error = NULL;
    WebKitJavascriptResult * js_result;

    value = webkit_web_view_evaluate_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
    if (!value) {
        g_warning ("Error running javascript: %s", error->message);
        g_error_free (error);
        return;
    }

    if (jsc_value_is_string (value)) {
        gchar        *str_value = jsc_value_to_string (value);
        JSCException *exception = jsc_context_get_exception (jsc_value_get_context (value));
        if (exception)
            g_warning ("Error running javascript: %s", jsc_exception_get_message (exception));
        else
            g_print ("Script result: %s\n", str_value);
        g_free (str_value);
    } else {
        g_warning ("Error running javascript: unexpected return value");
    }
    webkit_javascript_result_unref (js_result);
}

static void
web_view_get_link_url (WebKitWebView * web_view, const gchar * link_id){
    gchar *script = g_strdup_printf ("window.document.getElementById('%s').href;", link_id);
    webkit_web_view_evaluate_javascript (web_view, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);
    g_free (script);
}



static void
web_view_javascript_finished (GObject      *object,
                              GAsyncResult *result,
                              gpointer      user_data)
{
    JSCValue               *value;
    GError                 *error = NULL;

    value = webkit_web_view_evaluate_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);
    if (!value) {
        g_warning ("Error running javascript: %s", error->message);
        g_error_free (error);
        return;
    }

    if (jsc_value_is_string (value)) {
        gchar        *str_value = jsc_value_to_string (value);
        JSCException *exception = jsc_context_get_exception (jsc_value_get_context (value));
        if (exception)
            g_warning ("Error running javascript: %s", jsc_exception_get_message (exception));
        else
            g_print ("Script result: %s\n", str_value);
        g_free (str_value);
    } else {
        g_warning ("Error running javascript: unexpected return value");
    }
    webkit_javascript_result_unref (js_result);
}

static void
web_view_get_link_url (WebKitWebView *web_view,
                       const gchar   *link_id)
{
    gchar *script = g_strdup_printf ("window.document.getElementById('%s').href;", link_id);
    webkit_web_view_evaluate_javascript (web_view, script, -1, NULL, NULL, NULL, web_view_javascript_finished, NULL);
    g_free (script);
}


#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>

static void web_view_javascript_finished(GObject *object, GAsyncResult *result, gpointer user_data) {
    g_print("web_view_javascript_finished >> ");
    JSCValue *value;
    GError *error = NULL;

    value = webkit_web_view_evaluate_javascript_finish(webview, result, &error);
    if (!value) {
        g_warning("Error running javascript: %s", error->message);
        g_error_free(error);
        return;
    }

    JSCException *exception = jsc_context_get_exception(jsc_value_get_context(value));
    if (exception) {
        g_warning("Error running javascript(Exception): %s", jsc_exception_get_message(exception));
    } else {
        if (jsc_value_is_string(value)) {
            gchar *str_value = jsc_value_to_string(value);
            g_print("Script result: %s\n", str_value);
            g_free(str_value);
        } else if (jsc_value_is_number(value)) {
            double num_value = jsc_value_to_double(value);
            g_print("Script result is a number: %f\n", num_value);
        } else if (jsc_value_is_boolean(value)) {
            gboolean bool_value = jsc_value_to_boolean(value);
            g_print("Script result is a boolean: %s\n", bool_value ? "true" : "false");
        } else if (jsc_value_is_object(value)) {
            gchar *obj_value = jsc_value_to_string(value);
            g_print("Script result is an object: %s\n", obj_value);
            g_free(obj_value);
        } else {
            gchar *unknown_value = jsc_value_to_string(value);
            g_print("Script result is of an unexpected type: %s\n", unknown_value);
            g_free(unknown_value);
        }
    }

    g_object_unref(value);
    webkit_javascript_result_unref(g_result);
}













function callCHelloWorld() {
    return new Promise((resolve, reject) => {
        window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);

        window.onCFunctionResult = function(result) {
            resolve(result);
        };
    });
}


#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>

// Function to send data back to JavaScript
void send_data_to_javascript(WebKitWebView *web_view, const gchar *data) {
    gchar *script = g_strdup_printf("window.onCFunctionResult(%s);", data);
    webkit_web_view_evaluate_javascript(web_view, script, -1, NULL, NULL, NULL, NULL, NULL);
    g_free(script);
}

// Message handler callback
void C_HelloWorld1(WebKitUserContentManager *manager, WebKitJavascriptResult *result, gpointer user_data) {
    g_print("Hello world, got your call from JavaScript\n");

    JSCValue *value = webkit_javascript_result_get_js_value(result);
    if (jsc_value_is_array(value)) {
        JSCValue *str_value = jsc_value_to_string(jsc_value_get_property_at_index(value, 0));
        JSCValue *num_value = jsc_value_to_number(jsc_value_get_property_at_index(value, 1));
        JSCValue *bool_value = jsc_value_to_boolean(jsc_value_get_property_at_index(value, 2));

        // Here you can execute your C function and get the result
        const gchar *c_result = "C function result"; // Replace with actual function result

        // Send result back to JavaScript
        send_data_to_javascript(WEBKIT_WEB_VIEW(user_data), c_result);
    }
}

// Register the message handler
void register_message_handler(WebKitWebView *web_view) {
    WebKitUserContentManager *content_manager = webkit_web_view_get_user_content_manager(web_view);
    g_signal_connect(content_manager, "script-message-received::js_Call",
                     G_CALLBACK(C_HelloWorld1), web_view);
    webkit_user_content_manager_register_script_message_handler(content_manager, "js_Call");
}

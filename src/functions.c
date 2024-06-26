#include "functions.h"




void C_HelloWorld(){
    g_print("Hello world, got your call from JavaScript\n");
}




JSValueRef js_C_HelloWorld(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    C_HelloWorld();
    return JSValueMakeUndefined(context);
}

void inject_js_functions(WebKitWebView* webview) {
    WebKitUserContentManager* manager = webkit_web_view_get_user_content_manager(webview);
    webkit_user_content_manager_register_script_message_handler(manager, "C_HelloWorld");

    g_signal_connect(manager, "script-message-received::C_HelloWorld", G_CALLBACK(C_HelloWorld), NULL);
}



void inject_Hook_functions(WebKitWebView * webview){

    g_print("injecting Hook Functions");
    inject_js_functions(webview);



}
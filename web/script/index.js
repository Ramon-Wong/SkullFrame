document.addEventListener('DOMContentLoaded', () => { 
    document.getElementById('alertButton').addEventListener('click', () => { 
        callCHelloWorld();
    });
});


function callCHelloWorld() {
    // window.location.href        = "resources:///call/c_hello_world";
    // window.webkit.messageHandlers.C_HelloWorld.postMessage(null);
    // window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);
    window.webkit.messageHandlers.js_Call.postMessage("test");
    // return window.webkit.messageHandlers.js_Call.postMessage("test");
    // window.js_Call("Test");
}


document.addEventListener('DOMContentLoaded', () => { 
    document.getElementById('alertButton').addEventListener('click', () => { 
        callCHelloWorld();
    });
});


function callCHelloWorld() {
    window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);
    // window.webkit.messageHandlers.js_Call.postMessage("test");
    // return window.webkit.messageHandlers.js_Call.postMessage("test");
}


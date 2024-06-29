document.addEventListener('DOMContentLoaded', () => { 
    document.getElementById('alertButton').addEventListener('click', () => { 
        console.log(callCHelloWorld());
    });
});


function callCHelloWorld() {
    return new Promise((resolve, reject) => {
        window.webkit.messageHandlers.js_Call.postMessage(["Hello from JavaScript", 42, true]);

        window.onCFunctionReturn = function(result) {
            console.log(result);
            resolve(result);
        };
    });
}
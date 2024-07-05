
document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click', () => { 
		window.webkit.messageHandlers.js_Call.postMessage({});
	});
});


function onCFunctionReturn(result) {
    console.log("Received from C: " + result);
}

window.onCFunctionReturn = onCFunctionReturn;








// WEBKIT_LOAD_FINISHED
// WEBKIT_LOAD_REDIRECTED
// WEBKIT_LOAD_COMMITTED
// WEBKIT_LOAD_FINISHED

window.addEventListener("WEBKIT_LOAD_STARTED",		()=>{	console.log("WEBKIT_LOAD_STARTED");});
window.addEventListener("WEBKIT_LOAD_REDIRECTED",	()=>{	console.log("WEBKIT_LOAD_REDIRECTED");});
window.addEventListener("WEBKIT_LOAD_COMMITTED",	()=>{	console.log("WEBKIT_LOAD_COMMITTED");});
window.addEventListener("WEBKIT_LOAD_FINISHED", 	()=>{	console.log("WEBKIT_LOAD_FINISHED");});

window.addEventListener("WEBKIT_DESTROY", 			()=>{	alert("This is an alert box!"); console.log("WEBKIT_DESTROY");});
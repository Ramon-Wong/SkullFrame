
document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click', () => { 
		js_Call();	
	});
});


document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('Button2').addEventListener('click', () => { 
		js_DestroyWindow();
	});
});


function checkHello(event) {
	console.log("Event received: " + event.detail + "/" + Date.now());
	// alert("Event received: " + event.detail);
}

window.addEventListener("hello_world", checkHello);
window.addEventListener("WEBKIT_DESTROY",	()=>{	alert("This is an alert box!"); console.log("WEBKIT_DESTROY");});


// WEBKIT_LOAD_FINISHED
// WEBKIT_LOAD_REDIRECTED
// WEBKIT_LOAD_COMMITTED
// WEBKIT_LOAD_FINISHED

window.addEventListener("WEBKIT_LOAD_STARTED",		()=>{	console.log("WEBKIT_LOAD_STARTED");});
window.addEventListener("WEBKIT_LOAD_REDIRECTED",	()=>{	console.log("WEBKIT_LOAD_REDIRECTED");});
window.addEventListener("WEBKIT_LOAD_COMMITTED",	()=>{	console.log("WEBKIT_LOAD_COMMITTED");});
window.addEventListener("WEBKIT_LOAD_FINISHED", 	()=>{	console.log("WEBKIT_LOAD_FINISHED");});

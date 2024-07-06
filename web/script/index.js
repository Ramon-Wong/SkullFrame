
document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click', () => { 
		js_Call();	
	});
});


document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('Button2').addEventListener('click', () => { 
		// js_DestroyWindow();
		getSomething();
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


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Experimental function for solving synchronous communication between JavaScript and native code
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

function getSomething() {
	return new Promise((resolve, reject) => {								// Create a Promise to handle the asynchronous response
		const message	= "What's the meaning of life?";
		const eventName = 'CFunctionReturn_js_Call';						// Define a unique event name
		function onEvent(event) {											// Create an event listener for the custom event
			resolve(event.detail);			
			window.removeEventListener(eventName, onEvent);					// Remove the event listener after receiving the response
		}		
		window.addEventListener(eventName, onEvent);						// Add the event listener
		window.webkit.messageHandlers.js_FuncCall.postMessage(message);		// Send the message to the native code ==> js_FuncCall
	})
	.then(result => {		
		document.getElementById('result').innerText = 'result: ' + result;	// Handle the result when the Promise is fulfilled
	})
	.catch(error => {														// Handle any errors
		console.error('Error:', error);
		document.getElementById('result').innerText = 'Failed to get the answer.';
	});
}


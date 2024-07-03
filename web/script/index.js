document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click', () => { 
		// console.log(callCHelloWorld());
		ThisIsAFunction(["What is one plus one"], function(result) { console.log("Received from C: " + result);});
	});
});


function onCFunctionReturn(result){
	if(typeof window.onCFunctionReturn ===  'function'){
		window.onCFunctionCallback(result);
	}
}

window.onCFunctionReturn = onCFunctionReturn;


function ThisIsAFunction(message, callback) {
	window.onCFunctionCallback = callback;
	window.webkit.messageHandlers.js_Call.postMessage(message);
}


function testFunction() {
	ThisIsAFunction(["What is one plus one"], function(result){
		console.log("Received from C: " + result);
	});
}


// add custom event 

function checkHello(event) {
	console.log("Event received: " + event.detail);
	alert("Event received: " + event.detail);
}

window.addEventListener("hello_world", checkHello);

// use window to listen to events!


onDeviceReady();
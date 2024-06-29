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

function ThisIsAFunction(message, callback) {
	window.onCFunctionCallback = callback;
	window.webkit.messageHandlers.js_Call.postMessage(message);
}

window.onCFunctionReturn = onCFunctionReturn;


function testFunction() {
	ThisIsAFunction(["What is one plus one"], function(result) {
		console.log("Received from C: " + result);
	});
}
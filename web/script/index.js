
document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click', () => { 
		// js_Call();
		JSCORE_MessageLog("Button 1 smash");
	});
});


document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('Button2').addEventListener('click', () => { 
		// js_DestroyWindow();
		// getSomething();
		JSCORE_MessageLog("Button 2 smash");
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

window.addEventListener("WEBKIT_LOAD_STARTED",		    ()=>{	console.log("WEBKIT_LOAD_STARTED");});
window.addEventListener("WEBKIT_LOAD_REDIRECTED",	    ()=>{	console.log("WEBKIT_LOAD_REDIRECTED");});
window.addEventListener("WEBKIT_LOAD_COMMITTED",	    ()=>{	console.log("WEBKIT_LOAD_COMMITTED");});
window.addEventListener("WEBKIT_LOAD_FINISHED", 	    ()=>{	console.log("WEBKIT_LOAD_FINISHED");});

window.addEventListener("MAIN_THREAD_DESTROY_REQUEST",  ()=>{	Cleanup_Before_Destroy();});
// how system handle kill request..
// in C main if it detect the kill signal "delete-event"
// if detected we broadcast "MAIN_THREAD_DESTROY_REQUEST" to the javascript CORE
// in Javascript Core, when we detect that signal.
// we will either clean up and close up stuff before we call JSCore_Destroy()
// JSCore_Destroy(), goes to C main, to shut down everything


function Cleanup_Before_Destroy1(){
	console.log("MAIN_THREAD_DESTROY_REQUEST");
	JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 1");
}


async function Cleanup_Before_Destroy(){
	console.log("MAIN_THREAD_DESTROY_REQUEST");
	JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 1");
	await saveData();
	flushToilet();
	JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 2");	
	await releaseObjects();	
	window.removeEventListener("MAIN_THREAD_DESTROY_REQUEST", Cleanup_Before_Destroy);
	JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 3");
	JSCore_Destroy();	
	JSCORE_MessageLog("We'll never reach here...");
}


function saveData() {
	return new Promise((resolve) => {
		// Simulate saving data with a timeout
		setTimeout(() => {
			JSCORE_MessageLog("save Data");
			resolve();
		}, 4000); // Adjust time as necessary
	});
}

function releaseObjects() {
	return new Promise((resolve) => {
		// Simulate releasing objects with a timeout
		setTimeout(() => {
			JSCORE_MessageLog("Object Released");
			resolve();
		}, 2000); // Adjust time as necessary
	});
}

function flushToilet() {
	console.log("Toilet flushed");
	// Simulate flushing toilet
	// This can be synchronous if it's quick
}


async function getSomething() {
	const message = "What's the meaning of life?";
	const eventName = 'CFunctionReturn_js_Call';

	return new Promise((resolve, reject) => {
		function onEvent(event) {
			console.log('Event received:', event);
			console.log('Event detail:', event.detail);
			resolve(event.detail);
			window.removeEventListener(eventName, onEvent);
		}

		window.addEventListener(eventName, onEvent);
		window.webkit.messageHandlers.js_FuncCall.postMessage(message);
	});
}

// Usage example:
// (async () => {
// 	try{
// 		const result = await getSomething();
// 		console.log('Result received:', result);
// 		// You can now use the result here
// 	}catch(error){
// 		console.error('Error:', error);
// 	}
// })();

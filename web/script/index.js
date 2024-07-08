
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

window.addEventListener("WEBKIT_LOAD_STARTED",		    ()=>{	console.log("WEBKIT_LOAD_STARTED");});
window.addEventListener("WEBKIT_LOAD_REDIRECTED",	    ()=>{	console.log("WEBKIT_LOAD_REDIRECTED");});
window.addEventListener("WEBKIT_LOAD_COMMITTED",	    ()=>{	console.log("WEBKIT_LOAD_COMMITTED");});
window.addEventListener("WEBKIT_LOAD_FINISHED", 	    ()=>{	console.log("WEBKIT_LOAD_FINISHED");});

window.addEventListener("MAIN_THREAD_DESTROY_REQUEST",  ()=>{	Cleanup_Before_Destroy();});

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Experimental function for solving synchronous communication between JavaScript and native code
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

// function getSomething() {
// 	return new Promise((resolve, reject) => {								// Create a Promise to handle the asynchronous response
// 		const message	= "What's the meaning of life?";
// 		const eventName = 'CFunctionReturn_js_Call';						// Define a unique event name
// 		function onEvent(event) {											// Create an event listener for the custom event
// 			console.log('Event received:', event);							// Log the entire event object
// 			console.log('Event detail:', event.detail);						// Log the detail attached to the event			
// 			resolve(event.detail);			
// 			window.removeEventListener(eventName, onEvent);					// Remove the event listener after receiving the response
// 		}		
// 		window.addEventListener(eventName, onEvent);						// Add the event listener
// 		window.webkit.messageHandlers.js_FuncCall.postMessage(message);		// Send the message to the native code ==> js_FuncCall
// 	})
// 	.then(result => {
// 		console.log('Event received:', result);       
// 	})
// 	.catch(error => {														// Handle any errors
// 		console.error('Error:', error);		
// 	});
// }

JSCORE_MessageLog("\n\n JSCORE MESSAGE LOG TEST \n\n");

async function Cleanup_Before_Destroy(){
    console.log("MAIN_THREAD_DESTROY_REQUEST");
    // JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 1");
    await saveData();
    await releaseObjects();
    flushToilet();
    // JSCORE_MessageLog("MAIN_THREAD_DESTROY_REQUEST 2");

    window.removeEventListener("MAIN_THREAD_DESTROY_REQUEST", Cleanup_Before_Destroy);
}


function saveData() {
    return new Promise((resolve) => {
        // Simulate saving data with a timeout
        setTimeout(() => {
            console.log("Data saved");
            resolve();
            JSCore_Destroy();
        }, 10000000); // Adjust time as necessary
    });
}

function releaseObjects() {
    return new Promise((resolve) => {
        // Simulate releasing objects with a timeout
        setTimeout(() => {
            console.log("Objects released");
            resolve();
        }, 5000000); // Adjust time as necessary
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

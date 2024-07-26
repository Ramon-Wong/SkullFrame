

// group all the button events in the DOMContentLoaded....no need to have several of them in one page.
document.addEventListener('DOMContentLoaded', () => { 
	document.getElementById('alertButton').addEventListener('click',	() => { JSCORE_MessageLog("Button 1 smash");});
	document.getElementById('Button2').addEventListener('click',		() => { JSCORE_MessageLog("Button 2 smash");});
	document.getElementById("Button3").addEventListener("click", 		() => { Popup_Request()});
	document.getElementById("closePopupBtn").addEventListener("click",	() => {	JSCORE_MessageLog("Smash return");	Remove_Popup();});
	document.getElementById("exit_destroy").addEventListener("click",	() => {	JSCORE_Destroy();	});// bye bye
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

window.addEventListener("MAIN_THREAD_DESTROY_REQUEST",  ()=>{	Popup_Request();});
// how system handle kill request..
// in C main if it detect the kill signal "delete-event"
// if detected we broadcast "MAIN_THREAD_DESTROY_REQUEST" to the javascript CORE
// in Javascript Core, when we detect that signal.
// we will either clean up and close up stuff before we call JSCore_Destroy()
// JSCore_Destroy(), goes to C main, to shut down everything


function Popup_Request(){
    document.getElementById('overlay').classList.add('active');
    document.getElementById('popup').classList.add('active');		
}

function Remove_Popup(){
	document.getElementById('overlay').classList.remove('active');
	document.getElementById('popup').classList.remove('active');		
}

// starting up!
onDeviceReady();

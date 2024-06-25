document.addEventListener('DOMContentLoaded', () => { 
    document.getElementById('alertButton').addEventListener('click', () => { 
        callCHelloWorld();
    });
});


function callCHelloWorld() {
    window.location.href        = "resources:///call/c_hello_world";
}
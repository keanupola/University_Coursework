var today = new Date();
var hourNow = today.getHours();
var greeting;
var eltag=document.getElementById("greetingDiv");

if (hourNow > 18) {
    greeting = 'Good evening!';
} else if (hourNow > 12) {
    greeting = 'Good afternoon!';
} else if (hourNow > 0) {
    greeting = 'Good morning!';
} else {
    greeting = 'Welcome!';
}

eltag.innerHTML= '<h2>' + greeting + '</h2>';
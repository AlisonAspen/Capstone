const mqtt = require('mqtt')

//Setup MQTT settings
//check with broker for specidics
const options = {
  port: 1883,
clientId: 'client-Ally-Send',
  //your account details (HiveMQ)
  username: config.username,
  password: config.password
};
const client = mqtt.connect('mqtt://broker.mqttdashboard.com:8000', options);



function sendMessage(msg) {
    let payload = msg;
  client.publish('subscriptionurl', payload, function() {
    console.log("New Message: " + payload);
  });
}
/*
const name = "Ally";
const greetings = ["Hello, ", "Good Morning, ", "Good Afternoon, ", "Good Evening, ", "It's Late,  "];
var myCanvas = createCanvas(windowWidth, windowHeight);
*/

function setup() {
    const name = "Ally";
    const greetings = ["Hello, ", "Good Morning, ", "Good Afternoon, ", "Good Evening, ", "It's Late,  "];
    var myCanvas = createCanvas(windowWidth, windowHeight);
    myCanvas.parent('holder'); //puts canvas inside of holder div

}

function draw() {
    
}

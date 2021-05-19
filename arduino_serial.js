//Full explanation here:
//https://medium.com/@machadogj/arduino-and-node-js-via-serial-port-bcf9691fab6a

//Get your serial port ID
//Use Terminal to run:
//  npx @serialport/list

const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const mqtt = require('mqtt')

const port = new SerialPort('/dev/cu.usbmodem1422301');
const parser = port.pipe(new Readline({ delimiter: '\n' }));

//Setup MQTT settings
const options = {
  port: 1883,
	clientId: 'ally-js',
  username: "ally-arduino",
  password: "mkr5422"
};
const client = mqtt.connect('mqtt://broker.mqttdashboard.com', options);
let payload;

// Read the port data
port.on("open", () => {
  console.log('Serial port is open');
});
parser.on('data', data =>{
  console.log('Arduino value:', data);
  payload = data;

  //Send to the MQTT client
  client.publish('/topic1', String(payload), function() {
    console.log("Pushed to MQTT: " + payload);
    //client.end(); // Close the connection when published
  });
  //port.removeAllListeners('data')
});

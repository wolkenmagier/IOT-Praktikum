const SerialPort = require('serialport');
const ConsoleReader = require('readline');
const fs = require('fs');
const readline = require('readline');

//start of MQTT connection code
var mqtt    = require('mqtt');
var options={
	clientId:"group15",
	username:"JWT",
	password:"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE1OTIwNzk2NDUsImlzcyI6ImlvdHBsYXRmb3JtIiwic3ViIjoiMThfMzUifQ.LCeNZyRg8fjatSElGD-0lCkdwsjhizK6HDYrpGHuLiqxS-sDZsEES4vPyPP7f2m3t9A9c_vHVVPWJrJtwC1jdswdDkCrdSTcL2hOxX_4Pds7xc34kaB2oAGWHDPq3WQgz1omd6WXlRImm76YxQeN2xqnxTJJ65zu7SAQqmCAiAext7djIIpuM3kb-eUp-VbpXaHZ8_r2NWc8lDJZrUqiguCuSBznfBd26OfbMy2fD8aHg3AAZCHWXQwGBspmLZWtFdALgvd1QxiXDw2YHta6ULk4EWZFldrqzc7-H59l2duTCcxsD9aTpeTmeTjAte3HcEtoBFUVoqX84B-wNY5HOzOT4l4jWVqtRNe10e799WwzSwtj-uIXKjuDNJ2f-bfvwforZBEWA29j7c231puNrJvqzSUnub6pgazx6MuuEaCfRdH_NPIAbiGNVW3IIszuBMouhOFhiLgHbNfACVCelb92ewCWMBxC1glWy3hwvax0aikB-zZ2xmtFqQaHK3WY0-br9-y6Px5iW9kZUV97rN5drdKTZRl5eZCyvRUea_vb6Yd2_riXsmxLdU5qTwqJZRX41EkOfVjofOSu7KcX-hPPUN3g9yro8di1A30pVWvn-765XxNLjzdIgLXGAT4UaVg4XkRcBA7yCZHyQgAz6ZMrfBYmJd3m6RnVLc3dDO0"
};

var mqttclient  = mqtt.connect("mqtt://131.159.35.132:1883", options); 

mqttclient.on("connect",function(){	
	console.log("connected to MQTT broker");
}
//end of MQTT connection code.

const Readline = SerialPort.parsers.Readline;
const parser = new Readline();


var first=true;

var myArgs=process.argv.slice(2);
console.log('myArgs: ', myArgs);
if (myArgs.length==0){
	console.log("Error: serial port not specified.");
	process.abort();
}

if (myArgs.length>2){
	console.log("Error: too many arguments");
	process.abort();
}

const port = new SerialPort(myArgs[0]);

const rl = ConsoleReader.createInterface({
  input: process.stdin,
  prompt: "hallo>"
});


try{
	port.pipe(parser);
	parser.on('data', handleDeviceString);
}
catch(e) {
  console.log(e);
  process.abort();
}

//handle input from terminal
rl.on('line', (input) => {
  //console.log(`Received: ${input}`);
  input=input+"\n";
  port.write(input);
});


//If only the serial port is given, send current time only.
//If a file name is given, open file and read the commands and set he time to the time of the first command - 30 seconds
if (myArgs.length==2){
	//read and process file given in myArgs[1]
	processFile(myArgs[1],port);
} else {
	sendCurrentTime(port);
}


//Handles lines printed in device to serial connection
//Echos all lines and handles SEND commands by pushing them to the MQTT gateway of the IoT platform
function handleDeviceString(str){
  console.log('>>> '+str);

  str = str.replace(/</g, '')
  str = str.replace(/>/g, '')
  strarray = str.split(":")

	if(strarray[0]=="SEND"){
		var payload = {
	 		"username": "group15",
	 		"sensor15": strarray[2] * 1,
	 		"device_id": 35,
	 		"timestamp": strarray[1] * 1000
		};

		payload = JSON.stringify(payload);
		mqttclient.publish( '18_35', payload );
		console.log("Message sent to MQTT broker")
	}
}


function sendCurrentTime(port) {
    var utc = new Date();

	var hours = utc.getHours();
	var minutes = utc.getMinutes();
	var seconds = utc.getSeconds();
	var day =utc.getDate();
	var month = utc.getMonth()+1;
	var year = utc.getFullYear();
  
  
	var tmp = utc.getTime()/1000;
	var time=Math.trunc(tmp)+7200;
	var timeString = "0:0:"+String(time)+"\n";

	port.write(timeString);
};

function processFile(fileName,port){
	//console.log("Reading commands from file is not provided to you. Implement it by yourself.")

	const fileStream = fs.createReadStream(fileName);

	  const fl = readline.createInterface({
	    input: fileStream,
	    crlfDelay: Infinity
	  });
	  var firstLine = true;

	  fl.on('line', (line) => {

	  	if(firstLine){
	  		lineArray = line.split(":")
	  		time = lineArray[0] - 30;
	  		timeString = "0:0:"+String(time)+"\n";
	  		port.write(timeString);
	  		firstLine = false;
	  	}

	  	line = line + "\n";
	  	port.write(line);
	  });
}


process.on('uncaughtException', function (exception) {
	console.log(exception); // to see your exception details in the console
	// if you are on production, maybe you can send the exception details to your
	// email as well ?
});
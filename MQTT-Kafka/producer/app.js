var mqtt    = require('mqtt');
var client  = mqtt.connect("mqtt://localhost",{clientId:"producer"}); //change server to local, later.

client.on("connect",function(){	
	console.log("connected");

	let intervalID = setInterval(function() {
		var number = Math.floor(Math.random() * (100)) + 1
		client.publish( 'number', number.toString() );
		console.log('Message Sent: '+ number);
	}, 10000);

	setTimeout(() => { clearInterval(intervalID); }, 600000);
})
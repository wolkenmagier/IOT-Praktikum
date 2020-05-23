var mqtt    = require('mqtt');
var client  = mqtt.connect("mqtt://localhost",{clientId:"subscriber"}); //change server to local, later.

client.on("connect",function(){	
	console.log("connected");

	client.subscribe('number')
})

client.on('message', function (topic, message) {
	context = message.toString();
	console.log(context)
})
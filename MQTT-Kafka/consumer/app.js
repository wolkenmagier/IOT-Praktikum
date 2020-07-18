const kafka = require('kafka-node');

try {
  const Consumer = kafka.Consumer;
  const client = new kafka.KafkaClient({kafkaHost: '138.246.232.197:9092'});

  let consumer = new Consumer(
    client,
    [{ topic: "01_06_020", partition: 0 }],
    {
    	groupId: 'group1cx',
      autoCommit: true,
      fetchMaxWaitMs: 1000,
      encoding: 'utf8',
      fromOffset: "earliest"
    }
  );

  consumer.on('message', async function(message) {
    console.log(message.value);
  })

  consumer.on('error', function(err) {
    console.log('error', err);
  });

}
catch(e) {
  console.log(e);
}
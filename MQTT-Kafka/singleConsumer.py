from kafka import KafkaConsumer

# To consume latest messages and auto-commit offsets
consumer = KafkaConsumer('number',bootstrap_servers=['localhost:9092'], enable_auto_commit=False,)


while True:
    for message in consumer:
        # message value and key are raw bytes -- decode if necessary!
        # e.g., for unicode: `message.value.decode('utf-8')`
        print ((message.topic, message.partition,
                                              message.offset, message.key,
                                              message.value))

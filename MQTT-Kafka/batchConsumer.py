from kafka import KafkaConsumer
import time

while True:
    consumer = KafkaConsumer('number', bootstrap_servers=['localhost:9092'],
                             auto_offset_reset='earliest', enable_auto_commit=False,
                             auto_commit_interval_ms=1000)
    for message in consumer:
        # message value and key are raw bytes -- decode if necessary!
        # e.g., for unicode: `message.value.decode('utf-8')`
        print ((message.topic, message.partition,
                                              message.offset, message.key,
                                              message.value))


    time.sleep(3)

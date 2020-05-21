import random
import time
import paho.mqtt.client as mqtt

mqttc = mqtt.Client()
mqttc.connect("mqtt.eclipse.org", 1883, 60)


def randGen():
    num1 = random.randint(1, 100)
    print("Random integer: ", num1)
    return num1

if __name__ == "__main__":
    while True:
        num = randGen()
        mqttc.publish("number", num)
        time.sleep(1)
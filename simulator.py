import time
import paho.mqtt.client as mqtt
import json
from collections import defaultdict

def on_connect(client, userdata, flags, rc):
    print('Connected with result code', str(rc))

def on_publish(client,userdata,result):             #create function for callback
    print('Data published with ret code: ' + str(result))

broker_address = 'soldier.cloudmqtt.com'
port = 10132
user = 'KC'
password = 'kc'

client = mqtt.Client('simulator')
client.username_pw_set(user, password=password)
client.on_connect = on_connect
client.on_publish = on_publish

client.connect(broker_address, port=port)

ret =  client.publish("ultra", "New test pub from script")

print('Published: ' + 'Test pub from script' + ' | to topic: ' + 'ultra' + ' | with code: ' + str(ret))

print("End of script")

client.disconnect()
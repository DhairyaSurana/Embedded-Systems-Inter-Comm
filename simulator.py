import time
import paho.mqtt.client as mqtt
import json
from collections import defaultdict

def on_publish(client,userdata,result):             #create function for callback
    print('Data published with ret code: ' + str(result))

broker_address = 'soldier.cloudmqtt.com'
port = 10132
user = 'KC'
password = 'kc'

client = mqtt.Client('simulator')
client.username_pw_set(user, password=password)
client.on_publish = on_publish

client.connect(broker_address, port=port)

ret =  client.publish("topics", "{\"id\": \"pixy\", \"pub\": 1, \"rec\": 0, \"t1\": \"\", \"t2\": \"\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"rover\", \"pub\": 1, \"rec\": 0, \"t1\": \"pixy\", \"t2\": \"ultra\", \"t3\": \"arm\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"ultra\", \"pub\": 1, \"rec\": 0, \"t1\": \"\", \"t2\": \"\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"arm\", \"pub\": 1, \"rec\": 0, \"t1\": \"pixy\", \"t2\": \"rover\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)

print("End of script")

client.disconnect()
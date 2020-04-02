# Neccesary libraries
import time
import datetime
import paho.mqtt.client as mqtt
import json
from collections import defaultdict

# Function ran whenever script publishes anything
def on_publish(client,userdata,result):             #create function for callback
    print('Data published with ret code: ' + str(result))

# Set-up info for cloudmqtt
broker_address = 'soldier.cloudmqtt.com'
port = 10132
user = 'KC'
password = 'kc'

# Establishing connection with cloudmqtt server
client = mqtt.Client('simulator')
client.username_pw_set(user, password=password)
client.on_publish = on_publish
client.connect(broker_address, port=port)

# publishing topic information for all components with one second sleeps in between
ret =  client.publish("topics", "{\"id\": \"pixy\", \"pub\": 1, \"rec\": 0, \"t1\": \"\", \"t2\": \"\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"rover\", \"pub\": 1, \"rec\": 0, \"t1\": \"pixy\", \"t2\": \"ultra\", \"t3\": \"arm\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"ultra\", \"pub\": 1, \"rec\": 0, \"t1\": \"\", \"t2\": \"\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)
ret =  client.publish("topics", "{\"id\": \"arm\", \"pub\": 1, \"rec\": 0, \"t1\": \"pixy\", \"t2\": \"rover\", \"t3\": \"\", \"t4\": \"\"}")
time.sleep(1)

# Pixy publishing message of current status
timenow = datetime.datetime.now()
ret =  client.publish("pixy", "{\"id\": \"pixy\", \"pub\": 2, \"rec\": 0, \"x_coordinate\": 10, \"y_coordinate\": 5, \"height\": 2, \"width\": 1, \"signature\": 1234, \"time\": " + str(timenow.strftime("%H%M%S")) + "}")
time.sleep(1)

# Disconnecting from cloudmqtt
client.disconnect()

# letting user know that script has executed
print("End of script")
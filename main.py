import os
from twilio.rest import Client
from cassandra.cluster import Cluster
from cassandra.auth import PlainTextAuthProvider

client_id = os.environ['client_id']
client_secret = os.environ['client_secret']

cloud_config= {
  'secure_connect_bundle': 'secure-connect-myman.zip'
}

auth_provider = PlainTextAuthProvider(client_id, client_secret)
cluster = Cluster(cloud=cloud_config, auth_provider=auth_provider)
session2 = cluster.connect()
print(session2)

account_sid = os.environ['TWILIO_ACCOUNT_SID']
auth_token = os.environ['TWILIO_AUTH_TOKEN']
client = Client(account_sid, auth_token)

rows = session2.execute("select * from myman_keyspace.disateruser WHERE place='india' ALLOW FILTERING;")
for row in rows:
  print(row[3])

from flask import Flask, request
app = Flask('app')

@app.route('/')
def hello_world():
  return 'Hello, World!'


@app.route('/entry', methods = ['POST', 'GET'])
def entry():
  disaster = request.args.get('disaster')
  if disaster != 'none':
    rows = session2.execute("select * from myman_keyspace.disateruser WHERE place='india' ALLOW FILTERING;")
    for row in rows:
      # email
      message = client.messages \
                  .create(
                      body="Alert!" +disaster+ " detected in your area!",
                      from_='+12815476047',
                      to=row[3]
                  )

    print(message.sid)
    return disaster
  else:
    return "safe"
  return 'connect to node here'

app.run(host='0.0.0.0', port=8080)

import os
from twilio.rest import Client

account_sid = os.environ['TWILIO_ACCOUNT_SID']
auth_token = os.environ['TWILIO_AUTH_TOKEN']
client = Client(account_sid, auth_token)

from flask import Flask, request
app = Flask('app')

@app.route('/')
def hello_world():
  return 'Hello, World!'


@app.route('/entry', methods = ['POST', 'GET'])
def entry():
  disaster = request.args.get('disaster')
  if disaster != 'none':
    # email
    message = client.messages \
                .create(
                     body="Alert!" +disaster+ " detected in your area!",
                     from_='+12815476047',
                     to='+917976066450'
                 )

    print(message.sid)
    return disaster
  else:
    return "safe"
  return 'connect to node here'

app.run(host='0.0.0.0', port=8080)

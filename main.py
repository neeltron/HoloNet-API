from flask import Flask, request
app = Flask('app')

@app.route('/')
def hello_world():
  return 'Hello, World!'


@app.route('/entry')
def entry():
  disaster = request.args.get('disaster')
  if disaster != none:
    # email
    # twilio
    return disaster
  else:
    return "safe"
  return 'connect to node here'

app.run(host='0.0.0.0', port=8080)

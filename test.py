import requests
import json

url = "https://disaterapi.herokuapp.com/user/alert"

headers = {'content-type': 'application/json'}

r = requests.post(url, data=json.dumps({'place': 'india', 'type': 'earthquake'}), headers=headers)

print(r.status_code)

data = r.json()
print(data)
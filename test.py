import requests
import json

url = "https://disaterapi.herokuapp.com/user/save"


r = requests.post(url, data={'name': 'Neel Adwani', 'phone': '+917976066450', 'email': 'neeltr.n@gmail.com', 'place': 'india'})

if r.status_code != 200:
  print("Error:", r.status_code)

data = r.json()
print(data)
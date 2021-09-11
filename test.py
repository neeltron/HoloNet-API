import requests

url = "https://disaterapi.herokuapp.com/user/alert"

r = requests.post(url, params={'place': 'india', 'type': 'earthquake'})

if r.status_code != 200:
  print("Error:", r.status_code)

data = r.json()
print(data)
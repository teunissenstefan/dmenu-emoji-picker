import requests
import sys
import json
from urllib.request import urlopen

#emoji-api api key https://emoji-api.com/
api_key = ''

#url to send to ipstack with ip and api key
send_url = 'https://emoji-api.com/emojis?access_key='+api_key

#make request
r = requests.get(send_url)
j = json.loads(r.text)
with open('emoji', 'w') as emoji_file:
	for f in j:
		slug = f['slug']
		#just added some personal nicknames:
		slug = slug.replace("face-with-tears-of-joy","laughcry face with tears of joy")
		slug = slug.replace("pistol","pistol gun")
		slug = slug.replace("pleading-face","puppy pleading face") #this is obviously a puppy face emoji
		emoji_file.write(f['character'] + " " + slug.replace("-" ," ") + "\n")

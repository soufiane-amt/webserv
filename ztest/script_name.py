import tweepy
import wget

# Twitter API credentials
consumer_key = "YOUR_CONSUMER_KEY"
consumer_secret = "YOUR_CONSUMER_SECRET"
access_token = "YOUR_ACCESS_TOKEN"
access_token_secret = "YOUR_ACCESS_TOKEN_SECRET"

def get_profile_photo(username):
    # Authenticate with Twitter API
    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    api = tweepy.API(auth)

    try:
        # Retrieve user object
        user = api.get_user(username)
        # Retrieve profile photo URL
        photo_url = user.profile_image_url_https.replace("_normal", "")
        # Download the profile photo
        photo_filename = wget.download(photo_url)
        print("Profile photo downloaded:", photo_filename)
    except tweepy.error.TweepError as e:
        print("Error:", str(e))

# Prompt for the username
username = input("Enter the Twitter username: ")
# Call the function to retrieve the profile photo
get_profile_photo(username)

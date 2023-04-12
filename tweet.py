import requests
import json

url = "https://twitter.com/i/api/graphql/shjyg0Y1ez2QoihsYD05xA/CreateTweet"

def payloading(message):
    payload = json.dumps({
      "variables": {
        "tweet_text": message,
        "dark_request": False,
        "media": {
          "media_entities": [],
          "possibly_sensitive": False
        },
        "withDownvotePerspective": False,
        "semantic_annotation_ids": []
      },
      "features": {
        "tweetypie_unmention_optimization_enabled": True,
        "vibe_api_enabled": True,
        "responsive_web_edit_tweet_api_enabled": True,
        "graphql_is_translatable_rweb_tweet_is_translatable_enabled": True,
        "view_counts_everywhere_api_enabled": True,
        "longform_notetweets_consumption_enabled": True,
        "tweet_awards_web_tipping_enabled": False,
        "interactive_text_enabled": True,
        "responsive_web_text_conversations_enabled": False,
        "longform_notetweets_rich_text_read_enabled": False,
        "blue_business_profile_image_shape_enabled": False,
        "responsive_web_graphql_exclude_directive_enabled": True,
        "verified_phone_label_enabled": False,
        "freedom_of_speech_not_reach_fetch_enabled": False,
        "standardized_nudges_misinfo": True,
        "tweet_with_visibility_results_prefer_gql_limited_actions_policy_enabled": False,
        "responsive_web_graphql_timeline_navigation_enabled": True,
        "responsive_web_graphql_skip_user_profile_image_extensions_enabled": False,
        "responsive_web_enhance_cards_enabled": False
      },
      "queryId": "shjyg0Y1ez2QoihsYD05xA"
    })
    return payload
headers = {
  'authority': 'twitter.com',
  'accept': '*/*',
  'accept-language': 'fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7,ar;q=0.6',
  'authorization': 'Bearer AAAAAAAAAAAAAAAAAAAAANRILgAAAAAAnNwIzUejRCOuH5E6I8xnZz4puTs%3D1Zv7ttfk8LF81IUq16cHjhLTvJu4FA33AGWWjCpTnA',
  'content-type': 'application/json',
  'cookie': 'external_referer=padhuUp37zjgzgv1mFWxJ12Ozwit7owX|0|8e8t2xd8A2w%3D; guest_id_ads=v1%3A168096748068133472; guest_id_marketing=v1%3A168096748068133472; guest_id=v1%3A168096748068133472; _ga=GA1.2.1328323421.1680967482; g_state={"i_l":0}; kdt=0oY0CqhVgB2iqIAGDRWss94Cn4iaeEVHBYnHYR9K; auth_token=77352d1ac2215b3ceb4cd618248fab053042f4ee; ct0=c291e80b4fab01e340b49776d8829ef6835d31c5f0ae758d50f1626e98835d4001cf9c6021c879745fc24a8421a77eb192e98c0e8ecad1db183da7f413da32f7a134acfdf9c355c68b61e35a1ebd23aa; lang=en; twid=u%3D1535019381905838080; des_opt_in=Y; at_check=true; _gcl_au=1.1.724766199.1680969348; mbox=session#7d2df471d0d64d4f9b6ca8609dfb50b5#1680971210|PC#7d2df471d0d64d4f9b6ca8609dfb50b5.37_0#1744214149; _gid=GA1.2.1360725527.1681224526; personalization_id="v1_cVxLwy/6iArgSkuQEtARwQ=="',
  'origin': 'https://twitter.com',
  'referer': 'https://twitter.com/home',
  'sec-ch-ua': '"Chromium";v="112", "Google Chrome";v="112", "Not:A-Brand";v="99"',
  'sec-ch-ua-mobile': '?0',
  'sec-ch-ua-platform': '"macOS"',
  'sec-fetch-dest': 'empty',
  'sec-fetch-mode': 'cors',
  'sec-fetch-site': 'same-origin',
  'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36',
  'x-csrf-token': 'c291e80b4fab01e340b49776d8829ef6835d31c5f0ae758d50f1626e98835d4001cf9c6021c879745fc24a8421a77eb192e98c0e8ecad1db183da7f413da32f7a134acfdf9c355c68b61e35a1ebd23aa',
  'x-twitter-active-user': 'yes',
  'x-twitter-auth-type': 'OAuth2Session',
  'x-twitter-client-language': 'en'
}

for i in range(100):
    response = requests.request("POST", url, headers=headers, data=payloading("Hello world for the " + str(i + 100)) + "th time")

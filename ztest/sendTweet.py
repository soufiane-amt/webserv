from pytube import YouTube

# Function to download a YouTube video
def download_video():
    # Prompt for the YouTube video URL
    video_url = input("Enter the YouTube video URL: ")

    try:
        # Create a YouTube object
        video = YouTube(video_url)

        # Get the highest resolution video stream
        stream = video.streams.get_highest_resolution()

        # Download the video
        stream.download()
        print("Video downloaded successfully.")
    except Exception as e:
        print("An error occurred while downloading the video:", str(e))

# Call the download_video function
download_video()

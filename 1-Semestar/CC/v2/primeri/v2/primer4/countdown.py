import time

def countdown(seconds):
    while seconds > 0:
        mins, secs = divmod(seconds, 60)
        print(f"{mins:02}:{secs:02}", end="\r")
        time.sleep(1)
        seconds -= 1
    print("Time's up!")

if __name__ == "__main__":
    seconds = int(input("Enter the countdown time in seconds: "))
    countdown(seconds)


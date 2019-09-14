import os
import sys
import requests


def main():
    r = requests.get('http://0.0.0.0:2091', data={'temp': 100})
    print(r.status_code, r.text)

    return None

if __name__=="__main__":
    main()

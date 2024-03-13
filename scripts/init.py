import json
import urllib.request
import sys
import os
import re
import math
import zipfile


def download(entry):
    url = entry["perOSInfo"][sys.platform]["url"]
    file_name = os.path.split(url)[1]
    file_name = re.sub(r"\?.*$", "", file_name)
    print("Downloading %s" % file_name)

    count = 0
    with urllib.request.urlopen(url) as response, open(file_name, "wb") as out_file:
        size = int(response.headers.get("content-length"))
        chunk = 1024
        for i in range(math.ceil(size / chunk)):
            data = response.read(chunk)
            count += 1
            print("\r%i%%" % int(count / (size / chunk) * 100), end="")
            out_file.write(data)

    if file_name.endswith(".zip"):
        print("\nExtracting...")
        with zipfile.ZipFile(file_name, "r") as zip:
            zip.extractall(entry["path"])


def main():
    with open("scripts/manifest.json", "r") as f:
        manifest = json.load(f)

    for entry in manifest:
        download(entry)


if __name__ == "__main__":
    main()

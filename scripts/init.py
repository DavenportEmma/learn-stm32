import json
import urllib.request
import sys
import os
import re
import math
import zipfile
from git import Repo


def download(entry):
    try:
        for ele in os.listdir(entry["path"]):
            if entry["name"] in ele:
                return
    except:
        pass

    url = entry["url"] if "url" in entry else entry["perOSInfo"][sys.platform]["url"]
    file_name = os.path.split(url)[1]
    extension = os.path.splitext(file_name)[1]
    file_name = re.sub(r"\?.*$", "", file_name)
    print("Downloading %s" % file_name)

    if extension == ".git":
        if not os.path.exists(entry['path']):
            Repo.clone_from(url, entry["path"], no_checkout=True)
            repo = Repo(entry["path"])
            repo.remote().fetch()
            repo.git.checkout(entry["ref"])

    else:
        count = 0
        with urllib.request.urlopen(url) as response, open(file_name, "wb") as out_file:
            size = int(response.headers.get("content-length"))
            chunk = 1024
            for i in range(math.ceil(size / chunk)):
                data = response.read(chunk)
                count += 1
                print("\r%i%%" % int(count / (size / chunk) * 100), end="")
                out_file.write(data)

        if extension == ".zip":
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

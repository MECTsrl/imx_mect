import pandas as pd
import json
import os
import glob
import csv
import urllib.request as url
import difflib
import sys
import time
import itertools
import threading
import socket
import subprocess
import shutil
from urllib.error import HTTPError, URLError

processDone = False
def loadJsonData (URLvars):
    try:
        jsondata = json.loads(url.urlopen(URLvars,timeout=20).read().decode())
        time.sleep(1)
        return jsondata
    except HTTPError as error:
        print("HTTP Timeout!")
        processDone = True
        exit()

#here is the animation
def animate():
    for c in itertools.cycle(['|', '/', '-', '\\']):
        if processDone:
            sys.stdout.write('\r ')
            break
        sys.stdout.write('\r ' + c)
        sys.stdout.flush()
        time.sleep(0.1)
    sys.stdout.write('\r ')

def prepend_line(file_name, line):
    """ Insert given string as a new line at the beginning of a file """
    # define name of temporary dummy file
    dummy_file = file_name + '.bak'
    # open original file in read mode and dummy file in write mode
    with open(file_name, 'r') as read_obj, open(dummy_file, 'w') as write_obj:
        # Write given line to the dummy file
        write_obj.write(line + '\n')
        # Read lines from original file one by one and append them to the dummy file
        for line in read_obj:
            write_obj.write(line)
    # remove original file
    os.remove(file_name)
    # Rename dummy file as the original file
    os.rename(dummy_file, file_name)


IP= sys.argv[1]
#IP= "192.168.5.123";
URLvars="http://"+IP+"/get_trends.cgi"
jsonTrendPath = "jsontrend"
if os.path.exists(jsonTrendPath):
    shutil.rmtree(jsonTrendPath, ignore_errors=True)

os.mkdir(jsonTrendPath)

print("Loading trends from "+ IP + "\n")
t = threading.Thread(target=animate)
t.start()
jsondata = loadJsonData(URLvars)
processDone=True
trendsNameArray = jsondata['query']['trends']

print("\nWriting cgi_json_data.csv\n")
df = pd.DataFrame(jsondata['trends'])
df = df['filename']
for index in df.index:
    df_track = pd.DataFrame(jsondata['trends'][index]['track'])
    df_track['id'] = df_track['id'].str.pad(32, side='right', fillchar=' ')
    df_track.to_csv(jsonTrendPath+"/"+df[index],sep=';',header=False,index=False)
    prepend_line(jsonTrendPath+"/"+df[index],'L')

print("Downloading original files \n")
trendPath = "customtrend"
if os.path.exists(trendPath):
        shutil.rmtree(trendPath, ignore_errors=True)

try:
    subprocess.call(["rsync", "-Havx", "root@"+IP+":/local/data/"+trendPath, "./"])
#    fRes = subprocess.call(["rsync", "-Havx", "root@192.168.0.111:/local/data/"+trendPath, "./"])
except subprocess.CalledProcessError as rsyncRes:
    print("error code", rsyncRes.returncode, rsyncRes.output)

differenceFile = "data_difference_trends.diff"
print("Looking for differences \n")
for index in df.index:
    with open(trendPath + '/' + df[index], 'r') as t1, open(jsonTrendPath+"/"+df[index], 'r') as t2:
        fileone = t1.readlines()
        filetwo = t2.readlines()
        fileone = [line.replace(' ', '') for line in fileone]
        filetwo = [line.replace(' ', '') for line in filetwo]

    with open(differenceFile, 'a') as outFile:
        for line in difflib.unified_diff(fileone, filetwo, fromfile=trendPath + '/' + df[index], tofile=jsonTrendPath+"/"+df[index]):
            outFile.write(line)

if not os.stat(differenceFile).st_size == 0:
        print("Done! Differences are loaded in "+ differenceFile)
else:
        print("Done! No differences were found!")
        #clean
        shutil.rmtree(trendPath, ignore_errors=True)
        shutil.rmtree(jsonTrendPath, ignore_errors=True)
        os.remove(differenceFile)

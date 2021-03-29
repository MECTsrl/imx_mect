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
import subprocess
import shutil

processDone = False
def loadJsonData (URLvars):
    jsondata = json.loads(url.urlopen(URLvars).read().decode())
    time.sleep(1)
    return jsondata

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

IP= sys.argv[1]
#IP= "192.168.5.122";
URLvars="http://"+IP+"/get_log.cgi?vars=*"

print("Loading vars from "+ IP + "\n")
t = threading.Thread(target=animate)
t.start()
jsondata = loadJsonData(URLvars)
processDone=True
varArray = jsondata['query']['variables']
NEWURL= "http://"+IP+"/get_log.cgi?vars="

varString = ""
for variable in varArray :
    varString= varString + variable + ","

URL = NEWURL + varString
print("\nLoading data from "+ IP + "\n")
processDone=False
t = threading.Thread(target=animate)
t.start()
jsondata = loadJsonData(URL)
processDone=True
print("\nWriting cgi_json_data.csv\n")
varArray = jsondata['query']['variables']
del jsondata['query']
df = pd.DataFrame(jsondata)
df = df.transpose()
df.columns = varArray
df.index.name = "Datetime"
df = df.replace('None','')
df.to_csv (r'cgi_json_data.csv')


print("\nReading data from log files \n")
storePath = "store"
extension = 'log'
print("Downloading original files \n")
if os.path.exists(storePath):
        shutil.rmtree(storePath, ignore_errors=True)

try:
    subprocess.call(["rsync", "-Havx", "root@"+IP+":/local/data/"+storePath, "./"])
#    fRes = subprocess.call(["rsync", "-Havx", "root@192.168.0.111:/local/data/"+storePath, "./"])
except subprocess.CalledProcessError as rsyncRes:
    print("error code", rsyncRes.returncode, rsyncRes.output)



#os.chdir(os.path.join(os.getcwd(),storePath))
result = glob.glob('store/*.{}'.format(extension))
result.sort()
dfLog = pd.DataFrame()
for fileName in result:
    data = pd.read_csv(fileName,sep=';')
    dfLog = dfLog.append(data, True)

print("\nWriting store_csv_data.csv \n")
dfLog.head()
dfLog['Datetime'] = pd.to_datetime(dfLog['date']  + dfLog[' time'],format='%Y/%m/%d %H:%M:%S').map(lambda x: x.isoformat())
dfLog = dfLog.set_index(['Datetime'])
del dfLog['date']
del dfLog[' time']
dfLog = dfLog.replace(' ', '', regex=True)
dfLog = dfLog.replace('Nan', 'NaN', regex=True)
dfLog.columns = varArray
dfLog.to_csv(r'store_csv_data.csv')

differenceFile = "data_difference_logs.diff"
print("Looking for differences \n")
with open('cgi_json_data.csv', 'r') as t1, open('store_csv_data.csv', 'r') as t2:
    fileone = t1.readlines()
    filetwo = t2.readlines()

with open(differenceFile, 'w') as outFile:
    for line in difflib.unified_diff(fileone, filetwo, fromfile='cgi_json_data.csv', tofile='store_csv_data.csv'):
        outFile.write(line)

if not os.stat(differenceFile).st_size == 0:
        print("Done! Differences are loaded in "+ differenceFile)
else:
        print("Done! No differences were found!")
        #clean
        shutil.rmtree(storePath, ignore_errors=True)
        os.remove(differenceFile)
        os.remove('cgi_json_data.csv')

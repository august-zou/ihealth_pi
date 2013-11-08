import iHealth
import time
import urllib,urllib2,json

if __name__ == '__main__':
    while(1):
        data = {'ecg':iHealth.getECG()}
	print data
	f = urllib2.urlopen(
		url = 'http://192.168.49.207:3000/data/ecg',
		data = urllib.urlencode(data)
	)
        time.sleep(0.3)
	print f.read()

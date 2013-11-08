import iHealth
import time
import urllib,urllib2,json

if __name__ == '__main__':
    while(1):
        data = {'temperature':iHealth.getTemperature()}
	print data
	f = urllib2.urlopen(
		url = 'http://192.168.49.207:3000/data/temperature',
		data = urllib.urlencode(data)
	)
        time.sleep(1)
	print f.read()

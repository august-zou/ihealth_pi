import iHealth
import time
import urllib,urllib2,json

if __name__ == '__main__':
    iHealth.setupPulsioximeter()
    while(1):
        data = {'pulse':iHealth.getBPM(),'spo2':iHealth.getOxygenSaturation()}
	print data
	f = urllib2.urlopen(
		url = 'http://192.168.49.207:3000/data/pulse_spo2',
		data = urllib.urlencode(data)
	)
        time.sleep(0.5)
	print f.read()

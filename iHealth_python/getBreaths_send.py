import iHealth
import time
import urllib,urllib2,json

if __name__ == '__main__':
    last_data = 0
    while(1):
        datas = []
	i=0
	while(i < 20):
            airFlow = iHealth.getAirFlow()
	    data = {'breath':airFlow}
	    if (airFlow-last_data > 100):
		 continue
	    last_data = airFlow
	    datas.append(data)
	    i+=1
	    print data,i
            time.sleep(0.05)
        datas0 = json.dumps(datas)
	datas1 = {"breaths": datas0}
	print datas1
	f = urllib2.urlopen(
		url = 'http://192.168.49.207:3000/data/breaths',
		data = urllib.urlencode(datas1)
	)
	print f.read()

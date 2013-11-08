import iHealth
import time
import urllib,urllib2,json

if __name__ == '__main__':
    while(1):
        datas = []
	i=0
	while(i < 10):
            data = {'ecg':iHealth.getECG()}
	    datas.append(data)
	    i+=1
	    print data,i
            time.sleep(0.3)
        datas0 = json.dumps(datas)
	datas1 = {"ecgs": datas0}
	print datas1
	f = urllib2.urlopen(
		url = 'http://192.168.49.207:3000/data/ecgs',
		data = urllib.urlencode(datas1)
	)
	print f.read()

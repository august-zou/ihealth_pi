import iHealth,time,urllib,urllib2,json,threading
_url = "http://192.168.1.2:3000"
class ECGS(threading.Thread):
    def __init__(self,collectNum,interval):
        threading.Thread.__init__(self)
	self.collectNum = collectNum
	self.interval = interval
	self.thread_stop = False

    def run(self):
        while not self.thread_stop:
            datas=[]
            i=0
            while(i<self.collectNum):
                data = {"ecg":iHealth.getECG()}
 		datas.append(data)
                i+=1
		time.sleep(self.interval)
            data0 = json.dumps(datas)
            data1 = {"ecgs":data0}
            f = urllib2.urlopen(
		url = _url+'/data/ecgs',
		data = urllib.urlencode(data1)
	    )
            print f.read()
     
    def stop(self):
        self.thread_stop = True

class BreathS(threading.Thread):
    def __init__(self,collectNum,interval):
        threading.Thread.__init__(self)
	self.collectNum = collectNum
	self.interval = interval
	self.thread_stop = False

    def run(self):
        last_data = 0
        while not self.thread_stop:
            datas=[]
            i=0
            while(i<self.collectNum):
                airFlow = iHealth.getAirFlow()
                data = {"breath":airFlow}
                if(airFlow-last_data > 100):
                    continue
                last_data = airFlow
 		datas.append(data)
                i+=1
		time.sleep(self.interval)
            data0 = json.dumps(datas)
            data1 = {"breaths":data0}
            f = urllib2.urlopen(
		url = _url+'/data/breaths',
		data = urllib.urlencode(data1)
	    )
            print f.read()
     
    def stop(self):
        self.thread_stop = True
	
	
class BPMSPO2(threading.Thread):
    def __init__(self,interval):
        threading.Thread.__init__(self)
	self.interval = interval
	self.thread_stop = False

    def run(self):
        iHealth.setupPulsioximeter()
        while not self.thread_stop:
            data = {'pulse':iHealth.getBPM(),'spo2':iHealth.getOxygenSaturation()}
            f = urllib2.urlopen(
		url = _url+'/data/pulse_spo2',
		data = urllib.urlencode(data)
	    )
	    time.sleep(self.interval)
            print f.read()
     
    def stop(self):
        self.thread_stop = True
	
class TMP(threading.Thread):
    def __init__(self,interval):
        threading.Thread.__init__(self)
	self.interval = interval
	self.thread_stop = False

    def run(self):
        iHealth.setupPulsioximeter()
        while not self.thread_stop:
            data = {'temperature':iHealth.getTemperature()}
            f = urllib2.urlopen(
		url = _url+'/data/temperature',
		data = urllib.urlencode(data)
	    )
	    time.sleep(self.interval)
            print f.read()
     
    def stop(self):
        self.thread_stop = True
	
if __name__ == '__main__':
    threadECGS = ECGS(100,0.01)
    threadBPMSPO2 = BPMSPO2(0.5)
    threadBreathS = BreathS(20,0.05)
    threadTMP = TMP(0.5)
    threadECGS.start()
    threadBPMSPO2.start()
    threadBreathS.start()
    threadTMP.start()

import iHealth
import time
import urllib2

if __name__ == '__main__':
     iHealth.setupPulsioximeter()
     while(1):
        bpm = iHealth.getBPM()
        oxygen = iHealth.getOxygenSaturation()
        print "bpm: %d   spo2: %d" % (bpm,oxygen)
	time.sleep(0.5)

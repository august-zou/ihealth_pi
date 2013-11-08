import iHealth
import time

if __name__ == '__main__':
    while(1):
        print iHealth.getTemperature()
        time.sleep(1)

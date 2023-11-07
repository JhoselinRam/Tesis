from scipy.fft import fft, fftfreq
import numpy as np
import matplotlib.pyplot as plt
import csv

column = 2
n = 0

time = []
data = []

with open('ultrasonic_filter_raw_data.csv') as csvfile:
  csvReader = csv.reader(csvfile, delimiter=',')
  for row in csvReader:
    if n > 1:
      time.append(float(row[0]))
      data.append(float(row[column]))
    n += 1

n -= 2
step = time[1] - time[0]

data_f = fft(data)
freq = fftfreq(n, d=step)[1:n//2]

plt.plot(freq, 2.0/n*np.abs(data_f[1:n//2]))
plt.grid()
plt.show()
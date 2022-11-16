#!/usr/bin/env python3
import random
import os
import datetime

fName = 'daily_extraLarge.csv'
if os.path.isfile(fName):
    os.remove(fName)

f = open(fName, 'a')
f.write('Date,Brazil,China,Germany,India,Nigeria,Norway,South Korea,United Kingdom,United States\n')

date = datetime.datetime.now()

for i in range(300):
    f.write(date.strftime('%Y-%m-%d')+',')
    cases = [str(random.randint(0, 100000)) for _ in range(9)]
    f.write((',').join(cases)+'\n')
    date = date + datetime.timedelta(1)
    
f.close()

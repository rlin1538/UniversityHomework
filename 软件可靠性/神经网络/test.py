import numpy

my_data = numpy.loadtxt('CSR1.txt',delimiter='\t',usecols=0)[:,numpy.newaxis]
print(my_data)
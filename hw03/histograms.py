import matplotlib.pyplot as plt

myData = []
theirData = []

with open('mydouble.txt', 'r') as f:
	for line in f:
		myData.append(float(line))

with open('theirdouble.txt', 'r') as f:
	for line in f:
		theirData.append(float(line))

plt.hist(myData, 100)

plt.show()

plt.hist(theirData, 100)

plt.show()
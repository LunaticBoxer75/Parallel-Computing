import numpy as np
import matplotlib
import matplotlib.pyplot as plt

data =np.array([[0.0810207, 0.712934, 7.94048],
[0.0332742, 0.374044, 4.10953],
[0.0205079, 0.254543, 2.27585],])
X = np.arange(3)

# print(data)
X=X*2

plt.bar(X + 0.00, data[0], color = 'yellow', width = 0.25, label = 'sequential')
plt.bar(X + 0.25, data[1], color = 'blue', width = 0.25, label = '2 processes')
plt.bar(X + 0.50, data[2], color = 'purple', width = 0.25, label = '4 processes')



plt.xlabel('Number of elements in the array', fontweight = 'bold')
plt.ylabel('Runtime (in sec)', fontweight = 'bold')
# plt.grid()
# plt.title('Speedup vs Processors/Threads')
plt.xticks([2*r + 0.25+0.125 for r in range(3)], ['200', '500', '1000'])

plt.legend(loc="upper left", prop={'size': 7})
# matplotlib.use('Agg')
plt.savefig('./g2.jpg')
plt.show()
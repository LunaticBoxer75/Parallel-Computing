import numpy as np
import matplotlib
import matplotlib.pyplot as plt

data =np.array([[0.21996/0.21996,8.40129/8.40129, 100.83426/100.83426],
[0.21996/0.17993, 8.40129/7.86845, 100.83426/30.43219],
[0.21996/0.08013, 8.40129/2.90648, 100.83426/20.60630],
[0.21996/0.08148, 8.40129/2.45585, 100.83426/16.58329 ]])
X = np.arange(3)
data=np.transpose(data)
print(data)
X=X*2

# plt.bar(X + 0.00, data[0], color = 'yellow', width = 0.25, label = 'sequential')
# plt.bar(X + 0.25, data[1], color = 'blue', width = 0.25, label = '2 threads')
# plt.bar(X + 0.50, data[2], color = 'purple', width = 0.25, label = '3 threads')
# plt.bar(X + 0.75, data[3], color = 'red', width = 0.25, label = '4 threads')


# plt.xlabel('Number of nodes', fontweight = 'bold')
# plt.ylabel('Speedup', fontweight = 'bold')
# # plt.grid()
# # plt.title('Speedup vs Processors/Threads')
# plt.xticks([2*r + 0.25+0.125 for r in range(3)], ['200', '500', '1000'])

# plt.legend(loc="upper left", prop={'size': 7})
# # matplotlib.use('Agg')
# plt.savefig('./1.jpg')
# plt.show()
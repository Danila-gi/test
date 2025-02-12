import random
import time
import matplotlib.pyplot as plt
import numpy as np

nechet_y = [0, 0, 0, 0.000998, 0.002993, 0.032913, 0.136665, 0.086797, 2.02304, 5.45898]
nechet_x = [x for x in range(1, 20, 2)]

chet_y = [0, 0, 0.000997, 0.000997, 0.006015, 0.006011, 0.100817, 0.173417, 0.25834, 1.10584]
chet_x = [x for x in range(0, 20, 2)]


def pr(chet_x, chet_y, nechet_x, nechet_y):
    plt.plot(chet_x, chet_y, label="Время выполнения для нечетных", marker="o", color="blue")
    plt.plot(nechet_x, nechet_y, label="Время выполнения для четных", marker="o", color="red")
    plt.title("Время выполнения алгоритма")
    plt.xlabel("Количество элементов (n)")
    plt.ylabel("Время (сек.)")
    plt.legend()
    plt.show()


pr(nechet_x, nechet_y, chet_x, chet_y)

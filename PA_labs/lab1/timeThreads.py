import matplotlib.pyplot as plt
import numpy as np

threads = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]

times_data = [
    [6.955, 9.723, 9.811],
    [5.266, 8.498, 8.009],
    [4.362, 7.038, 7.030],
    [3.766, 6.190, 6.316],
    [3.601, 6.014, 6.036],
    [3.010, 5.549, 5.475],
    [4.301, 6.010, 6.774],
    [3.586, 5.950, 5.850],
    [3.380, 5.563, 5.535],
    [3.496, 5.558, 5.600],
    [4.158, 6.075, 6.098],
    [4.595, 6.637, 6.773],
    [3.352, 5.554, 5.469],
    [4.651, 6.609, 6.853],
    [3.558, 5.739, 5.549],
    [5.225, 7.185, 7.264],
    [4.072, 6.200, 6.305],
    [3.423, 5.428, 5.604],
    [5.648, 7.633, 7.905],
    [4.426, 6.769, 6.866],
    [3.930, 6.060, 5.925],
    [3.431, 5.399, 5.453],
    [6.099, 8.073, 8.447]
]

times_avg = [np.mean(times) for times in times_data]

plt.figure(figsize=(14, 8))

plt.plot(threads, times_avg, 'bo-', linewidth=2, markersize=8, label='Многопоточное умножение (среднее значение)')

plt.xlabel('Количество потоков', fontsize=14)
plt.ylabel('Время выполнения (секунды)', fontsize=14)
plt.title('Зависимость времени умножения матриц от количества потоков\nРазмер матрицы: 1408×1408, Размер блока: 128 (усредненные значения)', fontsize=16, pad=20)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=12)

for i, (thread, time_avg) in enumerate(zip(threads, times_avg)):
    plt.annotate(f'{time_avg:.2f}', (thread, time_avg), 
                 textcoords="offset points", 
                 xytext=(0,10), 
                 ha='center',
                 fontsize=9,
                 alpha=0.8)

plt.xlim(2, 26)
plt.ylim(3, 10)
plt.xticks(np.arange(3, 26, 1))
plt.yticks(np.arange(3, 10.5, 0.5))

plt.minorticks_on()
plt.grid(which='major', alpha=0.5)
plt.grid(which='minor', alpha=0.2)

plt.tight_layout()
plt.show()
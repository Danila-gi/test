import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

matrix_sizes = np.array([1152, 1280, 1408, 1536, 1664, 1792, 1920, 2048, 2176, 2304, 
                        2432, 2560, 2688, 2816, 2944, 3072, 3200, 3328, 3456])
times = np.array([1.651, 2.586, 2.927, 3.698, 4.996, 6.949, 8.042, 10.577, 12.845, 15.941,
                 17.787, 20.636, 24.212, 28.474, 31.530, 35.700, 40.706, 46.840, 50.891])

def cubic_func(x, a, b):
    return a * x**3 + b

popt, pcov = curve_fit(cubic_func, matrix_sizes, times)
a_fit, b_fit = popt

plt.figure(figsize=(14, 8))

plt.plot(matrix_sizes, times, 'ro-', linewidth=2, markersize=6, label='Экспериментальные данные')

x_fit = np.linspace(min(matrix_sizes), max(matrix_sizes), 100)
y_fit = cubic_func(x_fit, a_fit, b_fit)
plt.plot(x_fit, y_fit, 'b--', linewidth=2, label=f'Кубическая аппроксимация: y = {a_fit:.2e}·x³ + {b_fit:.2f}')

plt.xlabel('Размер матрицы', fontsize=14)
plt.ylabel('Время выполнения (секунды)', fontsize=14)
plt.title('Зависимость времени умножения матриц от их размера\n(кубическая аппроксимация O(n³))', fontsize=16, pad=20)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=12)

for i, (size, time_val) in enumerate(zip(matrix_sizes, times)):
    plt.annotate(f'{time_val:.1f}', (size, time_val), 
                 textcoords="offset points", 
                 xytext=(0,10), 
                 ha='center',
                 fontsize=8,
                 alpha=0.8)

plt.xlim(1100, 3500)
plt.ylim(0, 55)
plt.xticks(np.arange(1150, 3500, 250))
plt.yticks(np.arange(0, 55, 5))

plt.minorticks_on()
plt.grid(which='major', alpha=0.5)
plt.grid(which='minor', alpha=0.2)

plt.tight_layout()
plt.show()
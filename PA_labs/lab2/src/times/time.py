import matplotlib.pyplot as plt
import numpy as np

writers = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0]
#fine_times = [14246, 11496.67, 10909, 11082, 10832, 8350.67, 12003.33, 11262, 11714.33, 11268, 12343.33]
#coarse_times = [10992.67, 11448.67, 10996.33, 11195.67, 11448, 10805.33, 11533.67, 11332.67, 11096.67, 11149.33, 12313.33]
#lockfree_times = [10887, 11569.33, 11011.33, 11369, 11230.33, 11166.67, 11516.67, 11376.33, 11773, 11215, 11756]

fine_times = [2600, 2603.67, 2652.67, 2590, 2455.33, 2515, 2612.33, 2484, 2634, 2627.33, 2605]
coarse_times = [11136.67, 11333, 11187, 13088, 11399.33, 10944.33, 11731.33, 11196.33, 11723.67, 11358, 11249.67]
lockfree_times = [11423.33, 12216.67, 11436, 12404.67, 9714, 11403.33, 9260.33, 11582.33, 11476.67, 11325, 11253]

#fine_times = [2720.33, 2655.33, 2699, 2663.67, 2837, 2864.67, 2735, 2863.33, 2681.67, 2737, 2899]
#coarse_times = [10630.33, 11434.67, 12148.33, 11249.33, 11454.33, 11446.67, 12107.33, 10883.67, 11809.33, 11055.67, 11363.33]
#lockfree_times = [2530.67, 2489.33, 2550.33, 2521.33, 2611.67, 2562.67, 2748.33, 2585.33, 2476, 4217.67, 2415]

plt.figure(figsize=(12, 8))

plt.plot(writers, fine_times, 's-', label='Fine-grained', linewidth=2, markersize=8)
plt.plot(writers, coarse_times, 's-', label='Coarse-grained', linewidth=2, markersize=8)
plt.plot(writers, lockfree_times, 's-', label='LockFree', linewidth=2, markersize=8)
plt.xlabel('Количество писателей')
plt.ylabel('Время (мкс)')
plt.title('Сравнение производительности: Fine-grained vs Coarse-grained (3000 элементов)')
plt.legend()
plt.grid(True, alpha=0.3)
plt.gca().invert_xaxis()

plt.tight_layout()
plt.show()
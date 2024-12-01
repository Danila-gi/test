from main import ProctoringSystem, Record
import matplotlib.pyplot as plt
import time
import random
import math


# Тестирование производительности
def test_performance():
    system = ProctoringSystem()

    system.add_group(3342)

    sizes = [100, 1000, 3000, 8000, 15000, 30000]
    add_times = []
    del_times = []
    find_times = []
    most_times = []

    add_t = []
    del_t = []
    find_t = []

    records = [(f"Student{i}", random.randint(0, 100), 3342) for i in range(30000)]

    for size in sizes:
        rec = records[size // 2]
        add_t.append(math.log(size, 2))
        del_t.append(math.log(2, size))
        find_t.append(math.log(2, size))
        for name, suspicion, group in records[:size]:
            system.add_record(name, suspicion, 3342)

        # 1. Замер времени добавления
        start_time = time.perf_counter()
        system.add_record(rec[0], rec[1], 3342)
        end_time = time.perf_counter()
        add_times.append(end_time - start_time)

        # 2. Замер времени поиска
        start_time = time.perf_counter()
        system.find_record(3342, rec[0], rec[1])
        end_time = time.perf_counter()
        find_times.append(end_time - start_time)

        # 3. Замер времени удаления
        start_time = time.perf_counter()
        record = Record(rec[1], rec[0])
        system.del_record(record, 3342)
        end_time = time.perf_counter()
        del_times.append(end_time - start_time)

        # 4. Замеры времени нахождения самых подозрительных
        start_time = time.perf_counter()
        system.find_most_suspicion(10, 3342)
        end_time = time.perf_counter()
        most_times.append(end_time - start_time)

    # Построение графиков
    plt.figure(figsize=(10, 6))

    plt.plot(sizes, add_times, label="Addition Time", marker="o")

    plt.plot(sizes, find_times, label="Search Time", marker="o")

    plt.plot(sizes, del_times, label="Deletion Time", marker="o")

    plt.plot(sizes, most_times, label="Find Most Time", marker="o")

    plt.xlabel("Number of Records")
    plt.ylabel("Time (seconds)")
    plt.title("Performance of Proctoring System")
    plt.legend()
    plt.grid(True)
    plt.show()


# Запуск тестирования
test_performance()
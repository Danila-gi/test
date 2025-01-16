import time
import matplotlib.pyplot as plt

start_time = time.perf_counter()
system.add_record(rec[0], rec[1], 3342)
end_time = time.perf_counter()

plt.figure(figsize=(10, 6))
plt.plot(x_data, y_data, label="name of graphic", marker="o")

# --------------------

import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
def calculate_min_run(n):
    r = 0
    while n >= 16:
        r |= n & 1
        n >>= 1
    return n + r


def return_format_arr(arr):
    return ' '.join(list(map(str, arr)))


def find_index_of_element(T, N, arr):
    left, right = 0, N
    while left < right:
        if (left + right) % 2 == 0:
            mid = (left + right) // 2 - 1
        else:
            mid = (left + right) // 2
        if abs(arr[mid]) < abs(T):
            right = mid
        else:
            left = mid + 1
    return left


class Stack:
    def __init__(self):
        self.count_of_merge = 0
        self.blocks = []

    def push(self, block):
        if len(self.blocks) == 0:
            self.blocks.append(block)

        else:
            self.blocks.insert(0, block)
            flag1 = len(self.blocks[1]) > len(self.blocks[0])
            if len(self.blocks) == 2:
                while not flag1:
                    if len(self.blocks) == 1:
                        break
                    self.blocks[0] = merge_arr(self.blocks[0], self.blocks[1],
                                               self.count_of_merge)  # self.blocks[0] += self.blocks[1]
                    print(f"Merge {self.count_of_merge}:", return_format_arr(self.blocks[0]))
                    self.count_of_merge += 1
                    del self.blocks[1]
            else:
                flag2 = self.blocks[2] > self.blocks[1] + self.blocks[0]
                while (not flag1 or not flag2) and len(self.blocks) >= 2:
                    if len(self.blocks) == 3 and len(self.blocks[2]) < len(self.blocks[0]):
                        self.blocks[2] = merge_arr(self.blocks[2], self.blocks[1],
                                                   self.count_of_merge)  # self.blocks[2] += self.blocks[1]
                        print(f"Merge {self.count_of_merge}:", return_format_arr(self.blocks[2]))
                        self.count_of_merge += 1
                    else:
                        self.blocks[0] = merge_arr(self.blocks[0], self.blocks[1],
                                                   self.count_of_merge)  # self.blocks[0] += self.blocks[1]
                        print(f"Merge {self.count_of_merge}:", return_format_arr(self.blocks[0]))
                        self.count_of_merge += 1
                    del self.blocks[1]
                    if len(self.blocks) == 1:
                        flag1 = True
                    else:
                        flag1 = len(self.blocks[1]) > len(self.blocks[0])
                    if len(self.blocks) <= 2:
                        flag2 = True
                    else:
                        flag2 = len(self.blocks[2]) > len(self.blocks[1]) + len(self.blocks[0])

    def pop(self):
        del self.blocks[0]


def merge_with_stack(a):
    s = Stack()
    for i in a:
        s.push(i)
    count_of_merge = s.count_of_merge
    if len(s.blocks) == 1:
        return s.blocks[0]
    else:
        while len(s.blocks) > 1:
            if len(s.blocks) == 3 and len(s.blocks[2]) < len(s.blocks[0]):
                s.blocks[2] = merge_arr(s.blocks[2], s.blocks[1], s.count_of_merge)  # s.blocks[2] += s.blocks[1]
                print(f"Merge {count_of_merge}:", return_format_arr(s.blocks[2]))
                count_of_merge += 1
            else:
                s.blocks[0] = merge_arr(s.blocks[0], s.blocks[1], s.count_of_merge)  # s.blocks[0] += s.blocks[1]
                print(f"Merge {count_of_merge}:", return_format_arr(s.blocks[0]))
                count_of_merge += 1
            del s.blocks[1]
        return s.blocks[0]


def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1

        while j >= 0 and abs(arr[j]) < abs(key):
            arr[j + 1] = arr[j]
            j -= 1

        arr[j + 1] = key
    return arr


def merge_arr(N_array, M_array, number_of_merge):
    count_of_golops = 0
    n, m = len(N_array), len(M_array)
    k_n = 0
    k_m = 0
    index_n = 0
    index_m = 0
    result = []
    while index_n < n and index_m < m:
        if abs(N_array[index_n]) > abs(M_array[index_m]):
            result.append(N_array[index_n])
            k_n += 1
            k_m = 0
            index_n += 1

        else:
            result.append(M_array[index_m])
            k_n = 0
            k_m += 1
            index_m += 1

        if k_n == 3:
            ind = find_index_of_element(M_array[index_m], n - index_n, N_array[index_n:].copy()) + index_n
            count_of_golops += 1
            result.extend(N_array[index_n:ind])
            index_n = ind
            k_n = 0

        elif k_m == 3:
            ind = find_index_of_element(N_array[index_n], m - index_m, M_array[index_m:].copy()) + index_m
            count_of_golops += 1
            result.extend(M_array[index_m:ind])
            index_m = ind
            k_m = 0

    if index_m < m:
        while index_m < m:
            result.append(M_array[index_m])
            index_m += 1
    elif index_n < n:
        while index_n < n:
            result.append(N_array[index_n])
            index_n += 1

    print(f"Gallops {number_of_merge}:", count_of_golops)
    return result


def check_order(arr):
    flag_increase = True
    flag_decrease = True
    for i in range(len(arr) - 1):
        if abs(arr[i + 1]) > abs(arr[i]):
            flag_decrease = False
        elif abs(arr[i + 1]) < abs(arr[i]):
            flag_increase = False
        if not flag_increase and not flag_decrease:
            break
    return (flag_increase, flag_decrease)


def TimeSort(arr, n):
    min_run = calculate_min_run(n)
    Parts = []
    part = []
    k = 0
    index = 0
    while index < len(arr):
        if k < min_run:
            part.append(arr[index])
            k += 1
            index += 1
        else:
            flag_increase, flag_decrease = check_order(part)
            if flag_increase and flag_decrease:
                while abs(arr[index]) == abs(part[-1]):
                    part.append(arr[index])
                    index += 1
                Parts.append(part)
                part = []
                k = 0
                continue

            while index < len(arr) and ((flag_increase and abs(arr[index]) > abs(part[-1])) or (
                    flag_decrease and abs(arr[index]) < abs(part[-1]))):
                part.append(arr[index])
                index += 1

            if flag_increase:
                part.reverse()

            if not (flag_increase or flag_decrease):
                part = insertion_sort(part)

            Parts.append(part)
            part = []
            k = 0

    if len(part) != 0:
        flag_increase, flag_decrease = check_order(part)
        if flag_increase:
            part.reverse()

        if not (flag_increase or flag_decrease):
            part = insertion_sort(part)

        Parts.append(part)

    for j in range(len(Parts)):
        print(f"Part {j}: {return_format_arr(Parts[j])}")

    arr = merge_with_stack(Parts)
    if len(Parts) == 1:
        print()
    return arr


n = int(input())
arr = list(map(int, input().split()))
arr = TimeSort(arr, n)
print("Answer:", return_format_arr(arr))

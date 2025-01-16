def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1


# неточный поиск
def find_index_of_element(T, N, arr):
    left, right = 0, N
    while left < right:
        if (left + right) % 2 == 0:
            mid = (left + right) // 2 - 1
        else:
            mid = (left + right) // 2
        print(T, arr[mid])
        if abs(arr[mid]) > abs(T):
            right = mid
        else:
            left = mid + 1
    return left
from UnrolledLinkedList import UnrolledLinkedList
from LinkedList import LinkedList
import time

NUM = 100000
LinkedL = LinkedList()
Array = list()

start_time = time.perf_counter()
ListN = UnrolledLinkedList([x for x in range(NUM)])
end_time = time.perf_counter()
print(f"UnrolledListNode make: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
for i in range(NUM):
    LinkedL.append(i)
end_time = time.perf_counter()
print(f"LinkedList make: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
for i in range(NUM):
    Array.append(i)
end_time = time.perf_counter()
print(f"Array make: {end_time - start_time:.10f} seconds")

print('----------------------------')

start_time = time.perf_counter()
ListN.push(99)
end_time = time.perf_counter()
print(f"UnrolledListNode push: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.append(99)
end_time = time.perf_counter()
print(f"LinkedList push: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.append(99)
end_time = time.perf_counter()
print(f"Array push: {end_time - start_time:.10f} seconds")

print('----------------------------')

start_time = time.perf_counter()
ListN.insert(99, NUM // 2)
end_time = time.perf_counter()
print(f"UnrolledListNode insert in the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.insert_at_index(NUM // 2, 99)
end_time = time.perf_counter()
print(f"LinkedList insert in the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.insert(NUM // 2, 99)
end_time = time.perf_counter()
print(f"Array insert in the middle: {end_time - start_time:.10f} seconds")

print('----------------------------')

start_time = time.perf_counter()
ListN.insert(99, 0)
end_time = time.perf_counter()
print(f"UnrolledListNode insert in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.insert_at_index(0, 99)
end_time = time.perf_counter()
print(f"LinkedList insert in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.insert(0, 99)
end_time = time.perf_counter()
print(f"Array insert in the start: {end_time - start_time:.10f} seconds")
print('----------------------------')

start_time = time.perf_counter()
ListN.delete_number(NUM + 2)
end_time = time.perf_counter()
print(f"UnrolledListNode delete in the end: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.remove_at_index(NUM + 2)
end_time = time.perf_counter()
print(f"LinkedList delete in the end: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
del Array[NUM + 2]
end_time = time.perf_counter()
print(f"Array delete in the end: {end_time - start_time:.10f} seconds")

print('----------------------------')

start_time = time.perf_counter()
ListN.delete_number(0)
end_time = time.perf_counter()
print(f"UnrolledListNode delete in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.remove_at_index(0)
end_time = time.perf_counter()
print(f"LinkedList delete in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
del Array[0]
end_time = time.perf_counter()
print(f"Array delete in the start: {end_time - start_time:.10f} seconds")

print('----------------------------')

start_time = time.perf_counter()
ListN.delete_number(NUM // 2)
end_time = time.perf_counter()
print(f"UnrolledListNode delete in the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.remove_at_index(NUM // 2)
end_time = time.perf_counter()
print(f"LinkedList delete in the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
del Array[NUM // 2]
end_time = time.perf_counter()
print(f"Array delete in the middle: {end_time - start_time:.10f} seconds")

print('---------------------------')

start_time = time.perf_counter()
ListN.find_index_of_number(0)
end_time = time.perf_counter()
print(f"UnrolledListNode find in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.find_index_by_value(0)
end_time = time.perf_counter()
print(f"LinkedList find in the start: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.index(0)
end_time = time.perf_counter()
print(f"Array find in the start: {end_time - start_time:.10f} seconds")

print('---------------------------')

start_time = time.perf_counter()
ListN.find_index_of_number(NUM // 2)
end_time = time.perf_counter()
print(f"UnrolledListNode find the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.find_index_by_value(NUM // 2)
end_time = time.perf_counter()
print(f"LinkedList find in the middle: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.index(NUM // 2)
end_time = time.perf_counter()
print(f"Array find in the middle: {end_time - start_time:.10f} seconds")

print('---------------------------')

start_time = time.perf_counter()
ListN.find_index_of_number(NUM - 1)
end_time = time.perf_counter()
print(f"UnrolledListNode find the end: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
LinkedL.find_index_by_value(NUM - 1)
end_time = time.perf_counter()
print(f"LinkedList find in the end: {end_time - start_time:.10f} seconds")

start_time = time.perf_counter()
Array.index(NUM - 1)
end_time = time.perf_counter()
print(f"Array find in the end: {end_time - start_time:.10f} seconds")

print('---------------------------')
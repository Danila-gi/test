#!/bin/bash

gcc rr1_5_5.c -o rr1
gcc rr2_5_5.c -o rr2
gcc fifo1_5_5.c -o fifo1
gcc fifo2_5_5.c -o fifo2
EXECUTABLES_FIFO=("fifo1" "fifo2")
EXECUTABLES_RR=("rr1" "rr2")

PRIORITIES_FIFO=(30 30)
PRIORITIES_RR=(30 30)

# Функция для ожидания завершения группы процессов
wait_for_processes() {
    for pid in "$@"; do
        wait "$pid"
    done
}

pids=()

for i in "${!EXECUTABLES_RR[@]}"; do
    exe="${EXECUTABLES_RR[$i]}"
    prio="${PRIORITIES_RR[$i]}"
    echo "Запуск $exe с приоритетом $prio"
    sudo taskset -c 0 "./$exe" "$prio" &
    pids+=($!)
done

for i in "${!EXECUTABLES_FIFO[@]}"; do
    exe="${EXECUTABLES_FIFO[$i]}"
    prio="${PRIORITIES_FIFO[$i]}"
    echo "Запуск $exe с приоритетом $prio"
    sudo taskset -c 0 "./$exe" "$prio" &
    pids+=($!)
done

wait_for_processes "${pids[@]}"

rm rr1 rr2 fifo1 fifo2

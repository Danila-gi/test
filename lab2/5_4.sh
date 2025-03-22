#!/bin/bash

EXECUTABLES=("rr1" "rr2" "rr3")

DIFFERENT_PRIORITIES=(30 30 30)

# Функция для ожидания завершения группы процессов
wait_for_processes() {
    for pid in "$@"; do
        wait "$pid"
    done
}

pids=()
for i in "${!EXECUTABLES[@]}"; do
    exe="${EXECUTABLES[$i]}"
    prio="${DIFFERENT_PRIORITIES[$i]}"
    echo "Запуск $exe с приоритетом $prio"
    sudo taskset -c 0 "./$exe" "$prio" &
    pids+=($!)
done
wait_for_processes "${pids[@]}"

rm rr1 rr2 rr3

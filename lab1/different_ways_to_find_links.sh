#!/bin/bash

# Проверяем, что передан аргумент с именем файла
if [ -z "$1" ]; then
    echo "Использование: $0 <файл>"
    exit 1
fi

target_file=$(realpath "$1")  # Нормализация пути

find / -type l 2>/dev/null | while read -r link; do
    # Получаем цель символьной ссылки
    link_target=$(readlink -f "$link")
    # Сравниваем цель ссылки с целевым файлом
    if [ "$link_target" == "$target_file" ]; then
        echo "$link -> $link_target"
    fi
done

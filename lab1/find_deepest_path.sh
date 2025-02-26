#!/bin/bash

# Функция для поиска самого глубокого пути
find_deepest_path() {
    local dir="$1"
    local max_depth=0
    local deepest_path=""

    while IFS= read -r path; do
        depth=$(echo "$path" | tr -cd '/' | wc -c)
        if [ "$depth" -gt "$max_depth" ]; then
            max_depth=$depth
            deepest_path=$path
        fi
    done < <(find "$dir" -type d 2>/dev/null)

    echo "Самый глубокий путь: $deepest_path"
    echo "Глубина: $max_depth"
    echo "Длина самого глубокого пути: $(echo -n "$deepest_path" | wc -c)"
}

# Функция для анализа ограничений
analyze_limits() {
    echo "Анализ ограничений:"

    local path_max=$(getconf PATH_MAX /)
    echo "1. Максимальная длина пути (PATH_MAX): $path_max символов"

    local name_max=$(getconf NAME_MAX /)
    echo "2. Максимальная длина имени файла (NAME_MAX): $name_max символов"
}

# Начинаем поиск с корневой директории /
find_deepest_path "/"

analyze_limits

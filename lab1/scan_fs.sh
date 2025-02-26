#!/bin/bash

# Проверка аргументов
if [ -z "$1" ]; then
  echo "Использование: $0 <выходной_файл>"
  exit 1
fi

output_file="$1"
> "$output_file"  # Очистка файла

# Функция для поиска и записи первого файла указанного типа
find_and_write() {
    local type="$1"
    local name
    if [ "$type" == "l" ]; then
        name=$(ls -lR 2>/dev/null / | grep -E "^$type" | awk '{print $(NF-2); exit}')
    else
        name=$(ls -lR 2>/dev/null / | grep -E "^$type" | awk '{print $NF; exit}')
    fi
    echo $name
    find 2>/dev/null / -name "$name" | awk '{print $0; exit}' >> $output_file 
}

# Поиск и запись для каждого типа файла
echo "Поиск файлов..."
find_and_write "-"  # Обычный файл
find_and_write "b"  # Блочное устройство
find_and_write "c"  # Символьное устройство
find_and_write "d"  # Директория
find_and_write "l"  # Символьная ссылка
find_and_write "p"  # Именованный канал
find_and_write "s"  # Сокет

echo "Результаты записаны в $output_file"

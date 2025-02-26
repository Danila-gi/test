#!/bin/bash

# Проверяем, что передан аргумент с именем файла
if [ -z "$1" ]; then
    echo "Использование: $0 <файл>"
    exit 1
fi

target_file="$1"
count=0  # Счетчик символьных ссылок

# Поиск символьных ссылок на целевой файл
ls -lR / 2>/dev/null | grep "$target_file" | grep ^l | awk '
{
    print $0
    count++
}
END {
    print "Найдено символьных ссылок: " count
}
'

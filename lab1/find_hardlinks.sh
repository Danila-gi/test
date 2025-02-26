#!/bin/bash

# Проверяем, что передан аргумент с именем файла
if [ -z "$1" ]; then
    echo "Использование: $0 <файл>"
    exit 1
fi

# Получаем inode целевого файла
target_file="$1"
target_inode=$(stat -c %i "$target_file")

# Проверяем, что файл существует
if [ -z "$target_inode" ]; then
    echo "Файл '$target_file' не найден."
    exit 1
fi

echo "Поиск жёстких ссылок на файл '$target_file' (inode: $target_inode)..."

# Рекурсивно обходим файловую систему с помощью ls -iR
ls -iR / 2>/dev/null | awk -v target_inode="$target_inode" -v target_file="$target_file" '
BEGIN {
    dir = ""
}
{

    # Если строка начинается с "./", это путь к каталогу
    if ($0 ~ /^\//) {
        dir = substr($0, 1, length($0) - 1)  # Убираем двоеточие в конце
    }
    # Если строка содержит inode и имя файла
    else if ($1 ~ /^[0-9]+$/ && $2 != "") {
        # Если inode совпадает с целевым и это не исходный файл
        if ($1 == target_inode) {
            print dir "/" $2  # Выводим полный путь к файлу
        }
    }
}
'

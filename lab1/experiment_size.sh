#!/bin/bash

mkdir -p test_dir
echo "Создан каталог test_dir."

echo "Размер пустого каталога:"
du -sh test_dir

# Создаем 100 файлов
touch test_dir/file{1..100}
echo "Создано 100 файлов."

echo "Размер каталога после создания файлов:"
du -sh test_dir

mkdir -p test_dir/subdir{1..10}
echo "Создано 10 подкаталогов."

echo "Размер каталога после создания подкаталогов:"
du -sh test_dir

rm test_dir/file{1..50}
echo "Удалено 50 файлов."

echo "Размер каталога после удаления файлов:"
du -sh test_dir

rmdir test_dir/subdir{1..5}
echo "Удалено 5 подкаталогов."

echo "Размер каталога после удаления подкаталогов:"
du -sh test_dir

rm -rf test_dir
echo "Каталог test_dir удален."

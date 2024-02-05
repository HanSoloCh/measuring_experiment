#!/bin/bash

# Задание начальных значений переменных
type_of_alloc="c r w"  # Типы сортировки

sizes="0 1 10 50 100 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000"  # Размеры данных

#sizes="10000 20000 30000 40000 50000"  # Размеры данных


count=500  # Количество запусков

mkdir -p ./data

# Обработка опций командной строки
while getopts ":t:s:c:" op; do
  case $op in
    t)
      type_of_alloc=$OPTARG
      ;;
    s)
      sizes=$OPTARG
      ;;
    c)
      count=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

gcc main.c time_exp.c -o ./app.exe

mkdir -p data
# Цикл по размерам данных
for size in $sizes; do

# Цикл по количеству запусков
# Вложенные циклы для комбинаций параметров
  for type in $type_of_alloc; do
      for co in $(seq "$count"); do
          echo -n -e "size = $size $co/$count $type \r"
          # Запуск приложения с указанными параметрами и запись вывода в файл
          eval ./app.exe ./files/"$size" "$type" >> ./data/"$size"_"$type".txt
    done
  done
done
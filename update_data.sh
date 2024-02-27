#!/bin/bash

# Задание начальных значений переменных
type_of_alloc="c r w fr fw"  # Типы сортировки

sizes="0 1 10 50 100 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000"  # Размеры данных

compilers=("gcc" "diet gcc" "musl-gcc")


count=500  # Количество запусков
log="false"  # Флаг компиляции


# Обработка опций командной строки
while getopts ":t:s:c:l" op; do
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
    l)
      log="true"
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

if [ "$log" = "true" ]; then
  mkdir -p log
else
  mkdir -p data
fi

for compiler in "${compilers[@]}"; do
  if [ "$log" = "true" ]; then
    eval "$compiler" -DLOG -static -O0 ./src/main.c ./src/time_exp.c -I./inc -o ./app.exe
  else
    eval "$compiler" -static -O0 ./src/main.c ./src/time_exp.c -I./inc -o ./app.exe
  fi
  # Цикл по размерам данных
  for size in $sizes; do
  # Цикл по количеству запусков
  # Вложенные циклы для комбинаций параметров
    for type in $type_of_alloc; do
        for co in $(seq "$count"); do
            # Запуск приложения с указанными параметрами и запись вывода в файл
            if [ "$log" = "true" ]; then
              echo -n -e "$compiler size = $size $type \r"
              eval ./app.exe ./files/"$size" "$type" >> ./log/"$size"_"$type"_"$compiler".log
              break
            else
              echo -n -e "$compiler size = $size $co/$count $type \r"
              eval ./app.exe ./files/"$size" "$type" >> ./data/"$size"_"$type"_"$compiler".txt
            fi
      done
    done
  done
done
import random


# Задайте количество случайных чисел, которые нужно сгенерировать
lst = [0]

# Генерируем случайные числа и записываем их в файл
for num_numbers in lst:
    with open(str(num_numbers), 'w') as file:
        for _ in range(num_numbers):
            random_number = random.randint(1, 100)  # Генерируйте числа в нужном диапазоне
            file.write(str(random_number) + '\n')  # Записываем число в файл

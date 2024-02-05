import os
import matplotlib.pyplot as plt

# Путь к папке с данными
data_dir = 'preproc'

# Файлы с данными
files = sorted(os.listdir(data_dir), key=lambda x: int(x.split('_')[0]))

data_dict_1 = {}  # Данные для первого графика

# Проходимя по файлам с данными
for file_name in files:
    # Получаем название эксперимента из имени файла
    experiment_name = '_'.join(file_name[:-4].split('_')[1:])

    # Считываем данные из файла
    with open(os.path.join(data_dir, file_name)) as f:
        if experiment_name == 'c':
            experiment_name = 'count'
        elif experiment_name == 'r':
            experiment_name = 'realloc №1 (*2)'
        elif experiment_name == 'w':
            experiment_name = 'realloc №2 (+1)'
        elif experiment_name == 'fr':
            experiment_name = 'realloc №1 (*2) with fragmentation'
        elif experiment_name == 'fw':
            experiment_name = 'realloc №2 (+1) with fragmentation'

        # Инициализируем начальные данные
        if experiment_name not in data_dict_1:
            data_dict_1[experiment_name] = [[], []]

        # Размерность опытного массива
        data_dict_1[experiment_name][0].append(int(file_name.split('_')[0]))

        # Проверить, что считанное действительно среднее
        while 'Averange' not in (read_info := f.readline()) or not read_info:
            pass

        if 'Averange' in read_info:
            data_dict_1[experiment_name][1].append(float(read_info.split()[1]))
        # Если все-таки не нашлось нужных данных
        else:
            print('Something wrong with data. Run make_preproc.py\n')
            exit()

colors = ['red', 'green', 'blue', 'black', 'pink']

# Строим первые два графика
fig, ax = plt.subplots(figsize=(12, 8))
j = 0

for experiment_name, data in sorted(data_dict_1.items()):
    # создание графика
    ax.set_xlabel('NMAX')
    ax.set_ylabel('time, msec')

    # построение линии
    x, y = data
    ax.plot(x, y, 'o-', color=colors[j], label=experiment_name)
    j += 1

# добавление легенды
ax.plot()
ax.legend()

# Создаем папку "graphs" если её нет
if not os.path.exists('graphs'):
    os.makedirs('graphs')

name = input('Enter name for graph: ')

# Сохраняем график в папке "graphs"
fig.savefig(os.path.join('graphs', name))

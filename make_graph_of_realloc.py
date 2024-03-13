import os
import matplotlib.pyplot as plt

# Путь к папке с данными
data_dir = 'log'

# Файлы с данными
files = sorted(os.listdir(data_dir), key=lambda x: int(x.split('_')[0]))

data_dict = {}  # Данные для первого графика

data = {'gcc': {}, 'musl-gcc': {}, 'diet gcc': {}}

# Проходим по файлам с данными
for file_name in files:
    # Получаем название эксперимента из имени файла
    experiment_name = '_'.join(file_name[:-4].split('_')[1:])

    # Считываем данные из файла
    with open(os.path.join(data_dir, file_name)) as f:

        lib = experiment_name.split('_')[-1]
        experiment_name = experiment_name.split('_')[0]
        data_dict = data[lib]
        match experiment_name:
            case 'c':
                experiment_name = 'count'
            case 'r':
                experiment_name = 'realloc №1 (*2)'
            case 'w':
                experiment_name = 'realloc №2 (+1)'
            case 'fr':
                experiment_name = 'realloc №1 (*2) with fragmentation'
            case 'fw':
                experiment_name = 'realloc №2 (+1) with fragmentation'

        # Инициализируем начальные данные
        if experiment_name not in data_dict:
            data_dict[experiment_name] = [[], []]

        # Размерность опытного массива
        data_dict[experiment_name][0].append(int(file_name.split('_')[0]))

        reallocates = set()
        for line in f:
            address = line.split(',')[0]
            if 'realloc' in address:
                reallocates.add(address)

        data_dict[experiment_name][1].append(int(len(reallocates)))

colors = ['red', 'green', 'blue', 'black', 'pink']


for lib, data_dict in data.items():
    fig, ax = plt.subplots(figsize=(12, 8))
    j = 0
    for experiment_name, data in sorted(data_dict.items()):
        # создание графика
        ax.set_xlabel('NMAX')
        ax.set_ylabel('time, msec')
        if j == 4:
            continue

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

    # Сохраняем график в папке "graphs"
    fig.savefig(os.path.join('graphs', f'graph_of_reallocates_{lib}'))

import os

data_dir = 'preproc'

files = sorted(os.listdir(data_dir), key=lambda x: int(x.split('_')[0]))

need_more_info_list = list()
rse = float(input('Input max valiable rse: '))

# Перебор файлов
for file_name in files:
    with open(os.path.join(data_dir, file_name)) as f:
        # Чтение файла до строки с информацией о RSE
        while (read_data := f.readline()) and 'RSE' not in read_data:
            pass

        # Проверка значения RSE и добавление файла в список, если значение больше или равно заданному rse
        if 'RSE' in read_data:
            if float(read_data.split()[1]) >= rse:
                need_more_info_list.append(file_name)
        else:
            print('Something go wrong. Check data files\n')

# Вывод списка файлов, требующих дополнительной информации, или сообщение, если таких файлов нет
if need_more_info_list:
    print(*need_more_info_list, sep='\n')
else:
    print('No need update data')

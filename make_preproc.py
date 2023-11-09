import os

input_dir_name = "data"
output_dir_name = "preproc"
for filename in sorted(os.listdir(input_dir_name), ):
    if filename.endswith(".txt"):
        with open(os.path.join(input_dir_name, filename), "r") as file:
            lst = [float(line.strip()) * 10 ** 3 for line in file]

        lst.sort()
        n = len(lst)
        min_num = lst[0]
        max_num = lst[n-1]
        aver = sum(lst) / n
        cvart_down = lst[n // 4]  # Нижняя квартиль
        med = lst[n // 2] if n % 2 == 0 else (lst[n // 2] + lst[n // 2 + 1]) / 2  # Медиана
        cvart_up = lst[3 * n // 4]  # Верхняя квартиль
        disp = 0  # Дисперсия
        for i in lst:
            disp += (i - aver) ** 2
        disp = (disp / (n - 1)) ** 0.5
        stderr = disp / n ** 0.5
        rse = stderr / aver * 100

        with open(os.path.join(output_dir_name, filename), "w") as output_file:
            output_file.write(f"Averange: {aver}\n")
            output_file.write(f"Min: {min_num}\n")
            output_file.write(f"Cvart_down: {cvart_down}\n")
            output_file.write(f"Median: {med}\n")
            output_file.write(f"Cvart_up: {cvart_up}\n")
            output_file.write(f"Max: {max_num}\n")
            output_file.write(f"Disp: {disp}\n")
            output_file.write(f"Stderr: {stderr}\n")
            output_file.write(f"RSE: {rse}\n")


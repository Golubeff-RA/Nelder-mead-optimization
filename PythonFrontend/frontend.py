import gradio as gr
import subprocess
import matplotlib.pyplot as plt
import os
import re

def optimize(iterations, tolerance, function, point, log_file_path="opt.log"):
    """
    Вызывает бинарный файл с аргументами, строит графики из лог-файла.

    Args:
        iterations: Число итераций.
        tolerance: Погрешность.
        function: Функция (строка).
        point: Координаты начальной точки (строка, разделенные запятыми).
        log_file_path: Путь к файлу логов.

    Returns:
        Tuple: Путь к графику функции, путь к графику объема.
    """

    try:
        point_coords = [float(coord.strip()) for coord in point.split(',')]
        point_string = ' '.join(map(str, point_coords))
    except ValueError:
        print("Ошибка: Некорректный формат координат.")
        return "Error", "Error", "Error", "Error"

    binary_path = "build/NelderMeadSolver/NelderMeadSolver"

    command = [
        binary_path,
        str(iterations),
        str(tolerance),
        function,
        log_file_path,
        point_string,
    ]

    try:
        subprocess.run(command, capture_output=True, text=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при запуске: {e.stderr}")
        return "Error", "Error", "Ошибка при запуске скрипта", "Error"
    except FileNotFoundError:
        print(f"Ошибка: Бинарный файл не найден по пути {binary_path}")
        return "Error", "Error", "Файл скрипта найден по пути", "Error"

    function_values = []
    volumes = []
    min_q_x = None
    argmin = None

    try:
        with open(log_file_path, 'r') as f:
            for line in f:
                last_line = line
                match = re.match(r"([-\d\.]+)\s+([\d\.]+)\s+\{\(([\d., -]+)\).*?\}.*", line)
                if match:
                    function_value = float(match.group(1)) 
                    volume = float(match.group(2))
                    function_values.append(function_value)
                    volumes.append(volume)
            if last_line:
                match = re.match(r"([-\d\.]+)\s+([\d\.]+)\s+\{\(([\d., -]+)\).*?\}.*", last_line)
                if match:
                    min_q_x = float(match.group(1))
                    argmin = match.group(3)

    except FileNotFoundError:
        print("Ошибка: Файл логов не найден.")
        return "Error", "Error", "Файл логов не найден", "Error"
    except ValueError:
        print("Ошибка: Некорректный формат данных в файле логов.")
        return "Error", "Error", "Некорректный формат данных в файле логов", "Error"

    fig_function, ax_function = plt.subplots()
    ax_function.plot(function_values)
    ax_function.set_xlabel("Итерация")
    ax_function.set_ylabel("Q(X)")
    ax_function.set_title("Изменение Q(X)")
    ax_function.grid(True)
    function_plot_path = "function_plot.png"
    fig_function.savefig(function_plot_path)
    plt.close(fig_function)

    fig_volume, ax_volume = plt.subplots()
    ax_volume.plot(volumes)
    ax_volume.set_xlabel("Итерация")
    ax_volume.set_ylabel("Объем")
    ax_volume.set_title("Изменение меры")
    ax_volume.grid(True)
    volume_plot_path = "volume_plot.png"
    fig_volume.savefig(volume_plot_path)
    plt.close(fig_volume)

    return function_plot_path, volume_plot_path, str(min_q_x), str(argmin)


if __name__ == "__main__":
    with gr.Blocks() as iface:
        function_input = gr.Textbox(lines=1, label="Функция", placeholder="Введите функцию (например, x^2 + y^2)")
        iterations_input = gr.Number(label="Число итераций", value=100)
        tolerance_input = gr.Number(label="Погрешность", value=0.001)
        point_input = gr.Textbox(lines=1, label="Координаты начальной точки (через запятую)", placeholder="Например, 1.0, 2.5, -0.3")
        #log_file_path_input = gr.Textbox(label="Путь к файлу логов", value="optimization.log")
        optimize_button = gr.Button("Оптимизировать")

        min_q_x = gr.Textbox(label="Min Q(X)")
        point_c = gr.Textbox(label="argmin(Q(X))")
        function_plot_output = gr.Image(label="График значения функции")
        volume_plot_output = gr.Image(label="График меры")
        

        optimize_button.click(
            fn=optimize,
            inputs=[iterations_input, tolerance_input, function_input, point_input],
            outputs=[function_plot_output, volume_plot_output, min_q_x, point_c],
        )

    iface.launch(share=True)

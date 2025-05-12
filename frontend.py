import sys
import subprocess
import re
import matplotlib.pyplot as plt
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QLineEdit, QPushButton, QSpinBox, QDoubleSpinBox,
    QFileDialog, QMessageBox
)
from PyQt5.QtGui import QPixmap
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas


class NelderMeadOptimizerApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Nelder-Mead Optimizer (Desktop App)")
        self.setGeometry(100, 100, 900, 600)

        # Главный виджет и layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QHBoxLayout(central_widget)

        # Левая панель (ввод параметров)
        left_panel = QWidget()
        left_layout = QVBoxLayout(left_panel)

        # Поля ввода
        self.function_input = QLineEdit(placeholderText="x1**2 + x2**2")
        self.iterations_input = QSpinBox()
        self.iterations_input.setRange(1, 10000)
        self.iterations_input.setValue(100)
        self.tolerance_input = QDoubleSpinBox()
        self.tolerance_input.setRange(0.00001, 1.0)
        self.tolerance_input.setValue(0.001)
        self.tolerance_input.setDecimals(5)
        self.point_input = QLineEdit(placeholderText="1.0, 2.0")

        # Кнопка оптимизации
        self.optimize_button = QPushButton("Оптимизировать")
        self.optimize_button.clicked.connect(self.run_optimization)

        # Вывод результатов
        self.min_q_label = QLabel("Min Q(X):")
        self.min_q_value = QLineEdit()
        self.min_q_value.setReadOnly(True)
        self.argmin_label = QLabel("argmin(Q(X)):")
        self.argmin_value = QLineEdit()
        self.argmin_value.setReadOnly(True)

        # Добавление элементов в левую панель
        left_layout.addWidget(QLabel("Функция:"))
        left_layout.addWidget(self.function_input)
        left_layout.addWidget(QLabel("Число итераций:"))
        left_layout.addWidget(self.iterations_input)
        left_layout.addWidget(QLabel("Погрешность:"))
        left_layout.addWidget(self.tolerance_input)
        left_layout.addWidget(QLabel("Начальная точка (через запятую):"))
        left_layout.addWidget(self.point_input)
        left_layout.addWidget(self.optimize_button)
        left_layout.addWidget(self.min_q_label)
        left_layout.addWidget(self.min_q_value)
        left_layout.addWidget(self.argmin_label)
        left_layout.addWidget(self.argmin_value)
        left_layout.addStretch()

        # Правая панель (графики)
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)

        # График функции
        self.function_plot_label = QLabel("График Q(X)")
        self.function_plot_canvas = FigureCanvas(plt.figure())
        right_layout.addWidget(self.function_plot_label)
        right_layout.addWidget(self.function_plot_canvas)

        # График объема
        self.volume_plot_label = QLabel("График меры")
        self.volume_plot_canvas = FigureCanvas(plt.figure())
        right_layout.addWidget(self.volume_plot_label)
        right_layout.addWidget(self.volume_plot_canvas)

        # Объединение левой и правой панелей
        main_layout.addWidget(left_panel, stretch=1)
        main_layout.addWidget(right_panel, stretch=2)

    def run_optimization(self):
        """Запускает оптимизацию и отображает результаты."""
        function = self.function_input.text()
        iterations = self.iterations_input.value()
        tolerance = self.tolerance_input.value()
        point = self.point_input.text()
        log_file_path = "opt.log"

        try:
            point_coords = [float(coord.strip()) for coord in point.split(',')]
            point_string = ' '.join(map(str, point_coords))
        except ValueError:
            QMessageBox.critical(self, "Ошибка", "Некорректный формат координат!")
            return

        binary_path = "build/NelderMeadSolver/NelderMeadSolver.exe"

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
            QMessageBox.critical(self, "Ошибка", f"Ошибка при запуске:\n{e.stderr}")
            return
        except FileNotFoundError:
            QMessageBox.critical(self, "Ошибка", f"Бинарный файл не найден:\n{binary_path}")
            return

        # Чтение логов и построение графиков
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
                        function_values.append(float(match.group(1)))
                        volumes.append(float(match.group(2)))
                if last_line:
                    match = re.match(r"([-\d\.]+)\s+([\d\.]+)\s+\{\(([\d., -]+)\).*?\}.*", last_line)
                    if match:
                        min_q_x = float(match.group(1))
                        argmin = match.group(3)
        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Ошибка при чтении логов:\n{str(e)}")
            return

        # Обновление графиков
        self.update_plot(self.function_plot_canvas, function_values, "Q(X)", "Итерация", "Q(X)")
        self.update_plot(self.volume_plot_canvas, volumes, "Мера симплекса", "Итерация", "Объем")

        # Вывод результатов
        self.min_q_value.setText(str(min_q_x))
        self.argmin_value.setText(str(argmin))

    def update_plot(self, canvas, data, title, xlabel, ylabel):
        """Обновляет график на указанном canvas."""
        canvas.figure.clear()
        ax = canvas.figure.add_subplot(111)
        ax.plot(data)
        ax.set_title(title)
        ax.set_xlabel(xlabel)
        ax.set_ylabel(ylabel)
        ax.grid(True)
        canvas.draw()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = NelderMeadOptimizerApp()
    window.show()
    sys.exit(app.exec_())
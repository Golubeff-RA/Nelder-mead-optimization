# Nelder-mead-optimization
Приложение на Qt оптимизирующее функцию эвристикой Нелдера-Мида
Пишем только под винду, чтобы не парится с Cmake и подключением библиотеков в конфигах
# Наброски архитектуры:
# Front: 
  - Вверху окошка строчка в которую можно напечатать функцию Q(X).
  - Кнопка проверки правильности введённой функции или форматирует строку согласно правилам записи функции.
  - Кнопка запуска оптимизатора, выдающая введенную строку std::string в оптимизатор.
  - Окошко для печати логов, которые будут выданы ядром в виде std::vector(Log) или std::list(Log) (вектор структур логов, в которых будут координаты опорных точек, значение Q(X), мера опорного симплекса 
  (площадь, объём, 4-х мерный объём и т. д.).
  - В самом низу выделенное строковое окно для финального ответа Q(X*) и сам X*.
# Ярдо: 
  - Оформлено в виде подключаемой dll, чтобы просто заинклюдить его в Qt приложуху.
  - Содержит определение класса NelderMeadSolver.
# NelderMeadSolver:
  Поля класса: 
  - std::map(std::string, std::list(Log)) solution_logs // содержит ход решения для каждой оптимизированной функции
  - std::map(double, std::vector(Point)) landscape // содержит соответствие Q(X) и X
  

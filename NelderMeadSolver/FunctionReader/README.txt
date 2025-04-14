 ///
 класс Function высчитывает значение функции с неизвестными xi
 обрабатывает операции: '+', '-', '*', '/', '^'
 нормальных тестов пока нет
 
 //scr/main
 g++ -fpic -shared -o libfun.so src/Function.cpp -Iinclude
 g++ -o main -Iinclude src/StringDecode.cpp -lfun -L. -Wl,-rpath="./"
 ./main


 //test/main
 g++ -fpic -shared -o libfun.so src/Function.cpp -Iinclude
 g++ tests/main.cpp -lgtest -lpthread -Iinclude -lfun -L. -Wl,-rpath="./"
 ./a.out 


 //test 
 mkdir my-build; cd my-build; rm * ;cmake ../; make; ./my_test; 
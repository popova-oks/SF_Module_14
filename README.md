# SF_Module_14
## автодополнение введенного слова по изначально заданному словарю
**Учебный проект**

*Программа производит автодополнение слова, вставку и удаление слова*
*в словарь на основе префиксного дерева*
*Слова для словаря хранятся в json файле*

Для работы необходимо:
1. Ввести слово или его префикс
2. Нажать Enter
3. Выбрать действие
4. После выполнения действия распечатывается сохраненный текст и можно заново ввести другое слово

### Структура программы
*для работы программы необходимо подключить библиотеку https://github.com/nlohmann/json*
*для работы с файлами json.*
*При работе в VS Code путь к библиотеке прописывается в файлах: c_cpp_properties.json и tasks.json*

*В функции void clientCode выбирается действие:*
 - quit - выход из программы
 - find a word in the dictionary by prefix - найти слово по префиксу
 - add to dictionary - добавить слово в словарь (при его отсутствии) 
- remove from the dictionary - удалить слово из словаря

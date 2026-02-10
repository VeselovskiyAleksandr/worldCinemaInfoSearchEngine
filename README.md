#worldCinemaInfoSearchEngine                                                                                                                                                                                           
worldCinemaInfoSearchEngine - поисковый движок, который отыскивает документы по ключевым словам, вводимым пользователем.                                                                                               
Для сборки проекта необходима версия cMake 3.8 и выше.                                                                                                                                                                 
Поисковый движок использует стандарт С++ 17.                                                                                                                                                                           
Версия и перечень документов находятся в файле config.JSON .                                                                                                                                                           
Перечень параметров, с которыми работает программа, находятся в файле Configuration.h .                                                                                                                                
Содержания документов находятся в папке resources.                                                                                                                                                                     
Запросы от пользователей хранятся в файле requests.JSON .                                                                                                                                                              
Ответы на запросы поступают в файл answers.JSON .                                                                                                                                                                      
Для работы с программой необходимо задать в качестве элемента запуска worldCinemaInfoSearchEngine.cpp .                                                                                                                
Для тестирования необходимо задать в качестве элемента запуска serverTest.cpp .                                                                                                                                        
Для задания файла в качестве элемента запуска необходимо в обозревателе решений найти нужный файл и 
выбрать его как элемент запуска.                                                                                                                                                                                       
При добавлении или изменении документов, каждая строка в документе должна заканчиваться знаком пунктуации или пробелом.

ВНИМАНИЕ!!! Перед запуском необходимо скопировать файлы resources, config.json, answers.json, requests.json из проекта
(представлены на первом снимке) в папку out/build/x64-Debug/worldCinemaInfoSearchEngine (показано на втором снимке).

##Установка
 Клонируйте репозиторий:
   bash
   git clone https://github.com/VeselovskiyAleksandr/worldCinemaInfoSearchEngine.git
   cd worldCinemaInfoSearchEngine
   Создайте директорию для сборки:
   bash
   mkdir build
   cd build
   Запустите CMake:
   bash
   cmake ..
   Соберите проект:
   bash
   cmake --build . 
   Запустите исполняемый файл:
   bash
   ./worldCinemaInfoSearchEngine
#Вклад
Если вы хотите внести свой вклад, пожалуйста, создайте копию репозитория и отправьте пулл-реквест.                                                                                                                    
Расположение файлов в проекте:
<img width="1600" height="900" alt="расположение файлов" src="https://github.com/user-attachments/assets/0eacd714-dd6e-4dca-a455-5cf50b215d0c" />                                                                         
Выделенные файлы необходимо скопировать вуказанное место:
  <img width="1600" height="900" alt="требуемое расположение файлов" src="https://github.com/user-attachments/assets/6ebfd29b-c64b-41c5-b48c-52fbe80d2a79" />







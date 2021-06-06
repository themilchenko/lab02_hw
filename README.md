# ***Laboratory work 2***

`Цель работы`:
лабораторная работа посвещена
изучению систем контроля версий на примере Git.

### Ход выполнения `Tutorial`:

```
$ export GITHUB_USERNAME=themilchenko
$ export GITHUB_EMAIL=ivan.milchenko.92@mail.ru
$ export GITHUB_TOKEN=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
$ alias edit=vim

$ cd ${GITHUB_USERNAME}/workspace
$ source scripts/activate

$ mkdir ~/.config
$ cat > ~/.config/hub <<EOF
github.com:
- user: ${GITHUB_USERNAME}
  oauth_token: ${GITHUB_TOKEN}
  protocol: https
EOF
$ git config --global hub.protocol https

$ mkdir projects/lab02 && cd projects/lab02
$ git init
$ git config --global user.name ${GITHUB_USERNAME}
$ git config --global user.email ${GITHUB_EMAIL}

$ git config -e --global
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab02.git
$ git pull origin master
$ touch README.md
$ git status
$ git add README.md
$ git commit -m"added README.md"
$ git push origin master

$ nano .gignore
$ echo .gitgnore
$ cat > .gitgnore <<EOF
>*build*/
> *install*/
> *.swp
> .idea/
$ git add .
$ git commit -m"added .gitgnore"
$ git push origin master

$ git pull origin master
$ git log

$ mkdir sources
$ mkdir include
$ mkdir examples
$ cat > sources/print.cpp <<EOF
#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
  out << text;
}

void print(const std::string& text, std::ofstream& out)
{
  out << text;
}
EOF

$ cat > include/print.hpp <<EOF
#include <fstream>
#include <iostream>
#include <string>

void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);
EOF

$ cat > examples/example1.cpp <<EOF
#include <print.hpp>

int main(int argc, char** argv)
{
  print("hello");
}
EOF

$ cat > examples/example2.cpp <<EOF
#include <print.hpp>

#include <fstream>

int main(int argc, char** argv)
{
  std::ofstream file("log.txt");
  print(std::string("hello"), file);
}
EOF

$ edit README.md

$ git status
$ git add .
$ git commit -m"added sources"
$ git push origin master

$ cd ~/workspace/
$ export LAB_NUMBER=02
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER}.git tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

### Выполнение ДЗ

> Часть 1

- Создайте пустой репозиторий на сервисе github.com

- Выполните инструкцию по созданию первого коммита на странице репозитория, созданного на предыдещем шаге.
```
$ mkdir projects/lab02_hw
$ cd projects/lab02_hw
$ git init 
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab02_hw.git
$ git pull origin master 
$ touch README.md
$ git add README.md
$ git commit -m"added README.md"
$ git push origin master
```

- Создайте файл hello_world.cpp в локальной копии репозитория (который должен был появиться на шаге 2). Реализуйте программу Hello world на языке C++ используя плохой стиль кода. Например, после заголовочных файлов вставьте строку using namespace std;.
```c++
$ touch hello_world.cpp
$ cat > hello_world.cpp <<EOF
> #include <iostream>
>
> using namespace std;
> 
> int main()
< {
<    cout << "Hello world";
<    return 0;
< }
< EOF
```

- Добавьте этот файл в локальную копию репозитория.

`$ git add .`

- Закоммитьте изменения с осмысленным сообщением.

`$ git commit -m"added hello_world.cpp"`

- Изменитьте исходный код так, чтобы программа через стандартный поток ввода запрашивалось имя пользователя. А в стандартный поток вывода печаталось сообщение Hello world from @name, где @name имя пользователя.
```c++
$ cat > hello_world.cpp <<EOF
> #include <iostream>
> #include <string>
>
> using namespace std;
> 
> int main()
< {
>    string name;
>    cin >> name;   
<    cout << "Hello world from " << name;
<    return 0;
< }
< EOF
```

- Закоммитьте новую версию программы.

`$ git commit -m"changed hello_world.cpp"`

- Запуште изменения в удалёный репозиторий.

`$ git push origin master`


> Часть 2

- В локальной копии репозитория создайте локальную ветку patch1.

`$ git branch patch1`


- Внесите изменения в ветке patch1 по исправлению кода и избавления от using namespace std;

```c++
$ git checkout patch1
$ cat > hello_world.cpp <<EOF
> #include <iostream>
> #include <string>
> 
> using namespace std;
> 
> int main()
> {
>     string name;
>     cin >> name;
>     cout << "Hello world from " << name;
>     return 0;
> }
$ git add .
```

- commit, push локальную ветку в удалённый репозиторий.

```
$ git commit -m"new branch and updated hello_world.cpp"
$ git push origin patch1
```

- Проверьте, что ветка patch1 доступна в удалёный репозитории.

- Создайте pull-request patch1 -> master.

- В локальной копии в ветке patch1 добавьте в исходный код комментарии.

```c++
$ cat > hello_world.cpp <<EOF
> #include <iostream>
> #include <string>
> 
> int main()
> {
>     std::string name; // имя пользователя
>     std::getline(std::cin, name); // ввод имени с клавиатуры
>     std::cout << "Hello world from " << name << std::endl; // вывод имени на экран
>     return 0;
> }
```
- commit, push.
```
$git commit -am"added comments"
$git push origin patch1
```
- Проверьте, что новые изменения есть в созданном на шаге 5 pull-request

- В удалённый репозитории выполните слияние PR patch1 -> master и удалите ветку patch1 в удаленном репозитории.
```c++
$ git pull
$ git log
```

- Локально выполните pull.

`git pull origin master`

- С помощью команды git log просмотрите историю в локальной версии ветки master

- Удалите локальную ветку patch1.

> Часть 3

- Создайте новую локальную ветку patch2.
```
$ git branch patch2
$ git checkout patch2
```
- Измените code style с помощью утилиты clang-format. Например, используя опцию -style=Mozilla.

`clang-format --style=Mozilla hello_world.cpp`

- commit, push, создайте pull-request patch2 -> master.

```
$ git commit -am"clang-format"
$ git push origin master 
```

- В ветке master в удаленном репозитории измените комментарии, например, расставьте знаки препинания, переведите комментарии на другой язык.

- Убедитесь, что в pull-request появились конфликтны.

- Для этого локально выполните pull + rebase (точную последовательность команд, следует узнать самостоятельно). Исправьте конфликты.

```c++
$ git pull origin master
$ git rebase master
```

- Сделайте force push в ветку patch2

``` 
git push -f origin patch2 
```

- Убедитель, что в pull-request пропали конфликтны.

- Вмержите pull-request patch2 -> master.

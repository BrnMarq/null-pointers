# 📌 Null Pointers

**Null pointers** is a terminal task manager, that would help you improve the efficiency in which you assign tasks to each of the members of your team.

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## 📦 Requirements

- g++ compiler
- C++ 20
- make

## 📂 File structure

```
null-pointers/
├── lib/               # Source code
├── main/
  ├── src/main.cpp
  └── bin/main             # The program itself, the one that is going to handle the commands
├── resources/
  ├── graph/              # It contains a .png file with the representation of the match
├── tests/
  ├── src/test.cpp
  └── bin/test              # A executable that fills the project with fixed data
├── .gitignore
├── LICENSE
├── Makefile
├── README.md
```

## 🛠️ How to install

```bash
git clone https://github.com/BrnMarq/null-pointers.git
cd null-pointers
make
```

By now, we suggest you to configure an alias in your terminal configurations like this

```bash
cp ./main/bin/main np
export PATH=$PATH:path_to_np_file
```

This will allow you to execute the program just using the command **np**

## 🏁 Basic usage

By now there are a few commands defined, which are:

- init
- agents
- tasks
- add_agent
- add_task
- match

With these commands you will be able to perform task matching properly. For example

```bash
np init
np add_agent
```

This should prompt you some information in order to save the agent

## ✔ Tests

We provided for you 2 tests. In order to use them, you can use the following commands:

```bash
./test/bin/test test1

or

./test/bin/test test2
```

depending on which one you want to use.

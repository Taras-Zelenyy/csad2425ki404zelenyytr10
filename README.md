## Repository Details

This repository is for the **Computer Systems Automated Design** (CSAD) labs. The repository follows the naming convention `csad<YY1YY2><group><student's full name><student's number>`. 

In this case, the repository name would be structured as: `csad2425ki404zelenyytr07`

Main development branch: **develop**

## Task Details

1. Create a simple communication schema SW(client) <-> UART <-> HW(server).
2. The client should send a message to the server. The server should modify the message and send it back to the client.
3. Create YML file with next features: 
   a. build all binaries (create scripts in folder ci/ if need);
   c. create artifacts;

## Student Details and details from Table 1

| **Student Number** | **Student Name**            | **Group** | **Game**            | **Config format** |
|--------------------|-----------------------------|-----------|---------------------|-------------------|
| 07                 | Zelenyy Taras Romanovych    | KI-404    | tik-tac-toe 3x3     | XML               |


## Technologies, Programming Language, and Hardware

For the upcoming tasks, the following languages, and hardware will be used:

- **Programming Language**: C/C++
- **Hardware**: Arduino Nano
- **Enviroment**: 
   - VS code: To write and upload the logic code to the Arduino Uno, using C++ for low-level control.
   - Arduino IDE: To write and upload the logic code to the Arduino Uno, using C++ for low-level control.

## How to run project
### Server side
1) Clone repo using next command below:
```
https://github.com/Taras-Zelenyy/csad2425ki404zelenyytr07.git
```
2) Open `git bash`
3) Make checkout to feature/develop/task2. Use next command:
```
git checkout feature/develop/task2
```
4) Find next file usin following path: `your_path\server\server.ino`
5) Open Arduino IDE, choose you port (for me it's COM3), board and upload code

### Client side
1) Open `pull feature/develop/task2`
2) Navigate to `Action` tab
3) Choose last project build
4) Download artifacts
5) Unzip downloaded folder
6) Navigate to `"your_path\build-artifacts\Debug\client.exe"`
7) Double click to `client.exe`

## How it's work

User write message in client console. Server process user input, and return answer.

### Exsample 1
**User input:** `Привіт Arduino!`

**Server answer:** `Привіт User!`

![alt text](media/image.png)

### Exsample 2 (User enter anything else)
**User input:** `Привіт!`

**Server answer:** `Мені не відома така команда`

![alt text](media/image-1.png)
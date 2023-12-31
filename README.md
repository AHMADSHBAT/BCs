# Functional Programming Techniques in C++

This project includes a framework called `DEV` and several demo files that demonstrate its usage. The framework provides functionalities for inter-process communication and string manipulation.

## Building:
After cloning the repo, in the root dir, run the following command on a Linux machine:

```
make
```
Now you should have the framework lib in the root directory.





## Services:
1. IPC:
   1. INET/UNIX Client Socket.
   2. INET/UNIX Server Socket.
   3. Shared Memory Communication.
2. String Functionalities:
   1. Trim
   2. Replace
   3. Tokenize



## Demo Files:
To try out the framework, in the root directory, run:

```
./buildDemo.sh
```

The binaries are located in demoBuild folder in the root directory.

### IPC Server & Client Sockets demo running:
```
cd demoBuild

./ServerInetDemo
./ClientInetDemo

./ServerUnixDemo
./ClientUnixtDemo

```

### IPC Shared Memory demo running:
```
cd demoBuild
./ShareMemDemo
```


### IPC String func demo running:
```
cd demoBuild
./StringDemo
```

Project README
This project includes a framework called libmyframework.a and several demo files that demonstrate its usage. The framework provides functionalities for inter-process communication and string manipulation.

Compilation
To compile the framework, execute the following command:


make
This command will build the libmyframework.a library file.

To compile the demo files and link them with the framework, run the buildDemos.sh script:


./buildDemos.sh
This script will compile the demo files and generate executables in the demoBuild directory.

Running the Demos
Once the demos are compiled, you can run them using the following commands:

IPCClientDemo:


./demoBuild/IPCClientDemo
IPCServerDemo:


./demoBuild/IPCServerDemo
StringDemo:


./demoBuild/StringDemo
IPCShreMemDemo:


./demoBuild/IPCShreMemDemo
Execute each command to run the respective demo and observe the functionality provided by the framework.

Make sure to compile the framework and demos before running the executables to ensure all dependencies are correctly linked.



Contact
For any questions or inquiries, please contact ahmad.shbat93@e-uvt.ro.

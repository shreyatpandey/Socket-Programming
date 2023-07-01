# Objective of this Project:-
  In this project, I have performed a model of computational offloading where a single client offloads Taylor Series for Logarithm and Divison function to server which in turn distributes it over the 3 backend server. Basically, my whole project can be divided into 2 parts, i.e input phase and the output phase. In the input phase,the input would be given from the client which would consist of function and a value. That will be transmitted to my aws program through TCP connection. Further, the backend server would receive the value through the UDP connection.The 3 servers are dedicated to an individual task,i.e,serverA would calulate the power 2 value, serverB would calculate the power 4 value while server C would calculate the power 5 value. In the output phase, aws would collect power of x. Power 2 and power 4 value would be given from serverA, while power 3 and power 6 would be obtained froms serverB and power 5 value would be resulted from serverC. Then, the main server,i.e.aws would either calculate Logarithm or Division function value depending upon the input function by the user. The final value obtained from this calculation would then be transmitted through TCP connection to the client side. 
The problem statement of the given project has laid a definite guidelines for me to execute the project. I have done my project along these lines. The  ouput format as well as the input format for the project has been followed by me.

# Source Files:-
  In total I have 5 files, i.e:-
 (i) client.c:- In this the user would take in the input which consist of function and a value through the command line and send it to the aws through the TCP connection
 (ii) aws.c:- It is the main server which would receive the input function and a value from the client side. The value would be extracted from the buffer and passed it to the backend server i.e,serveA,serverB and serverC. It will then receive the power of the input value,i.e,2,4,5,6. On the other hand in the function part, my aws.c program would check whether the input string is a logarithm or divion fucntion. Accordingly, it wil calculate its value, as per the formula stated in the problem statement.
 (iii)serverA.c:- This code is specifically dedicated to the calculation of the square value of the input. Once the value is received from the aws, it would performs its calculation and return the square as well the fourth power value to the aws. It is important to note that for fourth power value,serverA would be called twice in aws.
  (iv) serverB.c:- This code is specifically dedicated to the calculation of the cube value of the input. Once the value is received from the aws, it would performs its calculation and return the cube as well the sixth power value to the aws. It is important to note that for sixth value,serverB would be called twice in aws.
 (v) serverC.c:- This code is specifically dedicated to the calculation of the fifth power value of the input. Once the value is received from the aws, it would performs its calculation and return the fifth power value to the aws.

# Format of all messages exchanged:-
1.client:- The client is up and running
          The client sent <0.25> and <LOG> to AWS
          According to AWS<LOG> on <0.25>:-0.28767090

2.serverA:- The serverA is up and running using UDP on port<21882>
            The serverA received the input<0.25>
            The server A calculated square <0.0625>
           The server A finished sending the output to AWS
           The Server A received the input <0.0625000000>
           The server A calculated square <0.00390625>
           The server A finished sending the output to AWS

  3.serverB:- 
    The Server B is up and running using UDP on port <22882>
    The Server B received the input <0.25>
    The server B calculated cube: <0.015625>
    The server B finished sending the output to AWS
    The Server B received the input <0.0625000000>
    The server B calculated cube: <0.000244141>
    The server B finished sending the output to AWS

  4.serverC:- 
    The Server C is up and running using UDP on port <23882>
    The Server C received the input <0.25>
    The server C calculated 5th power: <0.000976562>
    The server C finished sending the output to AWS

  5. AWS:-
    The AWS is up and running
    The AWS received <0.25> and function <log> from the client using TCP over port <25882>
    The AWS sent <0.25> to Backend-Server A
    The AWS received <0.0625> Backend-Server A using the UDP over port <21882>
    The AWS received <0.00390625> Backend-Server A using the UDP over port <21882>
    The AWS sent <0.25> to Backend-Server B
    The AWS received <0.015625> Backend-Server B using the UDP over port <22882>
    The AWS received <0.000244141> Backend-Server B using the UDP over port <22882>
    The AWS sent <0.25> to Backend-Server C

  The AWS received <0.015625> Backend-Server C using the UDP over port <23882>
  Values of power received by AWS:[0.25,0.0625,0.015625,0.00390625,0.000976562,0.000244141]
  AWS calculated <log> on <0.25> : <-0.287671>

# Any idiosyncrasy of the project:-
Firstly, my project has certain limitation on the value. If the value of the input becomes as low as 0.008(example), then the sixth power value obtained on the input would be displayed as 0.00000 on the aws screen.
Secondly, there does exist an offset in rounding of the digits from the 4th decimal point. On this, it differs a a little from the value obtained from the calculator. 
Third, when the user gives continous value ,i.e in the 1st instance user gives log 0.25, the output obtained would match the calculation. However, in the successive round, ie. user gives Div 0.85, there is slight deviation of the value that I have obtained. It could be due to the precision point accuracy of the float value.
Apart, from the header files that are enlisted in the socket programming project, I have also include #include<math.h>, this is used to use the function pow().To execute this, I have included -lm in gcc -o serverA serverA.c -lm. This has been listed in the Makefile
Also, I have implemented fork() that is concurrent process. But I have obtained help regarding this from the reference that I have enlisted below.

# Resources used in this project:-
  Socket programming in C, was a good challenge for me.I took help from the following books and site.
  (a) Book:- Beej Reference guide
  (b) Web-site:-
    www.linuxhowtos.org/C_C++/socket.html :- From this, I got help for UDP socket as well as fork() process






 

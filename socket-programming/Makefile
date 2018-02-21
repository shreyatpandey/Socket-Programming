all: client_compile aws_compile serverA_compile serverB_compile serverC_compile 



client_compile: client.c 
	gcc -o client client.c

aws_compile: aws.o
	gcc -o awsproj aws.c

serverA_compile: serverA.o
	gcc -o serverAproj serverA.c -lm

serverB_compile: serverB.o 
	gcc -o serverBproj serverB.c -lm

serverC_compile: serverC.o 
	gcc -o serverCproj serverC.c -lm

serverA: 
	./serverAproj
serverB: 
	./serverBproj

serverC: 
	./serverCproj

aws: 
	./awsproj 

clean:
	rm -rf *o myprog

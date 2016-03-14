#include <stdio.h>

const int BUF_SIZE = 1024;

int main(){
	char buf[BUF_SIZE];
	int recived;
	while ((recived = read(0, buf, BUF_SIZE)) != 0) 
	{
			
		int sended = 0;
		while (sended < recived) 
		{
			int c = write(1, buf + sended, recived - sended);
		
			sended += c;
		}	
	} 
	return 0;
}

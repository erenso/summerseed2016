#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>


int main(int argc, char *argv[])
{  
    
	char mesaj[1000];
	char nick[50];
	char okunan[50];
	char ip[13];
	char gonder[1024];
	FILE *dosya;

	while(1)
	{
		fflush(stdin);
		strcpy(mesaj,"");
		strcpy(nick,"");
		printf("Mesaj : ");
		gets(mesaj);
		fflush(stdin);
		printf("Kime : ");
		gets(nick);
		int bulundu=0;
		dosya=fopen("kisiler.txt","r");
		if(dosya!=NULL)
		{

			while(!feof(dosya))
			{
				fscanf(dosya,"%s\n",okunan);
				if(strstr(okunan,nick)!=NULL)
				{
					

					for (int i = 0; i < 11; ++i)
					{
						ip[i]=okunan[i];
					}

					ip[11]='\0';
					strcpy(gonder,"");
					strcat(gonder,"./send ");
					strcat(gonder,ip);
					strcat(gonder," 10002 seyfullah,");
					strcat(gonder,mesaj);
					strcat(gonder,"/t");
					printf("okunan=%s\n",gonder);
					system(gonder);

					bulundu=1;

				}
			}

		}
		else
		{
			break;
		}
		if(bulundu==0)
		{
			printf("nick bulunamadı ...\n");
		}
		strcpy(ip,"");
		strcpy(gonder,"");
		bulundu=0;
		printf("------------------------------------------------\n" );
		fclose(dosya);
	}



}



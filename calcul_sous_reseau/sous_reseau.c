#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct chiffre
{
    int un;
    int deux;
    int trois;
    int quatre;
    int masque;
};
typedef struct chiffre chiffre;

int *detect_reseau_bit(char *ip)
{
    chiffre ipv4;
	int i;
	int *reseau_bit;
	reseau_bit=(int *)malloc(32*sizeof(int));

    if(sscanf(ip, "%d.%d.%d.%d/%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre, &ipv4.masque)==5)
        {
			for (i=0; i<ipv4.masque; i++)
				{
					reseau_bit[i]=1;
				}
			for (i=ipv4.masque; i<32; i++)
				reseau_bit[i]=0;
		}
	printf("\n");
	return(reseau_bit);
}
int *binaire(char *ip)
{
	int ipv4[5];
	int i, j, k=0;
	int **octet;
	int *binary_ip;
	binary_ip=(int *)malloc(32*sizeof(int));
	octet=(int **)malloc(4*sizeof(int));
		for(i=0; i<8; i++)
			{
				octet[i]=(int *)malloc(8*sizeof(int));
			}
	if(sscanf(ip, "%d.%d.%d.%d/%d", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3], &ipv4[4])==5)
		{
			for(j=0; j<4; j++)
				{
					int a=ipv4[j], b=ipv4[j];
					for(i=7; i>-1; i--)
						{
							b=a%2;
							a=a/2;
							octet[j][i]=b;
						}
				}
			for(j=0; j<4; j++)
				{
					for (i=0; i<8; i++)
						{
							binary_ip[k]=octet[j][i];
							k++;
						}
				}
		}
	return (binary_ip);
}
int *addresse_reseau(int *masque, int *ip)
{
	int *reseau_ip;
	int i=0;
	reseau_ip=(int *)malloc(32*sizeof(int));
	for (i=0; i<32; i++)
		{
			if(masque[i]==1 && ip[i]==1)
				{
					reseau_ip[i]=1;
				}
			else
				reseau_ip[i]=0;
		}
	return(reseau_ip);
}
int *detect_reseau_bit_inverse(char *ip)
{
    chiffre ipv4;
	int i;
	int *reseau_bit;
	reseau_bit=(int *)malloc(32*sizeof(int));

    if(sscanf(ip, "%d.%d.%d.%d/%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre, &ipv4.masque)==5)
        {
			for (i=0; i<ipv4.masque; i++)
				{
					reseau_bit[i]=0;
				}
			for (i=ipv4.masque; i<32; i++)
				reseau_bit[i]=1;
		}
	printf("\n");
	return(reseau_bit);
}
int *addresse_broadcast(int *masque, int *ip)
{
	int *reseau_ip;
	reseau_ip=(int *)malloc(32*sizeof(int));
	int i=0;
	for (i=0; i<32; i++)
		{
			if(masque[i]==0 && ip[i]==0)
				reseau_ip[i]=0;
			else
				reseau_ip[i]=1;
		}
	return(reseau_ip);
}
void print_bin(int *binary_ip)
{
	int i;
	for (i=0; i<32; i++)
		{
			if(i%8==0 && 0<i)
				printf(".");
			printf("%d",binary_ip[i]);
		}
	printf("\n");
}
void print_dec(int *dec_ip)
{
	int i;
	for (i=0; i<4; i++)
		{
			printf("%d",dec_ip[i]);
			if(i!=3)
				printf(".");
			else
				printf("\n");
		}
}
int *decimal(int *ip)
{
	int i=0, k=7, somme=0;
	int* sortie;
	sortie=(int *)malloc(4*sizeof(int));
	for (i=0; i<8; i++)
		{
			ip[i]=ip[i]*pow(2, k);
			somme+=ip[i];
			k--;
		}
	sortie[0]=somme;
	somme=0;k=7;
	for (i=8; i<16; i++)
		{
			ip[i]=ip[i]*pow(2, k);
			somme+=ip[i];
			k--;
		}
	sortie[1]=somme;
	somme=0;k=7;
	for (i=16; i<24; i++)
		{
			ip[i]=ip[i]*pow(2, k);
			somme+=ip[i];
			k--;
		}
	sortie[2]=somme;
	somme=0;k=7;
	for (i=24; i<32; i++)
		{
			ip[i]=ip[i]*pow(2, k);
			somme+=ip[i];
			k--;
		}
	sortie[3]=somme;
	return (sortie);
}
int number_of_pc(char *ip)
{
	chiffre ipv4;
	if(sscanf(ip, "%d.%d.%d.%d/%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre, &ipv4.masque)==5)
        {
			return (pow(2, (32-ipv4.masque))-2);
		}
	return 0;
}

int nbre_de_decoupe()
{
	int decoupe;
	printf("Entrer le nombre de decoupe:");
	scanf("%d", &decoupe);
	return(decoupe);
}
void new_mask(char *ip)
{
	chiffre ipv4;
	int *tmp;
	int fix, i=0, j;
	if(sscanf(ip, "%d.%d.%d.%d/%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre, &ipv4.masque)==5)
        {
			tmp=decimal(addresse_reseau(detect_reseau_bit(ip), binaire(ip)));
			fix=nbre_de_decoupe();
			ipv4.masque+=fix;
			sprintf(ip,"%d.%d.%d.%d/%d", tmp[0], tmp[1], tmp[2], tmp[3], ipv4.masque);
			printf("nouveau masque:");
			print_dec(decimal(detect_reseau_bit(ip)));
			printf("\nVoici les sous reseau et leurs adresse reseau et broadcast:\n\n");
			printf("*-l'addresse reseau -----------------------------------------------l'adresse de broadcast-*\n");
			for(i=0; i<pow(2, fix); i++)
				{
					printf("|\t@R%d=%d.%d.%d.%d\t\t\t", i+1, tmp[0], tmp[1], tmp[2], tmp[3]);
					tmp[3] += (number_of_pc(ip)+1);
					for (j=3; j>0; j--)
						{
							if(tmp[j]>=256)
								{
									tmp[j-1]+=(tmp[j]/256);
									tmp[j]=tmp[j]%256;
								}
						}
					printf("\t\t\t@B%d=%d.%d.%d.%d\n", i+1, tmp[0], tmp[1], tmp[2],tmp[3]);
					printf("*-----------------------------------------------------------------------------------------*\n");
					tmp[3]++;
					for (j=3; j>0; j--)
						{
							if(tmp[j]>=256)
								{
									tmp[j-1]+=(tmp[j]/256);
									tmp[j]=tmp[j]%256;
								}
						}		
				}		
		}
	}

void exo2()
{	
	char ip[255];
	char masque_ip[255];
	chiffre ipv4;
	label:
	printf("Entrer un addresse ip:");
	scanf("%s", ip);
	if((sscanf(ip, "%d.%d.%d.%d/%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre, &ipv4.masque)==5) && (0<ipv4.un && ipv4.un<224) && (0<ipv4.masque && ipv4.masque<33))
        {
			////print number of machine
			printf("le nombre de pc pouvant se connecter est:%d\n", number_of_pc(ip));

			////print binary ip
			printf("adresse ip en binaire:");
			print_bin(binaire(ip));

			////print addresse reseau
			printf("l'addresse reseau est :");
			print_dec(decimal(addresse_reseau(detect_reseau_bit(ip), binaire(ip))));
			
			////print addresse broadcast
			printf("l'addresse broadcast est :");
			print_dec(decimal(addresse_broadcast(detect_reseau_bit_inverse(ip), binaire(ip))));
			new_mask(ip);
		}
	else
		goto label;

}

/// 
int *binaire_exo1(char *ip)
{
	int ipv4[4];
	int i, j, k=0;
	int **octet;
	int *binary_ip;
	binary_ip=(int *)malloc(32*sizeof(int));
	octet=(int **)malloc(4*sizeof(int));
		for(i=0; i<8; i++)
			{
				octet[i]=(int *)malloc(8*sizeof(int));
			}
	if(sscanf(ip, "%d.%d.%d.%d", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3])==4)
		{
			for(j=0; j<4; j++)
				{
					int a=ipv4[j], b=ipv4[j];
					for(i=7; i>-1; i--)
						{
							b=a%2;
							a=a/2;
							octet[j][i]=b;
						}
				}
			for(j=0; j<4; j++)
				{
					for (i=0; i<8; i++)
						{
							binary_ip[k]=octet[j][i];
							k++;
						}
				}
		}
	return (binary_ip);
}
int *bit_inverse(int *ip)
{
	int i;
	int *reseau_bit;
	reseau_bit=(int *)malloc(32*sizeof(int));
	for (i=0; i<32; i++)
		{
			if(ip[i]==0)
				reseau_bit[i]=1;
			if(ip[i]==1)
				reseau_bit[i]=0;
		}
	printf("\n");
	return(reseau_bit);
}
void exo1()
{
    chiffre ipv4;
	char ip[255];
	char masque_ip[255];
	label:
	printf("Entrer un addresse ip:");
	scanf("%s", ip);
	printf("Entrer un masque:");
	scanf("%s", masque_ip);
    if(sscanf(ip, "%d.%d.%d.%d", &ipv4.un, &ipv4.deux, &ipv4.trois, &ipv4.quatre)==4)
        {
            if (0<=ipv4.un && ipv4.un<224)
				{
					printf("l'adresse reseau:");
					print_dec(decimal(addresse_reseau(binaire_exo1(ip), binaire_exo1(masque_ip))));
					printf("l'adresse de broadcast:");
					print_dec(decimal(addresse_broadcast(binaire_exo1(ip), bit_inverse(binaire_exo1(masque_ip)))));
				}
			 else 
					{
						goto label;
					}
        }
    else 
		{
			goto label;
		}
		
}
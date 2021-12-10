/**************************************************************************/
/***			Projekt 1 - Praca s textem								***/
/***																	***/
/***			     Matus Vrablik										***/
/***																	***/
/***			    13.November 2019									***/
/**************************************************************************/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
void eoln_check(char str[101])	//funkcia zarovnava riadky nad 100 znakov
{
	int length=strlen(str)-1;
	while(str[length]!='\n')	//ak 101. znak nieje znak noveho riadku 
		if (str[length]==EOF)	// a ak nieje ani EOF tak nacita dalsi znak na 101. poziciu 
			str[length]='\n'; //danej premennej typu string az kym nenajde enter alebo znak EOF ktory
		else str[length]=fgetc(stdin); //nahradi znakom noveho riadku a skonci
}

void print_contact(char part1[101],char part2[101],char result[203])
{					//funkcia kopiruje obsah premenej part1 do result
	result[0]='\0';				//nahradza znak noveho riadku z part1 znakom ',' pridava medzeru
	strcpy(result,part1);			//do premenej result a nakoniec zluci premennu result a part2 
	result[strlen(result)-1]=(int)',';	//vysledkom je premenna result ktoru funkcia vypise
	strcat(result," ");
	strcat(result,part2);
	fprintf(stdout,"%s",result);
}

bool isnum(char *arg)
{					//funkcia zisti ci je cely argument cislo
	bool result=true;		//postupne porovna kazdy znak pomocou funkcie isdigit() z kniznice
	for (unsigned i=0;i<strlen(arg);i++)	//ctype.h ak aspon jeden znak nieje cislo tak do premennej result
	{					//typu bool nahrame hodnotu false ( povodna hodnota true)
		if (!(isdigit(arg[i]))) 	//vracia hodnotu premennej result
		{
			result=false;
			i=strlen(arg);
		}
	}
	return result;
}

char* ciselny_kontakt(char part[101],char num_contact[201])
{					//funkcia zmeni znaky na cisla podla zadania  
	int i=0,j=0;				//declarujeme premenne i a j s pociatocnou hodnotou 0 
	while (part[i]!='\0')			//i posun na stringu part1; j posun na stringu part2
	{				//porovnava hodnotu posun[i]teho znaku a ak je to alfanumericky znak 
		if ((isalnum(part[i])!=0)||((part[i])==43))	//priradi mu ciselnu hodnotu podla zadania
		{				//funkcia vracia string zlozeny z cisel
			if ((part[i]>47)&&(part[i]<58))
			{
				num_contact[j]=part[i];
				j++;
			}
			else if ((part[i]>64)&&(part[i]<91))
		  	   {if (part[i]<68) 
					{num_contact[j]=50;
					j++;}
		  	    else {
			   	if (part[i]<71) num_contact[j]=51;
			   	else if (part[i]<74) num_contact[j]=52;
			   	else if (part[i]<77) num_contact[j]=53;
			   	else if (part[i]<80) num_contact[j]=54;
			   	else if (part[i]<84) num_contact[j]=55;
			   	else if (part[i]<87) num_contact[j]=56;
			   	else if (part[i]<91) num_contact[j]=57;
			   	else{}
				j++;
				}
			   }
		else if ((part[i]>96)&&(part[i]<123))
			{
			if (part[i]<100) 
				{num_contact[j]=50;
			  	 j++;}
			else{
			   if (part[i]<103) num_contact[j]=51;
			   else if (part[i]<106) num_contact[j]=52;
			   else if (part[i]<109) num_contact[j]=53;
			   else if (part[i]<112) num_contact[j]=54;
			   else if (part[i]<116) num_contact[j]=55;
			   else if (part[i]<119) num_contact[j]=56;
			   else if (part[i]<123) num_contact[j]=57;
			   else{}
			   j++;
			   }
		   	}
		     else if(part[i]==43) 
			  {
				num_contact[j]=48;
				j++;
			  }
			  else{}
		}
	i++;
		
	}
	num_contact[j]='\0';
	return num_contact;
}

bool search(char string[100],char *hladaj)
{						//funkcia search porovnava string[i]ty znak s hladaj[j]tym znakom
	int i=0;				//i,j su lokalne premenne s pociatocnou hodnotou 0
	int j=0;				//spusti sa cyklus while pokial string[i] alebo hladaj[j] nebude
	while((string[i]!='\0')&& (hladaj[j]!='\0'))	//mat hodnotu konca stringu
	{					//ak su znaky zhodne zvysime hodnotu i aj j o 1 inak zvysime iba
		if (string[i]==hladaj[j]) 	//hodnotu i
		{				//ak je na konci hodnota j rovna dlzke stringu hladaj tak
			i++;			//sme nasli hladany vyraz v stringu a funkcia vracia hodnotu
			j++;			//true inac vrati hodnotu false
	}
	else i++;
	}
	if (j==(signed)strlen(hladaj))
		return true;
	else return false;
}

bool wanted_contact(char part1[101],char part2[101],char *argum)
{						//funkcia hlada argument v stringoch part1 a part2 pomocou
	char contact1[100],contact2[100];	//vlastnej funkcie ciselny_kontakt vracia hodnotu true
	*contact1=*ciselny_kontakt(part1,contact1);//ak nasla v aspon jednom zo stringov hladany
	*contact2=*ciselny_kontakt(part2,contact2);//vyraz inak vracia hodnotu false
	if (search(contact1,argum))
	{
		return true;
	}
	else 
		if (search(contact2,argum)) return true;
		else return false;
}

int main(int argc, char *argv[])
{
	char name[101],num[101],contact[203]; 	//main - deklarujeme 3 premenne typu string, z toho 2 o dlzke 101
	if (argc==1)				//a 1 o dlzke 203
	{					//kontroluje pocet argumentov - ak je len 1 argument tak pomocou
		while (fgets(name,102,stdin)!=NULL)	//funkcie while precita zo suboru, docita riadok pomocou 
		{				//eoln_check a nacita druhy riadok ktory znova docita pomocou
			eoln_check(name);	//tej istej funkcie a vypise kontakt pomocu print_contact funkcie
			if (fgets(num,102,stdin)!=NULL)
			{	eoln_check(num);
				print_contact(name,num,contact);
			}
		else fprintf(stderr,"No number for contact name:%s\n",name);
		}
	}
	else
	    if (argc==2)			//ak je pocet argumentov 2 tak nastavi hodnotu premennej found
	{					//na false a zacne cyklus while ktory postupne nacita 2 riadky,
		if (isnum(argv[1]))		//docita ich do konca a upravy na dlzku 100 alfanumerickych
		{				//znakov nasledne sa spusti podmienka na kotrolu hladaneho 
			bool found=false;	//kontaktu pomocou funkcie wanted_contact, ak vrati hodnotu true
			while (fgets(name,102,stdin)!=NULL)
			{			//premennej found sa nastavi hodnota found a vypise sa nacitany
				eoln_check(name);	//kontakt v pripade ziadnej zhody v kontaktoch funkcia 
				if (fgets(num,102,stdin)!=NULL)
					eoln_check(num);//vypise "Not Found"
				if (wanted_contact(name,num,argv[1])) 
				{
					print_contact(name,num,contact);
					found=true;
				}
			}
			if (!found) fprintf(stdout,"Not found\n");
		}
		else fprintf(stderr,"Argument is not number\n");
	}
	     else fprintf(stderr,"Too many arguments");	//ak je pocet argumentov viac ako 2 tak funkcia vypise
	return 0;					// "Too many arguments"
}

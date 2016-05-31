#include "percent_encoding.h"


void str_del(char * str, int i){
	while(str[i]!='\0'){
		str[i] = str[i+1];
		i++;
	}
}

void percent_encoding(char * url){
	int i=0, encoded=0;
	if(url[1]>='a' && url[1]<='z')
		url[1]-=32;
	if(url[2]>='a' && url[2]<='z')
		url[2]-=32;
	while((url[1]>percent_table[2*i+1][1] || (url[2]>=percent_table[2*i+1][2] && url[1]==percent_table[2*i+1][1])) && i<176){
		if(url[1]==percent_table[2*i+1][1] && url[2]==percent_table[2*i+1][2]){
			url[0]= percent_table[2*i][0];
			encoded=1;
		}
		i++;
	}
	if(encoded){		//si decodage reussis, on enleve le code hexa
		str_del(url, 1);
		str_del(url, 1);
	}
	else{
		printf("ERROR: unknown percent-character\n");
	}
}

void normalizeURL (char * url){
	int i, j, k;
	pos_sl=0;					//position du dernier slash pour ne pas modifier la casse des noms de fichier
	while(url[i]!='\0'){
		if(url[i]=='/'){
			pos_sl=i;
			i++;
		}
	}
	i=0;
	while(url[i]!='\0'){
		if(url[i]=='%'){							/////////////////////////percent-encoding//////////////////////////
			percent_encoding(&url[i]);
		}
		if(url[i]>='A' && url[i]<='Z' && i<pos_sl)				//////////////////////Convert to lower case////////////////////////
			url[i]+= 32;
		if(url[i]=='#')							//////////////////////removing the fragment////////////////////////
			url[i]='\0';							
		if(url[i]==':' && i>5){						//////////////////////removing default port////////////////////////
			if(url[i+1]=='8' && url[i+2]=='0'){
				str_del(url, i);
				str_del(url, i);
				str_del(url, i);
			}
			if(url[i+1]=='/')
				str_del(url, i);
		}
		i++;
	}
	
	i=2;
	while(url[i]!='\0'){
		if(url[i]=='.' && url[i-1]=='/'){			///////////////////////removing dot segment////////////////////////
			if(url[i+1]=='\0')		//point a la fin
				str_del(url, i);
			else{
				if(url[i+1]=='.' && url[i+2]=='/'){		//<=> /exemple/../
					j=i-2;
					while(j>1 && url[j]!='/')	//on cherche le dernier slash
						j--;
					if(url[j-1]=='/')		//si deux slashs
						str_del(url, i);
					else{					
						for(k=j;k<i+2;k++){
							str_del(url, j);
						}
						i-=i-j;
					}
				}
				if(url[i+1]=='/'){				//1 point
					str_del(url, i);
					str_del(url, i);
				}
			}
		}
		i++;
	}

	//adding trailing
	if(url[i-1]!='/'){
		//url[i]= '/';
		url[i]= '\0';
		url[i+1]= '\0';
	}
}

void init_percent_table(){
	
	char table[NB_PERCENT_CHAR][4] = {
	//backspace      %08				///Mettre les codes hexa en lower case 
	//tab            %09
	//linefeed       %0A
	"\r",			  "%0D",
	" ",	          "%20",
	"!",              "%21",
	"\"",             "%22",
	"#",              "%23",
	"$",              "%24",
	"%",              "%25",
	"&",              "%26",
	"'",              "%27",
	"(",              "%28",
	")",              "%29",
	"*",              "%2A",
	"+",              "%2B",
	",",              "%2C",
	"-",              "%2D",
	".",              "%2E",
	"/",              "%2F",
	"0",              "%30",
	"1",              "%31",
	"2",              "%32",
	"3",              "%33",
	"4",              "%34",
	"5",              "%35",
	"6",              "%36",
	"7",              "%37",
	"8",              "%38",
	"9",              "%39",
	":",              "%3A",
	";",              "%3B",
	"<",              "%3C",
	"=",              "%3D",
	">",              "%3E",
	"?",              "%3F",
	"@",              "%40",
	"A",              "%41",
	"B",              "%42",
	"C",              "%43",
	"D",              "%44",
	"E",              "%45",
	"F",              "%46",
	"G",              "%47",
	"H",              "%48",
	"I",              "%49",
	"J",              "%4A",
	"K",              "%4B",
	"L",              "%4C",
	"M",              "%4D",
	"N",              "%4E",
	"O",              "%4F",
	"P",              "%50",
	"Q",              "%51",
	"R",              "%52",
	"S",              "%53",
	"T",              "%54",
	"U",              "%55",
	"V",              "%56",
	"W",              "%57",
	"X",              "%58",
	"Y",              "%59",
	"Z",              "%5A",
	"[",              "%5B",
	"\\",             "%5C",
	"]",              "%5D",
	"^",              "%5E",
	"_",              "%5F",
	"`",              "%60",
	"a",              "%61",
	"b",              "%62",
	"c",              "%63",
	"d",              "%64",
	"e",              "%65",
	"f",              "%66",
	"g",              "%67",
	"h",              "%68",
	"i",              "%69",
	"j",              "%6A",
	"k",              "%6B",
	"l",              "%6C",
	"m",              "%6D",
	"n",              "%6E",
	"o",              "%6F",
	"p",              "%70",
	"q",              "%71",
	"r",              "%72",
	"s",              "%73",
	"t",              "%74",
	"u",              "%75",
	"v",              "%76",
	"w",              "%77",
	"x",              "%78",
	"y",              "%79",
	"z",              "%7A",
	"{",              "%7B",
	"|",              "%7C",
	"}",              "%7D",
	"~",              "%7E",
	"¢",              "%A2",
	"£",              "%A3",
	"¥",              "%A5",
	"|",              "%A6",
	"§",              "%A7",
	"«",              "%AB",
	"¬",              "%AC",
	"¯",              "%AD",
	"º",              "%B0",
	"±",              "%B1",
	"ª",              "%B2",
	",",              "%B4",
	"µ",              "%B5",
	"»",              "%BB",
	"¼",              "%BC",
	"½",              "%BD",
	"¿",              "%BF",
	"À",              "%C0",
	"Á",              "%C1",
	"Â",              "%C2",
	"Ã",              "%C3",
	"Ä",              "%C4",
	"Å",              "%C5",
	"Æ",              "%C6",
	"Ç",              "%C7",
	"È",              "%C8",
	"É",              "%C9",
	"Ê",              "%CA",
	"Ë",              "%CB",
	"Ì",              "%CC",
	"Í",              "%CD",
	"Î",              "%CE",
	"Ï",              "%CF",
	"Ð",              "%D0",
	"Ñ",              "%D1",
	"Ò",              "%D2",
	"Ó",              "%D3",
	"Ô",              "%D4",
	"Õ",              "%D5",
	"Ö",              "%D6",
	"Ø",              "%D8",
	"Ù",              "%D9",
	"Ú",              "%DA",
	"Û",              "%DB",
	"Ü",              "%DC",
	"Ý",              "%DD",
	"Þ",              "%DE",
	"ß",              "%DF",
	"à",              "%E0",
	"á",              "%E1",
	"â",              "%E2",
	"ã",              "%E3",
	"ä",              "%E4",
	"å",              "%E5",
	"æ",              "%E6",
	"ç",              "%E7",
	"è",              "%E8",
	"é",              "%E9",
	"ê",              "%EA",
	"ë",              "%EB",
	"ì",              "%EC",
	"í",              "%ED",
	"î",              "%EE",
	"ï",              "%EF",
	"ð",              "%F0",
	"ñ",              "%F1",
	"ò",              "%F2",
	"ó",              "%F3",
	"ô",              "%F4",
	"õ",              "%F5",
	"ö",              "%F6",
	"÷",              "%F7",
	"ø",              "%F8",
	"ù",              "%F9",
	"ú",              "%FA",
	"û",              "%FB",
	"ü",              "%FC",
	"ý",              "%FD",
	"þ",              "%FE",
	"ÿ",              "%FF",
	};
	int i,j;
	for(i=0;i<NB_PERCENT_CHAR;i++){
		j=0;
		while ( table[i][j]!='\0' ) {
			percent_table[i][j]= table[i][j];
			j++;
		}
	}
}
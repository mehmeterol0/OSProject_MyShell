#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>



#define KOMUTLISTESI 7

int main()
{
    asciiResimOlustur();
    //arayuzOlustur();
    char girilenDeger[1000] = {'\0'};
    char *ceviriciArgs[100] = {NULL};
    char *processes[100] = {NULL};
    char *komutlar[KOMUTLISTESI] = {"bash","execx", "cat","ls", "clear", "exit","help"}; 
    
    int i;

    while (1)
    {
        if (input(girilenDeger))
            continue;

        ayir(girilenDeger, processes, "|"); 
        i = 0;

        while (processes[i] != NULL)
        {
            ayir(processes[i], ceviriciArgs, " "); 
            if (cmd(ceviriciArgs, komutlar))
            {
                printf("yanlis bir komut girildi\n");
            }
            i++;
        }
    }
    return 0;
}

int bosmu(char *str)
{
    while (*str != '\0')
    {
        if (*str != ' ')
        {
            return 0;
        }
        str++;
    }
    return 1;
}





int input(char *str)
{
    printf("\nmyshell>>");
    fgets(str, 1000, stdin);
    yeniSatir(str);
    if (!bosmu(str))
    {
        return 0;
    }

    return -1;
}

int komutCalistir(char **args)
{
    // bu fonksiyon komutların calistirildigi fonksiyondur. 
    int pid = fork(); //ilk forklama islemi burda gerceklesir.
    int i,j; //donguler icin tanımlanan degiskenler
    int sonuc = 0; //fonksiyondan cikması icin gereken return degiskeni

    int argBoyut = (sizeof(args) / sizeof(int)); //parametre olarak gelen dizinin boyu
    
    if (strcmp("exit", args[0]) == 0) //args[0] consoldaki ilk argumanı temsil eder. exit yazildiginda kendi shellimizden cikar
    {
        exit(0);
    }
    if (strcmp("clear", args[0]) == 0)//clear komutu ile console ekranı temizlenir.
    {	
        temizle();  //temizle fonksiyonu asagidadir.
    }
    
    
    if (pid == 0) //forklama islemi yukarda yapmistik. pid = 0 ise;
    {
        if (strcmp("execx", args[0]) == 0) //eger ilk arguman execx komutu ise, 
        {
          if((strcmp("-t", args[1]) == 0)){ // eger ikinci arguman -t komutu ise,
		 if(args [2] != NULL){ // ucuncu arguman bos degil ise,
		      if(args [3] != NULL){// dorduncu arguman bos degilse,
		      	        i = execv(args[0],args);// bizim execx -t time programAdi komutunu calistirir.
		      }
		      else{
		      	printf("eksik parametre girildi. %d\n",argBoyut); //ilgili parametre eksikliginde, ekrana mesaj yazdirir.
		        exit(0);
		      }
		 }
		 else{
           //pdf'e gore bir programın calistirilmasi icin en az 4 parametreye ihtiyac var.		
	   //dogru bir sekilde girildiginde argBoyutumun 2 oldugunu gordum. yazdırma icinde 4'dur.
		     printf("eksik parametre girildi. %d\n",argBoyut);
		     exit(0);
		 }
          }
	  else{ 
		printf("yanlis parametre girildi. %d\n",argBoyut);// ilgili parametre eksikliginde, ekrana mesaj yazdirir.
	        exit(0);
          }
        }
        if(strcmp("cat", args[0]) == 0){ // cat komutu calistirmak icin /bin/cat klasoru calistirilir. 
	    	i = execv("/bin/cat", args); // bu klasor normal terminaldeki cat islemleri ile birebir aynidir.
        }
        if(strcmp("help", args[0]) == 0){// help komutu calistirmak olusturdugum fonksiyonu cagiririm.
            	helpKomutu(); //pdfte yok burasi ekstra ozellik ekledim.
        }
        if(strcmp("ls", args[0]) == 0){// ls komutu calistirmak icin /bin/ls klasoru calistirilir. 
            	i = execv("/bin/ls",args);// bu klasor normal terminaldeki ls islemleri ile birebir aynidir.
        }
        if (strcmp("bash", args[0]) == 0)// bash komutu calistirmak icin /bin/sh klasoru calistirilir.
        {
            	i =execv("/bin/sh", args);// bu klasor normal terminaldeki bash islemleri ile birebir aynidir.
        }
        else
        {
            i = execv(args[0], args);
        }
        if (i < 0)
        {
            printf("yanlis bir komut girildi\n"); //yanlis bir komut girildiginde ekrana hata yazdirilir.
            exit(0);
        }
    }
    else
    {
        wait(&i); //islem bittikten sonra waitle serbest birakilir.
        sonuc = WEXITSTATUS(i); //sonuc degiskenine aktarilir

    }


    return sonuc; //sonuc dondurulur.
}
void helpKomutu(){
        printf("||====================================================================================||\n");
	printf("|| 1-) bash: direk console'a bash yazarak bash islemlerini gerceklestirebilirisiniz.  ||\n");
	printf("|| 2-) execx: execx -t times programAdi seklinde kullanabilirsiniz.		      ||\n");
	printf("|| execx'in programAdi writef olduğu takdirde su sekilde kullanabilirsiniz; 	      ||\n");
	printf("||  		execx -t times writef -f dosyaAdi  				      ||\n");
	printf("|| 3-) cat: direk console'a cat yazarak cat islemlerini gerceklestirebilirisiniz.     ||\n");
	printf("|| 4-) ls:  direk console'a ls yazarak ls islemlerini gerceklestirebilirisiniz.       ||\n");
	printf("|| 5-) clear: console ekranını temizler. clear yazarak ulasabilirsiniz.               ||\n");
	printf("|| 6-) exit: exit yazarak, olusturdugumuz mevcut shellden cikis islemi gerceklesir.   ||\n");
	printf("||====================================================================================||\n");
}
int cmd(char **args, char **komutListesi)
{
    // komutlistesinde ilk parametre yazılan komut varmı yok mu orayı kontrol eden fonksiyondur.
    int i = 0; //komut listesini aramak icin for kullanmak icin olusturdugum i sayisi.
    int bulmaKontrol = 0; //komut listesinde bir komutu buldugunda gerisini aramasın diye olusturdugum kontrol degiskeni

    for(i=0; i<KOMUTLISTESI; i++){//tum komut listesi bu forda aranır.
        if (strcmp(args[0], komutListesi[i]) == 0) //girilen ilk arguman komut listesinde mevcutsa
        {
            bulmaKontrol = 1;//listesinin sonrasını aramasın diye bulmaKontrolu 1 yaptım.
            break;// break ile fordan ciktim
        }
    }
    if (bulmaKontrol == 1) //listede eger ilgili komut varsa bu ife girer.
    {
        komutCalistir(args); //ilgili komut listede varsa, 
        return 0;
    }
    else{
    	return -1; //eger bulmaKontrol = 1 ise 0 return et. degilse -1.
    }
}

void ayir(char *str, char **cevirici, char *sinirlayici)
{
    int i = 0;
    while ((cevirici[i] = strsep(&str, sinirlayici)) != NULL)
    {
        if (bosmu(cevirici[i]))
        {
            continue;
        }
        i++;
    }
}

void yeniSatir(char *str)
{
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            *str = '\0';
            break;
        }
        str++;
    }
}

void temizle()
{
    system("clear");
}

/*
void arayuzOlustur(){
        printf("                              ||======================================||\n");
	printf("                              ||______________________________________||\n");
	printf("                              ||.....Linux Shellime Hosgeldiniz.......||\n");
	printf("                              ||_____________{Mehmet EROL}____________||\n");
	printf("                              ||.....Kullanabileceginiz Komutlar......||\n");
	printf("                              ||                                      ||\n");
	printf("                              ||1- bash 		 	      ||\n");
	printf("                              ||2- execx 			      ||\n");
	printf("                              ||3- cat 				      ||\n");
	printf("                              ||4- ls 				      ||\n");
	printf("                              ||5- clear 			      ||\n");
	printf("                              ||6- exit 			      ||\n");
	printf("                              ||7- help : Komutlar hakkında bilgi     ||\n");
	printf("                              ||icin help komutunu kullanınız..	      ||\n");
	printf("                              ||				      ||\n");
	printf("                              ||======================================||\n");
	printf("\n");
	printf("\n");
}
*/
void asciiResimOlustur(){

	printf("MMMMMMMMMMMMMMMMMMMW0ooONWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||======================================||\n");
	printf("MMMMMMMMMMMMMMMMMMMNxc:coONWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||______________________________________||\n");
	printf("MMMMMMMMMMMMMMWXOKWW0o:::coONWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||.....Linux Shellime Hosgeldiniz.......||\n");
	printf("MMMMMMMMMMMMWXkl:oKWWKxl:::coONWMMMMMMMMMMMMMMMMMMMMWNNXXXXXXXXNWMWNXK00KXNWMMMMWNXXNWMMMMMMMWNXXNWM||______________________________________||\n");
	printf("MMMMMMMMMMWXklc::l0WNNNKxl:::coONWMMMMMMMMMMMMMMMMMNxcc:::::::ckNKxc;;;;;:lOWMMWkc:;l0WMMMMMWkc::lKM||.....Kullanabileceginiz Komutlar......||\n");
	printf("MMMMMMMMWXkl:::co0NNkox0XKxl:::coONWMMMMMMMMMMMMMMMNo,',cxkkkk0X0c,,cxOOkxxKWMMXl,'',lKMMMMWO:',';kW||                                      ||\n");
	printf("MMMMMMWXklc::coOXWMXd::lxKNKxl:::cdONWMMMMMMMMMMMMMNd,',xWMMMMMWx,',lKWMMMMMMMM0:';;,,dNMMMKl,;;',dN||1- bash 		 	            ||\n");
	printf("MMMMWXklc::coOXXKXWNkc:::lx0XKxl:::cd0NMMMMMMMMMMMMNo,',dNWWWWWW0:,,,:dOXWMMMMWk;,od;';kWMXd,:xl',lX||2- execx 		 	            ||\n");
	printf("MMWXklc::coOXXOocxXWN0dc::clxKXKxl:::cd0NWMMMMMMMMMNd,,,:clllldXW0o:,'',:oONWMXo,,xKo,,c0Wk;,xKo'':0||3- cat 		 	            ||\n");
	printf("WXkl:::coOXXOoc::oKWNNX0dc:::lx0XKxl:::cd0NWMMMMMMMNd,',:odddd0WMMWXko:,'',lKMKc';kW0:',okc,lKNd,';k||4- ls 		 	            ||\n");
	printf("klc::coOXXOoc::clONXdokXX0dc:::lxKNKxl:::cdKWMMMMMMNd,,,xWMMMMMMMMMMMWXx:,,,xWk;'c0MNx,',;,:OWWk;',d||5- clear 		 	            ||\n");
	printf("c:::cxXWKdc:::cdKWWOc:cokXX0dc:::lxKNKxl::cxNMMMMMMNd,,,dWMMMMMWKO0XNNNOc,,:ONd,'lXMMKl,,,,dNMMO:''l||6- exit 		 	            ||\n");
	printf("l:::cdKNXxl:::coONWKdc::cokXXOdc:::lxKNKxlckNMMMMMMNo,',dNMMMMMNx;;:ccc;,;cONKc',dNMMWO:',lKMMM0c'':||7- help : Komutlar hakkında bilgi     ||\n");
	printf("0dc:::lxKXKxl:::cd0XXkoc::cokXX0dc:::o0WWK0XMMMMMMMW0ddx0WMMMMMMN0xdooodx0NMMXkdxKWMMMN0kOXWMMMNOdxx||icin help komutunu kullanınız..	    ||\n");
	printf("WN0dc::clxKNKxl:::cd0XXklc::cokXXOdc:cxNMMMMMMMMMMMMNNNNNNNXXNWWWNNNWNNNNXNNWWNWWWNWNNNNWWWNWWNNNNXN||	     			            ||\n");
	printf("MMWN0dc:::lxKXKxl:::cd0XKklc::coONNOdd0WMMMMMMMMMMMWOO0xOkOOxkk0X0kO00k0KOOkOOkOKKkkkxkOOOOkkkkk00OX||======================================||\n");
			printf("MMMMWNOdc:::lxKXKxl:::cd0XXkoc::lOWWNNWMMMMMMMMMMMMWXKXKKKXX0KKKNKO00KK0KKKK00K0XX00000KKK000KKKXNXW||	     			            ||\n");
	printf("MMMMMMWNOdc:::lxKNKxl:::cd0NXklccOWMMMMMMMMMMMMMMMMWX0K0O00O00O0NK0KOO0OO000O0OO00O0O00O00OOXMMMMMMM||	     			            ||\n");
	printf("MMMMMMMMWNOdc:::lxKXKxlc::lOWWXOONMMMMMMMMMMMMMMMMMMN000O0OOK00XWX00000OKK0K000OK0OKKKK0KKO0XMMMMMMM||	     	    MEHMET EROL             ||\n");
	printf("MMMMMMMMMMWNOoc:::lxKXkl:::dXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWMMMMMMMMMMMMMMMMMM||	       BIYOMEDIKAL MUHENDISI        ||\n");
	printf("MMMMMMMMMMMMWNOoc::clolc::ckNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||        BILGISAYAR MUHENDISLIGI       ||\n");
	printf("MMMMMMMMMMMMMMWNOdc:::::clkXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||	        mhmterol@outlook.com	    ||\n");
	printf("MMMMMMMMMMMMMMMMWXkocccld0NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM||======================================||\n");

}

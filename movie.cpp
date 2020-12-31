/* A DVD shop needs an Object Oriented program that process the following information about ten (10) videos in their stock: dvd name, rent date, due date, rental status
	A customer (identified by ID) plus his full name can borrow at most 1 video @ R12.50 per day. A penalty of 10% per day is charged if returned late. The borrow period is at most 7 days
	A video should be checked if is not rented out before borrow transaction is processed. If borrowed out the customer should either be requested for the second choice or be advised when the video is expected back in the shop
	Failure for the shop to receive the video back within 7 days, is considered permanent loss and the customer is liable to a R400.00 compensation fee
	At the end of business, a report should be generated showing
	Which films are rented out and when are they due
	To which customers they are rented, rent date and due date of the dvds.
Generate your own test data that will test all cases to illustrate the accuracy and consistency of the program*/


//including header files
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

int customerid=1;
int numberofcustomers=0;

class customer;

struct date
	{
		int day;
		int month;
		int year;
	};
struct date tomorrow,returndate;

void nextday(struct date);        //global function to find the next day

class dvd          //creating a class for dvd
{
	char title[50];
	
	struct date rentdate,duedate;
	
	int avail;
	 public:
		  dvd()
		 {
		 			 	avail=1;
		  } 
     void gettitle();		//gets dvd title  
	 void getvideoinfo();    
	 void getrentdate();     //gets rent date
	 void getduedate();	      // gets due date
	 int checkavail();       //checks availability
	 void rentdvd();         //to rent dvd
	 void returndvd();       //to return dvd
	 int checktitle(char dvdname[50]);    //to check if entered title matches with dvd name
	
     friend void getcustomerinfo(int identity,customer c[10],dvd d[10]);
	 friend void title(dvd d[10]);        //to get all titles from a file
	 friend void getdvd();
	  float charges(struct date);
	 friend void addcustomerdvd(dvd d[10] ,customer c[10], int number,char customername1[50],int identity);
	 friend void removecustomerdvd(dvd d[10] ,customer c[10], int number,int identity);
      friend void enterdatabaseintofile(customer c[10],dvd d[10],int identity);	 
};
	
void getdvd()
{
	char data[100]; // buffer to store a line read from file
   ifstream ifile;
    //char name[50];
	//cin>>name;   
    // declaring an object of class ifstream
   ifile.open("database.txt");
   if(ifile.fail())return;
   //cout<<name; // open "file.txt" for reading
   
   char buffer[100];  char c;
   while (!ifile.eof()) { // while the end of file [ eof() ] is not reached 
      ifile.getline(data, 100);
      //cout<<"run2";
      strcpy(buffer,data);
      //cout<<"run1";
	  cout<<buffer<<endl;
        if(ifile.eof()||ifile.fail()||ifile.bad())break;	  
   }
   ifile.close();
}
void title(dvd d[10])
{
	char data[100]; // buffer to store a line read from file
   ifstream ifile; // declaring an object of class ifstream
   ifile.open("movie.txt"); // open "file.txt" for reading
   cout << "We rent the following DVDs :" << endl << endl;
   int i=0;
   while (!ifile.eof() && i<=9) { // while the end of file [ eof() ] is not reached 
      ifile.getline(data, 100); // read a line from file
      strcpy(d[i].title,data);
	  cout << d[i].title << endl;
	  //cout<<data;
	  i++; // print the file to console
   }
   ifile.close();
}

void dvd::gettitle()
{
	cout<<"\nenter title\n";
	cin>>title;
}

int dvd::checktitle(char dvdname[50])
{
	if (strcmp(dvdname,title)==0)
	  return 0;
    else
	    return 1;
}


class customer
{   char customername[50];
	char rentedname[100];
	int rented;
	int id;
	public:
	 
	 friend void addcustomerdvd(dvd d[10] ,customer c[10], int number,char customername1[50],int identity);
	 friend void removecustomerdvd(dvd d[10] ,customer c[10], int number,int identity);
	 
	 friend void getcustomerinfo(int identity,customer c[10],dvd d[10]);
	 friend void custid(customer c[10]);
	 friend int getidentifier(customer c[10], char customername1[50]);
	 
	 friend void enterdatabaseintofile(customer c[10],dvd d[10],int identity);   //to make a customer database	 
	friend int eligibility(customer c[10], char customername[50]);
};

void getcustomerinfo(int identity,customer c[10],dvd d[10])
{    int key;
     int found;
	for(int i=0;i<10;i++)
	{
		if(c[i].id==identity)
		   {
		   	  key=i;
		   	  break;
		   }
	}   
	cout<<"\nCustomer name:  "<<c[key].customername;
	if(c[key].rented==1)
	{
	    cout<<"\nDVD name:   "<<c[key].rentedname<<endl;
	    for(int j=0;j<10;j++)
	    {
	    	if(strcmp(d[j].title,c[key].rentedname)==0)
	    	   {
	    	   	found=j; 
	    	   	break;
			   }
		}
		cout<<"Rent date:  "<<(d[found].rentdate).day<<"/"<<(d[found].rentdate).month<<"/"<<(d[found].rentdate).year<<endl;
		cout<<"Due date:  "<<(d[found].duedate).day<<"/"<<(d[found].duedate).month<<"/"<<(d[found].duedate).year<<endl;
    }
	else
	cout<<"\nNo dvd rented\n";
}
int getidentifier(customer c[10],char customername1[50])
{
	 	for(int i=0;i<10;i++)
	 	{
	 		if(strcmp(c[i].customername,customername1)==0)
	 		  return i;
	     }  return numberofcustomers;
	 }  
void custid(customer c[10])
{
	 	for(int i=0;i<10;i++)
	 	{
	 		c[i].id=i;
		 }
	 }
void enterdatabaseintofile(customer c[10],dvd d[10],int identity)
{    int i=0; int success; int key;

   
     
	fstream f;
	f.open("database.txt",ios::out|ios::app);
	//f<<"name      DVD rented     Rent date     Due date\n";
	f<<c[identity].customername;
		//cout<<c[numberofcustomers-1].customername;
	f<<"   ";
	f<<c[identity].rentedname;
	//cout<<c[numberofcustomers-1].rentedname;
	f<<"   ";
	for(int j=0;j<=10;j++)
	{
		if(strcmp(d[j].title,c[identity].rentedname)==0)
		{
		    success=1; key =j; break;
			
		}   
		
	}
	
	if(success==1)
           {
				   		
			f<<(d[key].rentdate).day<<"/"<<(d[key].rentdate).month<<"/"<<(d[key].rentdate).year;
			f<<"     ";
			f<<(d[key].duedate).day<<"/"<<(d[key].duedate).month<<"/"<<(d[key].duedate).year;
			f<<"     ";
			f<<"\n";
			//f<<(d[key].duedate).day<<"/"<<(d[key].duedate).month<<"/"<<(d[key].duedate).year<<"   ";
		  }
	
	
  
}
void customer::openfile()
{
	fstream f;
	f.open(customername,ios::out);
	
}


void removecustomerdvd(dvd d[10] ,customer c[10], int number,int identity)
{    c[identity].rented=0;
	 
	
}
void addcustomerdvd(dvd d[10],customer c[10], int number,char customername1[50],int identity)
{     
   strcpy(c[identity].customername,customername1);
	 strcpy(c[identity].rentedname,d[number].title);
	  c[identity].rented=1;
      numberofcustomers++;
}

int eligibility(customer c[10],char customername[50])
{
	for(int i=0;i<10;i++)
	  {
	  	if(strcmp(customername,c[i].customername)==0)
	  	  {
	  	  	if(c[i].rented!=0)
		   {cout<<"\ncannot rent\n";
	  	     return 0;
	  	   }
      }
    }
      return 1;
	
}
void dvd::getrentdate()
{ 
    
	 	    cout<<"\nday\n";
	 	  	 cin>>rentdate.day;
	 	  	 cout<<"\nmonth\n";
	 	  	 cin>>rentdate.month;
		     cout<<"\nyear\n";
			 cin>>rentdate.year; 
		   
}

void dvd::getduedate()
{
	 cout<<"\nday\n";
	 	  	 cin>>duedate.day;
	 	  	 cout<<"\nmonth\n";
	 	  	 cin>>duedate.month;
		     cout<<"\nyear\n";
			 cin>>duedate.year;  
		   
}

int dvd::checkavail()
{
	 if(avail>0)
	   return 1;
	  
	  else
	  return 0;   
}

void dvd::rentdvd()
{
    avail=avail-1;	
}

void dvd::returndvd()
{
	avail=avail+1;
}

const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

bool valid_date (struct date today) 
{
    // Check month first.
    if (today.month < 1 || today.month > 12)
        return false;

    // Allow Feb 29 in leap year if needed.
    if (today.month == 2 && today.day == 29) {
        if (today.year % 400 == 0)
            return true;
        if ((today.year % 4 == 0) && (today.year % 100 != 0))
            return true;
    }

    // Then check day.
    if (today.day < 1 || today.day > days[today.month-1])
        return false;

    return true;
}

void nextday(struct date duedate) 
	{
		 
		 tomorrow.day=duedate.day;
		 tomorrow.month=duedate.month;
		 tomorrow.year=duedate.year;
    // Don't do anything for bad dates.
    if (!valid_date (duedate)) return;
    

   // Just blindly add a day with no checks.
       
    tomorrow.year = duedate.year;
    tomorrow.month = duedate.month;
    tomorrow.day = duedate.day + 1;
     

    // Allow Feb 29 in leap year if needed.
    if (tomorrow.month == 2 && tomorrow.day == 29) 
	{
    	
        if (tomorrow.year % 400 == 0)
            return;
        if ((tomorrow.year % 4 == 0) && (tomorrow.year % 100 != 0))
            return;
    }

    // Catch rolling into new month.
    if (tomorrow.day > days[tomorrow.month-1]) 
	{
        tomorrow.day = 1;
        tomorrow.month++;
       
        // Catch rolling into new year.
        if (tomorrow.month == 13) 
		{
            tomorrow.month = 1;
            tomorrow.year++;
        }
    }
        
    return;
}

float dvd::charges(struct date returndate)
{  int c1=1;int c2=0;   float cost; int flag=0;
     tomorrow.day=rentdate.day;
     tomorrow.month=rentdate.month;
     tomorrow.year=rentdate.year;
	 while(1)//(duedate.day)!=(tomorrow.day) || (duedate.month)!=(tomorrow.month) || (duedate.year)!=(tomorrow.year))
	{     
	    if(duedate.day==tomorrow.day && duedate.month==tomorrow.month && duedate.year==tomorrow.year) break;
	    
		nextday(tomorrow);
		   c1++; 
		   
     }
	if(duedate.day==returndate.day && duedate.month==returndate.month && duedate.year==returndate.year)
	{  
	    
	    flag=1;  

	}
	else
	{   tomorrow.day=duedate.day;
     tomorrow.month=duedate.month;
     tomorrow.year=duedate.year;
     cout<<returndate.day<<endl;
		while(tomorrow.day!=returndate.day || tomorrow.month!=returndate.month || tomorrow.year!=returndate.year)
	 {  
		nextday(tomorrow);
		 
		   c2++; 	cout<<c2; flag=2;
		 
     }    
	}
        //if(c2<8) 
		  //flag=2;
       if(flag==1)  
	    {  
		  return ((float)(12.5 * c1));
		   
		}
       else if(flag==2)
       {
         float total;       	
	    total=12.5 * c1 + 1.25 * c2;
	   return total;
      }
	    
	else
	 return 400;  
}
main()
{    dvd d[10];  //title(d);
     customer c[20];   custid(c);  int identifier;
     /*for(int k=0;k<10;k++)
     {
     	 d[k].gettitle();
	 } */
     int rent=0,returned=0;
     while(1)
     {
	 
	 cout<<"\n1:list of all dvds\n2:rent dvd\n3:return dvd\n4:display info about a customer\n5:dvd rent and due date entries\n6:exit\n";
	 int ch;
	 cin>>ch;
	  
	 
	 switch(ch)
	 {
	 	case 1:
	 		title(d);
	 		break;
	    case 5:
	    	 
	    	
		
	    	 getdvd();
		     break; 		
	 	case 2:
	 		{
              char customername1[50];
			  cout<<"enter your name:\n";
			  getchar();
			  gets(customername1);
			  //cin>>customername1;
			  
			   //c[numberofcustomers].getcustomername(); 
			  //c[numberofcustomers].openfile(); 
			 int e;
			   e=eligibility(c,customername1);
			   if(e!=0)		
	 	{
			  	 char dvdname[50];  int number;
	      //getchar();
	      cout<<"enter name of dvd to be rented:   ";
	      
	     // getchar();
		  gets(dvdname);
		  //cin>>dvdname;
		  for(int i=0;i<10;i++)
		  {  
		  	int x;  x=d[i].checktitle(dvdname);
		  	 if(x==0)
		  	 {    int check=d[i].checkavail();
		  	 	if(check==1)
		  	 	{
		  	 		d[i].rentdvd();
		  	 		cout<<"\ndvd available\n";
		  	 		rent=1; 
		  	 		number=i;
		  	 		break;
		  	
				   }
				   else
				   {  rent=0;
				   	 cout<<"\n Sorry! No dvd available\n";
				   	 
				   }
				   
			   }
		  }
			   
			   
		 if(rent==1)	   
		{
		  			   	   		
	 	  cout<<"\nenter rent date\n";
	 	  d[number].getrentdate();
	 	 
		    cout<<"\nenter due date\n"; 
	 	    d[number].getduedate();
	 	    
	 	    identifier=getidentifier(c,customername1);
	 	  if(identifier==-1) cout<<"error";
	 	    else
	 	    cout<<"your id is: "<<identifier<<"\n";
		    addcustomerdvd(d,c,number,customername1,identifier);
		    
	      enterdatabaseintofile(c,d,identifier);	
		   
		  cout<<"\n dvd rented!\n";  	
	    }
	    
	   else
	   cout<<"\nno dvd rented, please try again\n";
      }

	  else
	   cout<<"\ncannot rent\n"; 
	   break;
      } 
	   case 3: 
	     char dvdname1[50]; int number1; char customername2[50]; int iden;
	      cout<<"\nenter name:\n";
	      getchar();
		  gets(customername2); 
		   iden=getidentifier(c,customername2);
	      cout<<"\nenter name of dvd to be returned:      ";
	      //char ch3; 
		  //ch3=getchar();
		  
		  gets(dvdname1);
		  for(int i=0;i<10;i++)
		  {  int y;  y=d[i].checktitle(dvdname1);
		  	if(y==0)
		  	 {
		  	 	
		  	 	
		  	 		d[i].returndvd();
		  	 		cout<<"\ndvd can be returned\n";
		  	 		returned=1;
		  	 	    number1=i;
		  	 		break;
		  	 }
				  
				   
			   }
		  
		 	   
			   
		 if(returned==1)	   
		{
					   	   		
	 	  cout<<"\nenter return date\n";
	 	   cout<<"\nday\n";
	 	  	 cin>>returndate.day;
	 	  	 cout<<"\nmonth\n";
	 	  	 cin>>returndate.month;
		     cout<<"\nyear\n";
			 cin>>returndate.year; 
		
		   float charge;
		   charge=d[number1].charges(returndate);   
		   removecustomerdvd(d,c,number1,iden);
		  cout<<"\n dvd returned!\n";  	
		  cout<<"\ncharges are:\t"<<charge;
	    }
	    
	    
	   else
	   cout<<"\nno dvd returned, please try again\n";
	   
	   
	   break;
	   
	    	 
     case 4:
     	int i;
     	cout<<"\nEnter customer id\n";
     	cin>>i;
     	getcustomerinfo(i,c,d);
	 	break;	
	 
	 case 6:
	    exit(0);	
	   
      }     
   }
   //fflush(stdin);
}

#include<iostream>
#include <cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

class customer{
   public:
   char name[20];
   int deposit,r;
   
   void new_deposit(int x){
       deposit+=x; 
       cout<<"Your total balance is : "<<deposit;  
   }
   void modify(int r , int p){
       if(r!=p){
       deposit-=100;
       cout<<"Your current balance is "<<deposit;
       }
       else{
       deposit+=50;
       cout<<"Your current balance is "<<deposit;
}
}  

  int refno () const{
       return r;
  }

  void create_acct(){
       cout<<"Your name : ";
       cin.ignore();
       cin.getline(name,20);
       srand(time(0));
       r = rand()%1000;
       cout<<"Your reference no. is : "<<r<<endl;
       cout<<"PLEASE REMEMBER IT."<<endl;
       //cin.ignore();
	cin.get();
       system("cls");
       do{
       cout<<"Please enter your deposit money value(>1000):";
       cin>>deposit;
       }while(deposit<1000);
       cout<<"Account created successfully.";
}

};

void upgrade_deposit(int num){
     int a;
     bool found=false;
     customer acct;
     fstream File;
     File.open("customer.txt", ios::binary|ios::in|ios::out);
     cout<<"Please enter your reference no. : ";
     cin>>a;
     while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acct), sizeof(customer));
     if(acct.refno()==a){
     acct.new_deposit(num);
     found=true;
     }
       }
}



void play(){
    customer acct;
    bool found=false;
    fstream File;
    File.open("customer.txt", ios::binary|ios::in|ios::out);
    int a;
    cout<<"Please enter your reference no. : ";
    cin>>a;
     while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acct), sizeof(customer));
    if(acct.refno()==a){
       int p;
       cout<<"Please enter any number between 0-10 : ";
       cin>>p;
       srand(time(0));
       int r = rand()%10;
       cout<<"Computer generated number is : "<<r<<endl;
       acct.modify(r,p);
       char a;
       cout<<"Would like to play another round(Y/N): ";
       cin>>a;
       if(acct.deposit == 0){
       cout<<"Insufficient balance.";
       }
       a = toupper(a);
       if(a=='Y')
       play();
       else
       cout<<"Thank you for playing.";
       found=true;
    }
}
}
void intro(){

    
    cout<<"\n\n\n\tWelcome to our casino !!!"<<endl;
    cout<<"\n\nHere for every wrong guess you will be penaltised with Rs. 100\nBut for every right guess u get Rs. 50, so best of luck ."<<endl;
    cin.get();
}

void write_account()
{
	customer acct;
	ofstream outFile;
	outFile.open("customer.txt",ios::binary|ios::app);
	acct.create_acct();
	outFile.write(reinterpret_cast<char *> (&acct), sizeof(customer));
	outFile.close();
}

int main (){
    int i;
    intro();
    system("cls");
    do{
    cout<<"\n\n1.Create an account\t2.deposit money\n\n3.PLAY!!!\t\t4.Quit"<<endl;
    cout<<"\n\nPlease select your choice - ";
    cin>>i;
    system("cls");
    switch(i){
        case 1:write_account();
               break;
        case 2:int num;
               cout<<"Enter the amount : ";
               cin>>num;
               upgrade_deposit(num);
               break;
        case 3:play();
               break;
        case 4:cout<<"Thank you for your time. ";
               break;
        default:cout<<"Please enter a valid option.";
               continue;
        }
       cin.ignore();
	cin.get();
       system("cls");
    }while(i!=4);    
}
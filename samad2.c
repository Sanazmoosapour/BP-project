#include<iostream>
#include<cstdlib>
#include"clui.h"
using namespace std;
int adminnumber=0;
bool adminentered=false;
struct food{
  char*name=new char[100];
  double price;
  int availablenumber;
  int soldnumber;
};
struct reserve{
  bool reserved=false;
  food myfood;
};
struct user{
  char* username=new char[100];
  char* pass=new char[100];
  char* firstname=new char[100];
  char* lastname=new char[100];
  char* studentnumber=new char[100];
  char* phonenumber=new char[12];
  char* grade=new char[100];
  char* field=new char[100];
  reserve* reserved=new reserve[30];
  int money=0;
};
user admin;
struct entered{
  bool entered;
  int usernumber;
};
entered userenter={false,-1};
struct date{
    int number_of_foods=0;
  food* foods=new food[number_of_foods];
};
int length(char* string){
  int i=0;
  while(string[i]!='\0')
    i++;
  return i;
}
bool isequal(char* string1,char* string2){
  if(length(string1)!=length(string2))
  return false;
  else{
    for(int i=0;i<length(string1);i++)
      if(string1[i]!=string2[i])
        return false;
  }
  return true;
}
void entermenu(user* & users,int &userlength);
void adduser(user* &users,int &userslength);
void enterusermenu(user* users,int userslength);
void enteradmin(user* users,int userslength);
void enteruser(user* users,int userslength);
int isuser(user* users,int userslength,char* username,char* password){
  for(int i=0;i<userslength;i++)
    if(isequal(users[i].username,username))
      if(isequal(users[i].pass,password))
        return i;
    return -1;
}
void adminmode(date* &foodtable,date* &foodtablehos);
void addfood(date* &foodtable,int curdate);
void addfoodhos(date* &foodtablehos,int curdate);
void usermode(user* &users,date* &foodtable,date* &foodtablehos,int usernumber);
void reservefood(user* &users,date* &foodtable,int curdate,int usernumber);
void reservefoodhos(user* &users,date* &foodtablehos,int curdate,int usernumber);
int main(){
  int userslength=1;
  user* users=new user[userslength];
  date* foodtable=new date[30];
  date* foodtablehos=new date[30];
  while(true)
  {
    while((userenter.entered==false)&&(adminentered==false))
      entermenu(users,userslength);
    if(adminentered)
      adminmode(foodtable,foodtablehos);
    else if(userenter.entered)
      usermode(users,foodtable,foodtablehos,userenter.usernumber);
  }
}
void entermenu(user* & users,int &userslength){
  char enter;
  clear_screen();
cout<<"1: login"<<endl;
cout<<"2: signup"<<endl;
cin>>enter;
if(enter=='1'){
  enterusermenu(users,userslength);
}
else if(enter=='2'){
  adduser(users,userslength);
}
}
void adduser(user* &users,int &userslength){
  char a;
  clear_screen();
  cout<<"1:add user"<<endl<<"2:add admin"<<endl;
  cin>>a;
  if(a=='1'){

  user* temp=new user[userslength+1];
  for(int i=0;i<userslength;i++)
  temp[i]=users[i];
  delete[] users;
  users=temp;
  ///delete[] temp;
  userslength++;
  cout<<"creat username: ";
  cin>>users[userslength-2].username;
  cout<<"creat password: ";
  cin>>users[userslength-2].pass;
  change_color_rgb(240, 3, 252);
  cout<<"more information:)"<<endl;
  reset_color();
  delay(2000);
  cout<<"enter your firstname: ";
  cin>>users[userslength-2].firstname;
  cout<<"enter your lastname: ";
  cin>>users[userslength-2].lastname;
  cout<<"enter your student number: ";
  cin>>users[userslength-2].studentnumber;
  cout<<"enter your phone number: ";
  cin>>users[userslength-2].phonenumber;
  cout<<"enter your grade: ";
  cin>>users[userslength-2].grade;
  cout<<"enter your study field: ";
  cin>>users[userslength-2].field;
  change_color_rgb(32, 252, 3);
  cout<<"succesfully signed up!"<<endl;
  reset_color();
  delay(2000);
}
else if(a=='2'){
  if(adminnumber==1){
  change_color_rgb(150, 10, 15);
    cout<<"admin has already signed up!"<<endl;
    reset_color();
    delay(2000);
  }
  else{
    cout<<"creat username: ";
    cin>>admin.username;
    cout<<"creat password: ";
    cin>>admin.pass;
    change_color_rgb(32, 252, 3);
    cout<<"succesfully signed up!"<<endl;
    reset_color();
    delay(3000);
    adminnumber++;
  }
}
}
void enterusermenu(user* users,int userslength){
  char a;
  clear_screen();
  cout<<"1:enter as admin"<<endl<<"2:enter as user"<<endl;
  cin>>a;
  if(a=='1')
  enteradmin(users,userslength);
  else if(a=='2')
  enteruser( users,userslength);
}
void enteruser(user* users,int userslength){
  char* username=new char[100];
  char* password=new char[100];
  clear_screen();
  cout<<"enter username: ";
  cin>>username;
  cout<<"enter password ";
  cin>>password;
  if ((isuser(users,userslength,username,password))>=0){
    change_color_rgb(32, 252, 3);
    cout<<"you entered succesfully:)"<<endl;
    reset_color();
    delay(2000);
    userenter.entered=true;
    userenter.usernumber=isuser(users,userslength,username,password);
  }
  else{
    change_color_rgb(150, 10, 15);
    cout<<"username or password is incorrect."<<endl;
    cout<<"if you dont have an account please sign up first."<<endl;
    reset_color();
    delay(2000);
  }
  delete[] username;
  delete[] password;
}
void enteradmin(user* users,int userslength){
  char* username=new char[100];
  char* password=new char[100];
  clear_screen();
  cout<<"enter username: ";
  cin>>username;
  cout<<"enter password: ";
  cin>>password;
  if(isequal(username,admin.username) && isequal(password,admin.pass)){
    adminentered=true;
    change_color_rgb(32, 252, 3);
    cout<<"you succesfully entered!"<<endl;
    reset_color();
    delay(2000);
  }
  else{
    change_color_rgb(150, 10, 15);
    cout<<"username or password is incorrect"<<endl;
    reset_color();
    delay(2000);
  }
  delete[] username;
  delete[] password;
}
void adminmode(date* &foodtable,date* &foodtablehos){
  int curdate;
  char a;
  clear_screen();
  cout<<"enter today's date: ";cin>>curdate;
  while(true){
    clear_screen();
    cout<<"1)add food"<<endl<<"2)print food list"<<endl<<"3)log out"<<endl;cin>>a;
    if(a=='1'){
      char f;
      cout<<"1)central restaurant"<<endl<<"2)hostel restaurant"<<endl;cin>>f;
      if(f=='1')
      addfood(foodtable,curdate);
      else if(f=='2')
      addfoodhos(foodtablehos,curdate);
    }
    else if(a=='2'){
      change_color_rgb(252, 244, 3);
      for(int i=0;i<30;i++){
        cout<<"day"<<i+1<<": ";
        for(int j=0;j<foodtable[i].number_of_foods;j++){
          cout<<"("<<foodtable[i].foods[j].name<<") ";
          for(int j=0;j<foodtablehos[i].number_of_foods;j++)
            cout<<"("<<foodtablehos[i].foods[j].name<<") ";
        }
        cout<<endl;
      }
      reset_color();
      delay(3000);
    }
    else if(a=='3'){
      adminentered=false;
      break;
    }
  }
}
void addfood(date* &foodtable,int curdate){
  bool flag=false;
  int date;
  char a;
  while(!flag){
    clear_screen();
    cout<<"enter the date you want to add food: ";cin>>date;
    if(date>=curdate+2){
      date--;
      while(!flag){
        clear_screen();
        cout<<"1)add food in "<<date+1<<endl<<"2)change date"<<endl<<"3)previous menu "<<endl;cin>>a;
        if(a=='1'){
        food*  temp=new food[(foodtable[date].number_of_foods)+1];
          for(int i=0;i<(foodtable[date].number_of_foods);i++)
          temp[i]=foodtable[date].foods[i];
          delete[] foodtable[date].foods;
          foodtable[date].foods=temp;
          foodtable[date].number_of_foods++;
          cout<<"food name: ";
          cin>>foodtable[date].foods[(foodtable[date].number_of_foods)-1].name;
          cout<<"food price: ";
          cin>>foodtable[date].foods[(foodtable[date].number_of_foods)-1].price;
          cout<<"number of foods: ";
          cin>>foodtable[date].foods[(foodtable[date].number_of_foods)-1].availablenumber;
          change_color_rgb(32, 252, 3);
          cout<<"food added succesfully!"<<endl;
          reset_color();
          delay(3000);
        }
        else if(a=='2')
          break;
          else if(a=='3')
          flag=true;
      }
    }
    else{
      change_color_rgb(150, 10, 15);
    cout<<"you can't add today and tomarrow's food"<<endl;
    reset_color();
    delay(2000);
  }
  }

}
void addfoodhos(date* &foodtablehos,int curdate){
  bool flag=false;
  int date;
  char a;
  while(!flag){
    clear_screen();
    cout<<"enter the date you want to add food: ";cin>>date;
    if(date>=curdate+2){
      date--;
      while(!flag){
        clear_screen();
        cout<<"1)add food in "<<date+1<<endl<<"2)change date"<<endl<<"3)previous menu "<<endl;cin>>a;
        if(a=='1'){
        food*  temp=new food[(foodtablehos[date].number_of_foods)+1];
          for(int i=0;i<(foodtablehos[date].number_of_foods);i++)
          temp[i]=foodtablehos[date].foods[i];
          delete[] foodtablehos[date].foods;
          foodtablehos[date].foods=temp;
          foodtablehos[date].number_of_foods++;
          cout<<"food name: ";
          cin>>foodtablehos[date].foods[(foodtablehos[date].number_of_foods)-1].name;
          cout<<"food price: ";
          cin>>foodtablehos[date].foods[(foodtablehos[date].number_of_foods)-1].price;
          cout<<"number of foods: ";
          cin>>foodtablehos[date].foods[(foodtablehos[date].number_of_foods)-1].availablenumber;
          change_color_rgb(32, 252, 3);
          cout<<"food added succesfully!"<<endl;
          reset_color();
          delay(3000);
        }
        else if(a=='2')
          break;
          else if(a=='3')
          flag=true;
      }
    }
    else{
      change_color_rgb(150, 10, 15);
    cout<<"you can't add today and tomarrow's food"<<endl;
    reset_color();
    delay(2000);
  }
  }

}
void usermode(user* &users,date* &foodtable,date* &foodtablehos,int usernumber){
  int curdate;
  clear_screen();
  cout<<"enter today's date: ";cin>>curdate;
  char a;
  while(true){
    clear_screen();
    cout<<"1)reserve food"<<endl<<"2)top up wallet"<<endl<<"3)see reservations"<<endl<<"4)change password"<<endl<<"5)see profile"<<endl<<"6)log out"<<endl;cin>>a;
    if(a=='1'){
      char f;
      cout<<"1)central restaurant"<<endl<<"2)hostel restaurant"<<endl;cin>>f;
      if(f=='1')
      reservefood(users,foodtable,curdate,usernumber);
      else if(f=='2')
      reservefoodhos(users,foodtablehos,curdate,usernumber);
    }
    else if(a=='2'){
      change_color_rgb(150, 10, 15);
      cout<<"you have "<<users[usernumber].money<<" money"<<endl;
      reset_color();
      delay(1000);
      int m;
      cout<<"enter the amount of money you want to add to your wallet: ";cin>>m;
      users[usernumber].money+=m;
      change_color_rgb(32, 252, 3);
      cout<<"now you have "<<users[usernumber].money<<" money"<<endl;
      reset_color();
      delay(2000);
    }
    else if(a=='3'){
      for(int i=0;i<30;i++){
        change_color_rgb(252, 244, 3);
        cout<<i+1<<": ";
        if(users[usernumber].reserved[i].reserved==false){
          change_color_rgb(150, 10, 15);
          cout<<"no food had been reserved!"<<endl;
          reset_color();

        }
        else
          cout<<users[usernumber].reserved[i].myfood.name<<endl;
      }

      delay(2000);
      reset_color();
    }
    else if(a=='4'){
      char* newpass=new char[100];
      char* prepass=new char[100];
      int i=0;
      clear_screen();
      cout<<"enter your previous password: ";cin>>prepass;
      if(!(isequal(prepass,users[usernumber].pass))){
        change_color_rgb(150, 10, 15);
        cout<<"you're password is wrong"<<endl;
        reset_color();
        delay(2000);

      }
      else{
        cout<<"enter your new password";cin>>newpass;
          users[usernumber].pass=newpass;
          change_color_rgb(32, 252, 3);
          cout<<"you're password succesfully changed:)"<<endl;
          reset_color();
          delay(2000);
      }
      delete[] newpass;
      delete[] prepass;
    }
    else if(a=='5'){
      change_color_rgb(252, 244, 3);
    cout<<"first name: "<< users[usernumber].firstname<<endl;
    cout<<"last name: "<< users[usernumber].lastname<<endl;
    cout<<"student number: "<< users[usernumber].studentnumber<<endl;
    cout<<"phone number: "<< users[usernumber].phonenumber<<endl;
    cout<<"grade: "<< users[usernumber].grade<<endl;
    cout<<"study field: "<< users[usernumber].field<<endl;
    reset_color();
    delay(3000);
    }
    else if(a=='6'){
      userenter.entered=false;
      break;
    }
  }
  }
void reservefood(user* &users,date* &foodtable,int curdate,int usernumber){
    bool flag=false;
    while(!flag){
      int a;
      char b;
      clear_screen();
      cout<<"enter the date you want to reserve food: ";cin>>a;
      if(a>=curdate+2){
        while(true){
          clear_screen();
        cout<<"1)reserve"<<endl<<"2)see food list"<<endl<<"3)previous menu "<<endl;cin>>b;
        if(b=='1'){
          if(users[usernumber].reserved[a-1].reserved==true){
          change_color_rgb(150, 10, 15);
            cout<<"you have reserved today's food"<<endl;
            reset_color();
            delay(2000);
          }
          else if(foodtable[a-1].number_of_foods==0){
            change_color_rgb(150, 10, 15);
            cout<<"no food is available"<<endl;
            reset_color();
            delay(2000);
          }
          else{

            int n;
            for(int i=0;i<foodtable[a-1].number_of_foods;i++){
              change_color_rgb(252, 244, 3);
              cout<<i+1<<")"<<foodtable[a-1].foods[i].name<<" price: "<<foodtable[a-1].foods[i].price<<endl;
              reset_color();
            }
            cin>>n;
            char f;
            cout<<"1)complete meal"<<endl<<"2)half meal"<<endl;cin>>f;
            if(foodtable[a-1].foods[n-1].availablenumber==0){
              change_color_rgb(150, 10, 15);
              cout<<"this food is finished"<<endl;
              reset_color();
              delay(2000);
            }
            else if(users[usernumber].money>=foodtable[a-1].foods[n-1].price){
            users[usernumber].reserved[a-1].myfood=foodtable[a-1].foods[n-1];
            users[usernumber].reserved[a-1].reserved=true;
            foodtable[a-1].foods[n-1].availablenumber--;

            foodtable[a-1].foods[n-1].soldnumber++;
            if(f=='1')
              users[usernumber].money-=foodtable[a-1].foods[n-1].price;
            else if(f=='2')
              users[usernumber].money-=(foodtable[a-1].foods[n-1].price)/2;
            change_color_rgb(32, 252, 3);
            cout<<"food reseved!"<<endl;
            reset_color();
            delay(2000);
            flag=true;
            break;

          }
          else{
            change_color_rgb(150, 10, 15);
          cout<<"you don't have enough money"<<endl;
          reset_color();
          delay(2000);
        }
          }
        }
        if(b=='2'){
          change_color_rgb(252, 244, 3);
          if(foodtable[a-1].number_of_foods==0){
            change_color_rgb(150, 10, 15);
            cout<<"no food is in  the schedule"<<endl;
            reset_color();
          }
          else
          for(int i=0;i<foodtable[a-1].number_of_foods;i++)
            cout<<"("<<foodtable[a-1].foods[i].name<<") ";
          reset_color();
          delay(3000);
        }
        if(b=='3'){
          flag=true;
          break;
        }
        }
      }
      else{
        change_color_rgb(150, 10, 15);
        cout<<"you can't reserve food in this day"<<endl;
        reset_color();
        delay(2000);
      }
    }
  }
void reservefoodhos(user* &users,date* &foodtablehos,int curdate,int usernumber){
      bool flag=false;
      while(!flag){
        int a;
        char b;
        clear_screen();
        cout<<"enter the date you want to reserve food: ";cin>>a;
        if(a>=curdate+2){
          while(true){
            clear_screen();
          cout<<"1)reserve"<<endl<<"2)see food list"<<endl<<"3)previous menu "<<endl;cin>>b;
          if(b=='1'){
            if(users[usernumber].reserved[a-1].reserved==true){
            change_color_rgb(150, 10, 15);
              cout<<"you have reserved today's food"<<endl;
              reset_color();
              delay(2000);
            }
            else if(foodtablehos[a-1].number_of_foods==0){
              change_color_rgb(150, 10, 15);
              cout<<"no food is available"<<endl;
              reset_color();
              delay(2000);
            }
            else{
              int n;
              for(int i=0;i<foodtablehos[a-1].number_of_foods;i++){
                change_color_rgb(252, 244, 3);
                cout<<i+1<<")"<<foodtablehos[a-1].foods[i].name<<" price: "<<foodtablehos[a-1].foods[i].price<<endl;
                reset_color();
              }
              cin>>n;
              char f;
              cout<<"1)complete meal"<<endl<<"2)half meal"<<endl;cin>>f;
              if(foodtablehos[a-1].foods[n-1].availablenumber==0){
                change_color_rgb(150, 10, 15);
                cout<<"this food is finished"<<endl;
                reset_color();
                delay(2000);
              }
              else if(users[usernumber].money>=foodtablehos[a-1].foods[n-1].price){
              users[usernumber].reserved[a-1].myfood=foodtablehos[a-1].foods[n-1];
              users[usernumber].reserved[a-1].reserved=true;
              foodtablehos[a-1].foods[n-1].availablenumber--;

              foodtablehos[a-1].foods[n-1].soldnumber++;
              if(f=='1')
                users[usernumber].money-=foodtablehos[a-1].foods[n-1].price;
              else if(f=='2')
                users[usernumber].money-=(foodtablehos[a-1].foods[n-1].price)/2;
              change_color_rgb(32, 252, 3);
              cout<<"food reseved!"<<endl;
              reset_color();
              delay(2000);
              flag=true;
              break;

            }
            else{
              change_color_rgb(150, 10, 15);
            cout<<"you don't have enough money"<<endl;
            reset_color();
            delay(2000);
          }
            }
          }
          if(b=='2'){
            change_color_rgb(252, 244, 3);
            if(foodtablehos[a-1].number_of_foods==0){
              change_color_rgb(150, 10, 15);
              cout<<"no food is in  the schedule"<<endl;
              reset_color();
            }
            else
            for(int i=0;i<foodtablehos[a-1].number_of_foods;i++)
              cout<<"("<<foodtablehos[a-1].foods[i].name<<") ";
            reset_color();
            delay(3000);
          }
          if(b=='3'){
            flag=true;
            break;
          }
          }
        }
        else{
          change_color_rgb(150, 10, 15);
          cout<<"you can't reserve food in this day"<<endl;
          reset_color();
          delay(2000);
        }
      }
    }

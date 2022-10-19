/* **********AUTHOR:-CHETAN KUMAR REDDY NELLORE********
   **********ROLLNO:-2003316****************
   **********BRANCH:-MnC*************
   */
#include<bits/stdc++.h>
using namespace std;
//This function prints the main operations of the program
void main_menu()
{
  cout<<"               MAIN MENU"<<endl;
  cout<<"     1.CONFIGURE"<<endl;
  cout<<"     2.USE"<<endl;
  cout<<"     3.EXIT"<<endl;
}
//This function prints the operations present in the configure module
void configure_menu()
{
  cout<<endl<<"            CONFIGURE MODULE"<<endl;
  cout<<"     1.Add new locker entry"<<endl;
  cout<<"     2.Delete a locker entry"<<endl;
  cout<<"     3.Return"<<endl;
}
//checks whether a number is prime or not
int is_prime(long long int L)
{
    if (L == 1) {
        return 0;
    }
    long long int i = 2;
    // This loop will run from 2 to int(sqrt(L))
    while (i*i <= L) {
        // Check if i divides L
        if (L% i == 0) {
            // This means that L has a factor in between 2 and sqrt(L),so not a prime number
            return 0;
        }
        i += 1;
    }
    return 1;
}
//This function is used to generate k number of primes whose product is strictly greater than Locker key L
void construct_k_primes(vector<long long int>&p,int k,long long int L)
{
  long long int n=ceil(pow(L,1.0/k));//k-th root of L
  while(k>0)
  {
    n=n+1;
    if(is_prime(n))
    {
        p.push_back(n);//pushing k primes greater than k-th root of L
        k--;
    }
  }

}
//This function compares characters in two strings and check whether both are same or not
int compare(char locker_id[],string line)
{
      int flag=0;
      if(line[0]==locker_id[0])
      {
        flag++;
      }
      if(line[1]==locker_id[1])
      {
        flag++;
      }
      if(line[2]==locker_id[2])
      {
        flag++;
      }
      if(line[3]==locker_id[3])
      {
        flag++;
      }
      if(line[4]==locker_id[4])
      {
        flag++;
      }
      if(flag==5)
      {
          return 1;
      }
      return 0;
}
//This function checks whether the entered lockerid is present in the textfile or not
int is_present(char locker_id[])
{
  fstream fin;
  fin.open("config.txt",ios::in);
  if(!fin)
  {
      fin.close();
      return 0;
  }
  string line;
  while(getline(fin,line))
  {
      int flag=compare(locker_id,line);//checks if two lockerids are same or not
      if(flag==1)
      {
        fin.close();
        return 1;
      }
  }
  fin.close();
  return 0;
}
//This function calls the is_present function and if id is not present in the text file it adds the entry to the text file and prints the user keys on the screen
void Add()
{
  char locker_id[5];
  int k;
  long long int L;
  cout<<"Enter Lockerid:";
  cin>>locker_id;
  if(is_present(locker_id))
    {
      cout<<"Duplicate entry....This locker id is already present..."<<endl;
      return ;
    }
  cout<<"Enter Number of users:";
  cin>>k;
  cout<<"Enter the 10 digit Locker key L:";
  cin>>L;
  fstream fout;
  fout.open("config.txt",ios::app);
  vector<long long int>p;
  long long int u[k];
  construct_k_primes(p,k,L);
  fout<<locker_id<<" "<<k<<" ";
  for(int i=0;i<k;i++)
    fout<<p[i]<<" ";
  fout<<"\n";
  fout.close();
  cout<<"The user keys generated are:"<<endl; 
  for(int i=0;i<k;i++)
  {
  u[i]=L%p[i];
  if(u[i]==0)
    cout<<"0000"<<"  ";
  else if(u[i]/10==0)
    cout<<"000"<<u[i]<<"  ";
  else if(u[i]/100==0)
    cout<<"00"<<u[i]<<"  ";
  else if(u[i]/1000==0)
    cout<<"0"<<u[i]<<"  ";
  else
    cout<<u[i]<<"  ";

  }
}
/*This function calls the is_present function and if id is present in the text file it deletes the id
  for that we create a temporary text file and stores the data of the lockerid's expect  the data of the entered
  lockerid and rename the temporary text file.*/
void Delete()
{
  char locker_id[5];
  cout<<"Enter the locker id:";
  cin>>locker_id;
  fstream fp;
  fp.open("config.txt",ios::in);
  if(!fp)
  {
    cout<<"File can not be read.."<<endl;
    cout<<"Deletion operation failed...."<<endl;
    fp.close();
    return ;
  }
  if(!is_present(locker_id))
  {
    cout<<"This locker id is not present in the file"<<endl;
    cout<<"Deletion operation failed....."<<endl;
    fp.close();
    return ;
  }
  fstream fp1;
  fp1.open("temp.txt",ios::out);
  string line;
  while(getline(fp,line))
  {
      if(!compare(locker_id,line))
          fp1<<line<<endl;
  }
  fp.close();
  fp1.close();
  remove("config.txt");
  rename("temp.txt","config.txt");
  cout<<"Deletion operation Successful...."<<endl;
}
//This function prints the opeartions present in the configure module and takes the choice as input to perform which operation
void configure()
{
  while(1)
  {
  configure_menu();
  int flag=0;
  cout<<"\n"<<"Mention your prefence(1/2/3):";
  int choice;
  cin>>choice;
  switch (choice)
  {
  case 1:
  {
    Add();
    break;
  }
  case 2:
  {
    Delete();
    break;
  }
  case 3:
  {
    cout<<"Returning to the main menu...."<<endl;
    flag=1;
    break;
  }
  default:
  {
    cout<<"Terminating the program....Enter a valid integer"<<endl;
    exit(1);
    break;
  }
  }
  if(flag==1)
  {
    break;
  }
  }
}
//This function regenerates the locker key L from the data of user keys and prime numbers using Chinese remainder theorem.
long long int find_L(vector<long long int>&p, long long int u[], int k)
{
    long long int L = 1;
    while (true)
    {
        // Checking if the remainder of L and p[j] is u[j]
        int j;
        for (j=0; j<k; j++ )
            if (L%p[j] != u[j])
              break;
        // If all remainders are matched, we found L
        if (j == k)
            return L;
        // Else try next number
        L++;
    }
    return L;
}
/*This function takes lockerid as input and checks whether the lockerid is present in the text file or not.
  If it is present it takes the secondary user keys as input.Using these keys and prime numbers in the
  text file we regenerate the key L.*/
void Use()
{
  char lockerid[5];
  cout<<"Enter Locker id:";
  cin>>lockerid;
  fstream fp;
  fp.open("config.txt",ios::in);
  if(!fp)
  {
    cout<<"Text has no data in it"<<endl;
    fp.close();
    return;
  }
  if(!is_present(lockerid))
  {
    cout<<"This lockerid is not present in the text file"<<endl;
    fp.close();
    return ;
  }
  string line;
  int line_count=1;
  while(getline(fp,line))
  {
      if(compare(lockerid,line))
          break;
      line_count++;
  }
  vector<long long int>p;
  int k=0;
  int i=6;
  while(line[i]!=' ')
  {
    k=k*10+(line[i]-'0');
    i++;
  }
  i++;
  int temp=0;
  while(line[i]!='\0')
  {
      if(line[i]!=' ')
      {
        temp=temp*10+(line[i]-'0');
      }
      else
      {
          p.push_back(temp);
          temp=0;
      }
      i++;
  }
  long long int u[k];
  cout<<"Enter the user keys in the respective order"<<endl;
  for(i=0;i<k;i++)
  {
    cout<<"key["<<i+1<<"]=";
    cin>>u[i];
  }
  long long int L=find_L(p,u, k);
  cout<<"The Locker key L for this lockerid is "<<L<<endl;
}
//main function
int main()
{
  //menu driven program
  while(1)
  {
    main_menu();
    cout<<"\n"<<"Mention your prefence(1/2/3):";
    int choice;
    cin>>choice;
    switch (choice)
  {
      case 1:
    {
      configure();
      break;
    }
    case 2:
    {
      Use();
      break;
    }
    case 3:
    {
      cout<<"     EXITING THE PROGRAM.....THANK YOU!!..."<<endl;
      exit(1);
    }
    default:
    {
      cout<<"     Terminating the program....Enter a valid integer"<<endl;
      exit(1);
    }
  }
  }

  return 0;
}

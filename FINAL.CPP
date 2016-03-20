#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<process.h>
#include<ctype.h>
int done=0;
char * Upper(char *str)
{
    int i = 0;
    int len = 0;

    len = strlen(str);
    char *newstr=new char[len+1];

    for(i = 0; str[i]; i++)
    {
       newstr[i] = toupper(str[i]);
    }
    //terminate string
    newstr[i]= '\0';
    return  newstr;
}
int conversion(char *s){
	s=Upper(s);
	int total=0;
	for(int i=0;s[i]!=NULL;i++)	total+=s[i];
	return total;
}

//To Draw a line of *
void lines(){
	for(int i=0;i<80;i++)	cout<<"*";
	cout<<endl;
}
//To Check if the Phone Number entered is right
int ValidateNumber(char* s){
	int x=strlen(s);
	if (x==10) return 1;
	else return 0;
}
//To check if the Email entered is right
int ValidateEmail(char *s){
	for(int i=0,count=0;s[i]!=NULL;i++){
		if(s[i]=='@'||(s[i]=='.')) count++;
	}
	if(count>=2) return 1;
	else return 0;
}
//Password Modification
void ModifyPassword(){
	char* p;
	remove("pwd.txt");
	fstream ofs;
	ofs.open("pwd.txt",ios::out|ios::trunc);
	cout<<"\n\tEnter the new password\n";
	gets(p);
	ofs<<p;
	ofs.close();
}
//Checks if the password entered is correct
int CheckPassword(char* a){
	char *p;
	ifstream ifs;
	ifs.open("pwd.txt",ios::in);
	ifs>>p;
	ifs.close();
	if(strcmp(a,p)==0)	return 1;  //password entered is right
	else	return 0;
}
//Create password for the first time
void CreatePassword(){
	if(done==0){
		char* p="admin"; //default password
		fstream ofs;
		ofs.open("pwd.txt",ios::out);
		ofs<<p;
		ofs.close();
		done++;
	}
}

int substrcon(char str[], int len){
	int total=0;

	str=Upper(str);
	for(int i=0;i<len;i++)
	total+=(int) str[i];
	return total;
}

//student class
class student{
	student *lchild;
	student *rchild;
	friend class tree;
	public:
	char name[25];
	char phone[11];
	char email_id[35];
	int data;
	char roll[3];
	void askDetails();
	void showDetails();
	void deleteStudent(char[]);
	void listOfStudents();
	void modifyStudent(char[]);

};

class tree{
	public:
	student *root;
	tree();
	student* create(char *,char *,char *,int);
	void searchPhone(student* ,int);
	void searchEmail(student* ,int);
	void searchName(student* ,int,int);
	void searchRoll(student *,int,int);
	int searching(char *);
	void SearchEngine();
	void inorder(student*);
	void read();
	void iter(student *,int);

};

void student::askDetails(){
	clrscr();
	int x=0;
	cout<<"\n\n\n\tEnter Name of the student:\t";
	cin>>name;
	data=conversion(name);
	cout<<"\n\n\tEnter roll number of the student: \t";
	cin>>roll;
	while(x==0){
		cout<<"\n\n\n\tEnter Phone number of the student:\t";
		cin>>phone;
		x=ValidateNumber(phone);
	}
	x=0;
	while(x==0){
		cout<<"\n\n\n\tEnter Email id of the student:\t";
		cin>>email_id;
		x=ValidateEmail(email_id);
	}
}
void student::showDetails(){
	clrscr();
	lines();
	cout<<"\n\n\n\tRoll number of the student:\t";
	cout<< roll<<endl;
	cout<<"\n\n\n\tName of the student:\t";
	cout<< name<<endl;
	cout<<"\n\n\n\tPhone number of the student:\t";
	cout<<phone<<endl;
	cout<<"\n\n\n\tEmail id of the student:\t";
	cout<<email_id<<endl;
	cout<<"\nData value:\t";
	cout<<data<<endl;
	lines();
}
tree::tree(){
	root=NULL;
}
student* tree::create(char *name1, char* phone1 ,char *email_id1,int data1){
	student *p,*n;
	n=new student;
	strcpy(n->name,name1);
	strcpy(n->phone,phone1);
	strcpy(n->email_id,email_id1);
	n->data=data1;
	n->lchild=NULL;
	n->rchild=NULL;
	if(root== NULL){
		root=n;
		n->lchild=NULL;
		n->rchild=NULL;
		return root;
	 }
	p=root;
	while(1){
	if(n->data<p->data){
		if(p->lchild==NULL){
			p->lchild=n;
			n->lchild=NULL;
			n->rchild=NULL;
			return root;
		}
		else
			p=p->lchild;
	}
	else{
		if(p->rchild==NULL){
			p->rchild=n;
			n->rchild=NULL;
			n->lchild=NULL;
			return root;
		}
		else
			p=p->rchild;
		}
       }
}


void creation(){
	student s;
	s.askDetails();
	ofstream ofs;
	ofs.open("details.txt",ios::ate|ios::binary);
	ofs.write((char *) &s,sizeof(student));
	ofs.close();
	cout<<"\nCreation of new student successfully completed\n";
}

void tree::read(){
	student s;
	student *n;
	ifstream ifs;
	ifs.open("details.txt",ios::binary);
	ifs.seekg(0,ios::beg);
	while(ifs.read((char*) &s,sizeof (student)))
		create(s.name,s.phone,s.email_id,s.data);
	ifs.close();
}
void student:: deleteStudent(char* n){
	student s;
	ifstream ifs;
	ofstream ofs;
	ifs.open("details.txt",ios::binary);
	if(!ifs)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	ofs.open("Temp.txt",ios::binary);
	ifs.seekg(0,ios::beg);
	while(ifs.read((char *) &s, sizeof(student)))
	{
		if(strcmp(n,s.name))
			ofs.write((char *) &s, sizeof(student));
	}
	ifs.close();
	ofs.close();
	remove("details.txt");
	rename("Temp.txt","details.txt");
	cout<<"\n\n\tRecord Deleted..";
}

void student::listOfStudents(){
	student s;
	ifstream ifs;
	ifs.open("details.txt",ios::binary);
	if(!ifs)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"================================================\n";
	cout<<"Roll\t\tNAME\tPHONE NUMBER\tEMAIL ID\n";
	cout<<"================================================\n";
	while(ifs.read((char *) &s, sizeof(student)))
		cout<<"1602-13-737-"<<s.roll<<"\t"<<s.name<<"\t"<<s.phone<<"\t"<<s.email_id<<endl;
	ifs.close();
}

void student::modifyStudent(char *n)
{
	int found=0,pos;
	student s;
	fstream File;
	int n1=conversion(n);
	File.open("details.txt",ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not open!";
		return;
	}
	while(File.read((char *) &s, sizeof(student)) && found==0){
		if(s.data==n1){
			s.showDetails();
			cout<<"\n\nEnter The New Details of student"<<endl;
			s.askDetails();
			pos=(-1)*sizeof(student);
			File.seekp(pos,ios::cur);
			File.write((char *) &s, sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//The Menu Option Of the starting Page
void displaymenu(){
	cout<<"\n\n\n\t\tEnter 1:\t To access admin\n";
	cout<<"\n\n\n\t\tEnter 2:\t Others\n";
	cout<<"\n\n\n\t\tEnter 3:\t Exit\n";
}
// Menu Option For Admin Page
void adminmenu(){
	clrscr();
	cout<<"\n\n\t\tEnter 1:\tModify the password\n";
	cout<<"\n\n\t\tEnter 2:\tAdd new student\n";
	cout<<"\n\n\t\tEnter 3:\tRemove student\n";
	cout<<"\n\n\t\tEnter 4:\tModify details of the student\n";
	cout<<"\n\n\t\tEnter 5:\tDisplay all details of the student\n";
	cout<<"\n\n\t\tEnter 6:\tReturn back to Main menu\n";
	cout<<"\n\n\t\tEnter 7:\tExit\n";
}
// Menu for Others
void othersmenu(){
	clrscr();
	cout<<"\n\n\n\tEnter 1:\tSearch Engine\n";
	cout<<"\n\n\n\tEnter 2:\tReturn Back to Main Menu\n";
}

int found=0;
void tree::searchPhone(student *r,int word){
	if(r!=NULL&&(found==0)){
		searchPhone(r->lchild,word);
		if(conversion(r->phone)==word){
			found=1;
			r->showDetails();
		}
		searchPhone(r->rchild,word);
	}
}
void tree::searchEmail(student *r,int word){
	if(r!=NULL&&(found==0)){
		searchEmail(r->lchild,word);
		if(conversion(r->email_id)==word){
			found=1;
			r->showDetails();
		}
		searchEmail(r->rchild,word);
	}
}
int lock[20];
int countc=0;
void tree::searchName(student *r,int word,int length){
	int x;
	if(r!=NULL&&(found==0)){
		searchName(r->lchild,word,length);
		if(r->data==word){
			found=1;
			r->showDetails();
		}
		x=substrcon(r->name,length);
		if(x==word){
			lock[countc]=r->data;
			cout<<++countc<<".\t"<<r->name<<endl;
		}
		searchName(r->rchild,word,length);
	}
}
void tree::searchRoll(student *r,int word,int length){
	int x;
	if(r!=NULL&&(found==0)){
		searchRoll(r->lchild,word,length);
		if(conversion(r->roll)==word){
			found=1;
			r->showDetails();
		}
		x=substrcon(r->roll,length);
		if(x==word){
			lock[countc]=r->data;
			cout<<++countc<<".\t1602-13-737-"<<r->roll<<"\t"<<r->name<<endl;
		}
		searchRoll(r->rchild,word,length);
	}
}
int ValidateRoll(char *s){
	if((s[0]=='6')||(s[0]==1)&&(strlen(s)<=3))	return 1;
	else return 0;
}
//Check if its a phone number
int is_number(char *s){
	if(s[0]=='7'||s[0]=='8'||s[0]=='9')	return 1;
	return 0;
}

int tree::searching(char *s){
	int length=strlen(s);
	int word=conversion( s);
	int is_number1=is_number(s);
	int is_email=ValidateEmail(s);
	int is_roll=ValidateRoll(s);
	if(is_number1==1)	searchPhone(root,word);
	else if(is_email==1)	searchEmail(root,word);
	else if(is_roll==1)	searchRoll(root,word,length);
	else 			searchName(root,word,length);
	if(found==1){
		found=0;
		return 1;
	}
	return 0;

}

void tree::iter(student *r,int x){
	   if(r!=NULL){
	   iter(r->lchild,x);
	   if(r->data==x){
		r->showDetails();
		found=1;
	    }
	   iter(r->rchild,x);
	}
}

void tree::SearchEngine(){
	char* search;
	cout<<"\n\n\n\n";
	int opt;
	clrscr();
	lines();
	cout<<"\n\tENTER KEYWORD\n\n\n";
	lines();
	cin>>search;
	int x=searching(search);
	if(x!=1&&(countc==0))
	cout<<"\t\t KEY NOT FOUND";
	else if(countc>0&&x!=1){
		cout<<"\nEnter option of the following names:\t";
		cin>>opt;
		opt--;
		iter(root,lock[opt]);
		countc=0;
	}
}
void main(){
	char *a,*n;
	int ch=0,ch2=0;
	CreatePassword();
	clrscr();
	student s;
	tree t;
	while(ch!=3){
		displaymenu();	//to display menu
		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter the Password\n";
				cin>>a;
				if(CheckPassword(a)){
				       while(ch2!=7){
						adminmenu();
						cin>>ch2;
						switch(ch2){
							case 1: ModifyPassword();
								break;
							case 2:
								creation();
								getch();
								break;
							case 3:
								cout<<"\n\n\t Enter the name of the student\n";
								gets(n);
								s.deleteStudent(n);
								break;
							case 4:
								cout<<"\n\n\t Enter the name of the student\n";
								gets(n);
								s.modifyStudent(n);
								break;
							case 5:
								s.listOfStudents();
								cout<<"\n\n Enter any key to go back\n";
								getch();
								break;

							case 6:
								main();
								break;
							case 7:
								exit(0);
								break;

						}
				       }
				}
				else	cout<<"\n\nPassword entered incorrectly";
				break;
			case 2:
				t.read();
				ch2=0;
				while(ch2!=2){
					othersmenu();
					cin>>ch2;
					switch(ch2){
						case 1:
							t.SearchEngine();
							getch();
							break;
						case 2:
							main();
						default:
							cout<<"\nInvalid Choice\n";
					}
				}
				break;
			case 3:
				cout<<"\n\nExiting..";
				exit(1);
				break;
			default:
				cout<<"\n\n \n\n  Invalid Choice";
		}
	}
	getch();
}
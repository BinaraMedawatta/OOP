#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <cmath>

using namespace std;

const int MAXSUBJECTS = 10;
const int MAXSTUDENTS = 100;

struct student{
    
        string stdId;
        int mark;
        char grade;
};

class subject{

    private:
        string subCode;
        string indexNum;
        int noOfStudents;
        int gradeCount[5];
        float avg;
        float stdDev;
        student stdArray[MAXSTUDENTS];

    public:
        
        void setSubData(string,int);
        string getSubData();
        void setStdData(int,string,int);
        string getStdId();
        char getGrade(int);
        void displaySub();
        void displayStd(string);
        float findAvg();
        float findStdDev();
        void displaySubSum();
        friend void saveSubSum(subject []);
};

void subject::setSubData(string code,int num){
    subCode = code;
    noOfStudents = num;
}

string subject::getSubData(){
    return subCode;
}

void subject::setStdData(int j,string code,int mark){
    stdArray[j].mark=mark;
    stdArray[j].stdId=code;
    stdArray[j].grade=getGrade(mark);
}
string subject::getStdId(){

    for(int i=0;i<noOfStudents;i++){
        return (stdArray[i].stdId);
    }
}

char subject::getGrade(int mark){
    
    if(mark>=70){
        gradeCount[0]+=1;
        return 'A';
    }else if(mark>=55){
        gradeCount[1]+=1;
        return 'B';
    }else if(mark>=40){
        gradeCount[2]+=1;
        return 'C';
    }else if(mark>=30){
        gradeCount[3]+=1;
        return 'D';
    }else if(mark>=20){
        gradeCount[3]+=1;
        return 'E';
    }else{
        gradeCount[4]+=1;
        return 'F';
    }
}

void subject::displaySub(){

    cout<<"Details of Subject:"<<subCode<<endl;
    cout<<"Number of Students:"<<noOfStudents<<endl<<endl;
    cout<<"Index Number"<<"   "<<"Marks"<<"   "<<"Grade"<<endl<<endl;
    for(int j=0;j<noOfStudents;j++){
        cout<<stdArray[j].stdId<<"        "<<stdArray[j].mark<<"      "<<stdArray[j].grade<<endl;
    }
}

float subject::findAvg(){
    float sum;
    for(int i=0;i<noOfStudents;i++){
        sum = sum + (float)stdArray[i].mark;
    }
    avg = sum/noOfStudents;
    return avg;
}

float subject::findStdDev(){
    float sum=0.0,avg=findAvg();
    for(int i=0; i<noOfStudents; i++){
        sum += pow((float)stdArray[i].mark - avg, 2);
    }

    stdDev = sqrt(sum/noOfStudents);
    return stdDev;
}

void subject::displaySubSum(){
    cout<<"\t\t"<<"Summary of Subject :"<<subCode<<endl<<endl;
    cout<<"Number of Students :"<<noOfStudents<<endl;
    cout<<"Average            :"<<findAvg()<<endl;
    cout<<"Standard Deviation :"<<findStdDev()<<endl;;
    cout<<" __________________________________________"<<endl;
    cout<<"| Grade |  A  |   B  |   C  |   D  |   F   |"<<endl;
    cout<<"|_______|_____|______|______|______|_______|"<<endl;
    cout<<"| Count |  "<<gradeCount[0]<<"  |   "<<gradeCount[1]<<"  |   "<<gradeCount[2]<<"  |   "<<gradeCount[3]<<"  |   "<<gradeCount[4]<<"   |   "<<endl;
    cout<<"|_______|_____|______|______|______|_______|"<<endl;
}

void subject::displayStd(string code){
    
    for(int i=0;i<noOfStudents;i++){
        if(code.compare(stdArray[i].stdId)==0){
            cout<<subCode<<"     "<<stdArray[i].mark<<"       "<<stdArray[i].grade<<endl;
        }    
    }
}

void saveSubSum(subject arr[]){
    ofstream myfile;
	myfile.open ("Summary.txt");
    for(int i=0;i<MAXSUBJECTS;i++){
        if(arr[i].subCode.length()==7){
            myfile<<arr[i].subCode<<" "<<arr[i].noOfStudents<<" ";
            for(int j=0;j<4;j++){
                myfile<<char(j+65)<<" "<<((float(arr[i].gradeCount[j])/arr[i].noOfStudents)*100)<<"% ";
            }
            myfile<<"F"<<" "<<((float(arr[i].gradeCount[4])/arr[i].noOfStudents)*100)<<"%"<<endl<<endl;
        }
    }  
    myfile.close(); 
    cout<<"Subject Summaries Saved to Summary.txt"<<endl; 
}


subject list[10];

int main(){
    
    string line,code;
    int n,option,flag;
    ifstream in ("marks.txt");
    
    if(in.is_open()){
        int i=-1,j=0;
        while(getline(in,line)){

            
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> tokens(beg, end);
            stringstream num(tokens[1]);
            num >> n;
            
            if(tokens[0].length()==7){
                j=0;
                i++;
                list[i].setSubData(tokens[0],n);
                
            }else if(tokens[0].length()==8){
                list[i].setStdData(j,tokens[0],n);
                j++;
            }
        }
    
    }

    do{
        cout<<"\t\t\t ____________________________"<<endl;
        cout<<"\t\t\t|"<<"   .....MAIN MENU.....      |"<<endl<<"\t\t\t|                            |"<<endl;
        cout<<"\t\t\t|"<<"1.Display Subject           |"<<endl;
        cout<<"\t\t\t|"<<"2.Display Student           |"<<endl;
        cout<<"\t\t\t|"<<"3.Display Subject Summary   |"<<endl;
        cout<<"\t\t\t|"<<"4.Save Summaries            |"<<endl;
        cout<<"\t\t\t|"<<"5.Exit                      |"<<endl;
        cout<<"\t\t\t|____________________________|"<<endl<<endl;
        cout<<"\t\t"<<"Enter Your Option:";
        cin>>option;
        cout<<endl;
        
        switch(option){

            case 1:
                try{
                    cout<<"Enter the Subject Code:";
                    cin>>code;
                    if(code.length()!=7){
                        throw 1;
                    }
                    cout<<endl;
                    flag=1;
                    for(int i=0;i<MAXSUBJECTS;i++){
                        if(code.compare(list[i].getSubData())==0){
                            flag=0;
                            list[i].displaySub();
                            break;
                        }
                    }
                    if(flag==1){
                        cout<<"ERROR!Subject Not Found"<<endl;
                        flag=0;
                    }
                    cout<<endl;
                }
                catch (int x){
                    cout<<"ERROR!Invalid Subject Code"<<endl;
                }
                system("pause");
                break;
            case 2:
                try{
                    cout<<"Enter the Index Number:";
                    cin>>code;
                    if(code.length()!=8){
                        throw 1;
                    }
                    cout<<endl;
                    cout<<"Subject"<<"    "<<"Marks"<<"     "<<"Grade"<<endl<<endl;
                    for(int i=0;i<MAXSUBJECTS;i++){
                        list[i].displayStd(code);
                    }
                    cout<<endl;
                    
                }
                catch (int x){
                    cout<<"ERROR!Invalid Index Number"<<endl;
                }
                system("pause");
                break;
            case 3:
                try{
                    cout<<"Enter the Subject Code:";
                    cin>>code;
                    if(code.length()!=7){
                        throw 1;
                    }
                    cout<<endl;
                    for(int i=0;i<MAXSUBJECTS;i++){
                        if(code.compare(list[i].getSubData())==0){
                            list[i].displaySubSum();
                            break;
                        }
                    }
                    cout<<endl;
                }
                catch (int x){
                    cout<<"ERROR!Invalid Subject Code"<<endl;
                }
                system("pause");
                break;
            case 4:
                saveSubSum(list);
                system("pause");
                break;
            case 5:
                exit(0);
        }   
    }while(1);

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>
#include <iomanip>
using namespace std;

class Results{
	
	float average;
	int total;
	int i;
	
	public : 
		int marks[100][3];	// index, mark, grade
		string subjectCode;
		int count;
		int gradeC[5];	// Grades count A,B,C,D;
		Results();
		void getData(int id, int mark);	
		void findAverage();	
		void putData();
		void calculateSD();
		void getGradesCount();
		
};

Results :: Results(){
	i=0;
	count=0;
	average=0;
	total=0;
	gradeC[5] = {0};
}

void Results :: getGradesCount(){
	
	for(int j=0; j<count; j++){
		if('A'==(char)marks[j][2]) gradeC[0]++;
		else if('B'==(char)marks[j][2]) gradeC[1]++;
		else if('C'==(char)marks[j][2]) gradeC[2]++;
		else if('D'==(char)marks[j][2]) gradeC[3]++;
		else gradeC[4]++;
	}
	
}

char getGrade(int n){
	if(n>=70) return 'A';
	else if(n>=55) return 'B';
	else if(n>=40) return 'C';
	else if(n>=30) return 'D';
	else return 'F';
}

void Results :: getData(int id, int mark){
	marks[i][0] = id;
	marks[i][1] = mark;
	marks[i][2] = getGrade(mark);
	i++;
}

void Results :: findAverage(){
	total=0;
	for(int j=0; j<count; j++){
		total += marks[j][1];
	}
	average = (float)(total)/count;
	cout << "Average : " << average << endl;
}

void Results :: calculateSD(){
	float std=0.0;
	for(int j=0; j<count; j++){
		std += pow(marks[j][1] - average, 2);
	}
	
	float sd = sqrt(std/count);
	
	cout << "Standard Deviation : " << sd << endl;
        
}

void Results :: putData(){
	cout << subjectCode << endl;
	for(int j=0; j<count; j++){
		cout << marks[j][0] << " " << marks[j][1] << " " << (char)marks[j][2] << endl;
	}
}

int main(){
	string line;
	int err;
	int n=0;
	int j=-1;
	int x, m;
	string subject;
	string subCode;
	Results sub[10];
	
	label:
		
	int sel;
	string filename_i = "subjdata.txt";
	string filename_o = "Summary.txt";
		
	cout << "Select," << endl;
	cout << "0. to use default file (subjdata.txt)" << endl;
	cout << "1. to enter a file name." << endl;
	cin >> sel;
	
	if(sel){
		cout << "Enter file name : ";
		cin >> filename_i;
	}
	
	ifstream myfile (filename_i);
	
	if (myfile.is_open()){
	
		while(getline(myfile,line)){
	
			if(n==0){	// Getting the subject code
    			j++;
				istringstream buf(line);
    			istream_iterator<string> beg(buf), end;
    
				vector<string> tokens(beg, end);
				stringstream num(tokens[1]);	// tokens[1] = marks count
				
				num >> n;	// casting string to int
				
				sub[j].subjectCode = tokens[0];
				sub[j].count = n;

				n++;
			}
			
			else{	// Getting the marks and student numbers
				istringstream buf(line);
    			istream_iterator<string> beg(buf), end;
    
				vector<string> tokens(beg, end);
				
				stringstream mark(tokens[1]);
				stringstream num(tokens[0]);
				
				mark >> m;	// casting string to int
				num >> x;
				
				sub[j].getData(x, m);
			}
			n--;
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file, enter valid file name" << endl; 
		goto label;
	}

	do{
		cout << "+----------------------------+" << endl;
		cout << "| 1. Display Subject         |" << endl;
		cout << "| 2. Display Student         |" << endl;
		cout << "| 3. Display Subject Summary |" << endl;
		cout << "| 4. Save Summaries          |" << endl;
		cout << "| 5. Exit Program            |" << endl;
		cout << "+----------------------------+" << endl;
		
		cout << "Enter your Choice : ";	
		cin >> x;
		
		switch(x){
			case 1 :
				cout << "Enter 7 character Subject Code : ";
				cin >> subCode;
				err=1;
				
				for(int k=0; k<j+1; k++){
					if(sub[k].subjectCode==subCode){
						sub[k].putData();
						err=0;
						break;
					}
				}
				
				if(err){
					cout << "Enter valid Subject Code" << endl;
					err=0;
				}
				
				break;
			
			case 2 : 
				int stdNo;
				cout << "Enter Student Number : ";
				cin >> stdNo;
				
				for(int k=0; k<j+1; k++){
					for(int l=0; l<sub[k].count; l++){
						if(stdNo==sub[k].marks[l][0])
							cout << sub[k].subjectCode << " " << sub[k].marks[l][1] << " " << (char)sub[k].marks[l][2] << endl;
					}
				}
				break;
				
			case 3 : 
				cout << "Enter 7 character Subject Code : ";
				cin >> subCode;
				
				err=1;
				
				for(int k=0; k<j+1; k++){
					if(sub[k].subjectCode==subCode){
						sub[k].findAverage();
						sub[k].calculateSD();
						sub[k].getGradesCount();
						err=0;
						break;
					}
				}
				
				if(err){
					cout << "Enter valid Subject Code" << endl;
					err=0;
				}
				
				break;
				
			case 4 :
				cout << "Select," << endl;
				cout << "0. Save to default file (Summary.txt)" << endl;
				cout << "1. Save to new file" << endl;
				cin >> sel;
				
				if(sel){
					cout << "Enter new file name : ";
					cin >> filename_o;
				}				
				
				ofstream myfile_O;
				myfile_O.open (filename_o);
				
				for(int k=0; k<j+1; k++){
					myfile_O << sub[k].subjectCode << " " << sub[k].count << " ";
					sub[k].getGradesCount();
					myfile_O << setprecision(2) << fixed;
					for(int q=0; q<5; q++){
						myfile_O << (char)(q+65) << " " << (((float)sub[k].gradeC[q])/sub[k].count)*100 << "%" << " ";	
					}
					
					myfile_O << endl;
				}
				
				myfile_O.close();
				
				cout << "Saved summaries to " << filename_o << " file" << endl;
				break;
								
		}
	}while(x!=5);
	
	return 0;
}

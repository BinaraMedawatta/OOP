#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>
using namespace std;

class Results{
	int marks[100][3];	// index, mark, grade
	float average;
	int total;
	int i;
	
	public : 
		string subjectCode;
		int count;
		Results(){
			i=0;
			count=0;
			average=0;
			total=0;
		}
		void getData(int id, int mark);	
		void findAverage();	
		void putData();
		void calculateSD();
		void getGradesCount();
		
};

void Results :: getGradesCount(){
	int A=0;
	int B=0;
	int C=0;
	int D=0;
	int F=0;
	
	for(int j=0; j<count; j++){
		if('A'==(char)marks[j][2]) A++;
		else if('B'==(char)marks[j][2]) B++;
		else if('C'==(char)marks[j][2]) C++;
		else if('D'==(char)marks[j][2]) D++;
		else F++;
		
	}
	cout << "Number of grades" << endl;
	cout << "  A's' : " << A<< endl;	
	cout << "  B's' : " << B << endl;	
	cout << "  C's' : " << C << endl;	
	cout << "  D's' : " << D << endl;	
	cout << "  F's' : " << F << endl;	
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
	int n=0;
	int j=-1;
	int x, m;
	string subject;
	string subCode;
	Results sub[10];
	ifstream myfile ("subjdata.txt");
	
	if (myfile.is_open()){
	
		while(getline(myfile,line)){
	
			if(n==0){	// Getting the subject code
    			j++;
				istringstream buf(line);
    			istream_iterator<string> beg(buf), end;
    
				vector<string> tokens(beg, end);
				
				stringstream num(tokens[1]);	// tokens[1] = marks count
				
				num >> n;	// casting string to int
//				cout << n << endl;	// marks count 
				
				sub[j].subjectCode = tokens[0];
				sub[j].count = n;
//				cout << tokens[1] << endl;
				
//				cout << subject << endl;
//				Results subject;
				
//    			for(auto& s: tokens)
//        			cout << '"' << s << '"' << endl;

				n++;
	
			}
			
			else{// Getting the marks and student numbers
				
				istringstream buf(line);
    			istream_iterator<string> beg(buf), end;
    
				vector<string> tokens(beg, end);
				
				stringstream mark(tokens[1]);
				stringstream num(tokens[0]);
				
					// tokens[1] = marks count
				mark >> m;	// casting string to int
				num >> x;
				
				sub[j].getData(x, m);

//				cout << m << endl;	// marks count 
//				cout << x << endl;
				
//    			for(auto& s: tokens)
//        			cout << '"' << s << '"' << endl;
				
			}
			
//			cout << line << '\n';
			n--;
	
		}
	
		myfile.close();
	
	}

	else cout << "Unable to open file"; 
	
	for(int k=0; k<j+1; k++){
		sub[k].putData();
		sub[k].findAverage();
		sub[k].calculateSD();
		sub[k].getGradesCount();
		cout << endl;
	}

//	do{
//		cout << "+----------------------------+" << endl;
//		cout << "| 1. Display Subject         |" << endl;
//		cout << "| 2. Display Student         |" << endl;
//		cout << "| 3. Display Subject Summary |" << endl;
//		cout << "| 4. Save Summaries          |" << endl;
//		cout << "| 5. Exit Program            |" << endl;
//		cout << "+----------------------------+" << endl;
//		
//		cin >> x;
//		
//		switch(x){
//			case 1 :
//				cout << "Enter 7 character Subject Code : ";
//				cin >> subCode;
//				break;
//			
//			case 2 : 
//				int stdNo;
//				cout << "Enter Student Number : ";
//				cin >> stdNo;
//				
//			case 3 : 
//				cout << "Enter 7 character Subject Code : ";
//				cin >> subCode;
//				break;
//				
//			case 4 :
//				ofstream myfile_O;
//				myfile_O.open ("example.txt");
//				myfile_O << "Writing this to a file.\n";
//				myfile_O.close();
//				break;
//								
//		}
//	}while(x!=5);
	
	return 0;
}

//
// NEW SKELETON FOR PROJECT 7
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "/ee259/tools/pro_7/sample_p6_mod.h"
// #include "/ee259/cliow000/pro_7/sample_p6.h"
using namespace std;


	ofstream out("out_71", ios::out);
class EZ_CURVE_FIT: public LINEAR_SOLVER
{
   public:
	EZ_CURVE_FIT(int); // constructor; 
		// example: s.EZ_CURVE_FIT(5);
		// there are 5 pairs of data points;

	void LS_FIT_BY_ME(char *); 
		// example: s.LS_FIT_BY_ME("data_file");
		// perform least squares fit using inheritance 
		// data is in "data_file";
		
	void LS_FIT_BY_MATLAB (char *); 
		// example: s.LS_FIT_BY_MATLAB("data_file);
		// perform least squares fit using MATLAB; 
		
   private:
	int np; // number of data pairs
};
 
// constructor code 
EZ_CURVE_FIT::EZ_CURVE_FIT(int x)
	:LINEAR_SOLVER("in.6", 2) // initialize base class LINEAR_SOLVER;
				  // we need to solve a linear equation 
				  // system of AX=B, for a 2x2 A matrix 
{
        np = x;
}

void EZ_CURVE_FIT::LS_FIT_BY_ME(char * data_file)
{
	float S1, S2, S3, S4, S5, S6, error;
	error=S1=S2=S3=S4=S5=S6=0.0;
	float X[15], Y[15];
	int i, j;
	
	float m, b;	
	m = 0;
	b = 0;	
	ifstream input_file(data_file, ios::in);   
	
	 for(i=0; i<np; i++)
        {
        	input_file >> X[i]>> Y[i];
        }
	

	// calculate the S1-S6 values
    for(i=0;i<np;i++)
    {
    	S1 += (X[i]*X[i]);
    	S2 += X[i];
    	S3 += (X[i]*Y[i]);
    	S4 += X[i];
    	S5 += 1;
    	S6 += Y[i];
    	
    }

	// put them into a in.6 in the format that sample_p6_mod.h
	// will read them:

	ofstream out_s_file("in.6", ios::out);
	
	out_s_file << S1 <<" " << S2 << endl;
	out_s_file << S4 <<" " << S5 << endl;
	out_s_file << S3 << endl;
	out_s_file << S6 << endl;
	
	// declare an LINEAR_SOLVER object:
	// access SOLVE_LINEAR_EQUATION 
	LINEAR_SOLVER L(2);
	L.SOLVE_LINEAR_EQUATION("NONE");
	
	

	// results are in out.6 file
	char a[100];
	char c[100];
	ifstream in_out6("out.6", ios::in);
	in_out6.getline(a,100, '\n');
	int count;
	count = 0;





	for(i=0;!in_out6.eof();i++)
	{

		in_out6 >> a;
		 // cout << a << endl;
		 count++;
	}

	ifstream in_out66("out.6", ios::in);
	in_out66.getline(c,100,'\n');
	count = count - 8;
	for(i = 0; i < count ; i++)
	{
		in_out66 >> c;
		// cout << c << endl;
	}




	in_out66 >> m;
	in_out66 >> a;
	in_out66 >> b;

	
	// get the results from out.6 file and enter into out_71 file

	out << "LEAST_SQUARE_FIT RESULT:" << endl;
	out << "USING INHERITANCE:" << endl;
	out << "MATCHING FUNCTION IS Y = " << setprecision(2) << setiosflags(ios::fixed|ios::showpoint)
				<< m << " * X + " << b << endl;
	for(i=0;i<np;i++)
	{
		error += (Y[i] - (m*X[i]) - b) * (Y[i] - (m*X[i])-b);
	}

	out << "THE ERROR FROM LS_FIT_BY_ME METHOD IS " 
	<< setprecision(3) << setiosflags(ios::fixed|ios::showpoint)
	<< error << endl;

	// ofstream output("out_71", ios::out);
}

void EZ_CURVE_FIT::LS_FIT_BY_MATLAB(char * file_name)
{
   float X[50],Y[50];
   int i,j;
   
   ifstream input_file(file_name,ios::in);
   
   for (i=0;i<np;i++)
   {
   	input_file >> X[i] >>Y[i];
   }


    ofstream output_file("mat_1.m",ios::out); 

   output_file <<"x=[";
   for(i=0;i<np;i++)
   {
		output_file << X[i];
		   	if(i != np-1)
		   	{
		   		output_file << ",";
		   	}
		   	else{}
   	
   } 
	
	output_file << "];" << endl;
	output_file <<"y=[";

	for(i=0;i<np;i++)
	{
		output_file << Y[i];
		if(i != np-1)
		{
			output_file << ",";

		}
		else{}
	}	
	output_file << "];" << endl;

	output_file << "coef=polyfit(x,y,1);" << endl;
	output_file << "m=coef(1);" << endl;
	output_file << "b=coef(2);" << endl;
	output_file << "Y=m*x+b;" << endl;
	output_file << "matlab_error=sum((y - Y).^2);" << endl;
	output_file << "fid=fopen('out_71','a');" << endl;
	
	output_file << "fprintf(fid,'*** RESULT FROM MATLAB\\n');" << endl;
	output_file << "fprintf(fid,'*** THE MATCHING FUNCTION IS Y=(%.3f) * X +(%.3f) \\n',m,b);" << endl;
	output_file << "fprintf(fid,'*** THE ERROR FROM MATLAB IS %.3f \\n', matlab_error);" << endl;
   
   system("/bin/csh /ee259/tools/pro_7/run_mat_1");
}


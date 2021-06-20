#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define GNUPLOT_PATH "C:/gnuplot/bin/gnuplot.exe"

// ---------------------
#define INPUTNO 2  // Number of inputs
#define MAXINPUTNO 330    // Maximum size of data
#define N 256

// declare functions
double f_step(double u);
double f_sigmoid(double u);                                   // transfer function
void initw(double w[INPUTNO + 1]);                        //initialize weights and threshold
double forward(double w[INPUTNO + 1], double e[INPUTNO]); // forward computation
void getdata(double data_[][INPUTNO], int *mm, int *nn);// load data
void savedata(double data_[][INPUTNO], double output[MAXINPUTNO], int *mm, int *nn);
void plot_data(void);

int main()
{
	double weight_[INPUTNO + 1];/*weights and threshold*/
	double output[MAXINPUTNO];/*output value*/
	int ii, jj;
	int mm, nn;
	double data_[MAXINPUTNO][INPUTNO];/*dataset*/
	initw(weight_); /*initialize weights*/
	getdata(data_, &mm, &nn);

	printf("Number of data:%d\n", nn);
	printf("------------------------\n");
	printf("Input data        |  output\n", nn);

	/* actual computation is done here*/
	for (ii = 0; ii<nn; ii++) {
		printf("%d:", ii);
		for (jj = 0; jj<INPUTNO; jj++)	printf("%lf ", data_[ii][jj]);
		output[ii] = forward(weight_, data_[ii]);
		printf(" | %lf\n", output[ii]);
	}

	savedata(data_, output, &mm, &nn);
	plot_data();
	getchar();
	return 0;
}

//  forward computation
double forward(double weight_[INPUTNO + 1], double e[INPUTNO])
{
	double u;// buffer
	double o;// output value
	int i;
	// forward computation
	u = 0;
	for (i = 0; i<INPUTNO; ++i)
	{
		u += e[i] * weight_[i]; // sum all data after multiplied by weight_[]
	}
	u -= weight_[i];// thresholding

	o = f_step(u);  // compute output
					//o = f_sigmoid(u);  // compute output

	return o;
}

/*--- initialize weights -----------*/
void initw(double weight_[INPUTNO + 1])
{
	/* give constant value as weights*/
	weight_[0] = 1.0;
	weight_[1] = 1.0;
  	/* OR */
  	//weight_[2] = 0.5;
  	/* AND */
	weight_[2] = 1.2; // threshold
}


/*---  transfer function ------*/
double f_step(double u)
{
	// step function/
	if (u >= 0) return 1.0;
	else return 0.0;
}

/*---  transfer function ------*/
double f_sigmoid(double u)
{
	double o;
	o = 1.0 / (1.0 + exp(-u));
	return o;
}

void savedata(double data_[][INPUTNO], double output[MAXINPUTNO], int *mm_, int *nn_)
{
	int mm, nn;
	int nx;

	FILE *fin;
	char  filename[] = "./Output/Task14/data03_AND.txt";
	mm = (*mm_);
	nn = (*nn_);
	if ((fin = fopen(filename, "w")) == NULL)
	{
		fprintf(stderr, "Can't open file\n");
	}
	else
	{
		fprintf(fin, "#\tx\ty\tz\n");
		for (int ii = 0; ii < nn; ii++)
		{
			for (int jj = 0; jj < mm; jj++)	fprintf(fin, "\t%.4f", data_[ii][jj]);
			fprintf(fin, "\t%.4f\n", output[ii]);
		}
	fclose(fin);
	}

	return;
}


void getdata(double data_[][INPUTNO], int *mm_, int *nn_)
{
	int mm, nn;
	char  filename[] = "./data_14/data03.txt";
	char readline[N] = { '\0' };

	char temp_str;
	FILE *fin;
	char delim[] = " ";

	if ((fin = fopen(filename, "r")) == NULL)
		fprintf(stderr, "Can't open file\n");

	nn = 0;
	while (fgets(readline, N, fin) != NULL) {
		char * token = strtok(readline, delim);
		mm = 0;
		while (token != NULL) {
			data_[nn][mm] = atof(token);
			token = strtok(NULL, delim);
			mm++;
		}
		nn++;
	}
	fclose(fin);
	(*mm_) = mm;
	(*nn_) = nn;

	return;

}


void plot_data()
{
	FILE *gp;
	// Call Gnuplot
	if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) { //Use pipe to boot gnuplot
		fprintf(stderr, "Not Found %s.", GNUPLOT_PATH);
		exit(EXIT_FAILURE);
	}
	fprintf(gp, "set term wxt  0\n");
	fprintf(gp, "reset\n");
	fprintf(gp, "unset label\n");
	fprintf(gp, "unset key\n");
	fprintf(gp, "unset grid\n");
	fprintf(gp, "set title \"Simple perceptron output, O\"\n");
	fprintf(gp, "set xlabel \"Input X1\"\n");
	fprintf(gp, "set ylabel \"Input X2\"\n");
	fprintf(gp, "set terminal wxt size 1000, 1000 font \"Verdana,10\"\n");
	fprintf(gp, "set size ratio - 1\n");
	fprintf(gp, "set palette rgbformulae 22, 13, -31\n");
	fprintf(gp, "set pm3d map # no interpolation\n");
	fprintf(gp, "set term wxt  1\n");
	fprintf(gp, "splot './Output/Task14/data03_AND.txt' using 1:2:3 with points palette pointsize 3 pointtype 7\n");

	fflush(gp); //Flush the buffer
	system("pause");
	fprintf(gp, "exit\n"); //End the Gnu plot
	_pclose(gp);

	return;

}

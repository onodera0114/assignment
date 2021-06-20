#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GNUPLOT_PATH "C:/gnuplot/bin/gnuplot.exe"

#define INPUTNO 3  // Number of inputs
#define MAXINPUTNO 500 // Maximum size of data
#define HIDDENNO 3
#define N 256
#define ALPHA 1
#define LIMIT 0.01

// declare functions
double f_sigmoid(double u);                                   // transfer function
void initwh(double wh[HIDDENNO][INPUTNO + 1]);                        //initialize weights and threshold
void initwo(double wo[HIDDENNO + 1]);
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO]);// forward computation
void getdata(double data_[][INPUTNO + 1], int* mm_, int* nn_);// load data
void savedata(double data_[][2], int* mm_, int* nn_);
void plot_data(void);
void olearn(double wo[HIDDENNO + 1], double hi[], double data_[INPUTNO + 1], double o);
void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double data_[INPUTNO + 1], double o);

int main(void){
	double wh[HIDDENNO][INPUTNO + 1];
	double wo[INPUTNO + 1];
	double err_data[MAXINPUTNO][2];
	double data_[MAXINPUTNO][INPUTNO + 1];/*dataset*/
	double hi[HIDDENNO + 1];
	int i, j;
	int mm, nn;
	int count = 0;
	double o = 0.0, err = 200;

	initwh(wh);
	initwo(wo);
	getdata(data_, &mm, &nn);

	// training data
	while(err > LIMIT){
		err = 0.0;
		for(j = 0; j < nn; ++j){
			// train all the data
			o = forward(wh, wo, hi, data_[j]); // forward computation
			olearn(wo, hi, data_[j], o); // manipulate weights in output layer
			hlearn(wh, wo, hi, data_[j], o); // manipulate weights in hidden layer
			err += (o - data_[j][INPUTNO]) * (o - data_[j][INPUTNO]); // accumulate error value
		}
		// output error value
		fprintf(stderr, "%d\t%lf\n", count, err);
		err_data[count][0] = (double)count;
		err_data[count][1] = err;
		++count;
	}// training data

	// result output
	for(i = 0; i < nn; ++i){
		printf("%d, ", i);
		for(j = 0; j < INPUTNO + 1; ++j){
			printf("%lf, ", data_[i][j]);
		}
		printf("%lf\n", forward(wh, wo, hi, data_[i]));
	}

	savedata(err_data, &mm, &count);
	plot_data();

	return 0;
}

// transfer function, sigmoid function
double f_sigmoid(double u)
{
	double o;
	o = 1.0 / (1.0 + exp(-u));
	return o;
}

// training hidden layer
void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double data_[INPUTNO + 1], double o){
	int i, j;
	double dj;

	for(j = 0; j < HIDDENNO; ++j){
		dj = hi[j] * (1 -hi[j]) * wo[j] * (data_[INPUTNO] - o) * o * (1 - o);
		for(i = 0; i < INPUTNO; i++){
			wh[j][i] += ALPHA * data_[i] * dj;
		}
		wh[j][i] += ALPHA * (-1.0) * dj;
	}
}

// training output layer
void olearn(double wo[HIDDENNO + 1], double hi[], double data_[INPUTNO + 1], double o){
	int i;
	double d, E;
	E = data_[INPUTNO] - o;

	d = E * o * (1 - o); // compute error
	for(i = 0; i < HIDDENNO; ++i){
		wo[i] += ALPHA * hi[i] * d; // training wights
	}
	wo[i] += ALPHA * (-1.0) * d; // train threshold
}

// forward computation
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[INPUTNO + 1], double e[INPUTNO]){
	int i, j; // for loop index
	double u; // u = e*weight
	double o, out_val; // output value

	// compute hidden layer
	for(i = 0; i < HIDDENNO; i++){
		u = 0;
		for(j = 0; j < INPUTNO; j++){
			u += e[j] * wh[i][j];
		}
		u -= wh[i][j]; // thresholding
		hi[i] = f_sigmoid(u);
	}
	// compurate output value
	o = 0;
	for(i = 0; i < HIDDENNO; i++){
		o += hi[i] * wo[i];
	}
	o -= wo[i]; // thresholding
	out_val = f_sigmoid(o);

	return out_val;
}

// initialize weights
void initwh(double wh[HIDDENNO][INPUTNO + 1]){
    int i, j;

	srand((unsigned int )time(NULL));
	// initialize weights as ramdom number
    for(i = 0; i < HIDDENNO; ++i){
        for(j = 0; j < INPUTNO + 1; ++j){
            wh[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
}

void initwo(double wo[HIDDENNO + 1]){
	int i;

	srand((unsigned int )time(NULL));
	for(i = 0; i < INPUTNO + 1; i++){
		wo[i] = ((double)rand() / RAND_MAX) * 2 - 1;
	}
}


void savedata(double data_[][2], int *mm_, int *nn_){
	int mm, nn;
	int nx;

	FILE *fin;
	char  filename[] = "./Output/Task15/save.txt";
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
			fprintf(fin, "\n");
		}
		fclose(fin);
	}

	return;
}


void getdata(double data_[][INPUTNO + 1], int *mm_, int *nn_){
	int mm, nn;
	char filename[] = "./data_15/majority.txt";
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


void plot_data(){
	FILE *gp;
	// Call Gnuplot
	if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) { //Use pipe to boot gnuplot
		fprintf(stderr, "Not Found %s.", GNUPLOT_PATH);
		exit(EXIT_FAILURE);
	}
	fprintf(gp, "set style line 1 \n");
  fprintf(gp, "plot './Output/Task15/save.txt'\n");
  fprintf(gp, "set term wxt 1\n");
	fflush(gp); //Flush the buffer
	system("pause");
	fprintf(gp, "exit\n"); //End the Gnu plot
	_pclose(gp);

	return;
}

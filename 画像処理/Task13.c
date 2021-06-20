#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define GNUPLOT_PATH "C:/gnuplot/bin/gnuplot.exe"

// ---------------------
#define INPUTNO 2  // Number of inputs
#define MAXINPUTNO 500    // Maximum size of data
#define N 256
#define K 3
#define Nearest_neighbor true
#define k_Nearest_neighbor false
#define k_means false


void plot_data(void);
void getdata(double data_[][INPUTNO], double data_category[], int *mm, int *nn, char *path);// load data
void savedata(double data_[][INPUTNO], double output[MAXINPUTNO], int *mm, int *nn, char *path);


int main(){
		int ii, jj, i, j;
		int mm, nn, mm2, nn2;
		double sum, min, distance, tmp;
		double k_distance[MAXINPUTNO][INPUTNO];

		double data1_[MAXINPUTNO][INPUTNO];/*dataset*/
		double data1_category[MAXINPUTNO];/*data category*/

		double data2_[MAXINPUTNO][INPUTNO];/*dataset*/
		double data2_category[MAXINPUTNO];/*data category*/
		double output[MAXINPUTNO];/*output value*/

    if(Nearest_neighbor){
      char input_path1[] = "./resources/data_01.txt";
      char input_path2[] = "./resources/data_02.txt";
      char output_path[] = "./Output/Task13/Nearest_neighbor_method.txt";
      getdata(data1_, data1_category, &mm, &nn, input_path1);
      getdata(data2_, data2_category, &mm2, &nn2, input_path2);
      for (ii = 0; ii < nn2; ii++) {
        min = 100;
        for(jj = 0; jj < nn; jj++){
          distance = sqrt(((data1_[jj][0] - data2_[ii][0]) * (data1_[jj][0] - data2_[ii][0])) + ((data1_[jj][1] - data2_[ii][1]) * (data1_[jj][1] - data2_[ii][1])));
          if(min > distance){
            min = distance;
            output[ii] = data1_category[jj];
          }
        }
      }

      savedata(data2_, output, &mm2, &nn2, output_path);
      plot_data();
    }

    if(k_Nearest_neighbor){
      char input_path1[] = "./resources/data_01.txt";
      char input_path2[] = "./resources/data_02.txt";
      char output_path[] = "./Output/Task13/k_Nearest_neighbor_method.txt";
      getdata(data1_, data1_category, &mm, &nn, input_path1);
      getdata(data2_, data2_category, &mm2, &nn2, input_path2);

      for (ii = 0; ii < nn2; ii++) {
        for(jj = 0; jj < nn; jj++){
          k_distance[jj][0] = sqrt(((data1_[jj][0] - data2_[ii][0]) * (data1_[jj][0] - data2_[ii][0])) + ((data1_[jj][1] - data2_[ii][1]) * (data1_[jj][1] - data2_[ii][1])));
          k_distance[jj][1] = data1_category[jj];
        }
        for (i = 0; i < nn; i++){
          for (j = i + 1; j < nn; j++){
            if (k_distance[i][0] < k_distance[j][0]){
              tmp = k_distance[i][0];
              k_distance[i][0] = k_distance[j][0];
              k_distance[j][0] = tmp;

              tmp = k_distance[i][1];
              k_distance[i][1] = k_distance[j][1];
              k_distance[j][1] = tmp;
            }
          }
        }
        sum = 0;
        for(i = 0; i < K; i++){
          sum += k_distance[i][1];
        }
        output[ii] = round(sum / K);
      }
      savedata(data2_, output, &mm2, &nn2, output_path);
      plot_data();
    }

    if(k_means){
      char input_path1[] = "./resources/data_03.txt";
      char input_path2[] = "./resources/data_04.txt";
      char output_path[] = "./Output/Task13/k_means_method.txt";
      getdata(data1_, data1_category, &mm, &nn, input_path1);
      getdata(data2_, data2_category, &mm2, &nn2, input_path2);

      double Cog1[2] = { 1,1 };
      double Cog2[2] = { 6,6 };
      double distance1, distance2;
      double sum10, sum11, sum20, sum21, t;
      while (1) {
        sum10 = 0;
        sum11 = 0;
        sum20 = 0;
        sum21 = 0;
        t = 0;

        for (i = 0; i < nn2; i++) {
          distance1 = sqrt(((Cog1[0] - data2_[i][0]) * (Cog1[0] - data2_[i][0])) + ((Cog1[1] - data2_[i][1]) * (Cog1[1] - data2_[i][1])));
          distance2 = sqrt(((Cog2[0] - data2_[i][0]) * (Cog2[0] - data2_[i][0])) + ((Cog2[1] - data2_[i][1]) * (Cog2[1] - data2_[i][1])));
          if (distance1 <= distance2) {
            output[i] = 1;
            sum10 += data2_[i][0];
            sum11 += data2_[i][1];
            t++;
          }
          else {
            output[i] = 2;
            sum20 += data2_[i][0];
            sum21 += data2_[i][1];
          }
        }

        if (fabs(Cog1[0] - (sum10 / t)) < 0.01 && fabs(Cog1[1] - (sum11 / t)) < 0.01 &&fabs(Cog2[0] - (sum20 / (nn2 - t))) < 0.01 && fabs(Cog2[1] - (sum21 / (nn2 - t))) < 0.01){
          break;
        }
        Cog1[0] = sum10 / t;
        Cog1[1] = sum11 / t;
        Cog2[0] = sum20 / (nn2 - t);
        Cog2[1] = sum21 / (nn2 - t);
      }
      savedata(data2_, output, &mm2, &nn2, output_path);
      plot_data();
    }

	return 0;
}

void savedata(double data_[][INPUTNO], double output[MAXINPUTNO], int *mm_, int *nn_, char *path)
{
	int mm, nn;
	int nx;

	FILE *fin;
	mm = (*mm_);
	nn = (*nn_);
	if ((fin = fopen(path, "w")) == NULL)
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
	fprintf(gp, "show grid\n");
	fprintf(gp, "set title \"Data\"\n");
	fprintf(gp, "set xlabel \"x\"\n");
	fprintf(gp, "set ylabel \"y\"\n");
	fprintf(gp, "set terminal wxt size 1000, 1000 font \"Verdana,10\"\n");
	fprintf(gp, "set size ratio - 1\n");
	fprintf(gp, "set palette rgbformulae 22, 13, -31\n");
	fprintf(gp, "set pm3d map # no interpolation\n");
	fprintf(gp, "set term wxt  1\n");
	fprintf(gp, "splot './Output/Task13/Nearest_neighbor_method.txt' using 1:2:3 with points palette pointsize 1 pointtype 7\n");

	fflush(gp); //Flush the buffer
	system("pause");
	fprintf(gp, "exit\n"); //End the Gnu plot
	_pclose(gp);

	return;

}



void getdata(double data_[][INPUTNO], double data_category[], int *mm_, int *nn_, char *path)
{
	int mm, nn;
	char readline[N] = { '\0' };

	char temp_str;
	FILE *fin;
	char delim[] = " ";

	if ((fin = fopen(path, "r")) == NULL)
		fprintf(stderr, "Can't open file\n");

	nn = 0;
	while (fgets(readline, N, fin) != NULL) {
		char * token = strtok(readline, delim);
		mm = 0;
		while (token != NULL) {
			if (mm<2)
			{
				data_[nn][mm] = atof(token);
				//printf("%3.3g ", data_[nn][mm]);
			}
			else{
				data_category[nn] = atof(token);
				//printf(" category=%3.3g\n ", data_category[nn]);
			}
			token = strtok(NULL, delim);
			mm++;
		}
		nn++;
	}
	fclose(fin);
	mm = 2;
	(*mm_) = mm;
	(*nn_) = nn;

	return;

}

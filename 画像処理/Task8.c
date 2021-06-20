#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[256] = "airplane";                // ファイル名を宣言

int main(void){
  FILE *fp;                                   // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";    // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task8/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // グレイスケール画像のデータを格納する配列grayを宣言
  unsigned char gray_mirror[258][258];        // ミラーリングしたデータを格納する配列gray_mirrorを宣言
  unsigned char gray_laplacian[256][256];     // Laplacianフィルタを適用したデータを格納する配列gray_laplaciaｌを宣言
  unsigned char gray_sobel[256][256];         // Sobelフィルタを適用したデータを格納する配列gray_sobelを宣言
  int laplacianfilter[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};               // Laplacianフィルタ
  int sobelfilter_vertical[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};        // 垂直方向のSobelフィルタ
  int sobelfilter_horizontal[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};      // 水平方向のsobelフィルタ
  int sum = 0;                                // 合計値を代入する変数
  int sumH = 0;                               // 水平方向の合計値を代入する変数
  int sumV = 0;                               // 垂直方向の合計値を代入する変数
  int i, j, m, n;

  // inputpath, filename, Y.pgm を結合して読み取るファイルの相対パスを作成
  strcat(inputpath, filename);
  strcat(inputpath, "Y.pgm");

  // 読み込みモードでファイルを開く
  fp = fopen(inputpath, "rb");

  // ファイルを開けなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}

  fgets(format, 256, fp);                           // 形式を読み取り、配列formatに代入
  fgets(comment, 256, fp);                          // コメントを読み取り、配列commentに代入
  fscanf(fp, "%d %d", &width, &height);             // 幅と高さを読み取り、幅をwidth、高さをheightに代入
  fgets(msg, 128, fp);                              // 高さの後の改行コードを読み取り、配列msgに代入
  fgets(msg, 128, fp);                              // 最大階調値を読み取り、配列msgに代入
  g = atoi(msg);                                    // gradationのデータ(最大階調値)を数値に変換
  fread(gray, sizeof(char), width * height, fp);    // データ部を読み込む
  fclose(fp);                                       // ファイルを閉じる

  // outputpath, filename, Laplacian.pgmを結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task8/");
  strcat(outputpath, filename);
  strcat(outputpath, "Laplacian.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* ミラーリングした配列を作成する処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      if(j <= 0){
        gray_mirror[i + 1][j] = gray[i][j];
      }
      if(i <= 0){
        gray_mirror[i][j + 1] = gray[i][j];
      }
      if(j >= 255){
        gray_mirror[i + 1][j + 2] = gray[i][j];
      }
      if(i >= 255){
        gray_mirror[i + 2][j + 1] = gray[i][j];
      }
      gray_mirror[i + 1][j + 1] = gray[i][j];
    }
  }
  gray_mirror[0][0] = gray[0][0];
  gray_mirror[257][0] = gray[255][0];
  gray_mirror[0][257] = gray[0][255];
  gray_mirror[257][257] = gray[255][255];


  /* Laplacianフィルタを適用する処理 */
  for(i = 1; i < height + 1; i++){
    for(j = 1; j < width + 1; j++){
      for(m = 0; m < 3; m++){
        for(n = 0; n < 3; n++){
          sum += gray_mirror[i - 1 + m][j - 1 + n] * laplacianfilter[m][n];    // 合計値を計算
        }
      }
      sum = abs(sum);         // sumの絶対値を計算
      // sumが255以上かを確認
      if(sum >= 255){
        sum = 255;
      }
      gray_laplacian[i - 1][j - 1] = sum;       // sumを代入
      sum = 0;
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // ファイルにヘッダ部を書き込む
  fwrite(gray_laplacian, sizeof(char), width * height, fp);     // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  // outputpath, filename, Sobel.pgmを結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task8/");
  strcat(outputpath, filename);
  strcat(outputpath, "Sobel.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* Sobelフィルタを適用する処理 */
  for(i = 1; i < height + 1; i++){
    for(j = 1; j < width + 1; j++){
      for(m = 0; m < 3; m++){
        for(n = 0; n < 3; n++){
          sumH += gray_mirror[i - 1 + m][j - 1 + n] * sobelfilter_horizontal[m][n];    // 水平方向の合計値を計算
          sumV += gray_mirror[i - 1 + m][j - 1 + n] * sobelfilter_vertical[m][n];      // 垂直方向の合計値を計算
        }
      }
      sum = sqrt(pow(sumH, 2.0) + pow(sumV, 2.0));        // 水平方向の合計値の2乗と垂直方向の合計値の2乗の平方根を計算
      // sumが0～255の範囲内かを確認
      if(sum >= 255){
        sum = 255;
      }
      if(sum <= 0){
        sum = 0;
      }
      gray_sobel[i - 1][j - 1] = sum;                     // sumを代入

      sumH = 0;
      sumV = 0;
      sum = 0;
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // ファイルにヘッダ部を書き込む
  fwrite(gray_sobel, sizeof(char), width * height, fp);         // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  return 0;
}

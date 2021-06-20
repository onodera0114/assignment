#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[256] = "pepper";                // ファイル名を宣言

int main(void){
  FILE *fp;                                   // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";    // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task5/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // グレイスケール画像のデータを格納する配列grayを宣言
  unsigned char binarization[256][256];       // 2値化したデータを格納する配列binarizationを宣言
  unsigned char dither[256][256];             // ディザマトリクスによる2値化データを格納する配列ditherを宣言
  int average, sum;
  int bayermatrix[4][4] = {{0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}}; // Bayerマトリクス
  int i, j;

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

  // outputpath, filename, Binarization_Half を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task5/");
  strcat(outputpath, filename);
  strcat(outputpath, "Binarization_Half.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* 128をしきい値として2値化する処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // 画素の濃度が128以上の時に255、それ以外の時に0を代入
      if(gray[i][j] >= 128){
        binarization[i][j] = 255;
      }
      else{
        binarization[i][j] = 0;
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);              // ファイルにヘッダ部を書き込む
  fwrite(binarization, sizeof(char), width * height, fp);                   // ファイルにデータ部を書き込む
  fclose(fp);                                                               // ファイルを閉じる

  // outputpath, filename, Binarization_Average.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task5/");
  strcat(outputpath, filename);
  strcat(outputpath, "Binarization_Average.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* 画像全体の濃度の平均をしきい値として2値化する処理 */
  // 画像全体の濃度の平均を計算
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      sum += gray[i][j];
    }
  }
  average = sum / (width * height);

  // 2値化する処理
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // 画像全体の濃度の平均より大きい時は255、それ以外の時は0を代入する
      if(gray[i][j] >= average){
        binarization[i][j] = 255;
      }
      else{
        binarization[i][j] = 0;
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);              // ファイルにヘッダ部を書き込む
  fwrite(binarization, sizeof(char), width * height, fp);                   // ファイルにデータ部を書き込む
  fclose(fp);                                                               // ファイルを閉じる


  // outputpath, filename, BayerMatrix.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task5/");
  strcat(outputpath, filename);
  strcat(outputpath, "BayerMatrix.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* Bayerマトリクスを用いて2値化する処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      if(gray[i][j] / 16 >= bayermatrix[i % 4][j % 4]){
        dither[i][j] = 255;
      }
      else{
        dither[i][j] = 0;
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);            // ファイルにヘッダ部を書き込む
  fwrite(dither, sizeof(char), width * height, fp);                       // ファイルにデータ部を書き込む
  fclose(fp);                                                             // ファイルを閉じる

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[256] = "pepper"; // ファイル名を宣言

// 目標頻度と累積頻度の差の絶対値を返す関数
int CalculateDifference(int frequency, int accumulation){
  return abs(frequency - accumulation);
}

int main(void){
  FILE *fp;                                   // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";    // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task3/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // 補正前のデータを格納する配列grayを宣言
  unsigned char gray_correction[256][256];    // 補正後のデータを格納する配列gray_correctionを宣言
  int before_diff = 0;                        // 前の目標頻度と累積頻度の差の絶対値を格納する変数
  int concentration[256] = {0};               // 濃度に対する頻度を格納する配列concentrationを宣言
  int accumulation = 0;                // 濃度に対する累積頻度を格納する配列accumulationを宣言
  int correction[256] = {0};                  // 濃度に対する補正濃度を格納する配列correctionを宣言
  int targetfrequency;                        // 目標頻度を格納する変数
  int cor = 0;                                // 補正濃度を格納する変数
  int gradation = 64;                         // 目標階調数を宣言
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

  // outputpath, filename, .csv を結合して出力場所の相対パスを作成
  strcat(outputpath, filename);
  strcat(outputpath, ".csv");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした\n");
		exit(1);
	}

  /* 各画素に対する濃度を求める処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      concentration[gray[i][j]]++;
    }
  }

  /* 各画素に対する濃度をcsvファイルに出力する処理 */
  fprintf(fp, "濃度,頻度\n");
  for(i = 0; i < 256; i++){
    fprintf(fp, "%d, %d\n", i, concentration[i]);
  }
  fclose(fp); // ファイルを閉じる

  // outputpath, filename, Correction.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task3/");
  strcat(outputpath, filename);
  strcat(outputpath, "Correction.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  targetfrequency = (width * height) / gradation;  // 頻度目標値を計算

  /* 濃度変換表を作成する処理 */
  for(i = 0; i < 256; i++){
    // 現在の蓄積頻度に現在の濃度を加算
    accumulation += concentration[i];
    // 現在の目標頻度と累積頻度の差の絶対値と前回の目標頻度と累積頻度の差の絶対値を比較
    if(before_diff < CalculateDifference(targetfrequency, accumulation)){
      // 蓄積頻度を0にする
      accumulation = concentration[i];
      // 補正濃度を１加算
      cor++;

      // 補正濃度が目標階調数を超えた時に補正濃度を(目標階調数-1)にする
      if(cor >= gradation){
        cor = gradation - 1;
      }
    }
    // 現在の補正濃度を代入する
    correction[i] = cor;

    // 現在の目標頻度と累積頻度の差の絶対値を計算し、格納する
    before_diff = CalculateDifference(targetfrequency, accumulation);
  }

  /* 濃度変換表をもとに各画素の濃度を補正する処理 */
  for(i = 0; i < 256; i++){
    for(j = 0;j < 256; j++){
      gray_correction[i][j] = correction[gray[i][j]];
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, gradation);  // ファイルにヘッダ部を書き込む
  fwrite(gray_correction, sizeof(char), width * height, fp);                // ファイルにデータ部を書き込む
  fclose(fp);                                                               // ファイルを閉じる

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[256] = "Lenna";                // ファイル名を宣言

int main(void){
  FILE *fp;                                   // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";    // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task8/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // グレイスケール画像のデータを格納する配列grayを宣言
  unsigned char gray_mirror[258][258];        // ミラーリングしたデータを格納する配列gray_mirrorを宣言
  unsigned char gray_kirsch[256][256];
  int kirschfilter[8][3][3] = {{{5, 5, 5}, {-3, 0, -3}, {-3, -3, -3}},
                      {{5, 5, -3}, {5, 0, -3}, {-3, -3, -3}},
                      {{5, -3, -3}, {5, 0, -3}, {5, -3, -3}},
                      {{-3, -3, -3}, {5, 0, -3}, {5, 5, -3}},
                      {{-3, -3, -3}, {-3, 0, -3}, {5, 5, 5}},
                      {{-3, -3, -3}, {-3, 0, 5}, {-3, 5, 5}},
                      {{-3, -3, 5}, {-3, 0, 5}, {-3, -3, 5}},
                      {{-3, 5, 5}, {-3, 0, 5}, {-3, -3, -3}}};        // kirschフィルタ
  int sum = 0;                                 // 合計値を代入する変数を宣言
  int max = 0;                                 // 最大値を代入する変数を宣言
  int i, j, l, m, n;

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

  // outputpath, filename, Kirsch.pgmを結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task8/");
  strcat(outputpath, filename);
  strcat(outputpath, "Kirsch.pgm");

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


  /* kirschフィルタを適用する処理 */
  for(i = 1; i < height + 1; i++){
    for(j = 1; j < width + 1; j++){
      for(l = 0; l < 8; l++){
        for(m = 0; m < 3; m++){
          for(n = 0; n < 3; n++){
            sum += gray_mirror[i - 1 + m][j - 1 + n] * kirschfilter[l][m][n];    // 合計値を計算
          }
        }
        /* sumとmaxを比較し、sumの方が大きければmaxをsumの値にする*/
        if(sum >= max){
            max = sum;
          }
          sum = 0;
      }

      // maxが0～255の範囲内かを確認
      if(max >= 255){
        max = 255;
      }
      if(max <= 0){
        max = 0;
      }
      gray_kirsch[i - 1][j - 1] = max;       // maxを代入
      sum = 0;
      max = 0;
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // ファイルにヘッダ部を書き込む
  fwrite(gray_kirsch, sizeof(char), width * height, fp);        // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  return 0;
}

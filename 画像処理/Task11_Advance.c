#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define a 0.626623308
#define b -0.100265712
#define c 127.1685368
#define d 0.121648367
#define e 0.607867097
#define f 12.64918356
#define W width
#define H height
#define WS 900
#define HS 1000

int main(void){
  FILE *fp;                                                         // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, gradation;
  char inputpath_destination[256] = "./Affine/destination.pgm";     // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task11/gray_source.pgm";         // 出力するディレクトリを宣言
  int i, j;
  double x, y;
  double det;                                                       // 行列式を格納する変数
  int x_min = 0;                                                    // オーバーしている画素数を格納する変数

  // 読み込みモードでファイルを開く
  fp = fopen(inputpath_destination, "rb");

  // ファイルを開けなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}

  fgets(format, 256, fp);                                 // 形式を読み取り、配列formatに代入
  fgets(comment, 256, fp);                                // コメントを読み取り、配列commentに代入
  fscanf(fp, "%d %d", &width, &height);                   // 幅と高さを読み取り、幅をwidth、高さをheightに代入
  fgets(msg, 128, fp);                                    // 高さの後の改行コードを読み取り、配列msgに代入
  fgets(msg, 128, fp);                                    // 最大階調値を読み取り、配列msgに代入
  gradation = atoi(msg);                                  // gradationのデータ(最大階調値)を数値に変換
  unsigned char gray_destination[H][W];                   // 画像データを格納する配列gray_destinationを宣言
  fread(gray_destination, sizeof(char), W * H, fp);       // データ部を読み込む
  fclose(fp);                                             // ファイルを閉じる

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");
  unsigned char gray[HS][WS];                             // 逆アフィン変換後のデータを格納する配列grayを宣言

  // 配列grayを0で初期化
  for(i = 0; i < HS; i++){
    for(j = 0; j < WS; j++){
      gray[i][j] = 0;
    }
  }

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}
  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, WS, HS, gradation);  // ファイルにヘッダ部を書き込む

  det = a * e - b * d;      // 行列式を計算

  /* 範囲内からオーバーする画素数(x方向)を計算 */
  for(i = 0; i < 750; i++){
    for(j = 0; j < 700; j++){
      x = ((e * (j - c) - b * (i - f)) / det);
      y = (-d * (j - c) + a * (i - f)) / det;
      if(x_min > (int)(x + 0.5) && gray_destination[i][j] != 0){
        x_min = (int)(x + 0.5);
      }
    }
  }

  /* アフィン変換を行う処理 */
  for(i = 0; i < 750; i++){
    for(j = 0; j < 700; j++){
      /* 変換後の座標x, yを計算 */
      x = ((e * (j - c) - b * (i - f)) / det) + abs(x_min);
      y = (-d * (j - c) + a * (i - f)) / det;

      /* 画像サイズを超えた時の処理 */
      if(x < 0){
        x = 0;
      }
      if(x > WS){
        x = WS;
      }
      if(y < 0){
        y = 0;
      }
      if(y > HS){
        y = HS;
      }

      /* 最近隣内挿法を行い、代入 */
      gray[(int)(y + 0.5)][(int)(x + 0.5)] = gray_destination[i][j];
    }
  }
  fwrite(gray, sizeof(char), WS * HS, fp);        // ファイルにデータ部を書き込む
  fclose(fp);                                     // ファイルを閉じる

  return 0;
}

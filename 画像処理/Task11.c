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

int main(void){
  FILE *fp;                                                         // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, gradation;
  char inputpath_source[256] = "./Affine/source.pgm";               // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task11/gray_destination.pgm";    // 出力するディレクトリを宣言
  int i, j;
  double x, y;

  // 読み込みモードでファイルを開く
  fp = fopen(inputpath_source, "rb");

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
  gradation = atoi(msg);                            // gradationのデータ(最大階調値)を数値に変換
  unsigned char gray_source[H][W];                  // 画像データを格納する配列gray_sourceを宣言
  fread(gray_source, sizeof(char), W * H, fp);      // データ部を読み込む
  fclose(fp);                                       // ファイルを閉じる

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");
  unsigned char gray[H][W];                         // アフィン変換後のデータを格納する配列grayを宣言

  // 配列grayを0で初期化
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      gray[i][j] = 0;
    }
  }

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* アフィン変換を行う処理 */
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      /* 変換後の座標x, yを計算 */
      x = a * j + b * i + c;
      y = d * j + e * i + f;

      /* 最近隣内挿法を行い、代入 */
      gray[(int)(y + 0.5)][(int)(x + 0.5)] = gray_source[i][j];
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, 700, 750, gradation);   // ファイルにヘッダ部を書き込む
  for(i = 0; i < 750; i++){
    fwrite(gray[i], sizeof(char), 700, fp);                         // ファイルにデータ部を書き込む
  }
  fclose(fp);                                                       // ファイルを閉じる

  return 0;
}

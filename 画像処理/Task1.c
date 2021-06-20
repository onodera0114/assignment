#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char filename[256] = "Lenna"; // ファイル名を宣言
struct RGB{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void Output(struct RGB *rgb, char *comment, int w, int h, int g, char *color){
  FILE *fp;
  char path[] = "./Output/Task1/";  // 出力するディレクトリを宣言
  unsigned char gray[256*256];
  int i;

  // path, filename, color, 拡張子(.pgm)を結合して出力場所の相対パスを作成
  strcat(path, filename);
  strcat(path, color);
  strcat(path, ".pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(path, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // colorがRedの時、構造体RGBの配列rgbから赤だけを取り出す
  if(strcmp(color, "Red") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].red;
    }
  }
  // colorがGreenの時、構造体RGBの配列rgbから緑だけを取り出す
  else if(strcmp(color, "Green") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].green;
    }
  }
  // colorがBlueの時、構造体RGBの配列rgbから青だけを取り出す
  else if(strcmp(color, "Blue") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].blue;
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // ファイルにヘッダ部を書き込む
  fwrite(gray, sizeof(char), h*w, fp); // ファイルにデータ部を書き込む
  fclose(fp); // ファイルを閉じる
}

void OutputAverage(struct RGB *rgb, char *comment, int w, int h, int g){
  FILE *fp;
  char path[] = "./Output/Task1/"; // 出力するディレクトリを宣言
  unsigned char gray[256*256];
  int i;

  // path, filename, color, 拡張子(.pgm)を結合して出力場所の相対パスを作成
  strcat(path, filename);
  strcat(path, "Average");
  strcat(path, ".pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(path, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // 構造体RGBの配列rgbのメンバ(red, green, blue)の平均を出し、配列grayに代入
  for(i = 0; i < 256 * 256; i++){
      gray[i] = (rgb[i].red + rgb[i].green + rgb[i].blue) / 3;
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // ファイルにヘッダ部を書き込む
  fwrite(gray, sizeof(char), h*w, fp); // ファイルにデータ部を書き込む
  fclose(fp); // ファイルを閉じる
}

void OutputY(struct RGB *rgb, char *comment, int w, int h, int g){
  FILE *fp;
  char path[] = "./Output/Task1/"; // 出力するディレクトリを宣言
  unsigned char gray[256*256];
  int i;

  // path, filename, color, 拡張子(.pgm)を結合して出力場所の相対パスを作成
  strcat(path, filename);
  strcat(path, "Y");
  strcat(path, ".pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(path, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // 構造体RGBの配列rgbの値から輝度Yを計算し、配列grayに代入
  for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].red * 0.299 + rgb[i].green * 0.587 + rgb[i].blue * 0.114;
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // ファイルにヘッダ部を書き込む
  fwrite(gray, sizeof(char), h*w, fp); // ファイルにデータ部を書き込む
  fclose(fp); // ファイルを閉じる
}

int main(void){
  FILE *fp;
  char format[256], comment[256], gradation[128];
  int width, height, g;
  char red[256] = "Red";
  char green[256] = "Green";
  char blue[256] = "Blue";
  char path[256] = "./imgdata/"; // 読み取るディレクトリを宣言
  struct RGB rgb[256*256];

  // path, filename, color, 拡張子(.pgm)を結合して読み取るファイルの相対パスを作成
  strcat(path, filename);
  strcat(path, ".ppm");

  // 読み込みモードでファイルを開く
  fp = fopen(path, "rb");

  // ファイルを開けなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}

  fgets(format, 256, fp); // 形式を読み取り、配列formatに代入
  fgets(comment, 256, fp); // コメントを読み取り、配列commentに代入
  fscanf(fp, "%d %d", &width, &height); // 幅と高さを読み取り、幅をwidth、高さをheightに代入
  fgets(gradation, 128, fp); // 高さの後の改行コードを読み取り、配列gradationに代入
  fgets(gradation, 128, fp); // 最大階調値を読み取り、配列gradationに代入
  g = atoi(gradation); // gradationのデータ(最大階調値)を数値に変換
  fread(rgb, sizeof(struct RGB), width * height, fp); // データ部を読み込む
  fclose(fp); // ファイルを閉じる

  Output(rgb, comment, width, height, g, red); // 赤だけを取り出し、出力
  Output(rgb, comment, width, height, g, green); // 緑だけを取り出し、出力
  Output(rgb, comment, width, height, g, blue); // 青だけを取り出し、出力
  OutputAverage(rgb, comment, width, height, g); // 赤、緑、青の平均を計算し、出力
  OutputY(rgb, comment, width, height, g); // 輝度Yを計算し、出力

  return 0;
}

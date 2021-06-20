#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define W width
#define H height

char filename[256] = "HighColor";                   // ファイル名を宣言

struct RGB{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/* rgbからHSVに変換する関数 */
void rgb2hsv(unsigned char r, unsigned char g, unsigned char b, double *h, double *s, double *v){
  double max, min;
  double R, G, B;
  R = (double)r;
  G = (double)g;
  B = (double)b;
  max = MAX(MAX(R, G), B);            // 最大値を計算
  min = MIN(MIN(R, G), B);            // 最小値を計算

  if(max == min){
    *h = 0;
  }
  else if(max == R){
    *h = 60 * ((G - B) / (max - min));
  }
  else if(max == B){
    *h = 60 * ((B - R) / (max - min)) + 120;
  }
  else{
    *h = 60 * ((B - R) / (max - min)) + 240;
  }

  if(*h < 0){
    *h += 360;
  }

  if(max == 0){
    *s = 0;
  }
  else{
    *s = (max - min) / max;
  }
  *v = max;

}

/* HSVからrgbに変換 */
void hsv2rgb(double h, double s, double v, unsigned char *r, unsigned char *g, unsigned char *b){
  int h_dash;
  double p, q, t, f;

  h_dash = (int)(h / 60) % 6;
  f = (h / 60) - h_dash;
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - (1 - f) * s);

  switch (h_dash){
    case 0:
      *r = v;
      *g = t;
      *b = p;
      break;
    case 1:
      *r = q;
      *g = v;
      *b = p;
      break;
    case 2:
      *r = p;
      *g = v;
      *b = t;
      break;
    case 3:
      *r = p;
      *g = q;
      *b = v;
      break;
    case 4:
      *r = t;
      *g = p;
      *b = v;
      break;
    case 5:
      *r = v;
      *g = p;
      *b = q;
      break;
  default:
      *r = v;
      *g = v;
      *b = v;
    break;
  }
}

int main(void){
  FILE *fp;                                         // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, gradation;
  char inputpath_gray[256] = "./Data/High.pgm";     // 読み取るディレクトリを宣言
  char inputpath_color[256] = "./Data/Low.ppm";   // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task10/";        // 出力するディレクトリを宣言
  int i, j;
  double h, s, v;
  unsigned char r, g, b;


  // 読み込みモードでファイルを開く
  fp = fopen(inputpath_gray, "rb");

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
  gradation = atoi(msg);                            // 配列msgのデータ(最大階調値)を数値に変換

  unsigned char gray[W * H];                        // グレイスケール画像のデータを格納する配列grayを宣言
  fread(gray, sizeof(char), width * height, fp);    // データ部を読み込む
  fclose(fp);                                       // ファイルを閉じる

  // 読み込みモードでファイルを開く
  fp = fopen(inputpath_color, "rb");

  // ファイルを開けなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
		exit(1);
	}

  fgets(format, 256, fp);                               // 形式を読み取り、配列formatに代入
  fgets(comment, 256, fp);                              // コメントを読み取り、配列commentに代入
  fscanf(fp, "%d %d", &width, &height);                 // 幅と高さを読み取り、幅をwidth、高さをheightに代入
  fgets(msg, 128, fp);                                  // 高さの後の改行コードを読み取り、配列msgに代入
  fgets(msg, 128, fp);                                  // 最大階調値を読み取り、配列msgに代入
  gradation = atoi(msg);                                // 配列msgのデータ(最大階調値)を数値に変換

  struct RGB rgb[H * W];                                // カラー画像のデータを格納する配列rgbを宣言
  fread(rgb, sizeof(struct RGB), width * height, fp);   // データ部を読み込む
  fclose(fp);                                           // ファイルを閉じる

  // outputpath, filename, .ppmを結合して出力場所の相対パスを作成
  strcat(outputpath, filename);
  strcat(outputpath, ".ppm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* 高画質グレースケール画像と低画質カラー画像から高画質カラー画像を作成する処理 */
  for(i = 0; i < width * height; i++){
    r = rgb[i].red;
    g = rgb[i].green;
    b = rgb[i].blue;
    rgb2hsv(r, g, b, &h, &s, &v);         // rgbからHSVに変換
    v = gray[i];
    hsv2rgb(h, s, v, &r, &g, &b);         // HSVからrgbに変換
    rgb[i].red = r;
    rgb[i].green = g;
    rgb[i].blue = b;
  }
  fprintf(fp, "P6\n%s%d %d\n%d\n", comment, width, height, gradation);  // ファイルにヘッダ部を書き込む
  fwrite(rgb, sizeof(struct RGB), height * width, fp);                  // ファイルにデータ部を書き込む
  fclose(fp);                                                           // ファイルを閉じる

  return 0;
}

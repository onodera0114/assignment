#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WE width * N              // 拡大時の横幅を計算
#define HE height * N             // 拡大時の縦幅を計算
#define WR (int)(width / N)       // 縮小時の横幅を計算
#define HR (int)(height / N)      // 縮小時の縦幅を計算
#define pai 3.14159265            // 円周率
#define W (int)(abs(width * cos(theta)) + abs(height * sin(theta)))   // 回転時の横幅を計算
#define H (int)(abs(width * sin(theta)) + abs(height * cos(theta)))   // 回転時の縦幅を計算

char filename[] = "pepper"; // ファイル名を宣言

int main(void){
  FILE *fp;                                   // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  int N = 2;                                  // 拡大倍率・縮小倍率を宣言
  char inputpath[256] = "./Output/Task1/";    // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task2/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // グレイスケール画像のデータを格納する配列を宣言
  double theta = 30 * (pai / 180);            // 回転量をラジアンで宣言
  int x, y;                                   // 回転後の座標を格納する変数x, yを宣言
  int i, j;
  int e, f;                                   // 横方向の移動量e, 縦方向の移動量fを宣言

  // path, filename, color, 拡張子(.pgm)を結合して読み取るファイルの相対パスを作成
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


  /* 拡大処理 */
  unsigned char enlargement[WE][HE];            // 拡大データを格納する配列enlargementを宣言

  // outputpath, filename, Enlargement.pgm を結合して出力場所の相対パスを作成
  strcat(outputpath, filename);
  strcat(outputpath, "Enlargement.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // 直線補間法を用いて拡大処理
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      /* 下端部分の計算 */
      if(i >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j + 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i - 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i - 1][j + 1]) / 2;
      }
      /* 右端部分の計算 */
      else if(j >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j - 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i + 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i + 1][j - 1]) / 2;
      }
      /* 右下部分の計算 */
      else if(i >= 255 && j >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j - 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i - 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i - 1][j - 1]) / 2;
      }
      /* それ以外の部分の計算 */
      else{
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j + 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i + 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i + 1][j + 1]) / 2;
      }
    }
  }
  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, WE, HE, g); // ファイルにヘッダ部を書き込む
  fwrite(enlargement, sizeof(char), WE * HE, fp);       // ファイルにデータ部を書き込む
  fclose(fp);                                           // ファイルを閉じる


  /* 縮小処理 */
  unsigned char reduction[WR][HR];                // 縮小データを格納する配列reductionを宣言

  // outputpath, filename, Reduction.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task2/");
  strcat(outputpath, filename);
  strcat(outputpath, "Reduction.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // 平均操作法を用いて縮小処理
  for(i = 0; i < HR; i++){
    for(j = 0; j < WR; j++){
      /* 4箇所の画素の平均を計算し、配列reductionに格納する */
      reduction[i][j] = (gray[i * N][j * N] + gray[i * N][j * N + 1] + gray[i * N + 1][j * N] + gray[i * N + 1][j * N + 1]) / 4;
    }
  }
  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, WR, HR, g); // ファイルにヘッダ部を書き込む
  fwrite(reduction, sizeof(char), WR * HR, fp);         // ファイルにデータ部を書き込む
  fclose(fp);                                           // ファイルを閉じる


  /* 回転処理 */
  unsigned char rotation[W][H];                          // 回転データを格納する配列rotationを宣言

  // outputpath, filename, Rotation.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task2/");
  strcat(outputpath, filename);
  strcat(outputpath, "Rotation.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
  }

  // 配列rotationの全ての要素を0で初期化
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      rotation[i][j] = 0;
    }
  }

  // 平行移動する量を計算
  e = 0;
  f = H - height * cos(theta);

  // 回転処理
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      /* 回転後の座標を計算 */
      x = j * cos(theta) + i * sin(theta) + e;
      y = -j * sin(theta) + i * cos(theta) + f;
      /* 配列rotationに格納 */
      rotation[y][x] = gray[i][j];
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, W, H, g); // ファイルにヘッダ部を書き込む
  fwrite(rotation, sizeof(char), W * H, fp);          // ファイルにデータ部を書き込む
  fclose(fp);                                         // ファイルを閉じる

  return 0;
}

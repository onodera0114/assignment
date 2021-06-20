#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DATA 9                            // ソートする配列のデータ数
char filename[256] = "pepper";              // 画像のファイル名を宣言
char filename_noise[256] = "pepper_noise";  // ノイズ画像のファイル名を宣言

/* 配列をソートし、中央値を返す関数 */
int median(int *sort){
  int i, j;
  int tmp = 0;

  // バブルソートでソートを行う処理
  for(i = 0; i < DATA; i++){
    for(j = 0; j < DATA - i; j++){
      if(sort[j] > sort[j + 1]){
        tmp = sort[j];
        sort[j] = sort[j + 1];
        sort[j + 1] = tmp;
      }
    }
  }

  // 中央値を返す
  return sort[(DATA - 1) / 2];
}

/* 引数の値が範囲外の値であれば修正する関数 */
int CheckData(int number){
  // 0以下の時, 0を返す
  if(number <= 0){
    return 0;
  }
  // 255以上の時, 255を返す
  else if(number >= 255){
    return 255;
  }
  // それ以外の時はそのままの値を返す
  else{
    return number;
  }
}

int main(void){
  FILE *fp;                                               // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";                // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task4/";               // 出力するディレクトリを宣言
  unsigned char gray[256][256];                           // グレイスケール画像データを格納する配列を宣言
  unsigned char gray_noise[256][256];                     // ノイズ入りのグレイスケール画像データを格納する配列を宣言
  unsigned char gray_median[256][256];                    // ノイズ除去後のデータを格納する配列を宣言
  unsigned char gray_laplacian[256][256];                 // 鮮鋭化後のデータを格納する配列を宣言
  int neighborhood[9] = {0};                              // 近傍画素を格納する配列を宣言
  int filter[3][3] = {{1, 1, 1}, {1, -8, 1}, {1, 1, 1}};  // 8近傍ラプラシアンフィルタ
  int sum = 0;                                            // フィルタと近傍画素の積の和の合計を格納する変数
  int i, j, m, n;
  int k = 0;


  /* メディアンフィルタを用いてノイズ除去 */

  // inputpath, filename_noise, Y.pgm を結合して読み取るファイルの相対パスを作成
  strcat(inputpath, filename_noise);
  strcat(inputpath, "Y.pgm");

  // 読み込みモードでファイルを開く
  fp = fopen(inputpath, "rb");

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
  g = atoi(msg);                                          // gradationのデータ(最大階調値)を数値に変換
  fread(gray_noise, sizeof(char), width * height, fp);    // データ部を読み込む
  fclose(fp);                                             // ファイルを閉じる

  // outputpath, filename_noise, Median.pgm を結合して出力場所の相対パスを作成
  strcat(outputpath, filename_noise);
  strcat(outputpath, "Median.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // メディアンフィルタを用いてノイズ除去を行う処理
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // 近傍画素の値を配列neighborhoodに格納する
      if(i > 0 && j > 0 && i < 255 && j < 255){
        for(m = 0; m < 3; m++){
          for(n = 0; n < 3; n++){
            neighborhood[k] = gray_noise[i - 1 + m][j - 1 + n];
            k++;
          }
        }

        // 近傍画素の中央値を求め、注目画素の値とする
        gray_median[i][j] = median(neighborhood);
        k = 0;
      }
      // 上下左右端の画素のとき現在の画素の値を注目画素の値とする
      else{
        gray_median[i][j] = gray_noise[i][j];
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g); // ファイルにヘッダ部を書き込む
  fwrite(gray_median, sizeof(char), width * height, fp);       // ファイルにデータ部を書き込む
  fclose(fp);                                                  // ファイルを閉じる


  /* 8近傍ラプラシアンフィルタを用いて鮮鋭化 */

  // inputpath, filename, Y.pgm を結合して読み取るファイルの相対パスを作成
  strcpy(inputpath, "./Output/Task1/");
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

  // outputpath, filename, Laplacian.pgm を結合して出力場所の相対パスを作成
  strcpy(outputpath, "./Output/Task4/");
  strcat(outputpath, filename);
  strcat(outputpath, "Laplacian.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
		printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  // 8近傍ラプラシアンフィルタを用いて鮮鋭化を行う処理
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // 近傍画素とフィルタの積の合計を計算
      if(i > 0 && j > 0 && i < 255 && j < 255){
        for(m = 0; m < 3; m++){
          for(n = 0; n < 3; n++){
            sum += gray[i - 1 + m][j - 1 + n] * filter[m][n];
          }
        }
        // 現在の画素から近傍画素とフィルタの積の合計を引いたものを注目画素の値とする
        gray_laplacian[i][j] = CheckData(gray[i][j] - sum);
        sum = 0;
      }
      // 上下左右端の画素のとき現在の画素の値を注目画素の値とする
      else{
        gray_laplacian[i][j] = gray[i][j];
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // ファイルにヘッダ部を書き込む
  fwrite(gray_laplacian, sizeof(char), width * height, fp);     // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  return 0;
}

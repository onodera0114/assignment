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
  char outputpath[256] = "./Output/Task9/";   // 出力するディレクトリを宣言
  unsigned char gray[256][256];               // グレイスケール画像のデータを格納する配列grayを宣言
  unsigned char gray_quantization[256][256];  // 量子化後のデータを格納する配列gray_quantizationを宣言
  int concentration[256] = {0};               // 濃度に対する頻度を格納する配列concentrationを宣言
  int average[16] = {0};                      // 各範囲間の濃度の平均を格納する配列averageを宣言
  double psnr;                                // PSNRを格納する変数
  int sum = 0;                                // 濃度値の合計を格納する変数
  int count = 0;                              // 濃度の数の合計を格納する変数
  int i, j, k;

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

  // outputpath, filename, Quantization_Advance.pgmを結合して出力場所の相対パスを作成
  strcat(outputpath, filename);
  strcat(outputpath, "Quantization_Advance.pgm");

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* 各画素に対する濃度を求める処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      concentration[gray[i][j]]++;
    }
  }

  /* 濃度間(16ごと)の濃度の平均を求める処理 */
  for(i = 0; i < 15; i++){
    for(j = 0; j < 17; j++){
      sum += concentration[(17 * i) + j] * ((17 * i) + j);    // 濃度値の合計を計算
      count += concentration[(17 * i) + j];                   // 濃度数の合計を計算
    }
    /* countが0出ない時は平均を計算し、0のときは17 * iとする → ゼロ除算の回避 */
    if(count != 0){
      average[i] = sum / count;
    }
    else{
      average[i] = 17 * i;
    }
    sum = 0;
    count = 0;
  }
  average[15] = 255;

  /* 量子化を行う処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      for(k = 0; k < 16; k++){
        /* k * 17 <= gray[i][j] <= (k + 1) * 17 - 1 の時にk * 17 を量子化後の値とする */
        if(gray[i][j] >= k * 17 && gray[i][j] <= ((k + 1) * 17 - 1)){
          gray_quantization[i][j] = average[k];
          break;
        }
      }
    }
  }

  /* PSNRを計算する処理 */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      sum += (gray[i][j] - gray_quantization[i][j]) * (gray[i][j] - gray_quantization[i][j]);
    }
  }

  psnr = 10 * log10(255 * 255 / (sum / (256 * 256)));
  printf("PSNR : %f\n", psnr);

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // ファイルにヘッダ部を書き込む
  fwrite(gray_quantization, sizeof(char), width * height, fp);     // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  return 0;
}

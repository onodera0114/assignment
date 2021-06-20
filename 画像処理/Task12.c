#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define W 256             // 画像の幅(logo_gray_small.pgm)
#define H 256             // 画像の高さ(logo_gray_small.pgm)

int labeling[H][W];       // ラベリングした結果を格納する配列

/* ラベリングを行う関数*/
void Labeling(int i, int j, int count){
  /* ラベリング済みかを判定*/
  if(labeling[i][j] != 0){
    return;                           //ラベリングしていたら終了
  }
  else if(i < 0 || i > H || j < 0 || j > W){
    return;                           // 範囲外なら終了
  }
  else{
    labeling[i][j] = count;           // 配列labelingにラベリングナンバーを代入
    Labeling(i - 1, j - 1, count);    // 左上の探索
    Labeling(i, j - 1, count);        // 左の探索
    Labeling(i + 1, j - 1, count);    // 左下の探索
    Labeling(i - 1, j, count);        // 上の探索
    Labeling(i + 1, j, count);        // 下の探索
    Labeling(i - 1, j + 1, count);    // 右上の探索
    Labeling(i, j + 1, count);        // 右の探索
    Labeling(i + 1, j + 1, count);    // 右下の探索
  }
}

int main(void){
  FILE *fp;                                                      // ファイルポインタ
  char format[256], comment[256], msg[128];
  int width, height, gradation;
  unsigned char gray[H][W];                                      // 画像データを格納する配列grayを宣言
  unsigned char gray_Link[H][W];                                 // ラベリングした画像データを格納する配列gray_Linkを宣言
  char inputpath[256] = "./data-label/logo_gray_small.pgm";      // 読み取るディレクトリを宣言
  char outputpath[256] = "./Output/Task12/gray_Labeling.pgm";    // 出力するディレクトリを宣言
  int i, j;
  int count = 0;                                                 // ラベリングナンバーを格納する変数

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
  gradation = atoi(msg);                            // gradationのデータ(最大階調値)を数値に変換
  fread(gray, sizeof(char), W * H, fp);             // データ部を読み込む
  fclose(fp);                                       // ファイルを閉じる

  // 書き込みモードでファイルを作成
  fp = fopen(outputpath, "wb");

  // 配列gray_Linkとlabelingを0で初期化
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      gray_Link[i][j] = 0;
      labeling[i][j] = 0;
    }
  }

  // ファイルを作成できなかった時に終了する
	if(fp == NULL) {
    printf("ファイルを開けませんでした。\n");
    exit(1);
	}

  /* ２値化処理*/
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      if(gray[i][j] >= 100){
        gray_Link[i][j] = 255;
        labeling[i][j] = -1;      // 白の部分を-1に置き換える
      }
      else{
        gray_Link[i][j] = 0;
      }
    }
  }

  /* ラベリングを行う処理*/
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      /* 黒の部分をラベリングする */
      if(labeling[i][j] == 0){
        count++;                    // ラベリングナンバーを加算
        Labeling(i, j, count);      // 関数Labelingへ
      }
    }
  }

  /* 配列Labelingをもとに画像データを生成 */
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      if(labeling[i][j] != -1){
        gray_Link[i][j] = (255 / count - 1) * labeling[i][j] + 20;
      }
      else{
        gray_Link[i][j] = 0;
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, W, H, gradation);   // ファイルにヘッダ部を書き込む
  fwrite(gray_Link, sizeof(char), W * H, fp);                   // ファイルにデータ部を書き込む
  fclose(fp);                                                   // ファイルを閉じる

  return 0;
}

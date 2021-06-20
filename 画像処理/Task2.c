#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WE width * N              // �g�厞�̉������v�Z
#define HE height * N             // �g�厞�̏c�����v�Z
#define WR (int)(width / N)       // �k�����̉������v�Z
#define HR (int)(height / N)      // �k�����̏c�����v�Z
#define pai 3.14159265            // �~����
#define W (int)(abs(width * cos(theta)) + abs(height * sin(theta)))   // ��]���̉������v�Z
#define H (int)(abs(width * sin(theta)) + abs(height * cos(theta)))   // ��]���̏c�����v�Z

char filename[] = "pepper"; // �t�@�C������錾

int main(void){
  FILE *fp;                                   // �t�@�C���|�C���^
  char format[256], comment[256], msg[128];
  int width, height, g;
  int N = 2;                                  // �g��{���E�k���{����錾
  char inputpath[256] = "./Output/Task1/";    // �ǂݎ��f�B���N�g����錾
  char outputpath[256] = "./Output/Task2/";   // �o�͂���f�B���N�g����錾
  unsigned char gray[256][256];               // �O���C�X�P�[���摜�̃f�[�^���i�[����z���錾
  double theta = 30 * (pai / 180);            // ��]�ʂ����W�A���Ő錾
  int x, y;                                   // ��]��̍��W���i�[����ϐ�x, y��錾
  int i, j;
  int e, f;                                   // �������̈ړ���e, �c�����̈ړ���f��錾

  // path, filename, color, �g���q(.pgm)���������ēǂݎ��t�@�C���̑��΃p�X���쐬
  strcat(inputpath, filename);
  strcat(inputpath, "Y.pgm");

  // �ǂݍ��݃��[�h�Ńt�@�C�����J��
  fp = fopen(inputpath, "rb");

  // �t�@�C�����J���Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
		exit(1);
	}

  fgets(format, 256, fp);                           // �`����ǂݎ��A�z��format�ɑ��
  fgets(comment, 256, fp);                          // �R�����g��ǂݎ��A�z��comment�ɑ��
  fscanf(fp, "%d %d", &width, &height);             // ���ƍ�����ǂݎ��A����width�A������height�ɑ��
  fgets(msg, 128, fp);                              // �����̌�̉��s�R�[�h��ǂݎ��A�z��msg�ɑ��
  fgets(msg, 128, fp);                              // �ő�K���l��ǂݎ��A�z��msg�ɑ��
  g = atoi(msg);                                    // gradation�̃f�[�^(�ő�K���l)�𐔒l�ɕϊ�
  fread(gray, sizeof(char), width * height, fp);    // �f�[�^����ǂݍ���
  fclose(fp);                                       // �t�@�C�������


  /* �g�又�� */
  unsigned char enlargement[WE][HE];            // �g��f�[�^���i�[����z��enlargement��錾

  // outputpath, filename, Enlargement.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(outputpath, filename);
  strcat(outputpath, "Enlargement.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // ������Ԗ@��p���Ċg�又��
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      /* ���[�����̌v�Z */
      if(i >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j + 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i - 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i - 1][j + 1]) / 2;
      }
      /* �E�[�����̌v�Z */
      else if(j >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j - 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i + 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i + 1][j - 1]) / 2;
      }
      /* �E�������̌v�Z */
      else if(i >= 255 && j >= 255){
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j - 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i - 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i - 1][j - 1]) / 2;
      }
      /* ����ȊO�̕����̌v�Z */
      else{
        enlargement[i * N][j * N] = gray[i][j];
        enlargement[i * N][j * N + 1] = (gray[i][j] + gray[i][j + 1]) / 2;
        enlargement[i* N + 1][j * N] = (gray[i][j] + gray[i + 1][j]) / 2;
        enlargement[i * N + 1][j * N + 1] = (gray[i][j] + gray[i + 1][j + 1]) / 2;
      }
    }
  }
  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, WE, HE, g); // �t�@�C���Ƀw�b�_������������
  fwrite(enlargement, sizeof(char), WE * HE, fp);       // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                           // �t�@�C�������


  /* �k������ */
  unsigned char reduction[WR][HR];                // �k���f�[�^���i�[����z��reduction��錾

  // outputpath, filename, Reduction.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcpy(outputpath, "./Output/Task2/");
  strcat(outputpath, filename);
  strcat(outputpath, "Reduction.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
    printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // ���ϑ���@��p���ďk������
  for(i = 0; i < HR; i++){
    for(j = 0; j < WR; j++){
      /* 4�ӏ��̉�f�̕��ς��v�Z���A�z��reduction�Ɋi�[���� */
      reduction[i][j] = (gray[i * N][j * N] + gray[i * N][j * N + 1] + gray[i * N + 1][j * N] + gray[i * N + 1][j * N + 1]) / 4;
    }
  }
  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, WR, HR, g); // �t�@�C���Ƀw�b�_������������
  fwrite(reduction, sizeof(char), WR * HR, fp);         // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                           // �t�@�C�������


  /* ��]���� */
  unsigned char rotation[W][H];                          // ��]�f�[�^���i�[����z��rotation��錾

  // outputpath, filename, Rotation.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcpy(outputpath, "./Output/Task2/");
  strcat(outputpath, filename);
  strcat(outputpath, "Rotation.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
    printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
  }

  // �z��rotation�̑S�Ă̗v�f��0�ŏ�����
  for(i = 0; i < H; i++){
    for(j = 0; j < W; j++){
      rotation[i][j] = 0;
    }
  }

  // ���s�ړ�����ʂ��v�Z
  e = 0;
  f = H - height * cos(theta);

  // ��]����
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      /* ��]��̍��W���v�Z */
      x = j * cos(theta) + i * sin(theta) + e;
      y = -j * sin(theta) + i * cos(theta) + f;
      /* �z��rotation�Ɋi�[ */
      rotation[y][x] = gray[i][j];
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, W, H, g); // �t�@�C���Ƀw�b�_������������
  fwrite(rotation, sizeof(char), W * H, fp);          // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                         // �t�@�C�������

  return 0;
}

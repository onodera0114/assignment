#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char filename[256] = "Lenna"; // �t�@�C������錾
struct RGB{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void Output(struct RGB *rgb, char *comment, int w, int h, int g, char *color){
  FILE *fp;
  char path[] = "./Output/Task1/";  // �o�͂���f�B���N�g����錾
  unsigned char gray[256*256];
  int i;

  // path, filename, color, �g���q(.pgm)���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(path, filename);
  strcat(path, color);
  strcat(path, ".pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(path, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // color��Red�̎��A�\����RGB�̔z��rgb����Ԃ��������o��
  if(strcmp(color, "Red") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].red;
    }
  }
  // color��Green�̎��A�\����RGB�̔z��rgb����΂��������o��
  else if(strcmp(color, "Green") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].green;
    }
  }
  // color��Blue�̎��A�\����RGB�̔z��rgb������������o��
  else if(strcmp(color, "Blue") == 0){
    for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].blue;
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // �t�@�C���Ƀw�b�_������������
  fwrite(gray, sizeof(char), h*w, fp); // �t�@�C���Ƀf�[�^������������
  fclose(fp); // �t�@�C�������
}

void OutputAverage(struct RGB *rgb, char *comment, int w, int h, int g){
  FILE *fp;
  char path[] = "./Output/Task1/"; // �o�͂���f�B���N�g����錾
  unsigned char gray[256*256];
  int i;

  // path, filename, color, �g���q(.pgm)���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(path, filename);
  strcat(path, "Average");
  strcat(path, ".pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(path, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // �\����RGB�̔z��rgb�̃����o(red, green, blue)�̕��ς��o���A�z��gray�ɑ��
  for(i = 0; i < 256 * 256; i++){
      gray[i] = (rgb[i].red + rgb[i].green + rgb[i].blue) / 3;
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // �t�@�C���Ƀw�b�_������������
  fwrite(gray, sizeof(char), h*w, fp); // �t�@�C���Ƀf�[�^������������
  fclose(fp); // �t�@�C�������
}

void OutputY(struct RGB *rgb, char *comment, int w, int h, int g){
  FILE *fp;
  char path[] = "./Output/Task1/"; // �o�͂���f�B���N�g����錾
  unsigned char gray[256*256];
  int i;

  // path, filename, color, �g���q(.pgm)���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(path, filename);
  strcat(path, "Y");
  strcat(path, ".pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(path, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // �\����RGB�̔z��rgb�̒l����P�xY���v�Z���A�z��gray�ɑ��
  for(i = 0; i < 256 * 256; i++){
      gray[i] = rgb[i].red * 0.299 + rgb[i].green * 0.587 + rgb[i].blue * 0.114;
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, w, h, g); // �t�@�C���Ƀw�b�_������������
  fwrite(gray, sizeof(char), h*w, fp); // �t�@�C���Ƀf�[�^������������
  fclose(fp); // �t�@�C�������
}

int main(void){
  FILE *fp;
  char format[256], comment[256], gradation[128];
  int width, height, g;
  char red[256] = "Red";
  char green[256] = "Green";
  char blue[256] = "Blue";
  char path[256] = "./imgdata/"; // �ǂݎ��f�B���N�g����錾
  struct RGB rgb[256*256];

  // path, filename, color, �g���q(.pgm)���������ēǂݎ��t�@�C���̑��΃p�X���쐬
  strcat(path, filename);
  strcat(path, ".ppm");

  // �ǂݍ��݃��[�h�Ńt�@�C�����J��
  fp = fopen(path, "rb");

  // �t�@�C�����J���Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
		exit(1);
	}

  fgets(format, 256, fp); // �`����ǂݎ��A�z��format�ɑ��
  fgets(comment, 256, fp); // �R�����g��ǂݎ��A�z��comment�ɑ��
  fscanf(fp, "%d %d", &width, &height); // ���ƍ�����ǂݎ��A����width�A������height�ɑ��
  fgets(gradation, 128, fp); // �����̌�̉��s�R�[�h��ǂݎ��A�z��gradation�ɑ��
  fgets(gradation, 128, fp); // �ő�K���l��ǂݎ��A�z��gradation�ɑ��
  g = atoi(gradation); // gradation�̃f�[�^(�ő�K���l)�𐔒l�ɕϊ�
  fread(rgb, sizeof(struct RGB), width * height, fp); // �f�[�^����ǂݍ���
  fclose(fp); // �t�@�C�������

  Output(rgb, comment, width, height, g, red); // �Ԃ��������o���A�o��
  Output(rgb, comment, width, height, g, green); // �΂��������o���A�o��
  Output(rgb, comment, width, height, g, blue); // ���������o���A�o��
  OutputAverage(rgb, comment, width, height, g); // �ԁA�΁A�̕��ς��v�Z���A�o��
  OutputY(rgb, comment, width, height, g); // �P�xY���v�Z���A�o��

  return 0;
}

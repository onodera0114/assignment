#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DATA 9                            // �\�[�g����z��̃f�[�^��
char filename[256] = "pepper";              // �摜�̃t�@�C������錾
char filename_noise[256] = "pepper_noise";  // �m�C�Y�摜�̃t�@�C������錾

/* �z����\�[�g���A�����l��Ԃ��֐� */
int median(int *sort){
  int i, j;
  int tmp = 0;

  // �o�u���\�[�g�Ń\�[�g���s������
  for(i = 0; i < DATA; i++){
    for(j = 0; j < DATA - i; j++){
      if(sort[j] > sort[j + 1]){
        tmp = sort[j];
        sort[j] = sort[j + 1];
        sort[j + 1] = tmp;
      }
    }
  }

  // �����l��Ԃ�
  return sort[(DATA - 1) / 2];
}

/* �����̒l���͈͊O�̒l�ł���ΏC������֐� */
int CheckData(int number){
  // 0�ȉ��̎�, 0��Ԃ�
  if(number <= 0){
    return 0;
  }
  // 255�ȏ�̎�, 255��Ԃ�
  else if(number >= 255){
    return 255;
  }
  // ����ȊO�̎��͂��̂܂܂̒l��Ԃ�
  else{
    return number;
  }
}

int main(void){
  FILE *fp;                                               // �t�@�C���|�C���^
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";                // �ǂݎ��f�B���N�g����錾
  char outputpath[256] = "./Output/Task4/";               // �o�͂���f�B���N�g����錾
  unsigned char gray[256][256];                           // �O���C�X�P�[���摜�f�[�^���i�[����z���錾
  unsigned char gray_noise[256][256];                     // �m�C�Y����̃O���C�X�P�[���摜�f�[�^���i�[����z���錾
  unsigned char gray_median[256][256];                    // �m�C�Y������̃f�[�^���i�[����z���錾
  unsigned char gray_laplacian[256][256];                 // �N�s����̃f�[�^���i�[����z���錾
  int neighborhood[9] = {0};                              // �ߖT��f���i�[����z���錾
  int filter[3][3] = {{1, 1, 1}, {1, -8, 1}, {1, 1, 1}};  // 8�ߖT���v���V�A���t�B���^
  int sum = 0;                                            // �t�B���^�ƋߖT��f�̐ς̘a�̍��v���i�[����ϐ�
  int i, j, m, n;
  int k = 0;


  /* ���f�B�A���t�B���^��p���ăm�C�Y���� */

  // inputpath, filename_noise, Y.pgm ���������ēǂݎ��t�@�C���̑��΃p�X���쐬
  strcat(inputpath, filename_noise);
  strcat(inputpath, "Y.pgm");

  // �ǂݍ��݃��[�h�Ńt�@�C�����J��
  fp = fopen(inputpath, "rb");

  // �t�@�C�����J���Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
		exit(1);
	}

  fgets(format, 256, fp);                                 // �`����ǂݎ��A�z��format�ɑ��
  fgets(comment, 256, fp);                                // �R�����g��ǂݎ��A�z��comment�ɑ��
  fscanf(fp, "%d %d", &width, &height);                   // ���ƍ�����ǂݎ��A����width�A������height�ɑ��
  fgets(msg, 128, fp);                                    // �����̌�̉��s�R�[�h��ǂݎ��A�z��msg�ɑ��
  fgets(msg, 128, fp);                                    // �ő�K���l��ǂݎ��A�z��msg�ɑ��
  g = atoi(msg);                                          // gradation�̃f�[�^(�ő�K���l)�𐔒l�ɕϊ�
  fread(gray_noise, sizeof(char), width * height, fp);    // �f�[�^����ǂݍ���
  fclose(fp);                                             // �t�@�C�������

  // outputpath, filename_noise, Median.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(outputpath, filename_noise);
  strcat(outputpath, "Median.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // ���f�B�A���t�B���^��p���ăm�C�Y�������s������
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // �ߖT��f�̒l��z��neighborhood�Ɋi�[����
      if(i > 0 && j > 0 && i < 255 && j < 255){
        for(m = 0; m < 3; m++){
          for(n = 0; n < 3; n++){
            neighborhood[k] = gray_noise[i - 1 + m][j - 1 + n];
            k++;
          }
        }

        // �ߖT��f�̒����l�����߁A���ډ�f�̒l�Ƃ���
        gray_median[i][j] = median(neighborhood);
        k = 0;
      }
      // �㉺���E�[�̉�f�̂Ƃ����݂̉�f�̒l�𒍖ډ�f�̒l�Ƃ���
      else{
        gray_median[i][j] = gray_noise[i][j];
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g); // �t�@�C���Ƀw�b�_������������
  fwrite(gray_median, sizeof(char), width * height, fp);       // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                                  // �t�@�C�������


  /* 8�ߖT���v���V�A���t�B���^��p���đN�s�� */

  // inputpath, filename, Y.pgm ���������ēǂݎ��t�@�C���̑��΃p�X���쐬
  strcpy(inputpath, "./Output/Task1/");
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

  // outputpath, filename, Laplacian.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcpy(outputpath, "./Output/Task4/");
  strcat(outputpath, filename);
  strcat(outputpath, "Laplacian.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  // 8�ߖT���v���V�A���t�B���^��p���đN�s�����s������
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      // �ߖT��f�ƃt�B���^�̐ς̍��v���v�Z
      if(i > 0 && j > 0 && i < 255 && j < 255){
        for(m = 0; m < 3; m++){
          for(n = 0; n < 3; n++){
            sum += gray[i - 1 + m][j - 1 + n] * filter[m][n];
          }
        }
        // ���݂̉�f����ߖT��f�ƃt�B���^�̐ς̍��v�����������̂𒍖ډ�f�̒l�Ƃ���
        gray_laplacian[i][j] = CheckData(gray[i][j] - sum);
        sum = 0;
      }
      // �㉺���E�[�̉�f�̂Ƃ����݂̉�f�̒l�𒍖ډ�f�̒l�Ƃ���
      else{
        gray_laplacian[i][j] = gray[i][j];
      }
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, g);  // �t�@�C���Ƀw�b�_������������
  fwrite(gray_laplacian, sizeof(char), width * height, fp);     // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                                   // �t�@�C�������

  return 0;
}

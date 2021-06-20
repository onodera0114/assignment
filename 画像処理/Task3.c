#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[256] = "pepper"; // �t�@�C������錾

// �ڕW�p�x�Ɨݐϕp�x�̍��̐�Βl��Ԃ��֐�
int CalculateDifference(int frequency, int accumulation){
  return abs(frequency - accumulation);
}

int main(void){
  FILE *fp;                                   // �t�@�C���|�C���^
  char format[256], comment[256], msg[128];
  int width, height, g;
  char inputpath[256] = "./Output/Task1/";    // �ǂݎ��f�B���N�g����錾
  char outputpath[256] = "./Output/Task3/";   // �o�͂���f�B���N�g����錾
  unsigned char gray[256][256];               // �␳�O�̃f�[�^���i�[����z��gray��錾
  unsigned char gray_correction[256][256];    // �␳��̃f�[�^���i�[����z��gray_correction��錾
  int before_diff = 0;                        // �O�̖ڕW�p�x�Ɨݐϕp�x�̍��̐�Βl���i�[����ϐ�
  int concentration[256] = {0};               // �Z�x�ɑ΂���p�x���i�[����z��concentration��錾
  int accumulation = 0;                // �Z�x�ɑ΂���ݐϕp�x���i�[����z��accumulation��錾
  int correction[256] = {0};                  // �Z�x�ɑ΂���␳�Z�x���i�[����z��correction��錾
  int targetfrequency;                        // �ڕW�p�x���i�[����ϐ�
  int cor = 0;                                // �␳�Z�x���i�[����ϐ�
  int gradation = 64;                         // �ڕW�K������錾
  int i, j;

  // inputpath, filename, Y.pgm ���������ēǂݎ��t�@�C���̑��΃p�X���쐬
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

  // outputpath, filename, .csv ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcat(outputpath, filename);
  strcat(outputpath, ".csv");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
		printf("�t�@�C�����J���܂���ł���\n");
		exit(1);
	}

  /* �e��f�ɑ΂���Z�x�����߂鏈�� */
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      concentration[gray[i][j]]++;
    }
  }

  /* �e��f�ɑ΂���Z�x��csv�t�@�C���ɏo�͂��鏈�� */
  fprintf(fp, "�Z�x,�p�x\n");
  for(i = 0; i < 256; i++){
    fprintf(fp, "%d, %d\n", i, concentration[i]);
  }
  fclose(fp); // �t�@�C�������

  // outputpath, filename, Correction.pgm ���������ďo�͏ꏊ�̑��΃p�X���쐬
  strcpy(outputpath, "./Output/Task3/");
  strcat(outputpath, filename);
  strcat(outputpath, "Correction.pgm");

  // �������݃��[�h�Ńt�@�C�����쐬
  fp = fopen(outputpath, "wb");

  // �t�@�C�����쐬�ł��Ȃ��������ɏI������
	if(fp == NULL) {
    printf("�t�@�C�����J���܂���ł����B\n");
    exit(1);
	}

  targetfrequency = (width * height) / gradation;  // �p�x�ڕW�l���v�Z

  /* �Z�x�ϊ��\���쐬���鏈�� */
  for(i = 0; i < 256; i++){
    // ���݂̒~�ϕp�x�Ɍ��݂̔Z�x�����Z
    accumulation += concentration[i];
    // ���݂̖ڕW�p�x�Ɨݐϕp�x�̍��̐�Βl�ƑO��̖ڕW�p�x�Ɨݐϕp�x�̍��̐�Βl���r
    if(before_diff < CalculateDifference(targetfrequency, accumulation)){
      // �~�ϕp�x��0�ɂ���
      accumulation = concentration[i];
      // �␳�Z�x���P���Z
      cor++;

      // �␳�Z�x���ڕW�K�����𒴂������ɕ␳�Z�x��(�ڕW�K����-1)�ɂ���
      if(cor >= gradation){
        cor = gradation - 1;
      }
    }
    // ���݂̕␳�Z�x��������
    correction[i] = cor;

    // ���݂̖ڕW�p�x�Ɨݐϕp�x�̍��̐�Βl���v�Z���A�i�[����
    before_diff = CalculateDifference(targetfrequency, accumulation);
  }

  /* �Z�x�ϊ��\�����ƂɊe��f�̔Z�x��␳���鏈�� */
  for(i = 0; i < 256; i++){
    for(j = 0;j < 256; j++){
      gray_correction[i][j] = correction[gray[i][j]];
    }
  }

  fprintf(fp, "P5\n%s%d %d\n%d\n", comment, width, height, gradation);  // �t�@�C���Ƀw�b�_������������
  fwrite(gray_correction, sizeof(char), width * height, fp);                // �t�@�C���Ƀf�[�^������������
  fclose(fp);                                                               // �t�@�C�������

  return 0;
}

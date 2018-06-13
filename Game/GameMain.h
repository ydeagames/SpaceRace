//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  SpaceRace �m�[�}���ۑ�
//!
//! @date   2018/06/13
//!
//! @author GF1 26 �R������
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �萔�̒�` ==============================================================

// <�V�X�e��> ----------------------------------------------------------
#define GAME_TITLE "Space Race"        // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (640)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (480)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)




// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);


--VirtuaNES����v���O�C�� �J���L�b�g(LDK)--

1.���߂�

  ����LDK�́CVirtuaNES�̕������_�C�A���O���e����ɑΉ������邽�߂Ɏg�p����J��
  �L�b�g�ł��B
  �O���v���O�C���ɂ��鎖�ŁC����e����ɑΉ�����̂��y�����鎖���o����Ǝv���܂��B

2.�J���ɓ������ĕK�v�ȃ\�t�g�E�F�A

  �EVisual C++(v6.0�ō쐬���܂���)


3.��Ǝ菇

  �E�܂��C�A�[�J�C�u��K���ȃt�H���_�ɓW�J���܂��B

  �ELDK.dsw��Visual C++�ŊJ���܂��B

  �EVisual C++�̃��j���[����C[��ۼު��]->[�ݒ�]->[�ݸ]�^�u��I�����C�o�̓t�@�C
    ����(N)�̗���ύX���܂��B�g���q�͕K���C"vlp"�ɂ��Ă��������B

  �EVisual C++�̃��j���[����C[��ۼު��]->[�ݒ�]->[ؿ��]�^�u��I�����C����(L)��
    �Ή����錾��ɕύX���܂��B

  �E���j���[�C�_�C�A���O�C�X�g�����O�̊e���\�[�X���e����ɖ|�󂵕ύX���܂��B

  �E�����N���܂��B

  �J�����g�t�H���_��"���ꖼ.vlp"�t�@�C�����o���オ��܂��̂ŁC�����VirtuaNES��
  �����t�H���_�ɒu���Ă��������B

  �Ȃ��CVirtuaNES���ċN�����Ȃ��ƃv���O�C���Ƃ��ĔF������܂���B

  ��v0.20�ȑO��VirtuaNES�Ƃ̓��\�[�XID�Ɩ��̂��قȂ��Ă��܂��̂Œ��ӂ��Ă��������B

--------------------------------------------------------------------------------
�t�H���g�w��̖��ɕt����

  �e���ŃE�C���h�E�Y�ɂ����āC�_�C�A���O�Ɏg�p����t�H���g���C���X�g�[�������
  ���Ȃ��ꍇ���l������K�v������܂��̂ŁC�W���ŃC���X�g�[������Ă���͂��̃t
  �H���g�𗘗p����悤�ɂ��Ă����K�v������܂��B

  Visual C++�̃_�C�A���O�G�f�B�^�ł̕\���ƁC���ۂɓ����������ɑ傫�����ς���
  ��������܂��̂Œ��ӂ��Ă��������B

  �܂��C���{��ŃE�C���h�E�Y2000�ł́CMS Sans serif���g�p���Ă�Microsoft sans serif
  ���C���X�g�[������Ă���Ƃ�����ɂȂ��Ă��܂���肪����܂����B

  ����������ƁC�e����ł�Visual C++�ł��ς�����肷��̂����m��܂���B

  �Ȃ��C�_�C�A���O�͎g�p����ɍ��킹�ăt�H���g�w���"�K��"�s���Ă��������B

  ���̖��_�ɕt���Ă̌���I�ȉ�����͂킩��܂���B

--------------------------------------------------------------------------------

4.�K�{����

  �ȉ��̊֐��͕K���e����Ή��̍ۂɏC�����Ă��������B

--------------------------------------------------------------------------------
  INT	GetVlpVersion( void );

  �o�[�W������Ԃ��܂��BVirtuaNESv0.20�ȍ~�ŃT�|�[�g�����ׁC�K��v0.20�ȏ�Ƃ�
  ��܂��B

  AABBCCDD(HEX)�Ƃ����ꍇ�C

  AA,BB		�g�p���܂���
  CC		�o�[�W����
  DD		���r�W����

  0x00000120�Ƃ����ꍇ�C�o�[�W�������P�C���r�W�������Q�O�ƂȂ�܂��B

  ���j10�i���ŕ\�L���Ȃ����ɒ��ӂ��Ă��������B

  ���j���̊֐��̏C���͕K�v�Ȃ��Ȃ�܂����B

--------------------------------------------------------------------------------
  VOID	GetVlpLanguage( LPSTR lpLanguage );

  �Ή����ꖼ��Ԃ��܂��B�K���p�ꖼ(*1)�ŕԂ��܂��B

  ��)
  ����					| ���ꖼ
  --------------------------------------+--------------
  ���{��				| Japanese
  �؍���				| Korean
  �p��(�A�����J)(*2)			| English(US)
  �p��(�C�M���X)(*2)			| English(UK)
  �p��(�A�����J)(MS PGothic)(*3)	| English(US)(MS PGothic)


  (*1)  ���ʂɃ_�u���N�H�[�e�[�V�����Ŋ����������ł��B
  (*2)  ����ɑΉ����鍑������ꍇ�́C���ʓ��ɍ�������͂��܂��B
  (*3)  �g�p�t�H���g�����ʃC���X�g�[������Ă��Ȃ��ꍇ���l�����āC�t�H���g����
        ���͂���ꍇ������܂��B

--------------------------------------------------------------------------------

  LCID	GetVlpLocaleID( void );

  �g�p����̃��P�[��ID��Ԃ��܂��BVirtuaNES�������Ń��[�U�[���P�[�����擾���āC
  �v���O�C�����Ή����郍�P�[��ID�ƓK������ꍇ�C���̃v���O�C�����f�t�H���g�����
  ���܂��B

  LCID�ꗗ(MSDN���C�u���������p)

	Identifier	Language
	--------------------------------------------------------------
	0x0000		Language Neutral		�����g��Ȃ�
	0x0400		Process Default Language	�����g��Ȃ�
	0x0401		Arabic (Saudi Arabia)
	0x0801		Arabic (Iraq)
	0x0c01		Arabic (Egypt)
	0x1001		Arabic (Libya)
	0x1401		Arabic (Algeria)
	0x1801		Arabic (Morocco)
	0x1c01		Arabic (Tunisia)
	0x2001		Arabic (Oman)
	0x2401		Arabic (Yemen)
	0x2801		Arabic (Syria)
	0x2c01		Arabic (Jordan)
	0x3001		Arabic (Lebanon)
	0x3401		Arabic (Kuwait)
	0x3801		Arabic (U.A.E.)
	0x3c01		Arabic (Bahrain)
	0x4001		Arabic (Qatar)
	0x0402		Bulgarian
	0x0403		Catalan
	0x0404		Chinese (Taiwan Region)
	0x0804		Chinese (PRC)
	0x0c04		Chinese (Hong Kong SAR, PRC)
	0x1004		Chinese (Singapore)
	0x0405		Czech
	0x0406		Danish
	0x0407		German (Standard)
	0x0807		German (Swiss)
	0x0c07		German (Austrian)
	0x1007		German (Luxembourg)
	0x1407		German (Liechtenstein)
	0x0408		Greek
	0x0409		English (United States)
	0x0809		English (United Kingdom)
	0x0c09		English (Australian)
	0x1009		English (Canadian)
	0x1409		English (New Zealand)
	0x1809		English (Ireland)
	0x1c09		English (South Africa)
	0x2009		English (Jamaica)
	0x2409		English (Caribbean)
	0x2809		English (Belize)
	0x2c09		English (Trinidad)
	0x040a		Spanish (Traditional Sort)
	0x080a		Spanish (Mexican)
	0x0c0a		Spanish (Modern Sort)
	0x100a		Spanish (Guatemala)
	0x140a		Spanish (Costa Rica)
	0x180a		Spanish (Panama)
	0x1c0a		Spanish (Dominican Republic)
	0x200a		Spanish (Venezuela)
	0x240a		Spanish (Colombia)
	0x280a		Spanish (Peru)
	0x2c0a		Spanish (Argentina)
	0x300a		Spanish (Ecuador)
	0x340a		Spanish (Chile)
	0x380a		Spanish (Uruguay)
	0x3c0a		Spanish (Paraguay)
	0x400a		Spanish (Bolivia)
	0x440a		Spanish (El Salvador)
	0x480a		Spanish (Honduras)
	0x4c0a		Spanish (Nicaragua)
	0x500a		Spanish (Puerto Rico)
	0x040b		Finnish
	0x040c		French (Standard)
	0x080c		French (Belgian)
	0x0c0c		French (Canadian)
	0x100c		French (Swiss)
	0x140c		French (Luxembourg)
	0x040d		Hebrew
	0x040e		Hungarian
	0x040f		Icelandic
	0x0410		Italian (Standard)
	0x0810		Italian (Swiss)
	0x0411		Japanese
	0x0412		Korean
	0x0812		Korean (Johab)
	0x0413		Dutch (Standard)
	0x0813		Dutch (Belgian)
	0x0414		Norwegian (Bokmal)
	0x0814		Norwegian (Nynorsk)
	0x0415		Polish
	0x0416		Portuguese (Brazilian)
	0x0816		Portuguese (Standard)
	0x0418		Romanian
	0x0419		Russian
	0x041a		Croatian
	0x081a		Serbian (Latin)
	0x0c1a		Serbian (Cyrillic)
	0x041b		Slovak
	0x041c		Albanian
	0x041d		Swedish
	0x081d		Swedish (Finland)
	0x041e		Thai
	0x041f		Turkish
	0x0421		Indonesian
	0x0422		Ukrainian
	0x0423		Belarusian
	0x0424		Slovenian
	0x0425		Estonian
	0x0426		Latvian
	0x0427		Lithuanian
	0x0429		Farsi
	0x042a		Vietnamese
	0x042d		Basque
	0x0436		Afrikaans
	0x0438		Faeroese

--------------------------------------------------------------------------------


5.VirtuaNES���o�[�W�����A�b�v�����ꍇ�ɕt����

  ��{�I��VirtuaNES���o�[�W�����A�b�v�����ꍇ�Ƀ��\�[�X�̕ύX���������́CLDK����
  �l�Ƀo�[�W�������A�b�v���܂��B

  ����LDK���g�p���ăv���O�C��������Ă����ꍇ�́CLDK�̃A�[�J�C�u����K��,
  "VirtuaNESres.h" �t�@�C�����R�s�[���� "���r���h" ���Ă��������B

  �܂��C���j���[���ڂ�_�C�A���O�����ǉ����ꂽ�ꍇ�́C���̕���������"VirtuaNES.rc"
  �t�@�C������J�b�g�A���h�y�[�X�g����Ȃ肵�Ēǉ����Ă��������B

  "VirtuaNES.rc","VirtuaNESres.h" ���R�s�[���ĂP�����蒼���Ă�OK�ł��B

////////////////////////////////////////////////////////////////////////////////
// ���\�[�X�̃o�[�W���������X�V����̂�Y��Ȃ��悤�ɂ��Ă�������           //
////////////////////////////////////////////////////////////////////////////////


6.�����[�X�̍ۂ�

  ��ʂ�_�C�A���O�⃁�j���[���@�\���邩�ǂ������m���߂Ă��烊���[�X���Ă��������B

  �Ȃ�ׂ�VirtuaNES�����y�[�W�ɒu�������̂ŁCnorix_v@NOVIRUS!yahoo.co.jp�܂Ń��[��
  �ő����Ē�����Ƃ��肪�����ł��B



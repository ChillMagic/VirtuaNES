
--VirtuaNES言語プラグイン 開発キット(LDK)--

1.初めに

  このLDKは，VirtuaNESの文字列やダイアログを各言語に対応させるために使用する開発
  キットです。
  外部プラグインにする事で，毎回各言語に対応するのを軽減する事が出来ると思います。

2.開発に当たって必要なソフトウェア

  ・Visual C++(v6.0で作成しました)


3.作業手順

  ・まず，アーカイブを適当なフォルダに展開します。

  ・LDK.dswをVisual C++で開きます。

  ・Visual C++のメニューから，[ﾌﾟﾛｼﾞｪｸﾄ]->[設定]->[ﾘﾝｸ]タブを選択し，出力ファイ
    ル名(N)の欄を変更します。拡張子は必ず，"vlp"にしてください。

  ・Visual C++のメニューから，[ﾌﾟﾛｼﾞｪｸﾄ]->[設定]->[ﾘｿｰｽ]タブを選択し，言語(L)を
    対応する言語に変更します。

  ・メニュー，ダイアログ，ストリングの各リソースを各国語に翻訳し変更します。

  ・リンクします。

  カレントフォルダに"言語名.vlp"ファイルが出来上がりますので，それをVirtuaNESと
  同じフォルダに置いてください。

  なお，VirtuaNESを再起動しないとプラグインとして認識されません。

  ※v0.20以前のVirtuaNESとはリソースIDと名称が異なっていますので注意してください。

--------------------------------------------------------------------------------
フォント指定の問題に付いて

  各国版ウインドウズにおいて，ダイアログに使用するフォントがインストールされて
  いない場合を考慮する必要がありますので，標準でインストールされているはずのフ
  ォントを利用するようにしておく必要があります。

  Visual C++のダイアログエディタでの表示と，実際に動かした時に大きさが変わる場
  合もありますので注意してください。

  また，日本語版ウインドウズ2000では，MS Sans serifを使用してもMicrosoft sans serif
  がインストールされているとそちらになってしまう問題がありました。

  もしかすると，各言語版のVisual C++でも変わったりするのかも知れません。

  なお，ダイアログは使用言語に合わせてフォント指定を"必ず"行ってください。

  この問題点に付いての決定的な解決策はわかりません。

--------------------------------------------------------------------------------

4.必須事項

  以下の関数は必ず各言語対応の際に修正してください。

--------------------------------------------------------------------------------
  INT	GetVlpVersion( void );

  バージョンを返します。VirtuaNESv0.20以降でサポートされる為，必ずv0.20以上とな
  ります。

  AABBCCDD(HEX)とした場合，

  AA,BB		使用しません
  CC		バージョン
  DD		リビジョン

  0x00000120とした場合，バージョンが１，リビジョンが２０となります。

  注）10進数で表記しない所に注意してください。

  注）この関数の修正は必要なくなりました。

--------------------------------------------------------------------------------
  VOID	GetVlpLanguage( LPSTR lpLanguage );

  対応言語名を返します。必ず英語名(*1)で返します。

  例)
  言語					| 言語名
  --------------------------------------+--------------
  日本語				| Japanese
  韓国語				| Korean
  英語(アメリカ)(*2)			| English(US)
  英語(イギリス)(*2)			| English(UK)
  英語(アメリカ)(MS PGothic)(*3)	| English(US)(MS PGothic)


  (*1)  普通にダブルクォーテーションで括った文字です。
  (*2)  言語に対応する国がある場合は，括弧内に国名を入力します。
  (*3)  使用フォントが普通インストールされていない場合を考慮して，フォント名を
        入力する場合もあります。

--------------------------------------------------------------------------------

  LCID	GetVlpLocaleID( void );

  使用言語のロケールIDを返します。VirtuaNESが内部でユーザーロケールを取得して，
  プラグインが対応するロケールIDと適合する場合，そのプラグインをデフォルト言語と
  します。

  LCID一覧(MSDNライブラリより引用)

	Identifier	Language
	--------------------------------------------------------------
	0x0000		Language Neutral		多分使わない
	0x0400		Process Default Language	多分使わない
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


5.VirtuaNESがバージョンアップした場合に付いて

  基本的にVirtuaNESがバージョンアップした場合にリソースの変更が伴う時は，LDKも同
  様にバージョンがアップします。

  既にLDKを使用してプラグインを作っていた場合は，LDKのアーカイブから必ず,
  "VirtuaNESres.h" ファイルをコピーして "リビルド" してください。

  また，メニュー項目やダイアログ等が追加された場合は，その部分だけを"VirtuaNES.rc"
  ファイルからカットアンドペーストするなりして追加してください。

  "VirtuaNES.rc","VirtuaNESres.h" をコピーして１からやり直してもOKです。

////////////////////////////////////////////////////////////////////////////////
// リソースのバージョン情報を更新するのを忘れないようにしてください           //
////////////////////////////////////////////////////////////////////////////////


6.リリースの際に

  一通りダイアログやメニューが機能するかどうかを確かめてからリリースしてください。

  なるべくVirtuaNES公式ページに置きたいので，norix_v@NOVIRUS!yahoo.co.jpまでメール
  で送って頂けるとありがたいです。



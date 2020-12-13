
--VirtuaNES language plug-in Development Kit--

///////////////////////////////////////////////////////
/// The sentence was got with translation software. ///
///////////////////////////////////////////////////////

1.Introduction

This LDK is a development kit to use in order to let character string and 
DIALOG of VirtuaNES cope with each language.

I think that each language can reduce every time that I cope by making you 
outside plug-in.


2.Necessary software

Visual C++ (it was made with version 6.0)


3.Working

- At first an archive is developed in a suitable folder.

- LDK.dsw is opened with Visual C++.

- A tab is chosen among a menu of Visual C++ [Project]->[Setting]->[Link], 
  and a column of output file name (N) is changed. Please turn extension 
  into "vlp" by all means.

- A menu, DIALOG, each resource of a string are translated in each language, 
  and it is changed.

- Build.

- Because a "language name.vlp" file is completed in a baing current folder, 
  please put it with a folder the same as VirtuaNES.

In addition, it is not recognized that VirtuaNES is not activated again as 
plug-in.

Note) Because resource ID and a name are different from VirtuaNES before v0.20, 
      please pay attention.

--------------------------------------------------------------------------------
Be assigned to a problem of font appointment

  Because it is necessary to consider the case that a font to use for DIALOG 
  isn't installed in in Windows for each country, be normal, and it is necessary 
  to take advantage of the font that should be installed.

  Because there is it when size changes when, actually, moved it with indication 
  with a DIALOG editor of Visual C++, please pay attention.

  In addition, there was the problem that it had been it there that Microsoft 
  sans serif was installed even if used MS Sans serif in Windows 2000 for 
  Japanese.

  Even Visual C++ for each language may be what change when grazes it.

  In addition, DIALOG please do font appointment in accordance with a use 
  language by all means.

  Be assigned to these problems, and don't understand a decisive solution.

--------------------------------------------------------------------------------

4.Required matter

Please correct the following functions by all means in case for each language.

-------------------------------------------------------------------------------

  INT GetVlpVersion( void );

  A version is returned.

  I grow more than 0.20 by all means so that it is supported after VirtuaNES 
  version0.20.

  When it was done with AABBCCDD(HEX),

  AA,BB		Not use(must be zero)
  CC		version
  DD		revision

  When did it with 0120(Hex), version is 1(decimal), revision rises with 20(decimal).

  Note)Please pay attention to the place that is not transcribed in the 
       decimal system.

  Note)The revision of this function became needless.

-------------------------------------------------------------------------------

  VOID GetVlpLanguage( LPSTR lpLanguage )

  A correspondence language name is returned.

  It is returned by English name (*1) by all means.

  Example)
  Language				| Language name
  --------------------------------------+---------------
  Japanese				| Japanese
  The language of Republic of Korea	| Korea
  English (America) (*2)		| English(US)
  English (Britain) (*2)		| English(UK)
  English (America)(MS PGothic) (*3)	| English(US)(MS PGothic)

  (*1)It is a letter bound with a double quotation mark commonly.
  (*2)When there is a country corresponding to a language, the name of a 
      country is input in a parenthesis.
  (*3)Consider the case that a use font isn't installed in generally, and 
      there is it when inputs a font name.
-------------------------------------------------------------------------------

  LCID	GetVlpLocaleID( void );

  LocaleID(LCID) of a use language is returned.

  When VirtuaNES acquires user LCID inside, and plug-in conforms to it with 
  supporting LCID, the plug-in is done with a default language.

  LCID LIST (it is quoted than a MSDN library)

	Identifier	Language
	----------------------------------------------------
	0x0000		Language Neutral
	0x0400		Process Default Language
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

5.When VirtuaNES revised it, you are accompanied

When a change of a resource is accompanied when VirtuaNES revised it basically, 
LDK is similar, and a version ups.

When LDK is used already, and plug-in was made, a ,"VirtuaNESres.h" file is 
copied from an archive of LDK by all means, and please do "rebuilding".

In addition, only the part is cut and pasted from a "VirtuaNES.rc" file, it is 
done, and please add it when menu item or DIALOG were added.

"VirtuaNES.rc","VirtuaNESres.h" is copied, and it is revised from a beginning, 
and I may get over.

/////////////////////////////////////////////////////////////////////////////
// Please do not forget that version information of a resource is updated. //
/////////////////////////////////////////////////////////////////////////////

6.In case of release

Please release it after checking whether DIALOG and a menu function generally.

Because it wants to be put on a VirtuaNES formula page if possible, there is 
hard to be it that I have send it with an email to norix_v@NOVIRUS!yahoo.co.jp




	#include		<io.h>
	#include		<dos.h>
	#include		<bios.h>
	#include		<time.h>
	#include		<conio.h>
	#include		<stdio.h>
	#include		<ctype.h>
	#include		<stdlib.h>
	#include		<string.h>


	/* Remark : */
	/*
		Marco name are all captial letters
		Class	name begins with tt_
		Struct name begins with tts_
	*/

	struct	tts_score
	{
		int		nword;
		int		incorrect;
		int		nchar;
		int		timelength;

		tts_score(int w,int i,int c,int t)
		{
			this->nword 		= w;
			this->incorrect	= i;
			this->nchar			= c;
			this->timelength	= t;
		}
	};

	void 	form		(void);
	void	credit	(void);
	void	sform		(tts_score);
	void	fingerpos(char,char);
	char* format	(int,char*);
	int	fexists	(char*);
	int	score		(char**,tts_score);


	#define	RX			21
	#define	G1			22
	#define	G2			23
	#define	IY			3


	#define	IT_TIME			1000
	#define	RTIME				50
	#define	LIMIT_T			1000
	#define	SAME				1
	#define	END				0
	#define	NSAME				-1
	#define	ICOUNT			100
	#define	ID_ALIVE			1
	#define	ID_DEAD			0
	#define	ID_KILLING		1
	#define	ID_ACTIVE		1
	#define	ID_HIT			1
	#define	ID_ARRIVE		-1
	#define	NOTSCROLL	0
	#define	SCROLL		1
	#define	READ_BINARY		"rb"
	#define	MESSAGE_1	"PRESS ANY KEY TO GO TO MAIN MENU..."
	#define	FILEERROR	"FILE NOT FOUND ERROR ::"
	#define	FILESTMT		"FILE (%s) IS NOT FOUND.."
	#define	HEADER		"Typing Tutor"
	#define	FOOTER		"Press ALT+X to quit"
	#define	DEVELOPER	"Developed by Aung Thaw Aye"
	#define	STEP_1		"Use Up/Down Arrow to move selection"
	#define	STEP_2		"Press Enter to choose"
	#define	STEP_3		"Press Alt+X to quit to window"
	#define	STEP_4		"Press ESC to back"

	#define	TFILE_1		".\\ATA\\TYPING\\FILES\\TEST0001.FIL"
	#define	TFILE_2		".\\ATA\\TYPING\\FILES\\TEST0002.FIL"
	#define	TFILE_3		".\\ATA\\TYPING\\FILES\\TEST0003.FIL"
	#define	TFILE_4		".\\ATA\\TYPING\\FILES\\TEST0004.FIL"
	#define	TFILE_5		".\\ATA\\TYPING\\FILES\\TEST0005.FIL"
	#define	TFILE_6		".\\ATA\\TYPING\\FILES\\TEST0006.FIL"
	#define	TFILE_7		".\\ATA\\TYPING\\FILES\\TEST0007.FIL"
	#define	TFILE_8		".\\ATA\\TYPING\\FILES\\TEST0008.FIL"
	#define	TFILE_9		".\\ATA\\TYPING\\FILES\\TEST0009.FIL"
	#define	TFILE_10		".\\ATA\\TYPING\\FILES\\TEST0010.FIL"

	#define	LSFILE		".\\ATA\\TYPING\\FILES\\LESN000F.FIL"
	#define	GAFILE		".\\ATA\\TYPING\\FILES\\GAME000G.FIL"
	#define	FNFILE		".\\ATA\\TYPING\\FILES\\FINGER00.FIL"
	#define	NUFILE		".\\ATA\\TYPING\\FILES\\NUMERIC0.FIL"

	enum	KEYCODE
	{
		ALT_X			= 11520,
		ESC 			= 283,
		ENTER			= 7181,
		TAB			= 3849,
		SHIFT_TAB	= 3840,
		BACKSPACE	= 3592,
		LEFT_ARROW	= 19200,
		RIGHT_ARROW	= 19712,
		UP_ARROW		= 18432,
		DOWN_ARROW	= 20480
	};
	/* to draw box */
	struct	tts_style
	{
		int	upperleft_cor;
		int	lowerleft_cor;
		int	upperright_cor;
		int	lowerright_cor;
		int	horizontal;
		int	vertical;

		tts_style(int upl,int lol,int upr,int lor,int hor,int ver)
		{
			this->upperleft_cor 	= upl;
			this->lowerleft_cor	= lol;
			this->upperright_cor	= upr;
			this->lowerright_cor	= lor;
			this->horizontal		= hor;
			this->vertical			= ver;
		}
	};

	/* for structure of file and others */


	struct	tts_state
	{
		unsigned	bool : 2;
	};

	struct	tts_text
	{
		char	text[76];
	};

	struct	tts_lesson /* for lesson and finger */
	{
		char	text[52];
	};

	struct	tts_numeric
	{
		char	text[37];
	};

	struct	tts_invadertext
	{
		char	text[11];
		int	coorX;

	};

	struct	tt_item
	{
		char	text[11];
		int	x;
		int	y;
		int	length;
	};

	/* for displaying text */

	const static char		testnames[10][33] =	{	TFILE_1,
																TFILE_2,
																TFILE_3,
																TFILE_4,
																TFILE_5,
																TFILE_6,
																TFILE_7,
																TFILE_8,
																TFILE_9,
																TFILE_10
															};


	class	tt_writer
	{
		public	:	void	normalwrite	(int,int,char*,char);
						void	reversewrite(int,int,char*,char);
						void	ndelaywrite	(int,int,char*,int,char);
						void	rdelaywrite	(int,int,char*,int,char);
						void	nsoundwrite	(int,int,char*,int,int,char);
						void	rsoundwrite	(int,int,char*,int,int,char);
						void	textprinter(int,int,char*,char);
	};

	/* for drawing */
	class	tt_painter
	{
		private	:	char	color;

		public	:  tt_painter()
						{
							this->color = 0x1f;
						}
						void	setcolor(char,char);
						void	border(int,int,int,int,tts_style,char);
						void	basewindow(void);
						void	box(int,int,int,int,tts_style,char);
						void	defaultwindow(void);
						void	horizontalline(int,int,char,int,char);
						void	verticalline(int,int,char,int,char);
	};

	/* for highliting text */
	class	tt_highlite
	{
		public	:	void	highlite(int,int,int,char);
	};

	class	tt_counter
	{
		public	:	int	wordcount(char*);
	};

	class tt_typing
	{
		private	:	void 	form(void);
		public	:	void 	run(void);
	};


	class	tt_test
	{
		struct	tts_text		store [10];
		private	:  char	ttfilename [35];
						int	timelength;
						int	incorrect;
						int	nchar;
						int	nword;

						void	form(void);
						void  readname(void);

		public	:	void	run(void);
	};

	class	tt_class
	{
		struct	tts_lesson		lstore[3];/* for lesson and finger struct */
		struct	tts_numeric		nstore[3];

		private	:  int	incorrect;
						int	nchar;
						int	nword;
						int	timelength;

						void	form(void);
						int	lesson(void);
						int	finger(void);
						int	numeric(void);
						int	game(void);

						void	lesson_form(void);
						void	finger_form(void);
						void	numeric_form(void);
						void	game_form(void);

						int	gscore(int,int);

		public	:	void	run(void);

	};

	class	tt_invader
	{
		private	:  int			coorX;   		/* for coordinat X of text */
						int			coorY;			/* for Y of invader */
						int			index;
						int			length;
						int			rocket_coorY;
						char			attr;
						char			text[11];
						char			buffer[2];	/* to store bk text of rocket */
						tts_state	live;
						tts_state	active;
						tts_state	state;

						void	repaint(void);
						void	clear(void);
			public	:

						void	create(char*,int);
						void	kill(void);
						void	setactive(int);
						int	move(int);
						int	shoot(int);
						int	killing(void);
						int	compare(char);
						int	isdead(void);
						int	isactive(void);
	};


/*--------------------------------------------------------------------------*/
/* Source Code for typing tutor::                                           */
/*--------------------------------------------------------------------------*/




	int	score (char** item_names,tts_score T)
	{
		const	int size = 3;
		tt_painter		P;
		tt_writer		W;
		tt_highlite		H;

		int	item_index = 0;
		int	coorY = 2;
		int	keypress = 0;


		sform(T);
		/* to create the box for menu*/
		P.box(25,17,54,21,tts_style(213,212,184,190,205,179),0x2f);
		/* to print all the menu items into the menu box */
		for(item_index = 0 ,coorY = 2; item_index < size ; item_index++,coorY++)
			W.normalwrite(3,coorY,item_names[item_index],0x2f);
		/* to go to first menu item */
		coorY = 2;item_index = 0;

		while(1)
		{
			/* to highlite the current menu item */
			H.highlite(28,2,coorY,0x1E);
			/* wait for key pressed */
			while(bioskey(1)==0)	;
			/* to reset the current menu item*/
			H.highlite(28,2,coorY,0x2F);
			keypress = bioskey(0);
			switch(keypress)
			{
				case UP_ARROW:
				case SHIFT_TAB:   coorY--;
										if( --item_index == -1 )
										{
											item_index = size - 1;
											coorY = size + 1;
										}
										break;

				case DOWN_ARROW:
				case TAB:         coorY++;
										if( ++item_index == size )
										{
											item_index = 0;
												coorY = 2;
										}
										break;

				case ENTER:       if(item_index < 2)
											return item_index;
										else
											exit(0);
				case ESC:			return -1;
				case ALT_X:			exit(0);

			} /* end of switch case */
		} /* end of while loop */

	}/* end of method score */

/*--------------------------------------------------------------------------*/

	void 	sform (tts_score T)
	{
		tt_painter		P;
		tt_writer		W;
		tt_counter		C;
		int				line;
		int				speed;
		int				accuracy;
		long				percent;
		char				buffer[20];

		percent 	= T.nchar - T.incorrect;
		percent 	= 100 * percent;
		accuracy = percent / T.nchar;
		speed		= (T.timelength > 1) ? T.nword / T.timelength : T.nword / T.timelength * 2;

		P.basewindow();
		P.box(10,3,70,15,tts_style(201,200,187,188,205,186),0x1F);
		/* to draw table */
		P.horizontalline(2,3,'Í',60,0x1F);
		P.verticalline(30,2,'º',11,0x1F);
		gotoxy(30,1 ); putch('Ë');
		gotoxy(30,13); putch('Ê');
		gotoxy(30,3 ); putch('Î');
		gotoxy(1 ,3 ); putch('Ì');
		gotoxy(61,3 ); putch('¹');

		W.normalwrite(10,2,"Description",0x1F);
		W.normalwrite(40,2,"Performance",0x1F);

		W.normalwrite(10,5,"Total no of words",0x1F);
		W.normalwrite(10,7,"Timelength",0x1F);
		W.normalwrite(10,9,"Accuracy",0x1F);
		W.normalwrite(10,11,"Speed",0x1F);

		sprintf(buffer,"%d W",T.nword);
		W.normalwrite(45,5 ,buffer,0x17);
		sprintf(buffer,"%d MIN",T.timelength);
		W.normalwrite(45,7 ,buffer,0x17);
		sprintf(buffer,"%d %",accuracy);
		W.normalwrite(45,9 ,buffer,0x17);
		sprintf(buffer,"%d WPM",speed);
		W.normalwrite(45,11,buffer,0x17);
	}

/*--------------------------------------------------------------------------*/

	int	fexists (char *name)
	{
		/* to check whether file exists or not */
		if(access(name,0) != 0)
		{
			tt_writer		W;
			tt_painter		P;
			char				buffer[100];

			P.box(10,10,70,14,tts_style(218,192,191,217,196,179),0x4F);
			sprintf(buffer,FILESTMT,name);
			W.normalwrite(5,2,FILEERROR,0x4E);
			W.normalwrite(5,3,buffer	,0x4E);
			W.normalwrite(5,4,MESSAGE_1,0x4F);
			while(bioskey(1)==0);
			bioskey(0);
			return 0;
		}
		return 1;
	}

/*--------------------------------------------------------------------------*/

	void	paintkeyboard(char attr)
	{
		window(10,13,70,23);textattr(attr);
		clrscr();
		gotoxy(1,1); cprintf("  ÚÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÄÄÄÄÄÄ¿");
		gotoxy(1,2); cprintf("  ³ 1 ³ 2 ³ 3 ³ 4 ³ 5 ³ 6 ³ 7 ³ 8 ³ 9 ³ 0 ³- _³= +³  <ÄÄÄ   ³");
		gotoxy(1,3); cprintf("  ÀÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÄÄÄÄÄÄ´");
		gotoxy(1,4); cprintf("    ³ Q ³ W ³ E ³ R ³ T ³ Y ³ U ³ I ³ O ³ P ³[ }³] }³       ³");
		gotoxy(1,5); cprintf("    ÀÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÙ       ³");
		gotoxy(1,6); cprintf("      ³ A ³ S ³ D ³ F ³ G ³ H ³ J ³ K ³ L ³; :³' \"³  ENTER  ³");
		gotoxy(1,7); cprintf("ÚÄÄÄÄÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÂÄÁÄÄÄÄÄÂÄÄÄ´");
		gotoxy(1,8); cprintf("³ SHIFT ³ Z ³ X ³ C ³ V ³ B ³ N ³ M ³, <³. >³/ ?³ SHIFT ³\\ |³");
		gotoxy(1,9); cprintf("ÀÄÄÄÄÄÄÄÁÄÄÄÁÄÂÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÅÄÄÄÁÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÙ");
		gotoxy(1,10);cprintf("              ³        SPACEBAR         ³                    ");
		gotoxy(1,11);cprintf("              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                    ");
	}

/*--------------------------------------------------------------------------*/

	void	fingerpos(char ch,char attr)
	{
		int				x;
		int				y;
		int				n = 1;
		tt_highlite		H;

		window(10,13,70,23);
		_setcursortype(_NOCURSOR);
		switch(ch)
		{
			case 'Q':case 'q':	x = 7, 	y = 4;break;
			case 'W':case 'w':	x = 11, 	y = 4;break;
			case 'E':case 'e':	x = 15,  y = 4;break;
			case 'R':case 'r':	x = 19,  y = 4;break;
			case 'T':case 't':	x = 23, 	y = 4;break;
			case 'Y':case 'y':	x = 27,	y = 4;break;
			case 'U':case 'u':	x = 31, 	y = 4;break;
			case 'I':case 'i':	x = 35,	y = 4;break;
			case 'O':case 'o':	x = 39,	y = 4;break;
			case 'P':case 'p':	x = 43,  y = 4;break;

			case 'A':case 'a':	x = 9, 	y = 6;break;
			case 'S':case 's':	x = 13,	y = 6;break;
			case 'D':case 'd':	x = 17,	y = 6;break;
			case 'F':case 'f':	x = 21,	y = 6;break;
			case 'G':case 'g':	x = 25,	y = 6;break;
			case 'H':case 'h':	x = 29,	y = 6;break;
			case 'J':case 'j':	x = 33,	y = 6;break;
			case 'K':case 'k':	x = 37,	y = 6;break;
			case 'L':case 'l':	x = 41,	y = 6;break;

			case 'Z':case 'z':	x = 11,	y = 8;break;
			case 'X':case 'x':	x = 15,	y = 8;break;
			case 'C':case 'c':	x = 19,	y = 8;break;
			case 'V':case 'v':	x = 23,	y = 8;break;
			case 'B':case 'b':	x = 27,	y = 8;break;
			case 'N':case 'n':	x = 31,	y = 8;break;
			case 'M':case 'm':	x = 35,	y = 8;break;

			case ';':	x = 44,	y = 6;break;
			case ':':	x = 46,	y = 6;break;
			case '"':	x = 50,	y = 6;break;
			case ',':	x = 38,	y = 8;break;
			case '.':	x = 42,	y = 8;break;
			case ' ':	x = 24, y = 10, n = 8;break;
		}

		H.highlite(n,x,y,attr);
	}

/*--------------------------------------------------------------------------*/

	int	tt_counter	::	wordcount(char* text)
	{
		int	word=0;
		while(*text)
		{	while(*text == ' ')
				text++;
			if(*text)
			{	while(*text!=' ' && *text)
					text++;
				word++;
			}
		}
		return word;
	}

/*--------------------------------------------------------------------------*/
/*- For class tt_writer ----------------------------------------------------*/

	void	tt_writer	::	normalwrite	(int x,int y,char* s,char c = 0x1f)
	{
		char*	start = s;
		char* end 	= s + strlen(s);
		textattr(c);
		gotoxy(x,y);
		for( ; start <= end ; start++)
			putch(*start);
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	:: reversewrite (int x,int y,char* s,char c = 0x1f)
	{
		char*	end = s;
		char*	start = s + strlen(s);
		textattr(c);
		for( ; start >= end ; start--)
		{
			gotoxy(x--,y);	putch(*start);
		}
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	:: ndelaywrite (int x,int y,char* s,int d,char c = 0x1f)
	{
		char*	start = s;
		char* end 	= s + strlen(s);
		textattr(c);
		gotoxy(x,y);
		for( ; start <= end ; start++)
		{
			putch(*start);
			delay(d);
		}
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	:: rdelaywrite (int x,int y,char* s,int d,char c = 0x1f)
	{
		char*	end = s;
		char*	start = s + strlen(s);
		textattr(c);
		for( ; start >= end ; start--)
		{
			gotoxy(x--,y);	putch(*start);
			delay(d);
		}
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	:: nsoundwrite (int x,int y,char* s,int so,int d,
												 char c = 0x1f)
	{
		char*	start = s;
		char* end 	= s + strlen(s);
		textattr(c);
		gotoxy(x,y);
		for( ; start <= end ; start++)
		{
			putch(*start);
			sound(so);
			delay(d);
			nosound();
		}
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	:: rsoundwrite (int x,int y,char* s,int so,int d,
												 char c = 0x1f)
	{
		char*	end = s;
		char*	start = s + strlen(s);
		textattr(c);
		for( ; start >= end ; start--)
		{
			gotoxy(x--,y);	putch(*start);
			sound(so);
			delay(d);
			nosound();
		}
	}

/*--------------------------------------------------------------------------*/

	void	tt_writer	::	textprinter	(int x,int y,char* text
												  ,char attr)
	{
		textattr(attr);
		gotoxy(x,y);
		cprintf("%s",text);

	}

/*--------------------------------------------------------------------------*/
/*- For class tt_painter ---------------------------------------------------*/

	void	tt_painter	:: setcolor	(char forecolor,char backcolor)
	{
		this->color = forecolor + ( backcolor << 4 );
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	::	border	(int x1,int y1,int x2,int y2
											 ,tts_style sty,char c)
	{
		int	temp	= x1+1;

		_wscroll	= NOTSCROLL;
		textattr(c);
		/* to draw horizontal line */
		for(	;	temp < x2	;	temp++)
		{
			gotoxy(temp,y1);	putch(sty.horizontal);
			gotoxy(temp,y2);	putch(sty.horizontal);
		}

		/* to draw vertical line */
		for(temp = y1+1 ; temp < y2 ; temp++)
		{
			gotoxy(x1,temp);	putch(sty.vertical);
			gotoxy(x2,temp);	putch(sty.vertical);
		}

		/* to draw corners */
		gotoxy(x1,y1);	putch(sty.upperleft_cor);
		gotoxy(x1,y2);	putch(sty.lowerleft_cor);
		gotoxy(x2,y1);	putch(sty.upperright_cor);
		gotoxy(x2,y2);	putch(sty.lowerright_cor);
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	:: basewindow	(void)
	{
		tt_writer	W;

		this->defaultwindow();
		this->border(1,2,80,24,tts_style(213,212,184,190,205,179),0x1F);
		W.normalwrite	(2,1,HEADER);
		W.reversewrite	(79,1,DEVELOPER);
		window(1,25,80,25);textattr(0x5f);clrscr();
		W.normalwrite	(30,1,FOOTER,0x5f);
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	:: box (int x1,int y1,int x2,int y2,tts_style S,char c)
	{
		window(x1,y1,x2,y2);textattr(c);clrscr();
		this->border(1,1,(x2-x1+1),(y2-y1+1),S,c);
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	::	defaultwindow	(void)
	{
		_setcursortype(_NOCURSOR);
		window(1,1,80,25);
		textattr(0x1f);
		clrscr();
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	:: horizontalline(int x,int y,char sty,int len,char c)
	{

		len = x + len - 1;
		gotoxy(x,y);
		x = 1;
		textattr(c);
		for( ; x <= len ; x++)
			putch(sty);
	}

/*--------------------------------------------------------------------------*/

	void	tt_painter	:: verticalline(int x,int y,char sty,int h,char c)
	{
		int	b = y;
		y = y + h - 1;
		textattr(c);
		for( ; b <= y ; b++)
		{
			gotoxy(x,b);
			putch(sty);
		}
	}

/*--------------------------------------------------------------------------*/
/*-For class tt_highlite ---------------------------------------------------*/

	void	tt_highlite	:: highlite (int n,int col,int row,char attrib)
	{
		int	p;

		union REGS reg;

		for( p = 1 ; p <= n ; p++)
		{
			gotoxy(col++,row);
			reg.h.ah=8;
			reg.h.bh=0;
			int86(0x10,&reg,&reg);
			reg.h.ah=9;
			reg.h.bl=attrib;
			reg.h.bh=0;
			reg.x.cx=1;
			int86(0x10,&reg,&reg);
		}
	}

/*--------------------------------------------------------------------------*/
/*- For class tt_typing ----------------------------------------------------*/

	void	tt_typing	:: form(void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();
		P.box(5,4,76,16,tts_style(201,200,187,188,205,186),0x1f);

		W.normalwrite(5,3,"Here is the beginning of the typing tutor program. You can choose",0x1F);
		W.normalwrite(5,4,"test or classroom for your destination. Test is to practise",0x1F);
		W.normalwrite(5,5,"the long test. And classroom is suitable for the beginner. ",0x1F);
		W.normalwrite(5,6,"In classroom Lesson, Finger, Numeric, and Game are available.",0x1F);

		W.normalwrite(10,8,STEP_1,0x1F);
		W.normalwrite(10,9,STEP_2,0x1F);
		W.normalwrite(10,10,STEP_3,0x1F);
		W.normalwrite(10,11,STEP_4,0x1F);

		P.box(25,17,54,22,tts_style(213,212,184,190,205,179),0x2f);
	}

/*--------------------------------------------------------------------------*/

	void	tt_typing	:: run(void)
	{
		const	int size = 4;
		static char*	item_names [size] =	{	"Speed Test",
															"Classroom Lesson",
															"Credit",
															"Exit to Window"
														};
		tt_painter		P;
		tt_writer		W;
		tt_highlite		H;

		int	item_index = 0;
		int	coorY = 2;
		int	keypress = 0;
		int	repaint = 1;

		while(1)
		{
			if(repaint)
			{
				int	count;
				this->form();
				for(count = 0 ,coorY = 2; count < size ; count++,coorY++)
					W.normalwrite(3,coorY,item_names[count],0x2f);
				coorY = 2;
				item_index = 0;
				repaint = 0;
			}

			H.highlite(28,2,coorY,0x1E);

			while(bioskey(1)==0)	;

			H.highlite(28,2,coorY,0x2F);
			keypress = bioskey(0);
			switch(keypress)
			{
				case UP_ARROW:
				case SHIFT_TAB:   coorY--;
										if( --item_index == -1 )
										{
											item_index = size - 1;
											coorY = 5;
										}
										break;

				case DOWN_ARROW:
				case TAB:         coorY++;
										if( ++item_index == size )
										{
											item_index = 0;
												coorY = 2;
										}
										break;

				case ENTER:
										switch(item_index)
										{
											case	0 	:	{	tt_test		T;
																T.run();
																repaint = 1;
															}
															break;

											case	1	:	{	tt_class		C;
																C.run();
																repaint = 1;
															}
															break;

											case	2	:	credit();repaint = 1;break;

											case	3	:	exit(0);
										}

										break;

				case ESC:			return;
				case ALT_X:			exit(0);

			} /* end of switch case */
		} /* end of while loop */
	}

/*--------------------------------------------------------------------------*/

	void	credit	(void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();
		P.box(10,5,70,17,tts_style(218,192,191,217,196,179),0x1B);

		W.normalwrite(5,3,	"Developer        :",0x1F);
		W.normalwrite(5,5,	"Starting Date    :",0x1F);
		W.normalwrite(5,7,	"Version No.      :",0x1F);
		W.normalwrite(5,9,	"Language         :",0x1F);
		W.normalwrite(5,11,	"Teacher          :",0x1F);

		W.normalwrite(25,3,	"Aung Thaw Aye",0x1F);
		W.normalwrite(25,5,	"1st Nov 2003",0x1F);
		W.normalwrite(25,7,	"VER 01",0x1F);
		W.normalwrite(25,9,	"C++",0x1F);
		W.normalwrite(25,11,    "DAW EI EI HLAING",0x1F);

		P.box(10,19,70,21,tts_style(218,192,191,217,196,179),0x1B);
		W.normalwrite(13,2,"PRESS ANY KEY TO RETURN TO MAIN MENU..",0x1F);
		getch();
	}

/*--------------------------------------------------------------------------*/
/*- For class tt_test ------------------------------------------------------*/

	void	tt_test	::	form (void)
	{
		tt_painter		P;
		tt_writer		W;
		P.basewindow();
		P.box(2,3,79,23,tts_style(218,192,191,217,196,179),0x2F);
	}

/*--------------------------------------------------------------------------*/

	void	tt_test	:: readname (void)
	{
		int	ram_num = 0;
		randomize();
		ram_num = rand() % 10;
		strcpy(this->ttfilename,::testnames[ram_num]);
	}

/*--------------------------------------------------------------------------*/

	void	tt_test	::	run (void)
	{
		tt_writer		W;
		char*		string[3]	=	{	"Go to speed text",
											"Main Menu",
											"Exit to window"
										};
		int		keypress;
		int		index = 0;
		int		line = 0;
		int		len;
		int		x=1;
		int				y=2;
		int				repaint = 1;
		int				loop = 1;
		int				insert = 0;
		int				lastline = 6;
		int				topline = 0;
		char				ch;
		FILE*				FILE_TEST;
		tt_counter		C;
		time_t			begin;
		time_t			end;

		while(1)
		{
			begin = time(NULL);

			while(loop)
			{
				if(repaint)
				{
					int				tempY	= 2;

					this->incorrect 	= 	0;
					lastline				=	6;
					topline				= 	0;
					y						=  2;
					index					=  0;
					insert				=  0;
					repaint 				=  0;

					this->form();
					this->readname();
					/* to check whether file can be read or not */
					if(!fexists(this->ttfilename))
						return;
					/* to read the text to array */
					line = 0;
					FILE_TEST = fopen(this->ttfilename,READ_BINARY);
					/*
					fread(&this->store[line],sizeof(struct tts_text),1,FILE_TEST);
					while(!feof(FILE_TEST))
					{
						line++;
						fread(&this->store[line],sizeof(struct tts_text),1,FILE_TEST);
					}
					*/
					fread(this->store,sizeof(struct tts_text),10,FILE_TEST);
					fclose(FILE_TEST);

					/* to print the text on the screen */
					textattr(0x2F);
					for( line = 0; line < 6 ; line++,tempY+=3)
					{
						gotoxy(2,tempY);cputs(this->store[line].text);
					}
					line	= 0;
					_setcursortype(_NORMALCURSOR);
					window(3,4,78,22);
				}

				if(insert)
				{
					movetext(3,7,78,21,3,4);
					window(3,19,78,20);textattr(0x2F);clrscr();
					window(3,4,78,22);
					W.textprinter(1,y-1,this->store[line].text,0x2F);
					insert = 0;
				}

				textcolor(WHITE);gotoxy(x,y);
				while(bioskey(1)==0)	;
				keypress = bioskey(0);
				ch = keypress & 0xFF;
				switch(keypress)
				{
					case ENTER	: 	if(this->store[line].text[index] == '\0')
										{
											gotoxy(x,y);putch(' ');
											x = 1 , y+=3;
											index = 0;
											line++;
											if(line > 9)
												loop = 0;
											if(line == lastline)
											{
												insert = 1;
												y = 17;
												lastline++;
												topline++;
											}
										}

										break;
					case BACKSPACE:if(index == 0)
										{
											if( y > 1 )
											{
												if(line > topline)
												{	line --;
													len = strlen(this->store[line].text);
													x = len + 1;
													y -=3;
													gotoxy(x,y);
													index = len;
												}
											}
											else
												x = 1,y = 2;
										}
										else
										{
											index --,x--;
											gotoxy(x,y);putch(' ');
											gotoxy(x,y);
										}
										break;
					case ALT_X	:	exit(0);
					case ESC		:	return;
					default		:  if(iscntrl(ch))
											continue;

										if(ch == this->store[line].text[index])
											textcolor(BLACK);
										else
										{
											textcolor(RED);
											sound(800);
											delay(10);
											nosound();
											this->incorrect ++;
											if(ch == ' ')
												if( this->store[line].text[index] != '\0')
													ch = 25;
												else
													ch = 20;
										}
										gotoxy(x,y);putch(ch);
										index ++,x++;
										len = strlen(this->store[line].text);
										if(index > len)
										{	index=0,line++;
											x = 1,y+=3;
											if(line >9 )
												loop = 0;

											if( line == lastline )
											{
												lastline++;
												topline++;
												insert = 1;
												y = 17;
											}
										}

				} /* end of switch case */
			}	/* end of inner while loop */

			end = time(NULL);
			this->timelength = (int) difftime(end,begin) / 60;

			if(this->timelength < 1)
				this->timelength++;
			/* to count the number of words in the file */
			for(this->nword = 0, line = 0;line < 10;line++)
				this->nword += C.wordcount(this->store[line].text);

			/* to count the number of characters in the file */
			for( this->nchar = 0,line = 0;line < 10;line++)
				this->nchar += strlen((char*)this->store[line].text) + 1;

			switch(score(string,tts_score(this->nword,this->incorrect,
													this->nchar,this->timelength)))
			{
				/* go to speed test */
				case  0	:	loop = 1;
								repaint = 1;
								continue;
				/* to return to main menu */
				case	1	:
				/* for esc */
				case	-1 :	return;
				/* to exit to window */
				case 	2	: 	exit(0);
			}
		} 	/* end of outer while loop */
	}

/*--------------------------------------------------------------------------*/
/*- For class tt_class -----------------------------------------------------*/

	void	tt_class	::	form	(void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();
		P.box(5,7,76,22,tts_style(213,212,184,190,205,179),0x1F);
		W.normalwrite(5,3,"Welcome to class room..",0x1A);
		W.normalwrite(5,4,"It is suitable for the beginners. Here you can practise lesson,",0x1A);
		W.normalwrite(5,5,"fingering,numeric and can play typing game. You should take this",0x1A);
		W.normalwrite(5,6,"to improve your typing skill.",0x1A);
		W.normalwrite(5,8,"There are four menu items in this session. To select item you can",0x1A);
		W.normalwrite(5,9,"use Left/Right arrow and in order to choose you can press ENTER..",0x1A);
		W.normalwrite(3,11,"ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» É» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ» ÉÍÍÍ»",0x1B);
		W.normalwrite(3,12,"º T º º Y º º P º º I º º N º º G º ºº º T º º U º º T º º O º º R º",0x1A);
		W.normalwrite(3,13,"ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ È¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼ ÈÍÍÍ¼",0x1D);
		W.normalwrite(5,12,	"T",0x1C);
		W.normalwrite(11,12,	"Y",0x1C);
		W.normalwrite(17,12,	"P",0x1C);
		W.normalwrite(23,12,	"I",0x1C);
		W.normalwrite(29,12,	"N",0x1C);
		W.normalwrite(35,12,	"G",0x1C);
		W.normalwrite(44,12,	"T",0x1C);
		W.normalwrite(50,12,	"U",0x1C);
		W.normalwrite(56,12,	"T",0x1C);
		W.normalwrite(62,12,	"O",0x1C);
		W.normalwrite(68,12,	"R",0x1C);

	}

/*--------------------------------------------------------------------------*/

	void	tt_class	::	run	(void)
	{
		const	int size = 4;
		static char*	item_names [size] =	{	"Lesson",
															"Fingering",
															"Numeric",
															"Game"
														};
		tt_painter		P;
		tt_writer		W;
		tt_highlite		H;

		int	item_index ;
		int	coorX ;
		int	keypress;
		int	repaint ;

		while(1)
		{
			if(repaint)
			{
				int	count;
				this->form();
				item_index 	= 0;
				coorX			= 2;
				keypress		= 0;
				window(5,5,76,5);textattr(0x5F);clrscr();
				for( count=0 ; count < size ; count++ )
				{	gotoxy(coorX,1);cprintf("%s",item_names[count]);
					coorX+=strlen(item_names[count])+4;
				}
				coorX = 2;
				item_index = 0;
				repaint = 0;
			}

			H.highlite(strlen(item_names[item_index]),coorX,1,0x5E);
			while(bioskey(1)==0)			;
			H.highlite(strlen(item_names[item_index]) ,coorX,1,0x5F);
			keypress = bioskey(0);
			switch(keypress)
			{
				case LEFT_ARROW:
				case SHIFT_TAB:   if( item_index == 0 )
										{
											item_index = size - 1;
											coorX = 36;
										}
										else
										{
											coorX = coorX - strlen(item_names[item_index - 1]) - 4 ;
											item_index--;
										}
										break;

				case RIGHT_ARROW:
				case TAB:         coorX +=strlen(item_names[item_index])+4;
										if( ++item_index == size )
										{
											item_index = 0;
												coorX = 2;
										}
										break;

				case ENTER:			switch(item_index)
										{
											case 	0:	if(this->lesson())
															return;
														else
															repaint = 1;
														break;
											case  1:	if(this->finger())
															return;
														else
															repaint = 1;
														break;
											case	2:	if(this->numeric())
															return;
														else
															repaint = 1;
														break;
											case 	3:	if(this->game())
															return;
														else
															repaint = 1;
										}
										break;
				case ESC:			return;
				case ALT_X:			exit(0);

			} /* end of switch case */
		}
	}/* end of run method */

/*--------------------------------------------------------------------------*/

	void	tt_class	:: lesson_form (void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();window(1,1,80,25);
		W.normalwrite(20,4,"Welcome to the typing tutor lesson to improve ");
		W.normalwrite(20,5,"your typing skill..");
		P.box(15,15,65,17,tts_style(213,212,184,190,205,179),0x6F);
		W.normalwrite(8,2,"Put your fingers on A,S,D,F and J,K,L",0x6F);
		P.box(10,19,70,21,tts_style(213,212,184,190,205,179),0x1F);
		W.normalwrite(15,2,"Press ESC to return to menu.",0x1B);
		P.box(10,8,70,13,tts_style(213,212,184,190,205,179),0x2F);
	}

/*--------------------------------------------------------------------------*/

	int	tt_class	:: lesson (void)
	{
		char*				string[3]	=	{	"Go to class room",
													"Main Menu",
													"Exit to window"
												};

		tt_writer		W;
		int				keypress;
		int				index = 0;
		int				line = 0;
		int				x=1;
		int				loop = 1;
		int				ram_line 		= 0;
		int				begin_line		= 0;
		int				end_line			= 2;
		char				ch;

		FILE*				LESSON;
		time_t			begin;
		time_t			end;
		tt_counter		C;

		this->incorrect 	= 	0;
		index					=  0;

		this->lesson_form();
		/* to check whether file can be read or not */
		if(!fexists(LSFILE))
			return 0;
		/* to read the text to array */
		line = 0;

		LESSON = fopen(LSFILE,READ_BINARY);

		/* to get the lesson randomly */
		fseek(LESSON,0,SEEK_END);
		ram_line 	= rand() % (ftell(LESSON) / sizeof(tts_lesson) / 3);
		begin_line 	= ram_line * 3;
		end_line 	= begin_line + 2;
		for(line = 0 ;begin_line <= end_line ; begin_line++,line++)
		{
			fseek(LESSON,sizeof(tts_lesson) * begin_line,SEEK_SET);
			fread(&this->lstore[line],sizeof(tts_lesson),1,LESSON);
		}
		fclose(LESSON);

		/* to print the text on the screen */
		textattr(0x2F);
		line	= 0;
		_setcursortype(_NORMALCURSOR);
		window(15,10,67,11);textattr(0x2F);clrscr();
		gotoxy(1,1);cputs(this->lstore[line].text);


		begin = time(NULL);

		while(loop)
		{
			textcolor(WHITE);gotoxy(x,2);
			while(bioskey(1)==0)	;
			keypress = bioskey(0);
			ch = keypress & 0xFF;
			switch(keypress)
			{
				case BACKSPACE:if(index != 0)
									{
										index --,x--;
										gotoxy(x,2);putch(' ');
										gotoxy(x,2);
									}
									break;
				case ALT_X	:	exit(0);
				case ESC		:	return 0;
				default		:  if(iscntrl(ch))
											continue;

									if(ch == this->lstore[line].text[index])
										textcolor(BLACK);
									else if(this->lstore[line].text[index] != '\0')
									{
										textcolor(RED);
										sound(800);
										delay(10);
										nosound();
										this->incorrect ++;
										if( ch == ' ')
											ch = 25;
									}
									else
									{
										index=0,line++;
										x = 1;
										clrscr();
										textcolor(WHITE);
										if(line < 3)
										{	/* print next line */
											gotoxy(1,1);cputs(this->lstore[line].text);
											continue;
										}
										else
											goto en;
									}
									gotoxy(x,2);putch(ch);
									index ++,x++;
				} /* end of switch case */
		}	/* end of inner while loop */
en:
		end = time(NULL);
		this->timelength = (int) difftime(end,begin) / 60;
		if(this->timelength < 1)
			this->timelength = 1;
		/* to count the number of words in the file */
		for(this->nword = 0, line = 0;line < 3;line++)
			this->nword += C.wordcount(this->lstore[line].text);

		/* to count the number of characters in the file */
		for( this->nchar = 0,line = 0;line < 3;line++)
			this->nchar += strlen((char*)this->lstore[line].text) + 1;

		switch(score(string,tts_score(this->nword,this->incorrect,
												this->nchar,this->timelength)))
		{
			/* go to classroom */
			case  0	:	return 0;
			/* to return to main menu */
			case	1	:
			/* for esc */
			case	-1 :	return 1;
			/* to exit to window */
			case 	2	: 	exit(0);
		}
		return 0;
	}

/*--------------------------------------------------------------------------*/

	int	tt_class	:: finger (void)
	{
		char*				string[3]	=	{	"Go to class room",
													"Main Menu",
													"Exit to window"
												};

		tt_writer		W;
		int				keypress;
		int				index = 0;
		int				line = 0;
		int				x=1;
		int				loop = 1;
		int				ram_line 		= 0;
		int				begin_line		= 0;
		int				end_line			= 2;
		char				ch;

		FILE*				FINGER;
		time_t			begin;
		time_t			end;
		tt_counter		C;

		this->incorrect 	= 	0;
		index					=  0;

		this->finger_form();
		/* to check whether file can be read or not */
		if(!fexists(FNFILE))
			return 0;
		/* to read the text to array */
		line = 0;

		FINGER = fopen(FNFILE,READ_BINARY);
		/* to get the lesson randomly */
		fseek(FINGER,0,SEEK_END);
		ram_line 	= rand() % (ftell(FINGER) / sizeof(tts_lesson) / 3);
		begin_line 	= ram_line * 3;
		end_line 	= begin_line + 2;
		for(line = 0 ;begin_line <= end_line ; begin_line++,line++)
		{
			fseek(FINGER,sizeof(tts_lesson) * begin_line,SEEK_SET);
			fread(&this->lstore[line],sizeof(tts_lesson),1,FINGER);
		}
		fclose(FINGER);
		/* to print the text on the screen */
		textattr(0x2F);
		line	= 0;
		_setcursortype(_NORMALCURSOR);
		window(15,8,67,9);textattr(0x2F);clrscr();
		gotoxy(1,1);cputs(this->lstore[line].text);


		begin = time(NULL);

		while(loop)
		{
			fingerpos(this->lstore[line].text[index],0x1C);
			window(15,8,67,9);
			textcolor(WHITE);gotoxy(x,2);
			_setcursortype(_NORMALCURSOR);
			while(bioskey(1)==0)	;
			keypress = bioskey(0);
			ch = keypress & 0xFF;
			fingerpos(this->lstore[line].text[index],0x1F);
			window(15,8,67,9);

			switch(keypress)
			{
				case BACKSPACE:if(index != 0)
									{
										index --,x--;
										gotoxy(x,2);putch(' ');
										gotoxy(x,2);
									}
									break;
				case ALT_X	:	exit(0);
				case ESC		:	return 0;
				default		:  if(iscntrl(ch))
											continue;

									if(ch == this->lstore[line].text[index])
									{
										textcolor(BLACK);
									}
									else if(this->lstore[line].text[index] != '\0')
									{
										textcolor(RED);
										sound(800);
										delay(10);
										nosound();
										this->incorrect ++;
										if( ch == ' ')
											ch = 25;
									}
									else
									{
										index=0,line++;
										x = 1;
										window(15,8,67,9);textattr(0x2F);clrscr();
										textcolor(WHITE);
										if(line < 3)
										{	/* print next line */
											gotoxy(1,1);cputs(this->lstore[line].text);
											continue;
										}
										else
											goto en;
									}
									gotoxy(x,2);putch(ch);
									index ++,x++;
				} /* end of switch case */
		}	/* end of inner while loop */
en:
		end = time(NULL);
		this->timelength = (int) difftime(end,begin) / 60;
		if(this->timelength < 1)
			this->timelength++;
		/* to count the number of words in the file */
		for(this->nword = 0, line = 0;line < 3;line++)
			this->nword += C.wordcount(this->lstore[line].text);

		/* to count the number of characters in the file */
		for( this->nchar = 0,line = 0;line < 3;line++)
			this->nchar += strlen((char*)this->lstore[line].text) + 1;

		switch(score(string,tts_score(this->nword,this->incorrect,
												this->nchar,this->timelength)))
		{
			/* go to classroom */
			case  0	:	return 0;
			/* to return to main menu */
			case	1	:
			/* for esc */
			case	-1 :	return 1;
			/* to exit to window */
			case 	2	: 	exit(0);
		}
		return 0;
	}

/*--------------------------------------------------------------------------*/

	void	tt_class	::	finger_form(void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();window(1,1,80,25);
		paintkeyboard(0x1F);
		P.box(10,7,70,10,tts_style(213,212,184,190,205,179),0x2F);
	}

/*--------------------------------------------------------------------------*/

	int	tt_class	:: numeric (void)
	{
		tt_writer		W;
		char*		string[3]	=	{	"Return to classroom.",
											"Return to mainmenu.",
											"Exit to window."
										};
		int				keypress;
		int				index = 0;
		int				line = 0;
		int				len;
		int				x=1;
		int				y=2;
		int				ram_line;
		int				begin_line;
		int				end_line;
		int				loop = 1;
		char				ch;
		FILE*				NUMERIC;
		tt_counter		C;
		time_t			begin;
		time_t			end;

		this->incorrect 	= 	0;
		y						=  2;
		index					=  0;

		this->numeric_form();

		/* to check whether file can be read or not */
		if(!fexists(NUFILE))
			return 0;
		/* to read the text to array */
		line = 0;
		NUMERIC = fopen(NUFILE,READ_BINARY);
		/* to get the lesson randomly */
		fseek(NUMERIC,0,SEEK_END);
		ram_line 	= rand() % (ftell(NUMERIC) / sizeof(tts_numeric) / 3);
		begin_line 	= ram_line * 3;
		end_line 	= begin_line + 2;

		for(line = 0 ;begin_line <= end_line ; begin_line++,line++)
		{
			fseek(NUMERIC,sizeof(tts_numeric) * begin_line,SEEK_SET);
			fread(&this->nstore[line],sizeof(tts_numeric),1,NUMERIC);
		}
		fclose(NUMERIC);

		window(22,7,58,14);textattr(0x2F);
		/* to print the text on the screen */
		for( line = 0, y = 1; line < 3 ; line++,y+=3)
		{
			gotoxy(1,y);cputs(this->nstore[line].text);
		}
		y = 2;line	= 0;x = 1;
		_setcursortype(_NORMALCURSOR);

		begin = time(NULL);
		while(loop)
		{
			textcolor(WHITE);gotoxy(x,y);
			while(bioskey(1)==0)	;
			keypress = bioskey(0);
			ch = keypress & 0xFF;
			switch(keypress)
			{
				case ENTER	: 	if(this->nstore[line].text[index] == '\0')
									{
										gotoxy(x,y);putch(' ');
										x = 1 , y+=3;
										index = 0;
										line++;
										if(line > 2)
											loop = 0;
									}
												break;
				case BACKSPACE:if(index == 0)
									{
										if( y > 1 )
										{
											if(line > 0)
											{
												line --;
												len = strlen(this->nstore[line].text);
												x = len + 1;
												y -=3;
												gotoxy(x,y);
												index = len;
											}
										}
										else
											x = 1,y = 2;
									}
									else
									{
										index --,x--;
										gotoxy(x,y);putch(' ');
										gotoxy(x,y);
									}
									break;
				case ALT_X	:	exit(0);
				case ESC		:	return 0;
				default		:
									if(iscntrl(ch))
											continue;
									if(ch == this->nstore[line].text[index])
										textcolor(BLACK);
									else
									{
										textcolor(RED);
										sound(800);
										delay(10);
										nosound();
										this->incorrect ++;
										if(ch == ' ')
											if( this->nstore[line].text[index] != '\0')
												ch = 25;
											else
												ch = 20;
									}
									gotoxy(x,y);putch(ch);
									index ++,x++;
									len = strlen(this->nstore[line].text);
									if(index > len)
									{
										index=0,line++;
										x = 1,y+=3;
										if(line > 2 )
											loop = 0;
									}
			} /* end of switch case */
		}	/* end of inner while loop */

		end = time(NULL);
		this->timelength = (int) difftime(end,begin) / 60;

		if(this->timelength < 1)
			this->timelength++;
		/* to count the number of words in the file */
		for(this->nword = 0, line = 0;line < 10;line++)
			this->nword += C.wordcount(this->nstore[line].text);

		/* to count the number of characters in the file */
		for( this->nchar = 0,line = 0;line < 10;line++)
			this->nchar += strlen((char*)this->nstore[line].text) + 1;

		switch(score(string,tts_score(this->nword,this->incorrect,
											this->nchar,this->timelength)))
		{
			/* go to classroom */
			case  0	: return 0;
			/* to return to main menu */
			case	1	:
			/* for esc */
			case	-1 :	return 1;
			/* to exit to window */
			case 	2	: 	exit(0);
		}
		return 0;
	}/* end of method */

/*--------------------------------------------------------------------------*/

	void	tt_class	:: numeric_form(void)
	{
		tt_painter		P;
		tt_writer		W;

		P.basewindow();

		P.box(3,17,77,20,tts_style(213,212,184,190,205,179),0x6F);
		W.normalwrite(3,2,"Type the characters in the top box. The cursor will show you the next",0x6F);
		W.normalwrite(3,3,"character. At the end of each line, press ENTER for next line.",0x6F);
		P.box(20,6,59,15,tts_style(213,212,184,190,205,179),0x2F);

	}

/*--------------------------------------------------------------------------*/

	void	tt_class	:: game_form(void)
	{
		tt_painter		P;
		tt_writer		W;


		char				ground[2][79]=
		{ 	"ÛÛÜ    ÜÜ  ÜÛÛÜ  ÜÜ   ÛÜ    ÜÜÛÛÜ  Û   ÛÜ   ÜÛÛÜ   Ü ÛÛÜ     ÜÛÛÜ   Ü ÛÛÜÜÛÛÜÜ",
			"ÛÛÛÛÛÜÛÛÛÛÛÛÛÛÛÜÛÛÛÛÜÛÛÛÛÜÛÛÛÛÛÛÛÜÛÛÛÜÛÛÛÛÜÛÛÛÛÛÛÜÛÛÛÛÛÛÛÜÜÜÛÛÛÛÛÛÜÛÛÛÛÛÛÛÛÛÛÛ"
		};

		P.basewindow();
		window(1,1,80,25);
		textattr(0x17);gotoxy(2,G1);cputs(ground[0]);
		textattr(0x18);gotoxy(2,G2);cputs(ground[1]);

	}

/*--------------------------------------------------------------------------*/

	int 	tt_class	:: game (void)
	{
		tt_invader			invader[100];
		tts_invadertext	itext;

		int			keypress;
		int			index = 0;
		int			recpos;
		int			end 					= 0;
		int			hitcount 			= 0;
		int			misscount 			= 0;
		int			save		 			= -1;
		int			thread_time 		= 0;
		short			index_increase 	= 0;
		char			ch;

		FILE*				GAME;

		this->game_form();

		if(!fexists(GAFILE))
			return 0;

		GAME	= fopen(GAFILE,READ_BINARY);

		int	nrec;
		fseek(GAME,sizeof(tts_invadertext),SEEK_END);
		nrec = ftell(GAME) / sizeof (tts_invadertext);
		for(index = 0; index < ICOUNT ;index ++)
		{
			recpos = rand() % nrec;
			fseek(GAME,sizeof(struct tts_invadertext) * recpos, SEEK_SET);
			fread(&itext,sizeof(struct tts_invadertext),1,GAME);
			invader[index].create(itext.text,itext.coorX);
		}

		fclose(GAME);

		_setcursortype(_NOCURSOR);

		while(1)
		{
			do
			{
				for(index = 0;	index	<=	end ; index++)
				{
					if(invader[index].isdead() == ID_ALIVE)
					{
						if(invader[index].move(thread_time) == ID_ARRIVE)
						{  /* when invader arrives the ground */
							if(save > -1)		save = -1;
							misscount ++;
							if( (hitcount+misscount) == ICOUNT)
								goto en;
						}

						if(invader[index].killing() == ID_KILLING)
						{	/* while killing invader */
							if(invader[index].shoot(thread_time) == ID_HIT)
							{
								/* when rocket hits the invader */
								if(save > -1)
									save = -1;
								if( (hitcount+misscount) == ICOUNT)
									goto en;
							}
						}/* end of ID_KILLING if structure*/
						else if(invader[index].isactive() == ID_ACTIVE)
						{
							if(ch)
							{
								if(save == index)
								{
									switch(invader[index].compare(ch))
									{
										case SAME	: 	ch = NULL;break;
										case NSAME	:	save = -1;
															ch = NULL;
															break;
										case END		:	save = -1;
															invader[index].kill();
															invader[index].setactive(0);
															ch = NULL;
															hitcount++;
									}
								}
								else if(save == -1)
								{
									switch(invader[index].compare(ch))
									{
										case SAME	: 	save = index ;break;
										case NSAME	:  save = -1;
															break;
										case END		:	save = -1;
															invader[index].kill();
															invader[index].setactive(0);
															ch = NULL;
															hitcount++;
									}
								}

							} /* end of second inner if structure */
						} /* end of first inner if structure*/
					} /* end of outter if structure*/
				}/* end of for loop */

				ch = NULL;
				delay(1);
				thread_time++;

				if(thread_time > LIMIT_T)
				{
					for(index =0;index <= end ;index++)
						invader[index].setactive(1);

					thread_time = 0;
					index_increase++;
					if(index_increase > 1)
					{
						if(end < ICOUNT - 1)
							end++;
						index_increase = 0;
					}
				}
			}while(bioskey(1) == 0);

			keypress = bioskey(0);
			ch = keypress & 0xFF;
			switch(keypress)
			{
				case ESC	:	return 0;
				case ALT_X:	exit(0);
			}
		}
en:
		switch(gscore(hitcount,misscount))
		{
			case 0:	return 0;
			case 1:	return 1;
			case 2:	exit(0);
		}
		return 0;
	}/* end of method */

/*--------------------------------------------------------------------------*/

	int	tt_class	::	gscore(int hit,int miss)
	{
		tt_painter		P;
		tt_writer		W;
		tt_highlite		H;

		const int		size = 3;
		int				loop = 1;
		int				keypress;
		int				item_index = 0;
		int				coorY = 2;
		char*				item_names[size]	=	{
															"Return to classroom.",
															"Return to main menu.",
															"Exit to window."
														};

		P.basewindow();
		P.box(10,5,70,13,tts_style(201,200,187,188,205,186),0x1F);
		gotoxy(5,3);cprintf("Score        : %d",(hit < miss) ? 0 : (hit - miss) * 10);
		gotoxy(5,5);cprintf("Hit          : %d",hit);
		gotoxy(5,7);cprintf("Misses       : %d",miss);

		/* to create the box for menu*/
		P.box(25,17,54,21,tts_style(213,212,184,190,205,179),0x2f);
		/* to print all the menu items into the menu box */
		for(item_index = 0 ,coorY = 2; item_index < size ; item_index++,coorY++)
			W.normalwrite(3,coorY,item_names[item_index],0x2f);
		/* to go to first menu item */
		coorY = 2;item_index = 0;

		while(loop)
		{
			/* to highlite the current menu item */
			H.highlite(28,2,coorY,0x1E);
			/* wait for key pressed */
			while(bioskey(1)==0)	;
			/* to reset the current menu item*/
			H.highlite(28,2,coorY,0x2F);
			keypress = bioskey(0);
			switch(keypress)
			{
				case UP_ARROW:
				case SHIFT_TAB:   coorY--;
										if( --item_index == -1 )
										{
											item_index = size - 1;
											coorY = size + 1;
										}
										break;

				case DOWN_ARROW:
				case TAB:         coorY++;
										if( ++item_index == size )
										{
											item_index = 0;
												coorY = 2;
										}
										break;

				case ENTER:       loop = 0;break;
				case ESC:			return -1;
				case ALT_X:			exit(0);

			} /* end of switch case */
		} /* end of while loop */
		return	item_index;
	}

/*--------------------------------------------------------------------------*/
/*-For class tt_invader ----------------------------------------------------*/

	void	tt_invader :: repaint(void)
	{
		tt_highlite		H;
		/* to hide the text of invader by dispalying blue-colored text and bk */
		H.highlite(this->length ,this->coorX,this->coorY-1,0x11);
		/* to print the text of invader */
		textcolor(0x1F);gotoxy(this->coorX,this->coorY);cputs(this->text);
		/* to highlite the character(s) */
		if(this->index >0 )
			H.highlite(this->index ,this->coorX,this->coorY,this->attr);
	}

/*--------------------------------------------------------------------------*/

	void	tt_invader :: clear(void)
	{
		tt_highlite		H;
		H.highlite(this->length ,this->coorX,this->rocket_coorY+1,0x11);
		H.highlite(this->length ,this->coorX,this->rocket_coorY,0x11);
	}

/*--------------------------------------------------------------------------*/

	void	tt_invader	:: create(char * str,int tx)
	{
		if(strlen(str) < 11)      strcpy(this->text,str);
		else		return;

		this->live.bool		= ID_ALIVE;	/* for the status of dead or alive 	*/
		this->index 			= 0;	/* for the text index (array index) */
		this->coorY				= IY;	/* starting y of the invader text	*/
		this->length 			= strlen(this->text);
		this->state.bool		= ! ID_KILLING;
		//this->coorX 			= ((tx + length) > 78) ? 78 - length : tx ;
		if(tx + length > 78)
			tx = 78 - this->length;
		else if(tx == 1)
			tx = 2;
		this->coorX = tx;
		this->rocket_coorY	= RX;
		this->buffer[0]		= NULL;
	}

/*--------------------------------------------------------------------------*/

	int	tt_invader :: isdead(void)
	{
		return this->live.bool;
	}

/*--------------------------------------------------------------------------*/

	int	tt_invader	:: isactive(void)
	{
		return this->active.bool;
	}

/*--------------------------------------------------------------------------*/

	void	tt_invader :: kill(void)
	{
		/* to shoot the invader untill rocket does not hit invader */
		this->state.bool = ID_KILLING;
	}

/*--------------------------------------------------------------------------*/

	void	tt_invader	:: setactive(int s)
	{
		this->active.bool = s;
	}

/*--------------------------------------------------------------------------*/

	int	tt_invader	:: shoot(int thread_time)
	{

		if((thread_time % RTIME) == 0)
		{
			/* to get the background text along the path of rocket */

			if(this->rocket_coorY < RX)
				puttext(	this->coorX,this->rocket_coorY+1,this->coorX,this->rocket_coorY+1,this->buffer);

			gettext(	this->coorX,this->rocket_coorY,this->coorX,this->rocket_coorY,this->buffer);
			/* to display rocket on the screen*/
			textattr(0x14);gotoxy(this->coorX,this->rocket_coorY);
			putch(24);

			/* to move up , Y-coordinate is decreased */
			this->rocket_coorY--;
			if(this->rocket_coorY < this->coorY)
			{
				/* when rocket hits the invader */
				tt_highlite			H;

				this->state.bool 	= ! ID_KILLING;
				this->live.bool 	= ID_DEAD;
				this->active.bool	= ! ID_ACTIVE;
				this->clear();
				return 	ID_HIT;
			}

		}
		return !ID_HIT;
	}

/*--------------------------------------------------------------------------*/

	int  tt_invader :: move(int thread_time)
	{
		/* if the time (IT_TIME) is same as the thread time */
		/* the invader will move down */

		if((thread_time & IT_TIME) == IT_TIME)
		{
			this->coorY ++;
			if(this->coorY > RX || this->coorY >= this->rocket_coorY)
			{
				this->live.bool 	= ID_DEAD;
				this->state.bool 	= ! ID_KILLING;
				this->active.bool	= ! ID_ACTIVE;
				this->repaint();
				this->clear(); /* to clear text of invader */

				if(this->coorY >= 19)
				{
					tt_highlite		H;
					H.highlite(this->length,this->coorX,G1,0x11);
					H.highlite(this->length,this->coorX,G2,0x11);
					return ID_ARRIVE;
				}
				else
					return ID_DEAD;
			}
			this->repaint();
		}
		return !ID_DEAD;
	}

/*--------------------------------------------------------------------------*/

	int	tt_invader	:: killing(void)
	{
		return this->state.bool;
	}

/*--------------------------------------------------------------------------*/

	int	tt_invader :: compare(char c)
	{
		tt_highlite		H;
		if(this->text[index] == c)
		{
			this->index++;
			this->attr = 0x1A; /* to display the same character in green color */
			/* to display character int green color */
			H.highlite(this->index,this->coorX,this->coorY,this->attr);
			/* to check index is the last room no */
			/* if index is the last room no , all the characters pressed are  */
			/*	same as the text of the invader, so we should kill the invader */
			if(this->text[index] == '\0')
				return END;
			return SAME;
		}
		/* if c != this->text[index] . we should clear green-colored text */
		/* and should assign index = 0 */
		if(this->text[index] != c)
		{
			if(this->index > 0)
			{
				this->attr = 0x1F;
				/* to clear green-colored text */
				H.highlite(this->index+1, this->coorX, this->coorY, this->attr);
				this->index = 0;
			}
		}
		return NSAME;
	}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

	void	form(void)
	{
		tt_painter	P;
		tt_writer	W;

		P.basewindow();
		P.box(10,19,69,23,tts_style(213,212,184,190,205,179),0x1f);

		W.normalwrite(3,2,STEP_1,0x1f);
		W.normalwrite(3,3,STEP_2,0x1f);
		W.normalwrite(3,4,STEP_3,0x1f);

		P.box(25,4,54,18,tts_style(213,212,184,190,205,179),0x2f);
	}

/*--------------------------------------------------------------------------*/

	void	main(void)
	{
		_wscroll	= NOTSCROLL;
		const	int size = 13;
		static  char*	item_names [size] =		{	"Aung Min Htun",
																"Aung Thaw Aye",
																"Chit Toe Nyan",
																"Hlaing Min Tun",
																"Kaung Htet Htein",
																"Myo Ko Ko",
																"Nay Aung Latt",
																"Nyein Chan",
																"Nyein Chan Kyaw",
																"Sai Nay Linn",
																"Sithu Myint Oo",
																"Wai Zin Aye",
																"Zaw Latt"
															};

		int	item_index	= 0;
		int	keypress		= 0;
		int	coorY;
		char	srepaint 	= 1;

		tt_highlite		H;
		tt_writer		W;
		tt_typing		T;

		while(1)
		{
			if(srepaint)
			{
				int	count;
				form();
				for(count = 0 ,coorY = 2; count < size ; count++,coorY++)
					W.normalwrite(3,coorY,item_names[count],0x2f);
				coorY = 2;
				item_index = 0;
				srepaint = 0;
			}

			H.highlite(28,2,coorY,0x1E);

			while(bioskey(1)==0)	;

			H.highlite(28,2,coorY,0x2F);
			keypress = bioskey(0);

			switch(keypress)
			{
				case UP_ARROW :
				case SHIFT_TAB:   coorY--;
										if( --item_index == -1 )
										{
											item_index = size - 1;
											coorY = 14;
										}
										break;

				case DOWN_ARROW:
				case TAB:         coorY++;
										if( ++item_index == size )
										{
											item_index = 0;
											coorY = 2;
										}
										break;

				case ENTER:			T.run(); srepaint = 1;
										break;

				case ALT_X:			exit(0);

			} /* end of switch case */
		} /* end of while loop */
	} /* end of method , main */

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

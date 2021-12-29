#pragma once

#define WINCX		800
#define WINCY		600

#define		TILECX	50
#define		TILECY	50

#define		TILEX	5
#define		TILEY	5

#define DEPTH 0
#define DEPTH_MULTI 1

#define SCORE int
#define STATE int
#define WIN 1000
#define DRAW 0
#define LOSE -1000
#define DEFAULT -1

#define WINSTRIKE 5
#define BOARD_SIZE_X 5
#define BOARD_SIZE_Y 5


#define NONE '-'
#define PLAYER_MARKER 'O'
#define AI_MARKER 'X'

#define PLAYER 1
#define AI 2

#define POS	pair<int,int>
#define VECPOS vector<pair<int,int>>
#define SCOREPOS pair<int,pair<int,int>>




#define	MSG_BOX(message)			MessageBoxW(g_hWnd,message, L"System Message", MB_OK)

#define NO_COPY(CLASSNAME)								\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)					\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}

extern HWND g_hWnd;


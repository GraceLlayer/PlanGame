#include "StdAfx.h"
#include "PlaneWarGame.h"


CPlaneWarGame::CPlaneWarGame(void):m_clientRect(0,0,600,600),m_boss(0,0,800)
{
	this->m_pMe = new CMyPlane();
	mdc.CreateCompatibleDC(NULL);				//创建兼容性DC
	m_backgroundPic.LoadBitmap(IDB_BACKGROUND);//加载背景图片
	bufferDc.CreateCompatibleDC(NULL);			//创建缓冲DC
	y=0;										//背景图y坐标起始位置
	m_gameState = RUN;
	m_generateEnemyPlaneWait = 1000;
	m_enemyPlaneFireWait = 1000;
	m_pauseCount = 0;
	m_uniqueSkillWaitTime = 2000;

	this->m_gameState = CPlaneWarGame::BEFORE_START;
}

CPlaneWarGame::~CPlaneWarGame(void)
{
	for(int i=0;i<4;i++)
	{
		for(POSITION p=m_ObjList[i].GetHeadPosition();p!=NULL;)
		{
			delete m_ObjList[i].GetNext(p);
		}
		m_ObjList[i].RemoveAll();
	}
	mdc.DeleteDC();
	bufferDc.DeleteDC();
	m_pMemBitmap.DeleteObject();
}
void CPlaneWarGame::StartGame()
{
	this->m_gameState = CPlaneWarGame::RUN;
	InitGame();
}
BOOL CPlaneWarGame::InitGame()
{
	
	y=0;										//背景图y坐标起始位置
	m_score = 0;
	m_preLevelScore=0;
	m_gameLevel = 1;
	m_gameState = RUN;
	m_pMe->setSpeed(5);
	//m_generateEnemyPlaneWait = 1000;
	//m_enemyPlaneFireWait = 1000;
	m_hasBoss = false;
	m_boss.setSpeed(1);
	m_beginTime = timeGetTime();
	m_lastGenerateEnemyPlaneTime = timeGetTime()+m_generateEnemyPlaneWait;
	m_pMe->SetLife(50);
	m_pMe->SetPoint(m_clientRect.Width()/2-m_pMe->GetRect().Width()/2,m_clientRect.Height()/2);
	m_boss.SetLife(60);
	m_boss.SetPoint(0,0);
	m_pauseCount = 0;

	m_lastUniqueSkillTime=0;
	m_uniqueSkillCount = 5;
	return TRUE;
}

void CPlaneWarGame::NextLevel()
{
	if(m_pMe->GetLife()<=0)
		StopGame();
	for(int i=0;i<4;i++)
	{
		for(POSITION p=m_ObjList[i].GetHeadPosition();p!=NULL;)
		{
			delete m_ObjList[i].GetNext(p);
		}
		m_ObjList[i].RemoveAll();
	}

	if (m_pMe->GetFireWaitTime()>50)
		m_pMe->SetFireWaitTime(m_pMe->GetFireWaitTime()-m_score/m_gameLevel/1000);
	

	//int speed = (m_score-m_preLevelScore)/1000+;
	if (CBomb::getSpeed()<20)
	{
		CBomb::setSpeed(CBomb::getSpeed()+1);
	}
	
	m_pMe->SetLife(m_pMe->GetLife()+(m_score-m_preLevelScore)/500);
	m_pMe->setSpeed(m_score/(m_gameLevel*3000)+5);
	m_preLevelScore = m_score;
	
	y=0;									//背景图y坐标起始位置
	//m_score = 0;
	m_gameState = RUN;
	m_gameLevel++;
	m_hasBoss = false;
	m_boss.setSpeed(1);
	m_beginTime = timeGetTime();
	m_lastGenerateEnemyPlaneTime = timeGetTime()+m_generateEnemyPlaneWait;
	//this->m_pMe->SetLife(50);
	m_pauseCount = 0;
	m_boss.SetLife(60);
	m_boss.SetPoint(0,0);

	m_lastUniqueSkillTime=0;
	m_uniqueSkillCount = 5+m_gameLevel;
	m_boss.SetLife(60+m_gameLevel*100);
}

void CPlaneWarGame::PauseGame()
{
	if(m_gameState==RUN)
	{
		m_gameState = PAUSE;
		m_pauseBegin = timeGetTime();
	}
}
bool CPlaneWarGame::IsPause()
{
	return PAUSE == m_gameState;
}
void CPlaneWarGame::CancelPauseGame()
{
	if(m_gameState==PAUSE)
	{
		m_gameState = RUN;
		m_pauseCount+=timeGetTime()-m_pauseBegin;
	}
}
//结束游戏
void CPlaneWarGame::StopGame()
{
	m_gameState = STOP;
}

void CPlaneWarGame::DrawList(CObList *list)
{
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CGameObject *pObject = (CGameObject*)list->GetNext(p);
		pObject->Draw(&mdc,true);
	}
}
void UpdateFrame(const CRect &clientRect)
{

}
void CPlaneWarGame::DrawGameText(CDC &memdc,const CRect &clientRect)
{
	CMyPlane &plane = *m_pMe;
	if (m_gameState == STOP || m_gameState == PAUSE)
	{
		TEXTMETRIC textMetric;
		GetTextMetrics(mdc,&textMetric);//获取当前字体信息
		/*HFONT font = CreateFont(textMetric.tmHeight*3,textMetric.tmAveCharWidth*3,0,0,textMetric.tmWeight,textMetric.tmItalic,
			textMetric.tmUnderlined,textMetric.tmStruckOut,textMetric.tmCharSet,0,0,0,textMetric.tmPitchAndFamily,L"");*/
		HFONT font = CreateFont(m_clientRect.Width()/10,m_clientRect.Height()/10,0,0,textMetric.tmWeight,textMetric.tmItalic,
			textMetric.tmUnderlined,textMetric.tmStruckOut,textMetric.tmCharSet,0,0,0,textMetric.tmPitchAndFamily,L"");
		HFONT oldFont = (HFONT)SelectObject(mdc,font);
		
		int oldMode = mdc.SetBkMode(TRANSPARENT);
		if (m_gameState == STOP)
			DrawText(mdc,L"GAME OVER",-1,m_clientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		else
			DrawText(mdc,L"暂  停",-1,m_clientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		
		SelectObject(mdc,oldFont);
		SetBkMode(mdc,oldMode);
		
		DeleteObject(font);
		
	}

	CString str;
	mdc.SetBkMode(TRANSPARENT);
	str.Format(_T("当前生命值:%d"),plane.GetLife());
	DrawText(mdc,str,-1,CRect(0,0,clientRect.right,50),NULL);
	str.Format(_T("当前得分:%d"),m_score);
	DrawText(mdc,str,-1,CRect(0,0,clientRect.right,50),DT_RIGHT);
	str.Format(_T("BOSS当前生命值:%d"),m_boss.GetLife());
	DrawText(mdc,str,-1,CRect(0,30,clientRect.right,50),NULL);

	str.Format(_T("当前关卡:%d"),m_gameLevel);
	DrawText(mdc,str,-1,CRect(0,60,clientRect.right,100),NULL);
}
void CPlaneWarGame::Draw(CClientDC &dc,const CRect &clientRect)
{

	AI();
	m_clientRect = clientRect;
	
	CMyPlane &plane = *m_pMe;

	m_pMemBitmap.CreateCompatibleBitmap(&dc,clientRect.Width(),clientRect.Height());
	mdc.SelectObject(&m_pMemBitmap);

	//贴背景图
	CBitmap *oldBitmap = bufferDc.SelectObject(&m_backgroundPic);
	mdc.SetStretchBltMode(COLORONCOLOR);//设置拉伸模式，否则图像会不清晰
	mdc.StretchBlt(0,y,clientRect.Width(),clientRect.Height(),&bufferDc,0,y/clientRect.Height(),251,243,SRCCOPY);//绘制图像
	mdc.StretchBlt(0,y-clientRect.Height(),clientRect.Width(),clientRect.Height(),&bufferDc,0,(clientRect.Height()-y)/clientRect.Height(),251,243,SRCCOPY);//绘制图像

	y=(y+1)%clientRect.Height();
	

	if (m_gameState != STOP)
		plane.Draw(&mdc,true);			//贴我方战机
	DrawList(GetMyBombList());		//贴我方战机导弹
	DrawList(GetEnemyBallList());	//贴敌方炸弹
	DrawList(GetEnemyPlaneList());	//贴敌方战机

	if(HasBoss())
		m_boss.Draw(&mdc,true);

	DrawList(GetExplosionList());	//贴爆炸效果

	DrawGameText(mdc,clientRect);		//输出游戏当前信息
	

	dc.BitBlt(0,0,clientRect.Width(),clientRect.Height(),&mdc,0,0,SRCCOPY);	//向设备DC贴图

	m_pMemBitmap.DeleteObject();
	bufferDc.SelectObject(oldBitmap);
}


CObList* CPlaneWarGame::GetEnemyPlaneList()
{
	return m_ObjList;
}

CObList* CPlaneWarGame::GetMyBombList()
{
	return m_ObjList+1;
}

CObList* CPlaneWarGame::GetEnemyBallList()
{
	return m_ObjList+2;
}

CObList* CPlaneWarGame::GetExplosionList()
{
	return m_ObjList+3;
}

//获得键的状态1->down
int GetKey(int nVirtKey)
{
	return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
}

CMyPlane* CPlaneWarGame::GetMyPlane()
{
	return this->m_pMe;
}

void CPlaneWarGame::randomAddEnemyPlane(CRect &clientRect)
{
	if(m_gameLevel==0)
		m_gameLevel = 1;
	if(m_hasBoss)
		return;
	m_lastGenerateEnemyPlaneTime = timeGetTime();
	m_clientRect = clientRect;
	int randX,randY,randNum,randDir,randSpeed;
	CEnemyPlane *plane;
	srand((unsigned)time(NULL)); 
	randNum=rand()%3+rand()%m_gameLevel;
	for(int i=0;i<randNum;i++){
		randX=rand()%(clientRect.Width()-CEnemyPlane::GetWidth());
		randY=rand()%35;
		randDir = rand()%2;
		randSpeed = 2 + rand()%2;
		if(randDir)
			plane = new CEnemyPlane(randX,-randY,CGameObject::DOWN,2000,2+rand()%m_gameLevel);
		else
			plane = new CEnemyPlane(randX,clientRect.Height(),CGameObject::UP,2000,2+rand()%m_gameLevel);
		plane->setSpeed(randSpeed);
		GetEnemyPlaneList()->AddTail(plane);
	}
}

bool CPlaneWarGame::IsHit(CGameObject* p,CGameObject* q)
{
	if (p->GetRight() < q->GetLeft())
		return false;
	if (p->GetBottom() < q->GetTop())
		return false;
	if (p->GetTop() > q->GetBottom())
		return false;
	if (p->GetLeft() > q->GetRight())
		return false;
	return true;
}

void CPlaneWarGame::AI()
{
	
	if(m_gameState!=STOP&&m_gameState!=PAUSE)
		MoveMyPlaneControl();
	if (m_gameState!=PAUSE)
	{
		if (timeGetTime()-m_beginTime-m_pauseCount >= 20000 && m_boss.GetLife()>0)
		{
			m_hasBoss = true;
		}
		Move();
		if(timeGetTime() - m_lastGenerateEnemyPlaneTime>=this->m_generateEnemyPlaneWait)
			randomAddEnemyPlane(m_clientRect);
		//if(timeGetTime() - m_lastChangeTime>=m_enemyPlaneFireWait)
		EnemyPlaneFire();
	}
	
	CObList *list;
	//randomAddEnemyPlane(m_clientRect);
	
	//清除链表中不可见对象（屏幕之外）
	this->RemoveUnvaliableObject(GetEnemyPlaneList());
	this->RemoveUnvaliableObject(GetEnemyBallList());
	this->RemoveUnvaliableObject(GetMyBombList());
	//处理爆炸效果
	list = GetExplosionList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CExplosion *explosion = (CExplosion *)list->GetNext(p);
		if (explosion->IsOver())
		{
			list->RemoveAt(list->Find(explosion));
			delete explosion;
		}
		else
		{
			if (!(clock()%explosion->GetStateChangeWait()))
			{
				explosion->NextState();
			}
			
		}
	}

	int hurt = m_score/10000+1;

	//判断战机导弹是否击中敌机
	list = GetMyBombList();
	CObList *planeList = GetEnemyPlaneList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CGameObject *bomb = (CGameObject *)list->GetNext(p);
		
		for (POSITION q=planeList->GetHeadPosition();q!=NULL;)
		{
			//CGameObject *plane = (CGameObject *)planeList->GetNext(q);
			CEnemyPlane *plane = (CEnemyPlane*)planeList->GetNext(q);
			
			if (IsHit(bomb,plane))
			{
				m_score+=10;
				GetExplosionList()->AddTail(new CExplosion(plane->GetPoint()));
				plane->MinusLife(hurt);
				if (plane->GetLife()<=0)
				{
					m_score+=20;
					//删除敌机
					planeList->RemoveAt(planeList->Find(plane));
					delete plane;
				}
				
				//删除导弹
				list->RemoveAt(list->Find(bomb));
				delete bomb;
				bomb = NULL;
				break;
			}	
		}

		if(HasBoss()&&bomb!=NULL)
		{
			if (IsHit(bomb,&m_boss))
			{
				m_score+=20;
				//CPoint point = m_boss.GetPoint();
				CPoint point = bomb->GetPoint();
				//point.x -= m_boss.GetRect().Width()/2-10;
				point.y -= m_boss.GetRect().Height()/2;
				GetExplosionList()->AddTail(new CExplosion(point));
				
				list->RemoveAt(list->Find(bomb));
				delete bomb;
				bomb = NULL;
				if (m_boss.GetLife()<=0)
				{
					m_score+=1000;
					m_hasBoss = false;
					NextLevel();
					return;
				}
				else
					m_boss.MinusLife(hurt);
			}	
		}
	}

	if(m_gameState==STOP)
		return;
	//判断战机是否被击中
	list = GetEnemyBallList();
	CMyPlane *myPlane = this->m_pMe;

	//判断战机是否被击中
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CGameObject *ball = (CGameObject*)list->GetNext(p);
		if (IsHit(ball,myPlane))
		{
			myPlane->MinusLife(1);
			if(myPlane->GetLife()<=0)
			{
				//mciSendString(L"play 00111.wav",NULL,0,NULL);
				PlaySound(L"00111.wav",NULL,SND_ASYNC);
				StopGame();
			}
			GetExplosionList()->AddTail(new CExplosion(myPlane->GetPoint()));
			list->RemoveAt(list->Find(ball));
			delete ball;
			ball = NULL;
		}	
	}

	//判断战机是否与敌机相撞
	list = GetEnemyPlaneList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CGameObject *plane = (CGameObject*)list->GetNext(p);
		if (IsHit(plane,this->m_pMe))
		{
			myPlane->MinusLife(plane->GetLife());
			GetExplosionList()->AddTail(new CExplosion(myPlane->GetPoint()));
			if(myPlane->GetLife()<=0)
			{
				PlaySound(L"00111.wav",NULL,SND_ASYNC);
				StopGame();
			}
			
			plane->MinusLife(myPlane->GetLife());
			GetExplosionList()->AddTail(new CExplosion(plane->GetPoint()));
			if(plane->GetLife()<=0)
			{
				list->RemoveAt(list->Find(plane));
				delete plane;	
				plane = NULL;
			}
		}
	}

	//判断战机是否与BOSS相撞
	if (HasBoss()&&IsHit(&m_boss,this->m_pMe))
	{
		myPlane->MinusLife(m_boss.GetLife()*2);
		m_boss.MinusLife(myPlane->GetLife()/2);
		if(myPlane->GetLife()<=0)
		{
			PlaySound(L"00111.wav",NULL,SND_ASYNC);
			StopGame();
		}
		else if (m_boss.GetLife()<=0)
		{
			NextLevel();
		}
		
		GetExplosionList()->AddTail(new CExplosion(myPlane->GetPoint()));
	}

	
}
void CPlaneWarGame::RemoveUnvaliableObject(CObList *list)
{
	//清除可视区之外游戏对象
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CGameObject *pObject = (CGameObject*)list->GetNext(p);
		CRect rect(pObject->GetRect());
		if(rect.bottom<0||rect.top>m_clientRect.bottom||rect.right<0||rect.left>m_clientRect.right)
		{
			list->RemoveAt(list->Find(pObject));
			delete pObject;
			pObject = NULL;
		}
	}
}

void CPlaneWarGame::Move()
{
	//战机导弹运动
	CObList * list=GetMyBombList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
		((CBomb*)list->GetNext(p))->run();
	list=GetEnemyBallList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
		((CBall*)list->GetNext(p))->run();
	
	//敌机移动
	list = GetEnemyPlaneList();
	for(POSITION p=list->GetHeadPosition();p!=NULL;)
	{
		CEnemyPlane *plane = (CEnemyPlane*)list->GetNext(p);
		plane->moveForward();
		if(plane->GetLife()<2)
			plane->horizontalShock();
	}

	if(HasBoss())
	{
		CMyPlane &plane = *this->m_pMe;
		
		
		if(m_boss.GetRight()-m_boss.GetRect().Width()/2<(plane.GetLeft()+plane.GetRect().Width()/2))
			m_boss.moveRight();
		else
			m_boss.moveLeft();

		if (m_boss.GetLife()<60+m_gameLevel*20)
		{
			m_boss.horizontalShock();
			if (m_gameLevel<5)
				m_boss.setSpeed(m_gameLevel);
			else if (m_gameLevel>=5)
				m_boss.setSpeed(5);
			
			if (m_boss.GetBottom()<plane.GetTop())
				m_boss.moveBack();
			else
				m_boss.moveForward();
		}
		/*if(m_boss.GetRight()-m_boss.GetRect().Width()/2<(plane.GetLeft()+plane.GetRect().Width()/2))
			m_boss.moveRight();
		else
			m_boss.moveLeft();*/
		
		
	}

}

void CPlaneWarGame::EnemyPlaneFire()
{

	CObList* ballList = GetEnemyBallList();
	CObList* planeList = GetEnemyPlaneList();
	CMyPlane *myPlane = this->m_pMe;
	int fire=0;
	srand((unsigned)time(NULL)); 

	for(POSITION p=planeList->GetHeadPosition();p!=NULL;)
	{
		CEnemyPlane *plane = (CEnemyPlane*)planeList->GetNext(p);
		fire=rand()%2;
		if(fire)
		{
			int x,y;
			x = myPlane->GetLeft()+myPlane->GetRect().Width()/2;
			y = myPlane->GetTop()+myPlane->GetRect().Height()/2;
			if (plane->Fired())
			{
				CBall *ball = plane->fire(CPoint(x,y));
				ballList->AddTail(ball);
			}
			
		}

	}
	if(HasBoss())
	{
		CMyPlane &plane = *this->m_pMe;
	
		if(m_boss.Fired())
		{
			
			int left = m_boss.GetLeft();
			int right = m_boss.GetRight();
			int y = m_boss.GetTop()+m_boss.GetRect().Height()/2;
			CPoint pos = m_boss.GetPoint();
			for(int i=0;i<4;i++)
			{
				y+=15;

				for(int j=left;j<right-20;j+=30)
				{
					pos.x = j;
					pos.y = y;
					GetEnemyBallList()->AddTail(m_boss.fireFrom(pos));
					GetEnemyBallList()->AddTail(m_boss.fireFrom(pos));
				}
				
			}

		}
		
	}
}

void CPlaneWarGame::MoveMyPlaneControl()
{
	CMyPlane &plane = *this->m_pMe;

	if(GetKeyState(VK_LEFT)&0x8000)
	{
		if(plane.GetRect().left>0)
			plane.moveLeft();
		else
			plane.SetPoint(0,plane.GetTop());
	}
	if(GetKeyState(VK_DOWN)&0x8000)
	{
		if(plane.GetRect().bottom<m_clientRect.bottom)
			plane.moveBack();
		else
			plane.SetPoint(plane.GetLeft(),m_clientRect.bottom-plane.GetRect().Height());
	}
	if(GetKeyState(VK_UP)&0x8000)
	{
		if(plane.GetRect().top>0)
			plane.moveForward();
		else
			plane.SetPoint(plane.GetLeft(),0);
	}
	if(GetKeyState(VK_RIGHT)&0x8000)
	{
		if(plane.GetRect().right<m_clientRect.right)
			plane.moveRight();
		else
			plane.SetPoint(m_clientRect.right-plane.GetRect().Width(),plane.GetTop());
	}
	if(GetKeyState('Z')&0x8000)
	{
		
		if(plane.Fired())
		{
			PlaySound(L"00211.wav",NULL,SND_ASYNC);
			//sndPlaySound(L"i:\\1.wav",SND_ASYNC);
			//mciSendString(L"play 00211.wav",NULL,0,NULL);

			CBomb *bomb = plane.fireFrom(CPoint(plane.GetRect().left,plane.GetRect().top));
			GetMyBombList()->AddTail(bomb);
			bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width(),plane.GetRect().top));
			GetMyBombList()->AddTail(bomb);
			int rate = m_score/3000;
			if (rate==1)
			{
				bomb = plane.fireFrom(CPoint(plane.GetRect().left+20,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
			}
			else if (rate==2)
			{
				bomb = plane.fireFrom(CPoint(plane.GetRect().left+10,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
				bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width()-10,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
			}
			else if (rate>=3)
			{
				bomb = plane.fireFrom(CPoint(plane.GetRect().left+10,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
				bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width()-10,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
				bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width()-20,plane.GetRect().top));
				GetMyBombList()->AddTail(bomb);
			}
			unsigned int count = m_score/10000;
			for (unsigned int i=0;i<count;i++)
			{
				bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width()-20,plane.GetRect().top));
				int randNum = rand()%(count+1);
				if (rand()%2)
					bomb->SetVerSpeed(randNum);
				else
					bomb->SetVerSpeed(-randNum);
				GetMyBombList()->AddTail(bomb);
			}
			//for(unsigned int i=0;i<2+m_score/3000&&i<6;i++)
			//{
			//	CBomb *bomb = plane.fireFrom(CPoint(plane.GetRect().left+i*10,plane.GetRect().top));
			//	GetMyBombList()->AddTail(bomb);
			///*bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width(),plane.GetRect().top));
			//GetMyBombList()->AddTail(bomb);

			//bomb = plane.fireFrom(CPoint(plane.GetRect().left+15,plane.GetRect().top));
			//GetMyBombList()->AddTail(bomb);		
			//bomb = plane.fireFrom(CPoint(plane.GetRect().right-bomb->GetRect().Width()-15,plane.GetRect().top));
			//GetMyBombList()->AddTail(bomb);*/
			//}
		}
	
	}
	if(GetKeyState('X')&0x8000&&timeGetTime()-m_lastUniqueSkillTime>m_uniqueSkillWaitTime&&m_uniqueSkillCount>0)
	{
		ReleaseUniqueSkill();
	}


}

void CPlaneWarGame::SetGenerateEnemyPlaneWait(int nWait)
{
	m_generateEnemyPlaneWait = nWait;
}

const int CPlaneWarGame::BEFORE_START=0;	//初始状态
const int CPlaneWarGame::PAUSE = 1;	//暂停状态
const int CPlaneWarGame::STOP = 2;	//游戏结束	
const int CPlaneWarGame::RUN = 3;	//运行状态

void CPlaneWarGame::ReStartGame()
{
	for(int i=0;i<4;i++)
	{
		for(POSITION p=m_ObjList[i].GetHeadPosition();p!=NULL;)
		{
			delete m_ObjList[i].GetNext(p);
		}
		m_ObjList[i].RemoveAll();
	}
	InitGame();
}

int CPlaneWarGame::GetGenerateEnemyPlaneWait()
{
	return this->m_generateEnemyPlaneWait;
}

void CPlaneWarGame::SetEnemyPlaneFireWait(int nWait)
{
	this->m_enemyPlaneFireWait = nWait;
}
int CPlaneWarGame::GetEnemyPlaneFireWait()
{
	return this->m_enemyPlaneFireWait;
}

bool CPlaneWarGame::HasBoss()
{
	return m_hasBoss;
}

int CPlaneWarGame::GetGameState()
{
	return m_gameState;
}

void CPlaneWarGame::ReleaseUniqueSkill()
{
	PlaySound(L"00111.wav",NULL,SND_ASYNC);
		m_lastUniqueSkillTime = timeGetTime();
		m_uniqueSkillCount--;
		srand(timeGetTime());
		//int count = m_clientRect.Height()*m_clientRect.Width()/360000*500;
		for(int i=0;i<500;i++)
		{
			int randX = rand()%m_clientRect.Width()-33;
			int randY = rand()%m_clientRect.Height()-33;
			GetExplosionList()->AddTail(new CExplosion(CPoint(randX,randY)));
		}
		CObList *list = GetEnemyPlaneList();
		for(POSITION p=list->GetHeadPosition();p!=NULL;)
		{	
			//CGameObject *plane = (CGameObject *)planeList->GetNext(q);
			CEnemyPlane *plane = (CEnemyPlane*)list->GetNext(p);
			m_score+=10;
			GetExplosionList()->AddTail(new CExplosion(plane->GetPoint()));
			plane->MinusLife(m_gameLevel+2);
			if (plane->GetLife()<=0)				
			{
				m_score+=20;
				//删除敌机
				list->RemoveAt(list->Find(plane));
				delete plane;
			}
			
		}
		list = GetEnemyBallList();
		for(POSITION p=list->GetHeadPosition();p!=NULL;)
		{	
			CBall *ball = (CBall*)list->GetNext(p);
			list->RemoveAt(list->Find(ball));
			delete ball;
			
		}
		if (HasBoss())
		{
			m_boss.MinusLife(m_gameLevel+2);
			if (m_boss.GetLife()<=0)				
			{
				m_score+=20;
				NextLevel();
			}
		}


}
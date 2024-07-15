#pragma once
#include "MyPlane.h"
#include "Ball.h"
#include "Bomb.h"
#include "EnemyPlane.h"
#include "resource.h"
#include "Explosion.h"
#include "Boss.h"
class CPlaneWarGame
{
public:
	CPlaneWarGame(void);
	~CPlaneWarGame(void);
	//virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual void Draw(CClientDC &dc,const CRect &clientRect);	//往设备dc中绘图
	//开始游戏
	void StartGame();
	//暂停游戏
	void PauseGame();
	//判断是否暂停
	bool IsPause();
	int GetGameState();
	//取消暂停游戏
	void CancelPauseGame();
	CObList* GetEnemyPlaneList();	//获取敌机列表
	CObList* GetMyBombList();		//获取我方战机导弹列表
	CObList* GetEnemyBallList();	//获取敌机子弹列表
	CObList* GetExplosionList();	//获取爆炸列表
	CMyPlane* GetMyPlane();			//获取我方战机

	//int getBombSpeed();				//获取导弹速度
	//static void setSpeed(int speed);//设置导弹速度

	void randomAddEnemyPlane(CRect &clientRect);//随机添加敌机

	//设置敌机产生时间间隔
	void SetGenerateEnemyPlaneWait(int nWait);
	//获取敌机产生时间间隔
	int GetGenerateEnemyPlaneWait();
	//设置敌机发射子弹间隔时间
	void SetEnemyPlaneFireWait(int nWait);
	//获取敌机发射子弹间隔时间
	int GetEnemyPlaneFireWait();

	//重新开始游戏
	void ReStartGame();

public:
	const static int BEFORE_START;	//初始状态
	const static int PAUSE;	//暂停状态
	const static int STOP;	//游戏结束	
	const static int RUN;	//运行状态
private:
	void Move();

protected:
	//内存DC
	//CDC*        m_pMemDC;

	//内存DC
	CDC mdc;

	//缓冲DC
	CDC bufferDc;

	//设备DC
	CClientDC*  m_pDC;

	CRect m_clientRect;
	//内存位图
	//CBitmap*    m_pMemBitmap;
	CBitmap m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//游戏下一关
	void NextLevel();

	//刷新游戏的帧画面
	void UpdateFrame(const CRect &clientRect);

	void AI();

	void DrawGameText(CDC &memdc,const CRect &clientRect);

	//获得键的状态1->down
	int GetKey(int nVirtKey);

	CMyPlane*  m_pMe;

	CObList    m_ObjList[4]; //用链表来管理游戏对象

private:
	//判断两对象是否相撞，相撞返回true
	bool IsHit(CGameObject* p,CGameObject* q);	

	void DrawList(CObList *list);

	void RemoveUnvaliableObject(CObList *list);

	void EnemyPlaneFire();

	void MoveMyPlaneControl();

	bool HasBoss();

	void ReleaseUniqueSkill();

private:
	//背景图片
	CBitmap m_backgroundPic;
	//背景图y坐标
	int y;
	//标记游戏运行状态
	int m_gameState;
	//导弹速度
	//int m_bombSpeed;
	//敌机产生间隔时间
	unsigned int m_generateEnemyPlaneWait;
	

	Boss m_boss;
	bool m_hasBoss;
	unsigned long m_beginTime;
	unsigned long m_lastGenerateEnemyPlaneTime;
	unsigned long m_pauseBegin;
	unsigned long m_pauseCount;
	int m_gameLevel;
	int m_enemyPlaneLife;
	//敌机发射子弹间隔时间
	int m_enemyPlaneFireWait;
	unsigned long m_preLevelScore;//上一关卡得分
	unsigned long m_score;		//当前得分
	unsigned int m_lastUniqueSkillTime;	//上一次释放绝招时间
	unsigned int m_uniqueSkillWaitTime;		//绝招冷却时间
	unsigned int m_uniqueSkillCount;			//绝招剩余次数

};


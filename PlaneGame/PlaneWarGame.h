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
	//virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual void Draw(CClientDC &dc,const CRect &clientRect);	//���豸dc�л�ͼ
	//��ʼ��Ϸ
	void StartGame();
	//��ͣ��Ϸ
	void PauseGame();
	//�ж��Ƿ���ͣ
	bool IsPause();
	int GetGameState();
	//ȡ����ͣ��Ϸ
	void CancelPauseGame();
	CObList* GetEnemyPlaneList();	//��ȡ�л��б�
	CObList* GetMyBombList();		//��ȡ�ҷ�ս�������б�
	CObList* GetEnemyBallList();	//��ȡ�л��ӵ��б�
	CObList* GetExplosionList();	//��ȡ��ը�б�
	CMyPlane* GetMyPlane();			//��ȡ�ҷ�ս��

	//int getBombSpeed();				//��ȡ�����ٶ�
	//static void setSpeed(int speed);//���õ����ٶ�

	void randomAddEnemyPlane(CRect &clientRect);//�����ӵл�

	//���õл�����ʱ����
	void SetGenerateEnemyPlaneWait(int nWait);
	//��ȡ�л�����ʱ����
	int GetGenerateEnemyPlaneWait();
	//���õл������ӵ����ʱ��
	void SetEnemyPlaneFireWait(int nWait);
	//��ȡ�л������ӵ����ʱ��
	int GetEnemyPlaneFireWait();

	//���¿�ʼ��Ϸ
	void ReStartGame();

public:
	const static int BEFORE_START;	//��ʼ״̬
	const static int PAUSE;	//��ͣ״̬
	const static int STOP;	//��Ϸ����	
	const static int RUN;	//����״̬
private:
	void Move();

protected:
	//�ڴ�DC
	//CDC*        m_pMemDC;

	//�ڴ�DC
	CDC mdc;

	//����DC
	CDC bufferDc;

	//�豸DC
	CClientDC*  m_pDC;

	CRect m_clientRect;
	//�ڴ�λͼ
	//CBitmap*    m_pMemBitmap;
	CBitmap m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//��Ϸ��һ��
	void NextLevel();

	//ˢ����Ϸ��֡����
	void UpdateFrame(const CRect &clientRect);

	void AI();

	void DrawGameText(CDC &memdc,const CRect &clientRect);

	//��ü���״̬1->down
	int GetKey(int nVirtKey);

	CMyPlane*  m_pMe;

	CObList    m_ObjList[4]; //��������������Ϸ����

private:
	//�ж��������Ƿ���ײ����ײ����true
	bool IsHit(CGameObject* p,CGameObject* q);	

	void DrawList(CObList *list);

	void RemoveUnvaliableObject(CObList *list);

	void EnemyPlaneFire();

	void MoveMyPlaneControl();

	bool HasBoss();

	void ReleaseUniqueSkill();

private:
	//����ͼƬ
	CBitmap m_backgroundPic;
	//����ͼy����
	int y;
	//�����Ϸ����״̬
	int m_gameState;
	//�����ٶ�
	//int m_bombSpeed;
	//�л��������ʱ��
	unsigned int m_generateEnemyPlaneWait;
	

	Boss m_boss;
	bool m_hasBoss;
	unsigned long m_beginTime;
	unsigned long m_lastGenerateEnemyPlaneTime;
	unsigned long m_pauseBegin;
	unsigned long m_pauseCount;
	int m_gameLevel;
	int m_enemyPlaneLife;
	//�л������ӵ����ʱ��
	int m_enemyPlaneFireWait;
	unsigned long m_preLevelScore;//��һ�ؿ��÷�
	unsigned long m_score;		//��ǰ�÷�
	unsigned int m_lastUniqueSkillTime;	//��һ���ͷž���ʱ��
	unsigned int m_uniqueSkillWaitTime;		//������ȴʱ��
	unsigned int m_uniqueSkillCount;			//����ʣ�����

};


#!/usr/bin/lua


timer.start(int)
timer.stop()

timer.Create()

#ifndef __SC_NEW_TIMER_H
#define __SC_NEW_TIMER_H

struct _sc_timer_entry_t;

typedef void (*sc_timer_callback)(struct _sc_timer_entry_t *ptTimerHandle);

typedef struct _sc_timer_entry_t
{
	void*	m_pUsrData;

	//如果不同定时器使用同一个回调函数和usrdata，应用程序可以任意Id
	int 	m_iUsrId; 
	sc_timer_callback 	m_pCallBack;

	int		m_iDelay; //定时器时间ms
	int 	m_iRepeatCnt;//定时器触发次数 -1为loop
}sc_timer_entry_t;



int sctimer_init(int iMaxTimerCnt);
sc_timer_entry_t *sctimer_start(int iDelay, int iRepeatCnt, void *pUsrData, int iUsrId,sc_timer_callback pFuncCallBack);
int sctimer_reset(sc_timer_entry_t *ptTimerHandle);
int sctimer_stop(sc_timer_entry_t **pptTimerHandle);
void sctimer_process(); //定时器计数函数20ms执行一次，如果调用sctimer_loop，不能调用该函数
int sctimer_loop();


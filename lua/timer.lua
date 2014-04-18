#!/usr/bin/lua
print("---------------")

Timer = {}
Timer.prototype = {m_iDelay=1000, m_iRepeatCnt=-1, m_pCallBack=function() print("Timer CallBack Func.") end, m_pUsrData=nil} 
Timer.mt = {}
Timer.mt.__index = Timer.prototype

function Timer.new(o)
    o = o or {}
    setmetatable(o, Timer.mt)
    return o
end

function Timer.loop()
end

t = Timer.new()
print(t.m_iDelay)
t.m_pCallBack()

--[[

function Timer:start()

end

function Timer:stop()

end

function Timer:loop()

end

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

Timer={}
 
function Timer:new(p)
    local obj = p
    if (obj == nil) then
        obj = {="Tom", age=27, male=true}
    end
    self.__index = self
    return setmetatable(obj, self)
end

function Person:toString()
    return self.name .." : ".. self.age .." : ".. (self.male and "male" or "female")
end


tom = Person:new()
print(tom:toString())

--]]


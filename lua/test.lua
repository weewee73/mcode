#!/usr/bin/lua
require "timer"

function mycallback1(o)
    print("my callback1: ", o)
end
function mycallback2(o)
    print("\tmy callback2: ", o)
end

function mycallback3(o)
    print("\t\tmy callback3: ", o)
end

t1 = Timer.start({m_pCallBack=mycallback1,                m_iRepeatCnt=10,  m_pUsrData="1:hello, one!"})
t2 = Timer.start({m_pCallBack=mycallback2, m_iDelay=200, m_iRepeatCnt=-1})
t3 = Timer.start({m_pCallBack=mycallback3, m_iDelay=3000, m_iRepeatCnt=5, m_pUsrData="3:hello, three!"})


flag = 1
while flag == 1 do
    Timer.loop()
    if t1.m_iRepeatCnt == 5 then
        flag = 0
    end
end

Timer.stop(t2)
Timer.stop()
Timer.stop(x)

flag = 1
while flag == 1 do
    Timer.loop()
end


#!/usr/bin/lua
Timer = {}
Timer.prototype = {
    m_iDelay=1000, -- period time, default 1000ms
    m_iRepeatCnt=-1, -- loop times, -1: infinite loop, 0: stop loop  
    m_pCallBack=function() print("Timer default CallBack Func.") end,
    m_pUsrData=nil -- m_pCallBack's parameter
} 
Timer.mt = {}
Timer.mt.__index = Timer.prototype

function Timer.start(t)
    t = t or {}
    setmetatable(t, Timer.mt)
    t.m_fStart = os.clock() -- os.clock() resolution 10ms
    Timer[#Timer+1] = t
    return t
end

function Timer.stop(t)
    if t ~= nil then t.m_iRepeatCnt = 0 end
end

function Timer.loop()
    local fCurrTime = os.clock()
    for _,t in ipairs(Timer) do
        if type(t) == "table" and t.m_iRepeatCnt ~= 0 and 1000*(fCurrTime-t.m_fStart)-t.m_iDelay >= 0 then
            t.m_pCallBack(t.m_pUsrData)
            t.m_fStart = fCurrTime
            if t.m_iRepeatCnt > 0 then t.m_iRepeatCnt = t.m_iRepeatCnt - 1 end
        end
    end
end

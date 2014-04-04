#!/usr/bin/lua

Alarm={}
 
function Alarm:new(p)
    local obj = p
    if (obj == nil) then
        obj = {name="1000", msg="告警", status=true}
    end
    self.__index = self
    return setmetatable(obj, self)
end

function Alarm:toString()
    return self.name .. " : " .. (self.status and "出现告警!" or "解除告警!") .. " : ".. self.msg
end





function receive(prod)
    local status, value = coroutine.resume(prod)
    return value
end

function send(x)
    coroutine.yield(x)
end

function producer()
    return coroutine.create(
        function()
            while true do
                local x = io.read()
                send(x)
            end
        end
    )
end

function filter(prod)
    return coroutine.create(
        function()
            for line = 1, math.huge do
                local x = receive(prod)
                x = string.format("%5d %s", line, x)
                send(x)
            end
        end
    )
end

function consumer(prod)
    while true do
        local x = receive(prod)
        io.write(x, "\n")

        local user, stat, message = string.match(x, "alarm(%d+)-(%d):%s*(.*)")

        if stat == "1" then
            stat= true
        else
            stat= false
        end

        alarm = Alarm:new({name=user, status=stat, msg=message})
        print("\t", alarm:toString())
    end
end


-- consumer(filter(producer()))
--
p = producer()
f = filter(p)
consumer(f)

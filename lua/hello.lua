#!/usr/bin/lua
print("Hello World!")

sum = 0
i = 1

while i <= 100 do
    sum = sum + i
    i = i + 1
end

print("sum = "..sum)





function table_print(t)
    for key, value in pairs(t) do
        print(key, value)
    end
end

table = {[20]="string", ["key2"]=100, ["KEY3"]="abc", ["Key4"]=function() print("haa..") end}

table_print(table)
table["Key4"]()




function gcd(x, y)
    if (x == 0) then 
        return y
    end
    while y ~= 0 do
        if x > y then
            x = x -y
        else
            y = y -x
        end
    end
    return x
end


fraction_op={}
function fraction_op.__add(f1, f2)
    ret = {}
    ret.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator
    ret.denominator = f1.denominator * f2.denominator
    return ret
end


fraction_a = {numerator=2, denominator=3}
fraction_b = {numerator=4, denominator=6}

setmetatable(fraction_a, fraction_op)
setmetatable(fraction_b, fraction_op)

fraction_s = fraction_a + fraction_b

print(fraction_a.numerator .. "/" .. fraction_a.denominator..
        " + " .. fraction_b.numerator .. "/" .. fraction_b.denominator ..
        " = " .. fraction_s.numerator/gcd(fraction_s.numerator, fraction_s.denominator) .. "/" .. fraction_s.denominator/gcd(fraction_s.numerator, fraction_s.denominator))







window_prototype = {x=0, y=0, width=100, height=100}
mywin = {title="Hello"}
setmetatable(mywin, {__index = window_prototype})




Person={}
 
function Person:new(p)
    local obj = p
    if (obj == nil) then
        obj = {name="Tom", age=27, male=true}
    end
    self.__index = self
    return setmetatable(obj, self)
end

function Person:toString()
    return self.name .." : ".. self.age .." : ".. (self.male and "male" or "female")
end


tom = Person:new()
print(tom:toString())

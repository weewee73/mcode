#!/usr/bin/lua


print("---------------")
Window = {}
Window.prototype = {x=0, y=0, width=100, height=100}
Window.mt = {}

function Window.new(o)
    setmetatable(o, Window.mt)
    return o
end

--Window.mt.__index = function(table, key) return Window.prototype[key] end
Window.mt.__index = Window.prototype

w = Window.new{x=10, y=20}
print(w.width)

print("---------------")

















--[[

a = {}

for i=1,10 do
    a[i] = i*2
end

for i=1, #a do
    print(a[i])
end



a[100000] = 1
print(table.maxn(a)) --> 100000
print(a[#a]) --> 20

a[#a] = nil


print("---------------")
for _,v in ipairs(a) do
    print(_, v)
end
for k in ipairs(a) do print(k) end




print("---------------")

local mt = {}
Set = {}

function Set.new(l)
    local set = {}
    setmetatable(set, mt)
    for _,v in ipairs(l) do set[v] = true end
    return set
end

function Set.union(a, b)
    local res = Set.new{}
    for k in pairs(a) do res[k] = true end
    for k in pairs(b) do res[k] = true end
    return res
end

function Set.intersection(a, b)
    local res = Set.new{}
    for k in pairs(a) do res[k] = b[k] end
    return res
end

function Set.tostring(set)
    local l = {}
    for e in pairs(set) do
        l[#l + 1] = e
    end
    return "{" .. table.concat(l, ", ") .. "}"
end

function Set.print(s)
    print(Set.tostring(s))
end


s1 = Set.new{10, 20, 30, 50}
s2 = Set.new{30, 1}
print(getmetatable(s1))
print(getmetatable(s2))

mt.__add = Set.union
s3 = s1 + s2
Set.print(s3)

mt.__mul = Set.intersection
s4 = s1 * s2
Set.print(s4)

print(s3)
mt.__tostring = Set.tostring
print(s3)

--]]

#!/usr/bin/lua

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


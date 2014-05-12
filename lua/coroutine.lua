-- iteration

function printResult(a)
    for i=1, #a do
        io.write(a[i], " ")
    end
    io.write("\n")
end

function permgen(a, n)
    n = n or #a
    if n <= 1 then
        printResult(a)
    else
        for i=1,n do
            a[n], a[i] = a[i], a[n]
            permgen(a, n-1)
            a[n], a[i] = a[i], a[n]
        end
    end
end

permgen({1,2,3})
print("---------------\n")
function permgen_2(a, s)
    s = s or 1
    n = #a
    if s >= n then
        printResult(a)
    else
        for i=s,n do
            a[s], a[i] = a[i], a[s]
            permgen_2(a, s+1)
            a[s], a[i] = a[i], a[s]
        end
    end
end
permgen_2({1,2,3})
print("---------------\n")




--[[
function foo(a)
    print("foo_start", a)
    local ret = coroutine.yield(2*a)
    print("foo___end", ret)
    return ret
end

co = coroutine.create(function(a,b)
    print("co_start", a, b)

    local r = foo(a+1)

    print("co_midle", r)

    local r, s = coroutine.yield(a+b, a-b)

    print("co___end", r, s)

    return b, "end"
end)

print("main_start")
print("main", coroutine.resume(co, 1, 10))



print("main", coroutine.resume(co, "r"))

print("main___end")
--print("main", coroutine.resume(co, "x", "y"))
--print("main", coroutine.resume(co, "x", "y"))

--]]

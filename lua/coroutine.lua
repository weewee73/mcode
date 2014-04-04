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
--
--print("main", coroutine.resume(co, "x", "y"))
--print("main", coroutine.resume(co, "x", "y"))



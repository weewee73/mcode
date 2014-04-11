table1 = {
    name = "Android Developer",
    email = "hpccns@gmail.com",
    url = "http://blog.csdn.net/hpccn",
    quote = [[
    There are 
    10 types of pepole
    who can understand binary.
    ]],--多行文字
    embeddedTab = {
        em1 = xx,
        x =0,
        {x =1, y =2 } -- 再内嵌table
    }-- 内嵌table 
}

tab = "    "
function print_table(t, i)
    local indent ="" -- i缩进，当前调用缩进
    for j = 0, i do 
        indent = indent .. tab
    end
    for k, v in pairs(t) do 
        if (type(v) == "table") then -- type(v) 当前类型时否table 如果是，则需要递归，
            print(indent .. "< " .. k .. " is a table />")
            print_table(v, i + 1) -- 递归调用
            print(indent .. "/> end table ".. k .. "/>")
        else -- 否则直接输出当前值

            print(indent .. "<" .. k .. "=" .. v.."/>")
        end
    end
end


print_table(table1, 0)

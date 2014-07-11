BEGIN{
    FS=","
    OFS=","
}

{
    if (NF > max_field)
        max_field = NF

    if (NR == 1){
        print $0 ",# head_line"
        for (i=1; i<=max_field; i++) {
            min[i] = 999999999
        }
        next #next line
    }

    for (i=1; i<=max_field; i++) {
        sum[i] += $i
        cnt[i]++
        if (max[i] < $i)
            max[i] = $i
        if (min[i] > $i) {
            min[i] = $i
        }
    }
}

END{
    for (i=1; i<=max_field; i++) {
        printf("%0.2f,", sum[i])
    }
    printf("%s\n", "# sum")

    for (i=1; i<=max_field; i++) {
        printf("%0.2f,", max[i])
    }
    printf("%s\n", "# max")

    for (i=1; i<=max_field; i++) {
        printf("%0.2f,", sum[i]/cnt[i])
    }
    printf("%s\n", "# average")

    for (i=1; i<=max_field; i++) {
        printf("%0.2f,", min[i])
    }
    printf("%s\n", "# min")
}

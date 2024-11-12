$1 ~ /^[a-z]{3}[0-9]{3}$/ {

    # In case command has spaces, store in single variable
    cmd = $8;
    for (i = 9; i <= NF; i++) {
        cmd = cmd " " $i;
    }

    # Store multiple command variables for user in associative array to match output
    if (cmds[$1]) {
        cmds[$1] = cmds[$1] "\n" cmd;
    } else {
        cmds[$1] = cmd;
    }

    # Store vars for time if DNE or earliest
    if (!earliestTime || $5 < earliestTime) {
        earliestTime = $5;
        earliestUser = $1;
        earliestLine = $0;
    }

    # Store vars for time if DNE or latest
    if (!latestTime || $5 > latestTime) {
        latestTime = $5;
        latestUser = $1;
        latestLine = $0;
    }
}

END {

    # Print User with command(s) from associative array
    for (user in cmds) {
        printf("User: %s\n", user);
        printf("%s\n", cmds[user]);
        printf("\n");
    }

    printf("Earliest Start Time:\n");
    printf("%s\n", earliestLine);
    printf("\n");
    printf("Latest Start Time\n");
    printf("%s\n", latestLine);
}

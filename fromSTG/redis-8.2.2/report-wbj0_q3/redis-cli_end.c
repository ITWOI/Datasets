#include "header_func.h"
#include "sds.h"
static long long ustime (){
    struct timeval tv;
    long long ust;
    ust = ((long long)tv.tv_sec) * 1000000;
    ust += tv.tv_usec;
    return ust;
}
static long long mstime (){
    return ustime() / 1000;
}
static hisds getDotfilePath (char *envoverride, char *dotfilename){
    char *path = ((void *)0);
    hisds dotPath = ((void *)0);
    path = getenv(envoverride);
    if (path != ((void *)0) && *path != '\x00') {
        if (!strcmp("/dev/null", path)) {
            return ((void *)0);
        }
        dotPath = hi_sdsnew(path);
    } else {
        char *home = getenv("HOME");
        if (home != ((void *)0) && *home != '\x00') {
            dotPath = hi_sdscatprintf(hi_sdsempty(), "%s/%s", home, dotfilename);
        }
    }
    return dotPath;
}
extern int cleanPrintfln (char *fmt, ...){
    va_list args;
    char buf[1024];
    int char_count, line_count = 0;
    char *position, *string = buf;
    while ((position = strchr(string, '\n')) != ((void *)0))
        {
            int line_length;
            string = position + 1;
            line_count++;
        }
    ;
    return line_count + 1;
}
static void cliLegacyIntegrateHelp (){
    if (cliConnect((1 << 1)) == -1)
        return;
    redisReply *reply = redisCommand(context, "COMMAND");
    if (reply == ((void *)0))
        return;
    if (reply->type != 2) {
        ;
        return;
    }
    for (size_t j = 0; j < reply->elements; j++) {
        redisReply *entry = reply->element[j];
        if (entry->type != 2 || entry->elements < 4 || entry->element[0]->type != 1 || entry->element[1]->type != 3 || entry->element[3]->type != 3)
            return;
        char *cmdname = entry->element[0]->str;
        int i;
        for (i = 0; i < helpEntriesLen; i++) {
            helpEntry *he = helpEntries + i;
            if (!strcasecmp(he->argv[0], cmdname))
                break;
        }
        if (i != helpEntriesLen)
            continue;
        helpEntriesLen++;
        helpEntries = zrealloc(helpEntries, sizeof(helpEntry) * helpEntriesLen);
        helpEntry *new = helpEntries + (helpEntriesLen - 1);
        new->argc = 1;
        new->argv = zmalloc(sizeof(hisds));
        new->argv[0] = hi_sdsnew(cmdname);
        new->full = new->argv[0];
        new->type = 1;
        new->docs.name = new->argv[0];
        new->docs.args = ((void *)0);
        new->docs.numargs = 0;
        new->docs.params = hi_sdsempty();
        int args = llabs(entry->element[1]->integer);
        args--;
        if (entry->element[3]->integer == 1) {
            new->docs.params = hi_sdscat(new->docs.params, "key ");
            args--;
        }
        while (args-- > 0)
            new->docs.params = hi_sdscat(new->docs.params, "arg ");
        if (entry->element[1]->integer < 0)
            new->docs.params = hi_sdscat(new->docs.params, "...options...");
        new->docs.summary = "Help not available";
        new->docs.since = "Not known";
        new->docs.group = "generic";
    }
    ;
}
static hisds sdscat_orempty (hisds params, const char *value){
    if (value[0] == '\x00') {
        return hi_sdscat(params, "\"\"");
    }
    return hi_sdscat(params, value);
}
static void cliMakeCommandDocArgs (redisReply *arguments, cliCommandArg *result){
    for (size_t j = 0; j < arguments->elements; j++) {
        cliAddCommandDocArg(&result[j], arguments->element[j]);
    }
}
static void cliAddCommandDocArg (cliCommandArg *cmdArg, redisReply *argMap){
    if (argMap->type != 9 && argMap->type != 2) {
        return;
    }
    for (size_t i = 0; i < argMap->elements; i += 2) {
        ((void)sizeof ((argMap->element[i]->type == 1) ? 1 : 0) , __extension__ ({
            if (argMap->element[i]->type == 1)
                ;
            else
                __assert_fail("argMap->element[i]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 489, __extension__ __PRETTY_FUNCTION__);
        }));
        char *key = argMap->element[i]->str;
        if (!strcmp(key, "name")) {
            ((void)sizeof ((argMap->element[i + 1]->type == 1) ? 1 : 0) , __extension__ ({
                if (argMap->element[i + 1]->type == 1)
                    ;
                else
                    __assert_fail("argMap->element[i + 1]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 492, __extension__ __PRETTY_FUNCTION__);
            }));
            cmdArg->name = hi_sdsnew(argMap->element[i + 1]->str);
        } else if (!strcmp(key, "display_text")) {
            ((void)sizeof ((argMap->element[i + 1]->type == 1) ? 1 : 0) , __extension__ ({
                if (argMap->element[i + 1]->type == 1)
                    ;
                else
                    __assert_fail("argMap->element[i + 1]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 495, __extension__ __PRETTY_FUNCTION__);
            }));
            cmdArg->display_text = hi_sdsnew(argMap->element[i + 1]->str);
        } else if (!strcmp(key, "token")) {
            ((void)sizeof ((argMap->element[i + 1]->type == 1) ? 1 : 0) , __extension__ ({
                if (argMap->element[i + 1]->type == 1)
                    ;
                else
                    __assert_fail("argMap->element[i + 1]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 498, __extension__ __PRETTY_FUNCTION__);
            }));
            cmdArg->token = hi_sdsnew(argMap->element[i + 1]->str);
        } else if (!strcmp(key, "type")) {
            ((void)sizeof ((argMap->element[i + 1]->type == 1) ? 1 : 0) , __extension__ ({
                if (argMap->element[i + 1]->type == 1)
                    ;
                else
                    __assert_fail("argMap->element[i + 1]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 501, __extension__ __PRETTY_FUNCTION__);
            }));
            char *type = argMap->element[i + 1]->str;
            if (!strcmp(type, "string")) {
                cmdArg->type = ARG_TYPE_STRING;
            } else if (!strcmp(type, "integer")) {
                cmdArg->type = ARG_TYPE_INTEGER;
            } else if (!strcmp(type, "double")) {
                cmdArg->type = ARG_TYPE_DOUBLE;
            } else if (!strcmp(type, "key")) {
                cmdArg->type = ARG_TYPE_KEY;
            } else if (!strcmp(type, "pattern")) {
                cmdArg->type = ARG_TYPE_PATTERN;
            } else if (!strcmp(type, "unix-time")) {
                cmdArg->type = ARG_TYPE_UNIX_TIME;
            } else if (!strcmp(type, "pure-token")) {
                cmdArg->type = ARG_TYPE_PURE_TOKEN;
            } else if (!strcmp(type, "oneof")) {
                cmdArg->type = ARG_TYPE_ONEOF;
            } else if (!strcmp(type, "block")) {
                cmdArg->type = ARG_TYPE_BLOCK;
            }
        } else if (!strcmp(key, "arguments")) {
            redisReply *arguments = argMap->element[i + 1];
            cmdArg->subargs = zcalloc(arguments->elements * sizeof(cliCommandArg));
            cmdArg->numsubargs = arguments->elements;
            cliMakeCommandDocArgs(arguments, cmdArg->subargs);
        } else if (!strcmp(key, "flags")) {
            redisReply *flags = argMap->element[i + 1];
            ((void)sizeof ((flags->type == 10 || flags->type == 2) ? 1 : 0) , __extension__ ({
                if (flags->type == 10 || flags->type == 2)
                    ;
                else
                    __assert_fail("flags->type == REDIS_REPLY_SET || flags->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 529, __extension__ __PRETTY_FUNCTION__);
            }));
            for (size_t j = 0; j < flags->elements; j++) {
                ((void)sizeof ((flags->element[j]->type == 5) ? 1 : 0) , __extension__ ({
                    if (flags->element[j]->type == 5)
                        ;
                    else
                        __assert_fail("flags->element[j]->type == REDIS_REPLY_STATUS", "redis-cli_InstSlice.c", 531, __extension__ __PRETTY_FUNCTION__);
                }));
                char *flag = flags->element[j]->str;
                if (!strcmp(flag, "optional")) {
                    cmdArg->flags |= (1 << 0);
                } else if (!strcmp(flag, "multiple")) {
                    cmdArg->flags |= (1 << 1);
                } else if (!strcmp(flag, "multiple_token")) {
                    cmdArg->flags |= (1 << 2);
                }
            }
        }
    }
}
static void cliFillInCommandHelpEntry (helpEntry *help, char *cmdname, char *subcommandname){
    help->argc = subcommandname ? 2 : 1;
    help->argv = zmalloc(sizeof(hisds) * help->argc);
    help->argv[0] = hi_sdsnew(cmdname);
    if (subcommandname) {
        char *pipe = strchr(subcommandname, '|');
        if (pipe != ((void *)0)) {
            help->argv[1] = hi_sdsnew(pipe + 1);
        } else {
            help->argv[1] = hi_sdsnew(subcommandname);
        }
        ;
    }
    hisds fullname = hi_sdsnew(help->argv[0]);
    if (subcommandname) {
        fullname = hi_sdscat(fullname, " ");
        fullname = hi_sdscat(fullname, help->argv[1]);
    }
    help->full = fullname;
    help->type = 1;
    help->docs.name = help->full;
    help->docs.params = ((void *)0);
    help->docs.args = ((void *)0);
    help->docs.numargs = 0;
    help->docs.since = ((void *)0);
}
static helpEntry * cliInitCommandHelpEntry (char *cmdname, char *subcommandname, helpEntry *next, redisReply *specs, dict *groups){
    helpEntry *help = next++;
    cliFillInCommandHelpEntry(help, cmdname, subcommandname);
    ((void)sizeof ((specs->type == 9 || specs->type == 2) ? 1 : 0) , __extension__ ({
        if (specs->type == 9 || specs->type == 2)
            ;
        else
            __assert_fail("specs->type == REDIS_REPLY_MAP || specs->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 588, __extension__ __PRETTY_FUNCTION__);
    }));
    for (size_t j = 0; j < specs->elements; j += 2) {
        ((void)sizeof ((specs->element[j]->type == 1) ? 1 : 0) , __extension__ ({
            if (specs->element[j]->type == 1)
                ;
            else
                __assert_fail("specs->element[j]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 590, __extension__ __PRETTY_FUNCTION__);
        }));
        char *key = specs->element[j]->str;
        if (!strcmp(key, "summary")) {
            redisReply *reply = specs->element[j + 1];
            ((void)sizeof ((reply->type == 1) ? 1 : 0) , __extension__ ({
                if (reply->type == 1)
                    ;
                else
                    __assert_fail("reply->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 594, __extension__ __PRETTY_FUNCTION__);
            }));
            help->docs.summary = hi_sdsnew(reply->str);
        } else if (!strcmp(key, "since")) {
            redisReply *reply = specs->element[j + 1];
            ((void)sizeof ((reply->type == 1) ? 1 : 0) , __extension__ ({
                if (reply->type == 1)
                    ;
                else
                    __assert_fail("reply->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 598, __extension__ __PRETTY_FUNCTION__);
            }));
            help->docs.since = hi_sdsnew(reply->str);
        } else if (!strcmp(key, "group")) {
            redisReply *reply = specs->element[j + 1];
            ((void)sizeof ((reply->type == 1) ? 1 : 0) , __extension__ ({
                if (reply->type == 1)
                    ;
                else
                    __assert_fail("reply->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 602, __extension__ __PRETTY_FUNCTION__);
            }));
            help->docs.group = hi_sdsnew(reply->str);
            hisds group = hi_sdsdup(help->docs.group);
        } else if (!strcmp(key, "arguments")) {
            redisReply *arguments = specs->element[j + 1];
            ((void)sizeof ((arguments->type == 2) ? 1 : 0) , __extension__ ({
                if (arguments->type == 2)
                    ;
                else
                    __assert_fail("arguments->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 608, __extension__ __PRETTY_FUNCTION__);
            }));
            help->docs.args = zcalloc(arguments->elements * sizeof(cliCommandArg));
            help->docs.numargs = arguments->elements;
            cliMakeCommandDocArgs(arguments, help->docs.args);
            help->docs.params = makeHint(((void *)0), 0, 0, help->docs);
        } else if (!strcmp(key, "subcommands")) {
            redisReply *subcommands = specs->element[j + 1];
            ((void)sizeof ((subcommands->type == 9 || subcommands->type == 2) ? 1 : 0) , __extension__ ({
                if (subcommands->type == 9 || subcommands->type == 2)
                    ;
                else
                    __assert_fail("subcommands->type == REDIS_REPLY_MAP || subcommands->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 615, __extension__ __PRETTY_FUNCTION__);
            }));
            for (size_t i = 0; i < subcommands->elements; i += 2) {
                ((void)sizeof ((subcommands->element[i]->type == 1) ? 1 : 0) , __extension__ ({
                    if (subcommands->element[i]->type == 1)
                        ;
                    else
                        __assert_fail("subcommands->element[i]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 617, __extension__ __PRETTY_FUNCTION__);
                }));
                char *subcommandname = subcommands->element[i]->str;
                redisReply *subcommand = subcommands->element[i + 1];
                ((void)sizeof ((subcommand->type == 9 || subcommand->type == 2) ? 1 : 0) , __extension__ ({
                    if (subcommand->type == 9 || subcommand->type == 2)
                        ;
                    else
                        __assert_fail("subcommand->type == REDIS_REPLY_MAP || subcommand->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 620, __extension__ __PRETTY_FUNCTION__);
                }));
                next = cliInitCommandHelpEntry(cmdname, subcommandname, next, subcommand, groups);
            }
        }
    }
    return next;
}
static size_t cliCountCommands (redisReply *commandTable){
    size_t numCommands = commandTable->elements / 2;
    for (size_t i = 0; i < commandTable->elements; i += 2) {
        ((void)sizeof ((commandTable->element[i]->type == 1) ? 1 : 0) , __extension__ ({
            if (commandTable->element[i]->type == 1)
                ;
            else
                __assert_fail("commandTable->element[i]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 634, __extension__ __PRETTY_FUNCTION__);
        }));
        ((void)sizeof ((commandTable->element[i + 1]->type == 9 || commandTable->element[i + 1]->type == 2) ? 1 : 0) , __extension__ ({
            if (commandTable->element[i + 1]->type == 9 || commandTable->element[i + 1]->type == 2)
                ;
            else
                __assert_fail("commandTable->element[i + 1]->type == REDIS_REPLY_MAP || commandTable->element[i + 1]->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 636, __extension__ __PRETTY_FUNCTION__);
        }));
        redisReply *map = commandTable->element[i + 1];
        for (size_t j = 0; j < map->elements; j += 2) {
            ((void)sizeof ((map->element[j]->type == 1) ? 1 : 0) , __extension__ ({
                if (map->element[j]->type == 1)
                    ;
                else
                    __assert_fail("map->element[j]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 639, __extension__ __PRETTY_FUNCTION__);
            }));
            char *key = map->element[j]->str;
            if (!strcmp(key, "subcommands")) {
                redisReply *subcommands = map->element[j + 1];
                ((void)sizeof ((subcommands->type == 9 || subcommands->type == 2) ? 1 : 0) , __extension__ ({
                    if (subcommands->type == 9 || subcommands->type == 2)
                        ;
                    else
                        __assert_fail("subcommands->type == REDIS_REPLY_MAP || subcommands->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 643, __extension__ __PRETTY_FUNCTION__);
                }));
                numCommands += subcommands->elements / 2;
            }
        }
    }
    return numCommands;
}
extern void cliInitGroupHelpEntries (dict *groups){
    dictIterator iter;
    dictEntry *entry;
    helpEntry tmp;
    int numGroups = ((groups)->ht_used[0] + (groups)->ht_used[1]);
    int pos = helpEntriesLen;
    helpEntriesLen += numGroups;
    helpEntries = zrealloc(helpEntries, sizeof(helpEntry) * helpEntriesLen);
    for (entry = dictNext(&iter); entry != ((void *)0); entry = dictNext(&iter)) {
        tmp.argc = 1;
        tmp.argv = zmalloc(sizeof(hisds));
        tmp.argv[0] = hi_sdscatprintf(hi_sdsempty(), "@%s", (char *)dictGetKey(entry));
        tmp.full = tmp.argv[0];
        tmp.type = 2;
        tmp.docs.name = ((void *)0);
        tmp.docs.params = ((void *)0);
        tmp.docs.args = ((void *)0);
        tmp.docs.numargs = 0;
        tmp.docs.summary = ((void *)0);
        tmp.docs.since = ((void *)0);
        tmp.docs.group = ((void *)0);
        helpEntries[pos++] = tmp;
    }
    ;
}
extern void cliInitCommandHelpEntries (redisReply *commandTable, dict *groups){
    helpEntry *next = helpEntries;
    for (size_t i = 0; i < commandTable->elements; i += 2) {
        ((void)sizeof ((commandTable->element[i]->type == 1) ? 1 : 0) , __extension__ ({
            if (commandTable->element[i]->type == 1)
                ;
            else
                __assert_fail("commandTable->element[i]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 691, __extension__ __PRETTY_FUNCTION__);
        }));
        char *cmdname = commandTable->element[i]->str;
        ((void)sizeof ((commandTable->element[i + 1]->type == 9 || commandTable->element[i + 1]->type == 2) ? 1 : 0) , __extension__ ({
            if (commandTable->element[i + 1]->type == 9 || commandTable->element[i + 1]->type == 2)
                ;
            else
                __assert_fail("commandTable->element[i + 1]->type == REDIS_REPLY_MAP || commandTable->element[i + 1]->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 695, __extension__ __PRETTY_FUNCTION__);
        }));
        redisReply *cmdspecs = commandTable->element[i + 1];
        next = cliInitCommandHelpEntry(cmdname, ((void *)0), next, cmdspecs, groups);
    }
}
static int versionIsSupported (hisds version, hisds since){
    int i;
    char *versionPos = version;
    char *sincePos = since;
    if (!since) {
        return 1;
    }
    for (i = 0; i != 3; i++) {
        int versionPart = atoi(versionPos);
        int sincePart = atoi(sincePos);
        if (versionPart > sincePart) {
            return 1;
        } else if (sincePart > versionPart) {
            return 0;
        }
        versionPos = strchr(versionPos, '.');
        sincePos = strchr(sincePos, '.');
        if (!versionPos && !sincePos)
            return 1;
        if (!versionPos || !sincePos)
            return 0;
        versionPos++;
        sincePos++;
    }
    return 0;
}
static void removeUnsupportedArgs (struct cliCommandArg *args, int *numargs, hisds version){
    int i = 0, j;
    while (i != *numargs)
        {
            if (versionIsSupported(version, args[i].since)) {
                if (args[i].subargs) {
                    removeUnsupportedArgs(args[i].subargs, &args[i].numsubargs, version);
                }
                i++;
                continue;
            }
            for (j = i; j != *numargs - 1; j++) {
                ;
            }
            (*numargs)--;
        }
}
static helpEntry * cliLegacyInitCommandHelpEntry (char *cmdname, char *subcommandname, helpEntry *next, struct commandDocs *command, dict *groups, hisds version){
    helpEntry *help = next++;
    cliFillInCommandHelpEntry(help, cmdname, subcommandname);
    help->docs.summary = hi_sdsnew(command->summary);
    help->docs.since = hi_sdsnew(command->since);
    help->docs.group = hi_sdsnew(command->group);
    hisds group = hi_sdsdup(help->docs.group);
    if (command->args != ((void *)0)) {
        help->docs.args = command->args;
        help->docs.numargs = command->numargs;
        if (version)
            removeUnsupportedArgs(help->docs.args, &help->docs.numargs, version);
        help->docs.params = makeHint(((void *)0), 0, 0, help->docs);
    }
    if (command->subcommands != ((void *)0)) {
        for (size_t i = 0; command->subcommands[i].name != ((void *)0); i++) {
            if (!version || versionIsSupported(version, command->subcommands[i].since)) {
                char *subcommandname = command->subcommands[i].name;
                next = cliLegacyInitCommandHelpEntry(cmdname, subcommandname, next, &command->subcommands[i], groups, version);
            }
        }
    }
    return next;
}
extern int cliLegacyInitCommandHelpEntries (struct commandDocs *commands, dict *groups, hisds version){
    helpEntry *next = helpEntries;
    for (size_t i = 0; commands[i].name != ((void *)0); i++) {
        if (!version || versionIsSupported(version, commands[i].since)) {
            next = cliLegacyInitCommandHelpEntry(commands[i].name, ((void *)0), next, &commands[i], groups, version);
        }
    }
    return next - helpEntries;
}
static size_t cliLegacyCountCommands (struct commandDocs *commands, hisds version){
    int numCommands = 0;
    for (size_t i = 0; commands[i].name != ((void *)0); i++) {
        if (version && !versionIsSupported(version, commands[i].since)) {
            continue;
        }
        numCommands++;
        if (commands[i].subcommands != ((void *)0)) {
            numCommands += cliLegacyCountCommands(commands[i].subcommands, version);
        }
    }
    return numCommands;
}
static hisds cliGetServerVersion (){
    static const char *key = "\nredis_version:";
    redisReply *serverInfo = ((void *)0);
    char *pos;
    if (config.server_version != ((void *)0)) {
        return config.server_version;
    }
    if (!context)
        return ((void *)0);
    serverInfo = redisCommand(context, "INFO SERVER");
    if (serverInfo == ((void *)0) || serverInfo->type == 6) {
        ;
        return hi_sdsempty();
    }
    ((void)sizeof ((serverInfo->type == 1 || serverInfo->type == 14) ? 1 : 0) , __extension__ ({
        if (serverInfo->type == 1 || serverInfo->type == 14)
            ;
        else
            __assert_fail("serverInfo->type == REDIS_REPLY_STRING || serverInfo->type == REDIS_REPLY_VERB", "redis-cli_InstSlice.c", 828, __extension__ __PRETTY_FUNCTION__);
    }));
    hisds info = serverInfo->str;
    pos = strstr(info, key);
    if (pos) {
        pos += strlen(key);
        char *end = strchr(pos, '\r');
        if (end) {
            hisds version = hi_sdsnewlen(pos, end - pos);
            config.server_version = version;
            return version;
        }
    }
    ;
    return ((void *)0);
}
static void cliLegacyInitHelp (dict *groups){
    hisds serverVersion = cliGetServerVersion();
    helpEntriesLen = cliLegacyCountCommands(redisCommandTable, serverVersion);
    helpEntries = zmalloc(sizeof(helpEntry) * helpEntriesLen);
    helpEntriesLen = cliLegacyInitCommandHelpEntries(redisCommandTable, groups, serverVersion);
    cliInitGroupHelpEntries(groups);
    qsort(helpEntries, helpEntriesLen, sizeof(helpEntry), helpEntryCompare);
}
static void cliInitHelp (){
    dictType groupsdt = {dictSdsHash, ((void *)0), ((void *)0), dictSdsKeyCompare, dictSdsDestructor, ((void *)0), ((void *)0)};
    redisReply *commandTable;
    dict *groups;
    if (cliConnect((1 << 1)) == -1) {
        groups = dictCreate(&groupsdt);
        cliLegacyInitHelp(groups);
        return;
    }
    commandTable = redisCommand(context, "COMMAND DOCS");
    if (commandTable == ((void *)0) || commandTable->type == 6) {
        ;
        groups = dictCreate(&groupsdt);
        cliLegacyInitHelp(groups);
        cliLegacyIntegrateHelp();
        return;
    }
    ;
    if (commandTable->type != 9 && commandTable->type != 2) {
        ;
        return;
    }
    helpEntriesLen = cliCountCommands(commandTable);
    helpEntries = zmalloc(sizeof(helpEntry) * helpEntriesLen);
    groups = dictCreate(&groupsdt);
    cliInitCommandHelpEntries(commandTable, groups);
    cliInitGroupHelpEntries(groups);
}
static void cliOutputHelp (int argc, char **argv){
    int i, j;
    char *group;
    helpEntry *entry;
    struct commandDocs *help;
    if (argc == 0) {
        ;
        return;
    } else {
        ;
    }
    if (helpEntries == ((void *)0)) {
        cliInitHelp();
    }
    ((void)sizeof ((argc > 0) ? 1 : 0) , __extension__ ({
        if (argc > 0)
            ;
        else
            __assert_fail("argc > 0", "redis-cli_InstSlice.c", 930, __extension__ __PRETTY_FUNCTION__);
    }));
}
static hisds addSeparator (hisds str, size_t *len, char *separator, int is_last){
    if (hi_sdslen(str) > *len && !is_last) {
        str = hi_sdscat(str, separator);
        *len = hi_sdslen(str);
    }
    return str;
}
static void clearMatchedArgs (cliCommandArg *args, int numargs){
    for (int i = 0; i != numargs; ++i) {
        args[i].matched = 0;
        args[i].matched_token = 0;
        args[i].matched_name = 0;
        args[i].matched_all = 0;
        if (args[i].subargs) {
            clearMatchedArgs(args[i].subargs, args[i].numsubargs);
        }
    }
}
static hisds addHintForArguments (hisds hint, cliCommandArg *args, int numargs, char *separator){
    int i, j, incomplete;
    size_t len = hi_sdslen(hint);
    for (i = 0; i < numargs; i++) {
        if (!(args[i].flags & (1 << 0))) {
            hint = addHintForArgument(hint, &args[i]);
            hint = addSeparator(hint, &len, separator, i == numargs - 1);
            continue;
        }
        for (j = i , incomplete = -1; j < numargs; j++) {
            if (!(args[j].flags & (1 << 0)))
                break;
            if (args[j].matched != 0 && args[j].matched_all == 0) {
                hint = addHintForArgument(hint, &args[j]);
                hint = addSeparator(hint, &len, separator, i == numargs - 1);
                incomplete = j;
            }
        }
        if (j == numargs || args[j].matched == 0) {
            for (; i < j; i++) {
                if (incomplete != i) {
                    hint = addHintForArgument(hint, &args[i]);
                    hint = addSeparator(hint, &len, separator, i == numargs - 1);
                }
            }
        }
        i = j - 1;
    }
    return hint;
}
static hisds addHintForRepeatedArgument (hisds hint, cliCommandArg *arg){
    if (!(arg->flags & (1 << 1))) {
        return hint;
    }
    clearMatchedArgs(arg, 1);
    if (hint[0] != '\x00') {
        hint = hi_sdscat(hint, " ");
    }
    hint = hi_sdscat(hint, "[");
    if (arg->flags & (1 << 2)) {
        hint = sdscat_orempty(hint, arg->token);
        if (arg->type != ARG_TYPE_PURE_TOKEN) {
            hint = hi_sdscat(hint, " ");
        }
    }
    switch (arg->type) {
      case ARG_TYPE_ONEOF:
        hint = addHintForArguments(hint, arg->subargs, arg->numsubargs, "|");
        break;
      case ARG_TYPE_BLOCK:
        hint = addHintForArguments(hint, arg->subargs, arg->numsubargs, " ");
        break;
      default:
        hint = sdscat_orempty(hint, arg->display_text ? arg->display_text : arg->name);
        break;
    }
    hint = hi_sdscat(hint, " ...]");
    return hint;
}
static hisds addHintForArgument (hisds hint, cliCommandArg *arg){
    if (arg->matched_all) {
        return hint;
    }
    if ((arg->flags & (1 << 0)) && !arg->matched) {
        hint = hi_sdscat(hint, "[");
    }
    if (arg->token != ((void *)0) && !arg->matched_token) {
        hint = sdscat_orempty(hint, arg->token);
        if (arg->type != ARG_TYPE_PURE_TOKEN) {
            hint = hi_sdscat(hint, " ");
        }
    }
    switch (arg->type) {
      case ARG_TYPE_ONEOF:
        if (arg->matched == 0) {
            hint = addHintForArguments(hint, arg->subargs, arg->numsubargs, "|");
        } else {
            int i;
            for (i = 0; i < arg->numsubargs; i++) {
                if (arg->subargs[i].matched != 0) {
                    hint = addHintForArgument(hint, &arg->subargs[i]);
                }
            }
        }
        break;
      case ARG_TYPE_BLOCK:
        hint = addHintForArguments(hint, arg->subargs, arg->numsubargs, " ");
        break;
      default:
        if (!arg->matched_name) {
            hint = sdscat_orempty(hint, arg->display_text ? arg->display_text : arg->name);
        }
        break;
    }
    hint = addHintForRepeatedArgument(hint, arg);
    if ((arg->flags & (1 << 0)) && !arg->matched) {
        hint = hi_sdscat(hint, "]");
    }
    return hint;
}
static int matchNoTokenArg (char **nextword, int numwords, cliCommandArg *arg){
    int i;
    switch (arg->type) {
      case ARG_TYPE_BLOCK:
        {
            arg->matched += matchArgs(nextword, numwords, arg->subargs, arg->numsubargs);
            arg->matched_all = 1;
            for (i = 0; i < arg->numsubargs; i++) {
                if (arg->subargs[i].matched_all == 0) {
                    arg->matched_all = 0;
                }
            }
            break;
        }
      case ARG_TYPE_ONEOF:
        {
            for (i = 0; i < arg->numsubargs; i++) {
                if (matchArg(nextword, numwords, &arg->subargs[i])) {
                    arg->matched += arg->subargs[i].matched;
                    arg->matched_all = arg->subargs[i].matched_all;
                    break;
                }
            }
            break;
        }
      case ARG_TYPE_INTEGER:
      case ARG_TYPE_UNIX_TIME:
        {
            long long value;
            if (sscanf(*nextword, "%lld", &value) == 1) {
                arg->matched += 1;
                arg->matched_name = 1;
                arg->matched_all = 1;
            } else {
                arg->matched = 0;
                arg->matched_name = 0;
            }
            break;
        }
      case ARG_TYPE_DOUBLE:
        {
            double value;
            if (sscanf(*nextword, "%lf", &value) == 1) {
                arg->matched += 1;
                arg->matched_name = 1;
                arg->matched_all = 1;
            } else {
                arg->matched = 0;
                arg->matched_name = 0;
            }
            break;
        }
      default:
        arg->matched += 1;
        arg->matched_name = 1;
        arg->matched_all = 1;
        break;
    }
    return arg->matched;
}
static int matchToken (char **nextword, cliCommandArg *arg){
    if (strcasecmp(arg->token, nextword[0]) != 0) {
        return 0;
    }
    arg->matched_token = 1;
    arg->matched = 1;
    return 1;
}
static int matchArgOnce (char **nextword, int numwords, cliCommandArg *arg){
    if (arg->token != ((void *)0)) {
        if (!matchToken(nextword, arg)) {
            return 0;
        }
        if (arg->type == ARG_TYPE_PURE_TOKEN) {
            arg->matched_all = 1;
            return 1;
        }
        if (numwords == 1) {
            return 1;
        }
        nextword++;
        numwords--;
    }
    if (!matchNoTokenArg(nextword, numwords, arg)) {
        return 0;
    }
    return arg->matched;
}
static int matchArg (char **nextword, int numwords, cliCommandArg *arg){
    int matchedWords = 0;
    int matchedOnce = matchArgOnce(nextword, numwords, arg);
    if (!(arg->flags & (1 << 1))) {
        return matchedOnce;
    }
    matchedWords += matchedOnce;
    while (arg->matched_all && matchedWords < numwords)
        {
            clearMatchedArgs(arg, 1);
            if (arg->token != ((void *)0) && !(arg->flags & (1 << 2))) {
                matchedOnce = matchNoTokenArg(nextword + matchedWords, numwords - matchedWords, arg);
                if (arg->matched) {
                    arg->matched_token = 1;
                }
            } else {
                matchedOnce = matchArgOnce(nextword + matchedWords, numwords - matchedWords, arg);
            }
            matchedWords += matchedOnce;
        }
    arg->matched_all = 0;
    return matchedWords;
}
static int matchOneOptionalArg (char **words, int numwords, cliCommandArg *args, int numargs, int *matchedarg){
    for (int nextword = 0, nextarg = 0; nextword != numwords && nextarg != numargs; ++nextarg) {
        if (args[nextarg].matched) {
            continue;
        }
        int matchedWords = matchArg(&words[nextword], numwords - nextword, &args[nextarg]);
        if (matchedWords != 0) {
            *matchedarg = nextarg;
            return matchedWords;
        }
    }
    return 0;
}
static int matchOptionalArgs (char **words, int numwords, cliCommandArg *args, int numargs){
    int nextword = 0;
    int matchedarg = -1, lastmatchedarg = -1;
    while (nextword != numwords)
        {
            int matchedWords = matchOneOptionalArg(&words[nextword], numwords - nextword, args, numargs, &matchedarg);
            if (matchedWords == 0) {
                break;
            }
            if (lastmatchedarg != -1) {
                args[lastmatchedarg].matched_all = 1;
            }
            lastmatchedarg = matchedarg;
            nextword += matchedWords;
        }
    return nextword;
}
static int matchArgs (char **words, int numwords, cliCommandArg *args, int numargs){
    int nextword, nextarg, matchedWords;
    for (nextword = 0 , nextarg = 0; nextword != numwords && nextarg != numargs; ++nextarg) {
        if (args[nextarg].flags & (1 << 0)) {
            int lastoptional;
            for (lastoptional = nextarg; lastoptional < numargs; lastoptional++) {
                if (!(args[lastoptional].flags & (1 << 0)))
                    break;
            }
            matchedWords = matchOptionalArgs(&words[nextword], numwords - nextword, &args[nextarg], lastoptional - nextarg);
            nextarg = lastoptional - 1;
        } else {
            matchedWords = matchArg(&words[nextword], numwords - nextword, &args[nextarg]);
            if (matchedWords == 0) {
                return 0;
            }
        }
        nextword += matchedWords;
    }
    return nextword;
}
static hisds makeHint (char **inputargv, int inputargc, int cmdlen, struct commandDocs docs){
    hisds hint;
    if (docs.args) {
        clearMatchedArgs(docs.args, docs.numargs);
        hint = hi_sdsempty();
        int matchedWords = 0;
        if (inputargv && inputargc)
            matchedWords = matchArgs(inputargv + cmdlen, inputargc - cmdlen, docs.args, docs.numargs);
        if (matchedWords == inputargc - cmdlen) {
            hint = addHintForArguments(hint, docs.args, docs.numargs, " ");
        }
        return hint;
    }
    if (inputargc <= cmdlen) {
        hint = hi_sdsnew(docs.params);
    } else {
        hint = hi_sdsempty();
    }
    return hint;
}
static helpEntry * findHelpEntry (int argc, char **argv){
    helpEntry *entry = ((void *)0);
    int i, rawargc, matchlen = 0;
    hisds *rawargv;
    for (i = 0; i < helpEntriesLen; i++) {
        if (!(helpEntries[i].type & 1))
            continue;
        rawargv = helpEntries[i].argv;
        rawargc = helpEntries[i].argc;
        if (rawargc <= argc) {
            int j;
            for (j = 0; j < rawargc; j++) {
                if (strcasecmp(rawargv[j], argv[j])) {
                    break;
                }
            }
            if (j == rawargc && rawargc > matchlen) {
                matchlen = rawargc;
                entry = &helpEntries[i];
            }
        }
    }
    return entry;
}
static hisds getHintForInput (const char *charinput){
    hisds hint = ((void *)0);
    int inputargc, inputlen = strlen(charinput);
    hisds *inputargv = hi_sdssplitargs(charinput, &inputargc);
    int endspace = inputlen && ((*__ctype_b_loc())[(int)((charinput[inputlen - 1]))] & (unsigned short)_ISspace);
    int matchargc = endspace ? inputargc : inputargc - 1;
    helpEntry *entry = findHelpEntry(matchargc, inputargv);
    if (entry) {
        hint = makeHint(inputargv, matchargc, entry->argc, entry->docs);
    }
    ;
    return hint;
}
static void cliPressAnyKeyTTY (){
    if (!isatty(0))
        return;
    if (!orig_termios_saved) {
        if (tcgetattr(0, &orig_termios) == -1)
            return;
        orig_termios_saved = 1;
    }
    struct termios mode;
}
static int cliAuth (redisContext *ctx, char *user, char *auth){
    redisReply *reply;
    if (auth == ((void *)0))
        return 0;
    if (user == ((void *)0)) {
        reply = redisCommand(ctx, "AUTH %s", auth);
    } else
        reply = redisCommand(ctx, "AUTH %s %s", user, auth);
    if (reply == ((void *)0)) {
        ;
        return -1;
    }
    int result = 0;
    if (reply->type == 6) {
        result = -1;
    }
    ;
    return result;
}
static int cliSelect (){
    redisReply *reply;
    if (config.conn_info.input_dbnum == config.dbnum)
        return 0;
    reply = redisCommand(context, "SELECT %d", config.conn_info.input_dbnum);
    if (reply == ((void *)0)) {
        ;
        return -1;
    }
    int result = 0;
    if (reply->type == 6) {
        result = -1;
    } else {
        config.dbnum = config.conn_info.input_dbnum;
    }
    ;
    return result;
}
static int cliSwitchProto (){
    redisReply *reply;
    if (!config.resp3 || config.resp2)
        return 0;
    reply = redisCommand(context, "HELLO 3");
    if (reply == ((void *)0)) {
        ;
        return -1;
    }
    int result = 0;
    if (reply->type == 6) {
        ;
        if (config.resp3 == 1) {
            result = -1;
        } else if (config.resp3 == 2) {
            result = 0;
        }
    }
    for (size_t i = 0; i < reply->elements; i += 2) {
        ((void)sizeof ((reply->element[i]->type == 1) ? 1 : 0) , __extension__ ({
            if (reply->element[i]->type == 1)
                ;
            else
                __assert_fail("reply->element[i]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 1495, __extension__ __PRETTY_FUNCTION__);
        }));
        char *key = reply->element[i]->str;
        if (!strcmp(key, "version")) {
            ((void)sizeof ((reply->element[i + 1]->type == 1) ? 1 : 0) , __extension__ ({
                if (reply->element[i + 1]->type == 1)
                    ;
                else
                    __assert_fail("reply->element[i + 1]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 1498, __extension__ __PRETTY_FUNCTION__);
            }));
            config.server_version = hi_sdsnew(reply->element[i + 1]->str);
        }
    }
    ;
    config.current_resp3 = 1;
    return result;
}
static int cliConnect (int flags){
    if (context == ((void *)0) || flags & (1 << 0)) {
        if (context != ((void *)0)) {
            ;
            config.dbnum = 0;
            config.in_multi = 0;
            config.pubsub_mode = 0;
        }
        if (config.hostsocket == ((void *)0) || (config.cluster_mode && config.cluster_reissue_command)) {
            context = redisConnectWrapper(config.conn_info.hostip, config.conn_info.hostport, config.connect_timeout);
        } else {
            context = redisConnectUnixWrapper(config.hostsocket, config.connect_timeout);
        }
        if (!context->err && config.tls) {
            const char *err = ((void *)0);
            if (cliSecureConnection(context, config.sslconfig, &err) == -1 && err) {
                ;
                context = ((void *)0);
                return -1;
            }
        }
        if (context->err) {
            ;
            context = ((void *)0);
            return -1;
        }
        ;
        config.current_resp3 = 0;
        if (cliAuth(context, config.conn_info.user, config.conn_info.auth) != 0)
            return -1;
        if (cliSelect() != 0)
            return -1;
        if (cliSwitchProto() != 0)
            return -1;
    }
    return 0;
}
static int cliSendAsking (){
    redisReply *reply;
    config.cluster_send_asking = 0;
    if (context == ((void *)0)) {
        return -1;
    }
    reply = redisCommand(context, "ASKING");
    if (reply == ((void *)0)) {
        ;
        return -1;
    }
    int result = 0;
    if (reply->type == 6) {
        result = -1;
    }
    ;
    return result;
}
static int cliIsMultilineValueTTY (redisReply *r){
    switch (r->type) {
      case 2:
      case 10:
      case 12:
        if (r->elements == 0)
            return 0;
        if (r->elements > 1)
            return 1;
        return cliIsMultilineValueTTY(r->element[0]);
      case 9:
        if (r->elements == 0)
            return 0;
        if (r->elements > 2)
            return 1;
        return cliIsMultilineValueTTY(r->element[1]);
      default:
        return 0;
    }
}
static hisds cliFormatReplyTTY (redisReply *r, char *prefix){
    hisds out = hi_sdsempty();
    switch (r->type) {
      case 6:
        out = hi_sdscatprintf(out, "(error) %s\n", r->str);
        break;
      case 5:
        out = hi_sdscat(out, r->str);
        out = hi_sdscat(out, "\n");
        break;
      case 3:
        out = hi_sdscatprintf(out, "(integer) %lld\n", r->integer);
        break;
      case 7:
        out = hi_sdscatprintf(out, "(double) %s\n", r->str);
        break;
      case 1:
      case 14:
        if (r->type == 1) {
            out = hi_sdscatrepr(out, r->str, r->len);
            out = hi_sdscat(out, "\n");
        } else {
            out = hi_sdscatlen(out, r->str, r->len);
            out = hi_sdscat(out, "\n");
        }
        break;
      case 4:
        out = hi_sdscat(out, "(nil)\n");
        break;
      case 8:
        out = hi_sdscat(out, r->integer ? "(true)\n" : "(false)\n");
        break;
      case 2:
      case 9:
      case 10:
      case 12:
        if (r->elements == 0) {
            if (r->type == 2) {
                out = hi_sdscat(out, "(empty array)\n");
            } else if (r->type == 9) {
                out = hi_sdscat(out, "(empty hash)\n");
            } else if (r->type == 10) {
                out = hi_sdscat(out, "(empty set)\n");
            } else if (r->type == 12) {
                out = hi_sdscat(out, "(empty push)\n");
            } else
                out = hi_sdscat(out, "(empty aggregate type)\n");
        } else {
            unsigned int i, idxlen = 0;
            char _prefixlen[16];
            char _prefixfmt[16];
            hisds _prefix;
            hisds tmp;
            i = r->elements;
            if (r->type == 9)
                i /= 2;
            do {
                idxlen++;
                i /= 10;
            } while (i);
            memset(_prefixlen, ' ', idxlen + 2);
            _prefixlen[idxlen + 2] = '\x00';
            _prefix = hi_sdscat(hi_sdsnew(prefix), _prefixlen);
            char numsep;
            if (r->type == 10) {
                numsep = '~';
            } else if (r->type == 9) {
                numsep = '#';
            } else
                numsep = ')';
            for (i = 0; i < r->elements; i++) {
                unsigned int human_idx = (r->type == 9) ? i / 2 : i;
                human_idx++;
                out = hi_sdscatprintf(out, _prefixfmt, i == 0 ? "" : prefix, human_idx);
                tmp = cliFormatReplyTTY(r->element[i], _prefix);
                out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
                if (r->type == 9) {
                    i++;
                    out = hi_sdscat(out, " => ");
                    if (cliIsMultilineValueTTY(r->element[i])) {
                        out = hi_sdscat(out, "\n");
                        out = hi_sdscat(out, _prefix);
                    }
                    tmp = cliFormatReplyTTY(r->element[i], _prefix);
                    out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
                }
            }
            ;
        }
        break;
    }
    return out;
}
extern int isPubsubPush (redisReply *r){
    if (r == ((void *)0) || r->type != (config.current_resp3 ? 12 : 2) || r->elements < 3 || r->element[0]->type != 1) {
        return 0;
    }
    char *str = r->element[0]->str;
    size_t len = r->element[0]->len;
    return ((len >= strlen("message") && !strcmp(str + len - strlen("message"), "message")) || (len >= strlen("subscribe") && !strcmp(str + len - strlen("subscribe"), "subscribe")));
}
extern int isColorTerm (){
    char *t = getenv("TERM");
    return t != ((void *)0) && strstr(t, "xterm") != ((void *)0);
}
extern hisds sdscatcolor (hisds o, char *s, size_t len, char *color){
    if (!isColorTerm())
        return hi_sdscatlen(o, s, len);
    int bold = strstr(color, "bold") != ((void *)0);
    int ccode = 37;
    if (strstr(color, "red")) {
        ccode = 31;
    } else if (strstr(color, "green")) {
        ccode = 32;
    } else if (strstr(color, "yellow")) {
        ccode = 33;
    } else if (strstr(color, "blue")) {
        ccode = 34;
    } else if (strstr(color, "magenta")) {
        ccode = 35;
    } else if (strstr(color, "cyan")) {
        ccode = 36;
    } else if (strstr(color, "white"))
        ccode = 37;
    o = hi_sdscatfmt(o, "\033[%i;%i;49m", bold, ccode);
    o = hi_sdscatlen(o, s, len);
    o = hi_sdscat(o, "\033[0m");
    return o;
}
extern hisds sdsCatColorizedLdbReply (hisds o, char *s, size_t len){
    char *color = "white";
    if (strstr(s, "<debug>"))
        color = "bold";
    if (strstr(s, "<redis>"))
        color = "green";
    if (strstr(s, "<reply>"))
        color = "cyan";
    if (strstr(s, "<error>"))
        color = "red";
    if (strstr(s, "<hint>"))
        color = "bold";
    if (strstr(s, "<value>") || strstr(s, "<retval>"))
        color = "magenta";
    if (len > 4 && ((*__ctype_b_loc())[(int)((s[3]))] & (unsigned short)_ISdigit)) {
        if (s[1] == '>') {
            color = "yellow";
        } else if (s[2] == '#')
            color = "bold";
    }
    return sdscatcolor(o, s, len, color);
}
static hisds cliFormatReplyRaw (redisReply *r){
    hisds out = hi_sdsempty(), tmp;
    size_t i;
    switch (r->type) {
        ;
      case 6:
        out = hi_sdscatlen(out, r->str, r->len);
        out = hi_sdscatlen(out, "\n", 1);
        break;
      case 5:
      case 1:
      case 14:
        if (r->type == 5 && config.eval_ldb) {
            if (strstr(r->str, "<endsession>") == r->str) {
                config.enable_ldb_on_eval = 0;
                config.eval_ldb = 0;
                config.eval_ldb_end = 1;
                config.output = 0;
            } else {
                out = sdsCatColorizedLdbReply(out, r->str, r->len);
            }
        } else {
            out = hi_sdscatlen(out, r->str, r->len);
        }
        break;
      case 8:
        out = hi_sdscat(out, r->integer ? "(true)" : "(false)");
        break;
      case 3:
        out = hi_sdscatprintf(out, "%lld", r->integer);
        break;
      case 7:
        out = hi_sdscatprintf(out, "%s", r->str);
        break;
      case 10:
      case 2:
      case 12:
        for (i = 0; i < r->elements; i++) {
            if (i > 0)
                out = hi_sdscat(out, config.mb_delim);
            tmp = cliFormatReplyRaw(r->element[i]);
            out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
        }
        break;
      case 9:
        for (i = 0; i < r->elements; i += 2) {
            if (i > 0)
                out = hi_sdscat(out, config.mb_delim);
            tmp = cliFormatReplyRaw(r->element[i]);
            out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
            out = hi_sdscatlen(out, " ", 1);
            tmp = cliFormatReplyRaw(r->element[i + 1]);
            out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
        }
        break;
    }
    return out;
}
static hisds cliFormatReplyCSV (redisReply *r){
    unsigned int i;
    hisds out = hi_sdsempty();
    switch (r->type) {
      case 6:
        out = hi_sdscat(out, "ERROR,");
        out = hi_sdscatrepr(out, r->str, strlen(r->str));
        break;
      case 5:
        out = hi_sdscatrepr(out, r->str, r->len);
        break;
      case 3:
        out = hi_sdscatprintf(out, "%lld", r->integer);
        break;
      case 7:
        out = hi_sdscatprintf(out, "%s", r->str);
        break;
      case 1:
      case 14:
        out = hi_sdscatrepr(out, r->str, r->len);
        break;
      case 4:
        out = hi_sdscat(out, "NULL");
        break;
      case 8:
        out = hi_sdscat(out, r->integer ? "true" : "false");
        break;
      case 2:
      case 10:
      case 12:
      case 9:
        for (i = 0; i < r->elements; i++) {
            hisds tmp = cliFormatReplyCSV(r->element[i]);
            out = hi_sdscatlen(out, tmp, hi_sdslen(tmp));
            if (i != r->elements - 1)
                out = hi_sdscat(out, ",");
        }
        break;
    }
    return out;
}
static hisds jsonStringOutput (hisds out, const char *p, int len, int mode){
    if (mode == 3) {
        return escapeJsonString(out, p, len);
    } else if (mode == 4) {
        hisds tmp = hi_sdscatrepr(hi_sdsempty(), p, len);
        int tmplen = hi_sdslen(tmp);
        char *n = tmp;
        while (tmplen--)
            {
                if (*n == '\\') {
                    out = hi_sdscatlen(out, "\\\\", 2);
                } else
                    out = hi_sdscatlen(out, n, 1);
                n++;
            }
        ;
        return out;
    } else {
        ;
    }
}
static hisds cliFormatReplyJson (hisds out, redisReply *r, int mode){
    unsigned int i;
    switch (r->type) {
      case 6:
        out = hi_sdscat(out, "error:");
        out = jsonStringOutput(out, r->str, strlen(r->str), mode);
        break;
      case 5:
        out = jsonStringOutput(out, r->str, r->len, mode);
        break;
      case 3:
        out = hi_sdscatprintf(out, "%lld", r->integer);
        break;
      case 7:
        out = hi_sdscatprintf(out, "%s", r->str);
        break;
      case 1:
      case 14:
        out = jsonStringOutput(out, r->str, r->len, mode);
        break;
      case 4:
        out = hi_sdscat(out, "null");
        break;
      case 8:
        out = hi_sdscat(out, r->integer ? "true" : "false");
        break;
      case 2:
      case 10:
      case 12:
        out = hi_sdscat(out, "[");
        for (i = 0; i < r->elements; i++) {
            out = cliFormatReplyJson(out, r->element[i], mode);
            if (i != r->elements - 1)
                out = hi_sdscat(out, ",");
        }
        out = hi_sdscat(out, "]");
        break;
      case 9:
        out = hi_sdscat(out, "{");
        for (i = 0; i < r->elements; i += 2) {
            redisReply *key = r->element[i];
            if (key->type == 6 || key->type == 5 || key->type == 1 || key->type == 14) {
                out = cliFormatReplyJson(out, key, mode);
            } else {
                hisds keystr = cliFormatReplyJson(hi_sdsempty(), key, mode);
                if (keystr[0] == '"') {
                    out = hi_sdscatsds(out, keystr);
                } else
                    out = hi_sdscatfmt(out, "\"%S\"", keystr);
            }
            out = hi_sdscat(out, ":");
            out = cliFormatReplyJson(out, r->element[i + 1], mode);
            if (i != r->elements - 2)
                out = hi_sdscat(out, ",");
        }
        out = hi_sdscat(out, "}");
        break;
    }
    return out;
}
static hisds cliFormatReply (redisReply *reply, int mode, int verbatim){
    hisds out;
    if (verbatim) {
        out = cliFormatReplyRaw(reply);
    } else if (mode == 0) {
        out = cliFormatReplyTTY(reply, "");
    } else if (mode == 1) {
        out = cliFormatReplyRaw(reply);
        out = hi_sdscatsds(out, config.cmd_delim);
    } else if (mode == 2) {
        out = cliFormatReplyCSV(reply);
        out = hi_sdscatlen(out, "\n", 1);
    } else if (mode == 3 || mode == 4) {
        out = cliFormatReplyJson(hi_sdsempty(), reply, mode);
        out = hi_sdscatlen(out, "\n", 1);
    } else {
        ;
    }
    return out;
}
static int cliReadReply (int output_raw_strings){
    void *_reply;
    redisReply *reply;
    hisds out = ((void *)0);
    int output = 1;
    if (config.last_reply) {
        ;
        config.last_reply = ((void *)0);
    }
    if (redisGetReply(context, &_reply) != 0) {
        if (config.blocking_state_aborted) {
            config.blocking_state_aborted = 0;
            config.monitor_mode = 0;
            config.pubsub_mode = 0;
            return cliConnect((1 << 0));
        }
        if (config.shutdown) {
            ;
            context = ((void *)0);
            return 0;
        }
        if (config.interactive) {
            if (context->err == 1 && ((*__errno_location()) == 104 || (*__errno_location()) == 32))
                return -1;
            if (context->err == 3)
                return -1;
        }
        ;
        exit(1);
        return -1;
    }
    config.last_reply = reply = (redisReply *)_reply;
    config.last_cmd_type = reply->type;
    if (config.cluster_mode && reply->type == 6 && (!strncmp(reply->str, "MOVED ", 6) || !strncmp(reply->str, "ASK ", 4))) {
        char *p = reply->str, *s;
        int slot;
        output = 0;
        s = strchr(p, ' ');
        p = strchr(s + 1, ' ');
        *p = '\x00';
        slot = atoi(s + 1);
        s = strrchr(p + 1, ':');
        *s = '\x00';
        if (p + 1 != s) {
            ;
            config.conn_info.hostip = hi_sdsnew(p + 1);
        }
        config.conn_info.hostport = atoi(s + 1);
        config.cluster_reissue_command = 1;
        if (!strncmp(reply->str, "ASK ", 4)) {
            config.cluster_send_asking = 1;
        }
        ;
    } else if (!config.interactive && config.set_errcode && reply->type == 6) {
        ;
        return -1;
    }
    if (output) {
        out = cliFormatReply(reply, config.output, output_raw_strings);
        fwrite(out, hi_sdslen(out), 1, stdout);
    }
    return 0;
}
static void cliWaitForMessagesOrStdin (){
    int show_info = config.output != 1 && (isatty(1) || getenv("FAKETTY"));
    int use_color = show_info && isColorTerm();
    cliPressAnyKeyTTY();
    while (config.pubsub_mode)
        {
            redisReply *reply;
            do {
                if (redisGetReplyFromReader(context, (void **)&reply) != 0) {
                    ;
                    exit(1);
                }
                if (reply) {
                    hisds out = cliFormatReply(reply, config.output, 0);
                    fwrite(out, hi_sdslen(out), 1, stdout);
                }
            } while (reply);
            struct timeval tv;
            fd_set readfds;
            do {
                int __d0, __d1;
                asm volatile ("cld; rep; stosq" : "=c" (__d0), "=D" (__d1) : "a" (0), "0" (sizeof(fd_set) / sizeof(__fd_mask)), "1" (&((&readfds)->fds_bits)[0]) : "memory");
            } while (0);
            ((void)(((&readfds)->fds_bits)[((context->fd) / (8 * (int)sizeof(__fd_mask)))] |= ((__fd_mask)(1UL << ((context->fd) % (8 * (int)sizeof(__fd_mask)))))));
            ((void)(((&readfds)->fds_bits)[((0) / (8 * (int)sizeof(__fd_mask)))] |= ((__fd_mask)(1UL << ((0) % (8 * (int)sizeof(__fd_mask)))))));
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            if (config.blocking_state_aborted) {
                config.blocking_state_aborted = 0;
                config.pubsub_mode = 0;
                if (cliConnect((1 << 0)) != 0) {
                    ;
                    exit(1);
                }
                break;
            } else if (((((&readfds)->fds_bits)[((context->fd) / (8 * (int)sizeof(__fd_mask)))] & ((__fd_mask)(1UL << ((context->fd) % (8 * (int)sizeof(__fd_mask)))))) != 0)) {
                if (cliReadReply(0) != 0) {
                    ;
                    exit(1);
                }
                ;
            } else if (((((&readfds)->fds_bits)[((0) / (8 * (int)sizeof(__fd_mask)))] & ((__fd_mask)(1UL << ((0) % (8 * (int)sizeof(__fd_mask)))))) != 0)) {
                break;
            }
        }
    ;
}
static int cliSendCommand (int argc, char **argv, long repeat){
    char *command = argv[0];
    size_t *argvlen;
    int j, output_raw;
    if (context == ((void *)0))
        return -1;
    output_raw = 0;
    if (!strcasecmp(command, "info") || !strcasecmp(command, "lolwut") || (argc >= 2 && !strcasecmp(command, "debug") && !strcasecmp(argv[1], "htstats")) || (argc >= 2 && !strcasecmp(command, "debug") && !strcasecmp(argv[1], "htstats-key")) || (argc >= 2 && !strcasecmp(command, "debug") && !strcasecmp(argv[1], "client-eviction")) || (argc >= 2 && !strcasecmp(command, "memory") && (!strcasecmp(argv[1], "malloc-stats") || !strcasecmp(argv[1], "doctor"))) || (argc == 2 && !strcasecmp(command, "cluster") && (!strcasecmp(argv[1], "nodes") || !strcasecmp(argv[1], "info"))) || (argc >= 2 && !strcasecmp(command, "client") && (!strcasecmp(argv[1], "list") || !strcasecmp(argv[1], "info"))) || (argc == 3 && !strcasecmp(command, "latency") && !strcasecmp(argv[1], "graph")) || (argc == 2 && !strcasecmp(command, "latency") && !strcasecmp(argv[1], "doctor")) || (argc >= 2 && !strcasecmp(command, "proxy") && !strcasecmp(argv[1], "info"))) {
        output_raw = 1;
    }
    if (!strcasecmp(command, "shutdown"))
        config.shutdown = 1;
    if (!strcasecmp(command, "monitor"))
        config.monitor_mode = 1;
    int is_subscribe = (!strcasecmp(command, "subscribe") || !strcasecmp(command, "psubscribe") || !strcasecmp(command, "ssubscribe"));
    int is_unsubscribe = (!strcasecmp(command, "unsubscribe") || !strcasecmp(command, "punsubscribe") || !strcasecmp(command, "sunsubscribe"));
    if (!strcasecmp(command, "sync") || !strcasecmp(command, "psync"))
        config.slave_mode = 1;
    if (argc == 3 && !strcasecmp(argv[0], "script") && !strcasecmp(argv[1], "debug")) {
        if (!strcasecmp(argv[2], "yes") || !strcasecmp(argv[2], "sync")) {
            config.enable_ldb_on_eval = 1;
        } else {
            config.enable_ldb_on_eval = 0;
        }
    }
    if (!strcasecmp(command, "eval") && config.enable_ldb_on_eval) {
        config.eval_ldb = 1;
        config.output = 1;
    }
    argvlen = zmalloc(argc * sizeof(size_t));
    for (j = 0; j < argc; j++)
        argvlen[j] = hi_sdslen(argv[j]);
    while (repeat < 0 || repeat-- > 0)
        {
            ;
            if (config.monitor_mode) {
                do {
                    if (cliReadReply(output_raw) != 0) {
                        ;
                        exit(1);
                    }
                    ;
                    if (config.last_cmd_type == 6)
                        config.monitor_mode = 0;
                } while (config.monitor_mode);
                return 0;
            }
            int num_expected_pubsub_push = 0;
            if (is_subscribe || is_unsubscribe) {
                num_expected_pubsub_push = argc > 1 ? argc - 1 : 1;
            }
            if (config.slave_mode) {
                ;
                slaveMode(0);
                config.slave_mode = 0;
                return -1;
            }
            while (1)
                {
                    if (cliReadReply(output_raw) != 0) {
                        ;
                        return -1;
                    }
                    ;
                    if (config.pubsub_mode || num_expected_pubsub_push > 0) {
                        if (isPubsubPush(config.last_reply)) {
                            if (num_expected_pubsub_push > 0 && !strcasecmp(config.last_reply->element[0]->str, command)) {
                                if (is_subscribe && !config.pubsub_mode) {
                                    config.pubsub_mode = 1;
                                }
                                if (--num_expected_pubsub_push > 0) {
                                    continue;
                                }
                            } else {
                                ;
                            }
                        } else if (config.last_reply->type == 12) {
                            continue;
                        }
                    }
                    if (!strcasecmp(command, "select") && argc == 2 && config.last_cmd_type != 6) {
                        config.conn_info.input_dbnum = config.dbnum = atoi(argv[1]);
                    } else if (!strcasecmp(command, "auth") && (argc == 2 || argc == 3)) {
                        cliSelect();
                    } else if (!strcasecmp(command, "multi") && argc == 1 && config.last_cmd_type != 6) {
                        config.in_multi = 1;
                        config.pre_multi_dbnum = config.dbnum;
                    } else if (!strcasecmp(command, "exec") && argc == 1 && config.in_multi) {
                        config.in_multi = 0;
                        if (config.last_cmd_type == 6 || config.last_cmd_type == 4) {
                            config.conn_info.input_dbnum = config.dbnum = config.pre_multi_dbnum;
                        }
                        ;
                    } else if (!strcasecmp(command, "discard") && argc == 1 && config.last_cmd_type != 6) {
                        config.in_multi = 0;
                        config.conn_info.input_dbnum = config.dbnum = config.pre_multi_dbnum;
                    } else if (!strcasecmp(command, "reset") && argc == 1 && config.last_cmd_type != 6) {
                        config.in_multi = 0;
                        config.dbnum = 0;
                        config.conn_info.input_dbnum = 0;
                        config.current_resp3 = 0;
                        config.pubsub_mode = 0;
                    } else if (!strcasecmp(command, "hello")) {
                        if (config.last_cmd_type == 9) {
                            config.current_resp3 = 1;
                        } else if (config.last_cmd_type == 2) {
                            config.current_resp3 = 0;
                        }
                    } else {
                        ;
                    }
                    ;
                }
            if (config.cluster_reissue_command) {
                break;
            }
            ;
        }
    ;
    return 0;
}
static redisReply * reconnectingRedisCommand (redisContext *c, const char *fmt, ...){
    redisReply *reply = ((void *)0);
    int tries = 0;
    va_list ap;
    ((void)sizeof ((!c->err) ? 1 : 0) , __extension__ ({
        if (!c->err)
            ;
        else
            __assert_fail("!c->err", "redis-cli_InstSlice.c", 2357, __extension__ __PRETTY_FUNCTION__);
    }));
    while (reply == ((void *)0))
        {
            while (c->err & (1 | 3))
                {
                    ;
                    printf("Reconnecting... %d\r", ++tries);
                    c = redisConnectWrapper(config.conn_info.hostip, config.conn_info.hostport, config.connect_timeout);
                    if (!c->err && config.tls) {
                        const char *err = ((void *)0);
                        if (cliSecureConnection(c, config.sslconfig, &err) == -1 && err) {
                            ;
                        }
                    }
                    ;
                }
            __builtin_va_start(ap, fmt);
            reply = redisvCommand(c, fmt, ap);
            if (c->err && !(c->err & (1 | 3))) {
                ;
            } else {
                ;
            }
        }
    context = c;
    return reply;
}
static int parseOptions (int argc, char **argv){
    int i;
    for (i = 1; i < argc; i++) {
        int lastarg = i == argc - 1;
        if (!strcmp(argv[i], "-h") && !lastarg) {
            ;
            config.conn_info.hostip = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "-h") && lastarg) {
            ;
        } else if (!strcmp(argv[i], "--help")) {
            ;
        } else if (!strcmp(argv[i], "-x")) {
            config.stdin_lastarg = 1;
        } else if (!strcmp(argv[i], "-X") && !lastarg) {
            config.stdin_tag_arg = 1;
            config.stdin_tag_name = argv[++i];
        } else if (!strcmp(argv[i], "-p") && !lastarg) {
            config.conn_info.hostport = atoi(argv[++i]);
            if (config.conn_info.hostport < 0 || config.conn_info.hostport > 65535) {
                ;
            }
        } else if (!strcmp(argv[i], "-t") && !lastarg) {
            char *eptr;
            double seconds = strtod(argv[++i], &eptr);
            if (eptr[0] != '\x00' || __builtin_isnan(seconds) || seconds < 0.) {
                ;
            }
            config.connect_timeout.tv_sec = (long long)seconds;
            config.connect_timeout.tv_usec = ((long long)(seconds * 1000000)) % 1000000;
        } else if (!strcmp(argv[i], "-s") && !lastarg) {
            config.hostsocket = argv[++i];
        } else if (!strcmp(argv[i], "-r") && !lastarg) {
            config.repeat = strtoll(argv[++i], ((void *)0), 10);
        } else if (!strcmp(argv[i], "-i") && !lastarg) {
            double seconds = atof(argv[++i]);
            config.interval = seconds * 1000000;
        } else if (!strcmp(argv[i], "-n") && !lastarg) {
            config.conn_info.input_dbnum = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--no-auth-warning")) {
            config.no_auth_warning = 1;
        } else if (!strcmp(argv[i], "--askpass")) {
            config.askpass = 1;
        } else if ((!strcmp(argv[i], "-a") || !strcmp(argv[i], "--pass")) && !lastarg) {
            config.conn_info.auth = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "--user") && !lastarg) {
            config.conn_info.user = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "-u") && !lastarg) {
            parseRedisUri(argv[++i], "redis-cli", &config.conn_info, &config.tls);
            if (config.conn_info.hostport < 0 || config.conn_info.hostport > 65535) {
                ;
            }
        } else if (!strcmp(argv[i], "--raw")) {
            config.output = 1;
        } else if (!strcmp(argv[i], "--no-raw")) {
            config.output = 0;
        } else if (!strcmp(argv[i], "--quoted-input")) {
            config.quoted_input = 1;
        } else if (!strcmp(argv[i], "--csv")) {
            config.output = 2;
        } else if (!strcmp(argv[i], "--json")) {
            if (config.resp3 == 0) {
                config.resp3 = 2;
            }
            config.output = 3;
        } else if (!strcmp(argv[i], "--quoted-json")) {
            if (config.resp3 == 0) {
                config.resp3 = 2;
            }
            config.output = 4;
        } else if (!strcmp(argv[i], "--latency")) {
            config.latency_mode = 1;
        } else if (!strcmp(argv[i], "--latency-dist")) {
            config.latency_dist_mode = 1;
        } else if (!strcmp(argv[i], "--mono")) {
            spectrum_palette = spectrum_palette_mono;
            spectrum_palette_size = spectrum_palette_mono_size;
        } else if (!strcmp(argv[i], "--latency-history")) {
            config.latency_mode = 1;
            config.latency_history = 1;
        } else if (!strcmp(argv[i], "--lru-test") && !lastarg) {
            config.lru_test_mode = 1;
            config.lru_test_sample_size = strtoll(argv[++i], ((void *)0), 10);
        } else if (!strcmp(argv[i], "--slave")) {
            config.slave_mode = 1;
        } else if (!strcmp(argv[i], "--replica")) {
            config.slave_mode = 1;
        } else if (!strcmp(argv[i], "--stat")) {
            config.stat_mode = 1;
        } else if (!strcmp(argv[i], "--scan")) {
            config.scan_mode = 1;
        } else if (!strcmp(argv[i], "--pattern") && !lastarg) {
            ;
            config.pattern = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "--count") && !lastarg) {
            config.count = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--quoted-pattern") && !lastarg) {
            ;
            config.pattern = unquoteCString(argv[++i]);
            if (!config.pattern) {
                ;
            }
        } else if (!strcmp(argv[i], "--intrinsic-latency") && !lastarg) {
            config.intrinsic_latency_mode = 1;
            config.intrinsic_latency_duration = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--rdb") && !lastarg) {
            config.getrdb_mode = 1;
            config.rdb_filename = argv[++i];
        } else if (!strcmp(argv[i], "--functions-rdb") && !lastarg) {
            config.get_functions_rdb_mode = 1;
            config.rdb_filename = argv[++i];
        } else if (!strcmp(argv[i], "--pipe")) {
            config.pipe_mode = 1;
        } else if (!strcmp(argv[i], "--pipe-timeout") && !lastarg) {
            config.pipe_timeout = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--bigkeys")) {
            config.bigkeys = 1;
        } else if (!strcmp(argv[i], "--memkeys")) {
            config.memkeys = 1;
            config.memkeys_samples = -1;
        } else if (!strcmp(argv[i], "--memkeys-samples") && !lastarg) {
            char *endptr;
            config.memkeys = 1;
            config.keystats = 1;
            config.memkeys_samples = strtoll(argv[++i], &endptr, 10);
            if (*endptr) {
                ;
            }
            if (config.memkeys_samples < 0) {
                ;
            }
        } else if (!strcmp(argv[i], "--hotkeys")) {
            config.hotkeys = 1;
        } else if (!strcmp(argv[i], "--keystats")) {
            config.keystats = 1;
            config.memkeys_samples = -1;
        } else if (!strcmp(argv[i], "--keystats-samples") && !lastarg) {
            char *endptr;
            config.keystats = 1;
            config.memkeys_samples = strtoll(argv[++i], &endptr, 10);
            if (*endptr) {
                ;
            }
            if (config.memkeys_samples < 0) {
                ;
            }
        } else if (!strcmp(argv[i], "--cursor") && !lastarg) {
            i++;
            char sign = *argv[i];
            char *endptr;
            config.cursor = strtoull(argv[i], &endptr, 10);
            if (*endptr) {
                ;
            }
            if (sign == '-' && config.cursor != 0) {
                ;
            }
        } else if (!strcmp(argv[i], "--top") && !lastarg) {
            i++;
            char sign = *argv[i];
            char *endptr;
            config.top_sizes_limit = strtoull(argv[i], &endptr, 10);
            if (*endptr) {
                ;
            }
            if (sign == '-' && config.top_sizes_limit != 0) {
                ;
            }
        } else if (!strcmp(argv[i], "--eval") && !lastarg) {
            config.eval = argv[++i];
        } else if (!strcmp(argv[i], "--ldb")) {
            config.eval_ldb = 1;
            config.output = 1;
        } else if (!strcmp(argv[i], "--ldb-sync-mode")) {
            config.eval_ldb = 1;
            config.eval_ldb_sync = 1;
            config.output = 1;
        } else if (!strcmp(argv[i], "-c")) {
            config.cluster_mode = 1;
        } else if (!strcmp(argv[i], "-d") && !lastarg) {
            ;
            config.mb_delim = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "-D") && !lastarg) {
            ;
            config.cmd_delim = hi_sdsnew(argv[++i]);
        } else if (!strcmp(argv[i], "-e")) {
            config.set_errcode = 1;
        } else if (!strcmp(argv[i], "--verbose")) {
            config.verbose = 1;
        } else if (!strcmp(argv[i], "-4")) {
            config.prefer_ipv4 = 1;
        } else if (!strcmp(argv[i], "-6")) {
            config.prefer_ipv6 = 1;
        } else if (!strcmp(argv[i], "--cluster") && !lastarg) {
            ;
            char *cmd = argv[++i];
            int j = i;
            while (j < argc && argv[j][0] != '-')
                j++;
            if (j > i)
                j--;
            int err = createClusterManagerCommand(cmd, j - i, argv + i + 1);
            if (err)
                exit(err);
            i = j;
        } else if (!strcmp(argv[i], "--cluster") && lastarg) {
            ;
        } else if ((!strcmp(argv[i], "--cluster-only-masters"))) {
            config.cluster_manager_command.flags |= 1 << 11;
        } else if ((!strcmp(argv[i], "--cluster-only-replicas"))) {
            config.cluster_manager_command.flags |= 1 << 12;
        } else if (!strcmp(argv[i], "--cluster-replicas") && !lastarg) {
            config.cluster_manager_command.replicas = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--cluster-master-id") && !lastarg) {
            config.cluster_manager_command.master_id = argv[++i];
        } else if (!strcmp(argv[i], "--cluster-from") && !lastarg) {
            config.cluster_manager_command.from = argv[++i];
        } else if (!strcmp(argv[i], "--cluster-to") && !lastarg) {
            config.cluster_manager_command.to = argv[++i];
        } else if (!strcmp(argv[i], "--cluster-from-user") && !lastarg) {
            config.cluster_manager_command.from_user = argv[++i];
        } else if (!strcmp(argv[i], "--cluster-from-pass") && !lastarg) {
            config.cluster_manager_command.from_pass = argv[++i];
        } else if (!strcmp(argv[i], "--cluster-from-askpass")) {
            config.cluster_manager_command.from_askpass = 1;
        } else if (!strcmp(argv[i], "--cluster-weight") && !lastarg) {
            if (config.cluster_manager_command.weight != ((void *)0)) {
                ;
            }
            int widx = i + 1;
            char **weight = argv + widx;
            int wargc = 0;
            for (; widx < argc; widx++) {
                if (strstr(argv[widx], "--") == argv[widx])
                    break;
                if (strchr(argv[widx], '=') == ((void *)0))
                    break;
                wargc++;
            }
            if (wargc > 0) {
                config.cluster_manager_command.weight = weight;
                config.cluster_manager_command.weight_argc = wargc;
                i += wargc;
            }
        } else if (!strcmp(argv[i], "--cluster-slots") && !lastarg) {
            config.cluster_manager_command.slots = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--cluster-timeout") && !lastarg) {
            config.cluster_manager_command.timeout = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--cluster-pipeline") && !lastarg) {
            config.cluster_manager_command.pipeline = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--cluster-threshold") && !lastarg) {
            config.cluster_manager_command.threshold = atof(argv[++i]);
        } else if (!strcmp(argv[i], "--cluster-yes")) {
            config.cluster_manager_command.flags |= 1 << 2;
        } else if (!strcmp(argv[i], "--cluster-simulate")) {
            config.cluster_manager_command.flags |= 1 << 5;
        } else if (!strcmp(argv[i], "--cluster-replace")) {
            config.cluster_manager_command.flags |= 1 << 6;
        } else if (!strcmp(argv[i], "--cluster-copy")) {
            config.cluster_manager_command.flags |= 1 << 7;
        } else if (!strcmp(argv[i], "--cluster-slave")) {
            config.cluster_manager_command.flags |= 1 << 1;
        } else if (!strcmp(argv[i], "--cluster-use-empty-masters")) {
            config.cluster_manager_command.flags |= 1 << 4;
        } else if (!strcmp(argv[i], "--cluster-search-multiple-owners")) {
            config.cluster_manager_command.flags |= 1 << 9;
        } else if (!strcmp(argv[i], "--cluster-fix-with-unreachable-masters")) {
            config.cluster_manager_command.flags |= 1 << 10;
        } else if (!strcmp(argv[i], "--test_hint") && !lastarg) {
            config.test_hint = argv[++i];
        } else if (!strcmp(argv[i], "--test_hint_file") && !lastarg) {
            config.test_hint_file = argv[++i];
        } else if (!strcmp(argv[i], "--tls")) {
            config.tls = 1;
        } else if (!strcmp(argv[i], "--sni") && !lastarg) {
            config.sslconfig.sni = argv[++i];
        } else if (!strcmp(argv[i], "--cacertdir") && !lastarg) {
            config.sslconfig.cacertdir = argv[++i];
        } else if (!strcmp(argv[i], "--cacert") && !lastarg) {
            config.sslconfig.cacert = argv[++i];
        } else if (!strcmp(argv[i], "--cert") && !lastarg) {
            config.sslconfig.cert = argv[++i];
        } else if (!strcmp(argv[i], "--key") && !lastarg) {
            config.sslconfig.key = argv[++i];
        } else if (!strcmp(argv[i], "--tls-ciphers") && !lastarg) {
            config.sslconfig.ciphers = argv[++i];
        } else if (!strcmp(argv[i], "--insecure")) {
            config.sslconfig.skip_cert_verify = 1;
        } else if (!strcmp(argv[i], "--tls-ciphersuites") && !lastarg) {
            config.sslconfig.ciphersuites = argv[++i];
        } else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            hisds version = cliVersion();
        } else if (!strcmp(argv[i], "-2")) {
            config.resp2 = 1;
        } else if (!strcmp(argv[i], "-3")) {
            config.resp3 = 1;
        } else if (!strcmp(argv[i], "--show-pushes") && !lastarg) {
            char *argval = argv[++i];
            if (!strncasecmp(argval, "n", 1)) {
                config.push_output = 0;
            } else if (!strncasecmp(argval, "y", 1)) {
                config.push_output = 1;
            } else {
                ;
            }
        } else if ((config.cluster_manager_command.name != ((void *)0)) && argv[i][0] != '-') {
            if (config.cluster_manager_command.argc == 0) {
                int j = i + 1;
                while (j < argc && argv[j][0] != '-')
                    j++;
                int cmd_argc = j - i;
                config.cluster_manager_command.argc = cmd_argc;
                config.cluster_manager_command.argv = argv + i;
                if (cmd_argc > 1)
                    i = j - 1;
            }
        } else {
            if (argv[i][0] == '-') {
                ;
            } else {
                ;
            }
        }
    }
    if (config.hostsocket && config.cluster_mode) {
        ;
    }
    if (config.resp2 && config.resp3 == 1) {
        ;
    }
    if (config.eval_ldb && config.eval == ((void *)0)) {
        ;
    }
    if (config.get_functions_rdb_mode && config.getrdb_mode) {
        ;
    }
    if (config.stdin_lastarg && config.stdin_tag_arg) {
        ;
    }
    if (config.prefer_ipv4 && config.prefer_ipv6) {
        ;
    }
    return i;
}
static void parseEnv (){
    char *auth = getenv("REDISCLI_AUTH");
    if (auth != ((void *)0) && config.conn_info.auth == ((void *)0)) {
        config.conn_info.auth = auth;
    }
    char *cluster_yes = getenv("REDISCLI_CLUSTER_YES");
    if (cluster_yes != ((void *)0) && !strcmp(cluster_yes, "1")) {
        config.cluster_manager_command.flags |= 1 << 2;
    }
}
static int confirmWithYes (char *msg, int ignore_force){
    if (!ignore_force && (config.cluster_manager_command.flags & 1 << 2)) {
        return 1;
    }
    ;
    char buf[4];
    int nread = read(fileno(stdin), buf, 4);
    buf[3] = '\x00';
    return (nread != 0 && !strcmp("yes", buf));
}
static int issueCommandRepeat (int argc, char **argv, long repeat){
    if (!config.eval_ldb && (!strcasecmp(argv[0], "help") || !strcasecmp(argv[0], "?"))) {
        cliOutputHelp(--argc, ++argv);
        return 0;
    }
    while (1)
        {
            if (config.cluster_reissue_command || context == ((void *)0) || context->err == 1 || context->err == 3) {
                if (cliConnect((1 << 0)) != 0) {
                    ;
                    config.cluster_reissue_command = 0;
                    return -1;
                }
                config.dbnum = 0;
                cliSelect();
            }
            config.cluster_reissue_command = 0;
            if (config.cluster_send_asking) {
                if (cliSendAsking() != 0) {
                    ;
                    return -1;
                }
            }
            if (cliSendCommand(argc, argv, repeat) != 0) {
                ;
                context = ((void *)0);
                return -1;
            }
            if (config.cluster_mode && config.cluster_reissue_command) {
                continue;
            }
            ;
        }
    return 0;
}
static int issueCommand (int argc, char **argv){
    return issueCommandRepeat(argc, argv, config.repeat);
}
static hisds * cliSplitArgs (char *line, int *argc){
    if (config.eval_ldb && (strstr(line, "eval ") == line || strstr(line, "e ") == line)) {
        hisds *argv = hi_sds_malloc(sizeof(hisds) * 2);
        *argc = 2;
        int len = strlen(line);
        int elen = line[1] == ' ' ? 2 : 5;
        argv[0] = hi_sdsnewlen(line, elen - 1);
        argv[1] = hi_sdsnewlen(line + elen, len - elen);
        return argv;
    } else {
        return hi_sdssplitargs(line, argc);
    }
}
extern void cliSetPreferences (char **argv, int argc, int interactive){
    if (!strcasecmp(argv[0], ":set") && argc >= 2) {
        if (!strcasecmp(argv[1], "hints")) {
            pref.hints = 1;
        } else if (!strcasecmp(argv[1], "nohints")) {
            pref.hints = 0;
        } else {
            ;
        }
    } else {
        ;
    }
}
extern void cliLoadPreferences (){
    hisds rcfile = getDotfilePath("REDISCLI_RCFILE", ".redisclirc");
    if (rcfile == ((void *)0))
        return;
    FILE *fp = fopen(rcfile, "r");
    char buf[1024];
    if (fp) {
        while (fgets(buf, sizeof (buf), fp) != ((void *)0))
            {
                hisds *argv;
                int argc;
                argv = hi_sdssplitargs(buf, &argc);
                if (argc > 0)
                    cliSetPreferences(argv, argc, 0);
            }
        ;
    }
    ;
}
static int isSensitiveCommand (int argc, char **argv){
    if (!strcasecmp(argv[0], "auth")) {
        return 1;
    } else if (argc > 1 && !strcasecmp(argv[0], "acl") && (!strcasecmp(argv[1], "deluser") || !strcasecmp(argv[1], "setuser") || !strcasecmp(argv[1], "getuser"))) {
        return 1;
    } else if (argc > 2 && !strcasecmp(argv[0], "config") && !strcasecmp(argv[1], "set")) {
        for (int j = 2; j < argc; j = j + 2) {
            if (!strcasecmp(argv[j], "masterauth") || !strcasecmp(argv[j], "masteruser") || !strcasecmp(argv[j], "tls-key-file-pass") || !strcasecmp(argv[j], "tls-client-key-file-pass") || !strcasecmp(argv[j], "requirepass")) {
                return 1;
            }
        }
        return 0;
    } else if (argc > 4 && !strcasecmp(argv[0], "hello")) {
        for (int j = 2; j < argc; j++) {
            int moreargs = argc - 1 - j;
            if (!strcasecmp(argv[j], "AUTH") && moreargs >= 2) {
                return 1;
            } else if (!strcasecmp(argv[j], "SETNAME") && moreargs) {
                j++;
            } else {
                return 0;
            }
        }
    } else if (argc > 7 && !strcasecmp(argv[0], "migrate")) {
        for (int j = 6; j < argc; j++) {
            int moreargs = argc - 1 - j;
            if (!strcasecmp(argv[j], "auth") && moreargs) {
                return 1;
            } else if (!strcasecmp(argv[j], "auth2") && moreargs >= 2) {
                return 1;
            } else if (!strcasecmp(argv[j], "keys") && moreargs) {
                return 0;
            }
        }
    } else if (argc > 4 && !strcasecmp(argv[0], "sentinel")) {
        if (!strcasecmp(argv[1], "config") && !strcasecmp(argv[2], "set") && (!strcasecmp(argv[3], "sentinel-pass") || !strcasecmp(argv[3], "sentinel-user"))) {
            return 1;
        }
        if (!strcasecmp(argv[1], "set") && (!strcasecmp(argv[3], "auth-pass") || !strcasecmp(argv[3], "auth-user"))) {
            return 1;
        }
    }
    return 0;
}
static void repl (){
    hisds historyfile = ((void *)0);
    int history = 0;
    char *line;
    int argc;
    hisds *argv;
    if ((!config.eval_ldb) && isatty(fileno(stdin))) {
        cliInitHelp();
    }
    config.interactive = 1;
    if (getenv("FAKETTY_WITH_PROMPT") != ((void *)0) || isatty(fileno(stdin))) {
        historyfile = getDotfilePath("REDISCLI_HISTFILE", ".rediscli_history");
        history = 1;
        cliLoadPreferences();
    }
    ;
    while (1)
        {
            line = linenoise(context ? config.prompt : "not connected> ");
            if (line == ((void *)0)) {
                if (config.pubsub_mode) {
                    config.pubsub_mode = 0;
                    if (cliConnect((1 << 0)) == 0)
                        continue;
                }
                break;
            } else if (line[0] != '\x00') {
                long repeat = 1;
                int skipargs = 0;
                char *endptr = ((void *)0);
                argv = cliSplitArgs(line, &argc);
                if (argv == ((void *)0)) {
                    ;
                    continue;
                } else if (argc == 0) {
                    ;
                    continue;
                }
                (*__errno_location()) = 0;
                repeat = strtol(argv[0], &endptr, 10);
                if (argc > 1 && *endptr == '\x00') {
                    if ((*__errno_location()) == 34 || (*__errno_location()) == 22 || repeat <= 0) {
                        ;
                        continue;
                    }
                    skipargs = 1;
                } else {
                    repeat = 1;
                }
                int is_sensitive = isSensitiveCommand(argc - skipargs, argv + skipargs);
                if (strcasecmp(argv[0], "quit") == 0 || strcasecmp(argv[0], "exit") == 0) {
                    ;
                } else if (argv[0][0] == ':') {
                    cliSetPreferences(argv, argc, 1);
                    continue;
                } else if (strcasecmp(argv[0], "restart") == 0) {
                    if (config.eval) {
                        config.eval_ldb = 1;
                        config.output = 1;
                        return;
                    } else {
                        ;
                    }
                } else if (argc == 3 && !strcasecmp(argv[0], "connect")) {
                    ;
                    config.conn_info.hostip = hi_sdsnew(argv[1]);
                    config.conn_info.hostport = atoi(argv[2]);
                    cliConnect((1 << 0));
                } else if (argc == 1 && !strcasecmp(argv[0], "clear")) {
                    ;
                } else {
                    long long start_time = mstime(), elapsed;
                    issueCommandRepeat(argc - skipargs, argv + skipargs, repeat);
                    if (config.eval_ldb_end) {
                        config.eval_ldb_end = 0;
                        cliReadReply(0);
                        cliInitHelp();
                    }
                    elapsed = mstime() - start_time;
                }
                ;
            }
            if (config.pubsub_mode) {
                cliWaitForMessagesOrStdin();
            }
            ;
        }
    ;
}
static int noninteractive (int argc, char **argv){
    int retval = 0;
    hisds *sds_args = getSdsArrayFromArgv(argc, argv, config.quoted_input);
    if (!sds_args) {
        ;
        return 1;
    }
    if (config.stdin_lastarg) {
        sds_args = hi_sds_realloc(sds_args, (argc + 1) * sizeof(hisds));
        sds_args[argc] = readArgFromStdin();
        argc++;
    } else if (config.stdin_tag_arg) {
        int i = 0, tag_match = 0;
        for (; i < argc; i++) {
            if (strcmp(config.stdin_tag_name, sds_args[i]) != 0)
                continue;
            tag_match = 1;
            sds_args[i] = readArgFromStdin();
            break;
        }
        if (!tag_match) {
            ;
            return 1;
        }
    }
    retval = issueCommand(argc, sds_args);
    while (config.pubsub_mode)
        {
            if (cliReadReply(0) != 0) {
                ;
            }
            ;
        }
    return retval == 0 ? 0 : 1;
}
static int evalMode (int argc, char **argv){
    hisds script = ((void *)0);
    FILE *fp;
    char buf[1024];
    size_t nread;
    char **argv2;
    int j, got_comma, keys;
    int retval = 0;
    while (1)
        {
            ;
            script = hi_sdsempty();
            got_comma = 0;
            keys = 0;
            fp = fopen(config.eval, "r");
            if (!fp) {
                ;
            }
            while ((nread = fread(buf, 1, sizeof (buf), fp)) != 0)
                {
                    script = hi_sdscatlen(script, buf, nread);
                }
            ;
            if (config.eval_ldb) {
                redisReply *reply = redisCommand(context, config.eval_ldb_sync ? "SCRIPT DEBUG sync" : "SCRIPT DEBUG yes");
            }
            argv2 = zmalloc(sizeof(hisds) * (argc + 3));
            argv2[0] = hi_sdsnew("EVAL");
            argv2[1] = script;
            for (j = 0; j < argc; j++) {
                if (!got_comma && argv[j][0] == ',' && argv[j][1] == 0) {
                    got_comma = 1;
                    continue;
                }
                argv2[j + 3 - got_comma] = hi_sdsnew(argv[j]);
                if (!got_comma)
                    keys++;
            }
            argv2[2] = hi_sdscatprintf(hi_sdsempty(), "%d", keys);
            int eval_ldb = config.eval_ldb;
            retval = issueCommand(argc + 3 - got_comma, argv2);
            if (eval_ldb) {
                if (!config.eval_ldb) {
                    ;
                    cliReadReply(0);
                    break;
                } else {
                    strncpy(config.prompt, "lua debugger> ", sizeof (config.prompt));
                    repl();
                    cliConnect((1 << 0));
                }
            } else {
                ;
            }
        }
    return retval == 0 ? 0 : 1;
}
static int createClusterManagerCommand (char *cmdname, int argc, char **argv){
    clusterManagerCommand *cmd = &config.cluster_manager_command;
    cmd->name = cmdname;
    cmd->argc = argc;
    cmd->argv = argc ? argv : ((void *)0);
    if (isColorTerm())
        cmd->flags |= 1 << 8;
    if (config.stdin_lastarg) {
        char **new_argv = zmalloc(sizeof(char *) * (cmd->argc + 1));
        cmd->stdin_arg = readArgFromStdin();
        new_argv[cmd->argc++] = cmd->stdin_arg;
        cmd->argv = new_argv;
    } else if (config.stdin_tag_arg) {
        int i = 0, tag_match = 0;
        cmd->stdin_arg = readArgFromStdin();
        for (; i < argc; i++) {
            if (strcmp(argv[i], config.stdin_tag_name) != 0)
                continue;
            tag_match = 1;
            cmd->argv[i] = (char *)cmd->stdin_arg;
            break;
        }
        if (!tag_match) {
            ;
            return 1;
        }
    }
    return 0;
}
static clusterManagerCommandProc * validateClusterManagerCommand (){
    int i, commands_count = sizeof (clusterManagerCommands) / sizeof(clusterManagerCommandDef);
    clusterManagerCommandProc *proc = ((void *)0);
    char *cmdname = config.cluster_manager_command.name;
    int argc = config.cluster_manager_command.argc;
    for (i = 0; i < commands_count; i++) {
        clusterManagerCommandDef cmddef = clusterManagerCommands[i];
        if (!strcmp(cmddef.name, cmdname)) {
            if ((cmddef.arity > 0 && argc != cmddef.arity) || (cmddef.arity < 0 && argc < (cmddef.arity * -1))) {
                ;
                return ((void *)0);
            }
            proc = cmddef.proc;
        }
    }
    ;
    return proc;
}
static int parseClusterNodeAddress (char *addr, char **ip_ptr, int *port_ptr, int *bus_port_ptr){
    char *c = strrchr(addr, '@');
    if (c != ((void *)0)) {
        *c = '\x00';
        if (bus_port_ptr != ((void *)0))
            *bus_port_ptr = atoi(c + 1);
    }
    c = strrchr(addr, ':');
    if (c != ((void *)0)) {
        *c = '\x00';
        *ip_ptr = addr;
        *port_ptr = atoi(++c);
    } else
        return 0;
    return 1;
}
static int getClusterHostFromCmdArgs (int argc, char **argv, char **ip_ptr, int *port_ptr){
    int port = 0;
    char *ip = ((void *)0);
    if (argc == 1) {
        char *addr = argv[0];
        if (!parseClusterNodeAddress(addr, &ip, &port, ((void *)0)))
            return 0;
    } else {
        ip = argv[0];
        port = atoi(argv[1]);
    }
    if (!ip || !port) {
        return 0;
    } else {
        *ip_ptr = ip;
        *port_ptr = port;
    }
    return 1;
}
static void freeClusterManagerNode (clusterManagerNode *node){
    ;
    if (node->friends != ((void *)0)) {
        listIter li;
        listNode *ln;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *fn = ln->value;
                freeClusterManagerNode(fn);
            }
        ;
        node->friends = ((void *)0);
    }
    ;
    int i;
    if (node->migrating != ((void *)0)) {
        for (i = 0; i < node->migrating_count; i++)
            hi_sdsfree(node->migrating[i]);
    }
    if (node->importing != ((void *)0)) {
        for (i = 0; i < node->importing_count; i++)
            hi_sdsfree(node->importing[i]);
    }
    if (node->flags_str != ((void *)0)) {
        ;
        node->flags_str = ((void *)0);
    }
    ;
}
static void freeClusterManager (){
    listIter li;
    listNode *ln;
    if (cluster_manager.nodes != ((void *)0)) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                freeClusterManagerNode(n);
            }
        ;
    }
    if (cluster_manager.errors != ((void *)0)) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                hisds err = ln->value;
            }
        ;
    }
    ;
}
static clusterManagerNode * clusterManagerNewNode (char *ip, int port, int bus_port){
    clusterManagerNode *node = zmalloc(sizeof (*node));
    node->context = ((void *)0);
    node->name = ((void *)0);
    node->ip = ip;
    node->port = port;
    node->bus_port = bus_port ? bus_port : port + 10000;
    node->current_epoch = 0;
    node->ping_sent = 0;
    node->ping_recv = 0;
    node->flags = 0;
    node->flags_str = ((void *)0);
    node->replicate = ((void *)0);
    node->dirty = 0;
    node->friends = ((void *)0);
    node->migrating = ((void *)0);
    node->importing = ((void *)0);
    node->migrating_count = 0;
    node->importing_count = 0;
    node->replicas_count = 0;
    node->weight = 1.F;
    node->balance = 0;
    clusterManagerNodeResetSlots(node);
    return node;
}
static hisds clusterManagerGetNodeRDBFilename (clusterManagerNode *node){
    ((void)sizeof ((config.cluster_manager_command.backup_dir) ? 1 : 0) , __extension__ ({
        if (config.cluster_manager_command.backup_dir)
            ;
        else
            __assert_fail("config.cluster_manager_command.backup_dir", "redis-cli_InstSlice.c", 3615, __extension__ __PRETTY_FUNCTION__);
    }));
    hisds filename = hi_sdsnew(config.cluster_manager_command.backup_dir);
    if (filename[hi_sdslen(filename) - 1] != '/')
        filename = hi_sdscat(filename, "/");
    filename = hi_sdscatprintf(filename, "redis-node-%s-%d-%s.rdb", node->ip, node->port, node->name);
    return filename;
}
static int clusterManagerCheckRedisReply (clusterManagerNode *n, redisReply *r, char **err){
    int is_err = 0;
    if (!r || (is_err = (r->type == 6))) {
        if (is_err) {
            if (err != ((void *)0)) {
                *err = zmalloc((r->len + 1) * sizeof(char));
                redis_strlcpy(*err, r->str, (r->len + 1));
            } else
                clusterManagerLog(3, "Node %s:%d replied with error:\n%s\n", (n)->ip, (n)->port, (r->str));
        }
        return 0;
    }
    return 1;
}
static int clusterManagerStartTransaction (clusterManagerNode *node){
    redisReply *reply = (redisCommand((node)->context, "MULTI"));
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    return success;
}
static int clusterManagerExecTransaction (clusterManagerNode *node, clusterManagerOnReplyError onerror){
    redisReply *reply = (redisCommand((node)->context, "EXEC"));
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    if (success) {
        if (reply->type != 2) {
            success = 0;
            goto cleanup;
        }
        size_t i;
        for (i = 0; i < reply->elements; i++) {
            redisReply *r = reply->element[i];
            char *err = ((void *)0);
            success = clusterManagerCheckRedisReply(node, r, &err);
            if (!success && onerror)
                success = onerror(r, node, i);
            if (!success)
                break;
        }
    }
  cleanup:
    ;
    return success;
}
static int clusterManagerNodeConnect (clusterManagerNode *node){
    ;
    node->context = redisConnectWrapper(node->ip, node->port, config.connect_timeout);
    if (!node->context->err && config.tls) {
        const char *err = ((void *)0);
        if (cliSecureConnection(node->context, config.sslconfig, &err) == -1 && err) {
            ;
            node->context = ((void *)0);
            return 0;
        }
    }
    if (node->context->err) {
        ;
        node->context = ((void *)0);
        return 0;
    }
    ;
    if (config.conn_info.auth) {
        redisReply *reply;
        if (config.conn_info.user == ((void *)0)) {
            reply = redisCommand(node->context, "AUTH %s", config.conn_info.auth);
        } else
            reply = redisCommand(node->context, "AUTH %s %s", config.conn_info.user, config.conn_info.auth);
        int ok = clusterManagerCheckRedisReply(node, reply, ((void *)0));
        if (!ok)
            return 0;
    }
    return 1;
}
static clusterManagerNode * clusterManagerNodeByName (const char *name){
    if (cluster_manager.nodes == ((void *)0))
        return ((void *)0);
    clusterManagerNode *found = ((void *)0);
    hisds lcname = hi_sdsempty();
    lcname = hi_sdscpy(lcname, name);
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->name && !hi_sdscmp(n->name, lcname)) {
                found = n;
                break;
            }
        }
    ;
    return found;
}
static clusterManagerNode * clusterManagerNodeByAbbreviatedName (const char *name){
    if (cluster_manager.nodes == ((void *)0))
        return ((void *)0);
    clusterManagerNode *found = ((void *)0);
    hisds lcname = hi_sdsempty();
    lcname = hi_sdscpy(lcname, name);
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->name && strstr(n->name, lcname) == n->name) {
                found = n;
                break;
            }
        }
    ;
    return found;
}
static void clusterManagerNodeResetSlots (clusterManagerNode *node){
    ;
    node->slots_count = 0;
}
static redisReply * clusterManagerGetNodeRedisInfo (clusterManagerNode *node, char **err){
    redisReply *info = (redisCommand((node)->context, "INFO"));
    if (err != ((void *)0))
        *err = ((void *)0);
    if (info == ((void *)0))
        return ((void *)0);
    if (info->type == 6) {
        if (err != ((void *)0)) {
            *err = zmalloc((info->len + 1) * sizeof(char));
        }
        ;
        return ((void *)0);
    }
    return info;
}
static int clusterManagerNodeIsCluster (clusterManagerNode *node, char **err){
    redisReply *info = clusterManagerGetNodeRedisInfo(node, err);
    if (info == ((void *)0))
        return 0;
    int is_cluster = (int)getLongInfoField(info->str, "cluster_enabled");
    return is_cluster;
}
static int clusterManagerNodeIsEmpty (clusterManagerNode *node, char **err){
    redisReply *info = clusterManagerGetNodeRedisInfo(node, err);
    int is_empty = 1;
    if (info == ((void *)0))
        return 0;
    if (strstr(info->str, "db0:") != ((void *)0)) {
        is_empty = 0;
        goto result;
    }
    ;
    info = (redisCommand((node)->context, "CLUSTER INFO"));
    if (err != ((void *)0))
        *err = ((void *)0);
    if (!clusterManagerCheckRedisReply(node, info, err)) {
        is_empty = 0;
        goto result;
    }
    long known_nodes = getLongInfoField(info->str, "cluster_known_nodes");
    is_empty = (known_nodes == 1);
  result:
    ;
    return is_empty;
}
static int clusterManagerGetAntiAffinityScore (clusterManagerNodeArray *ipnodes, int ip_count, clusterManagerNode ***offending, int *offending_len){
    int score = 0, i, j;
    int node_len = cluster_manager.nodes->len;
    clusterManagerNode **offending_p = ((void *)0);
    if (offending != ((void *)0)) {
        *offending = zcalloc(node_len * sizeof(clusterManagerNode *));
        offending_p = *offending;
    }
    for (i = 0; i < ip_count; i++) {
        clusterManagerNodeArray *node_array = &(ipnodes[i]);
        dict *related = dictCreate(&clusterManagerDictType);
        char *ip = ((void *)0);
        for (j = 0; j < node_array->len; j++) {
            clusterManagerNode *node = node_array->nodes[j];
            if (node == ((void *)0))
                continue;
            if (!ip)
                ip = node->ip;
            hisds types;
            hisds key = (!node->replicate ? node->name : node->replicate);
            ((void)sizeof ((key != ((void *)0)) ? 1 : 0) , __extension__ ({
                if (key != ((void *)0))
                    ;
                else
                    __assert_fail("key != NULL", "redis-cli_InstSlice.c", 3873, __extension__ __PRETTY_FUNCTION__);
            }));
            dictEntry *entry = dictFind(related, key);
            if (entry) {
                types = hi_sdsdup((hisds)dictGetVal(entry));
            } else
                types = hi_sdsempty();
            if (node->replicate) {
                types = hi_sdscat(types, "s");
            } else {
                hisds s = hi_sdscatsds(hi_sdsnew("m"), types);
                types = s;
            }
            ;
        }
        dictIterator iter;
        dictEntry *entry;
        while ((entry = dictNext(&iter)) != ((void *)0))
            {
                hisds types = (hisds)dictGetVal(entry);
                hisds name = (hisds)dictGetKey(entry);
                int typeslen = hi_sdslen(types);
                if (typeslen < 2)
                    continue;
                if (types[0] == 'm') {
                    score += (10000 * (typeslen - 1));
                } else
                    score += (1 * typeslen);
                if (offending == ((void *)0))
                    continue;
                listIter li;
                listNode *ln;
                while ((ln = listNext(&li)) != ((void *)0))
                    {
                        clusterManagerNode *n = ln->value;
                        if (n->replicate == ((void *)0))
                            continue;
                        if (!strcmp(n->replicate, name) && !strcmp(n->ip, ip)) {
                            *(offending_p++) = n;
                            if (offending_len != ((void *)0))
                                (*offending_len)++;
                            break;
                        }
                    }
            }
        ;
    }
    return score;
}
static void clusterManagerOptimizeAntiAffinity (clusterManagerNodeArray *ipnodes, int ip_count){
    clusterManagerNode **offenders = ((void *)0);
    int score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
    if (score == 0)
        goto cleanup;
    int node_len = cluster_manager.nodes->len;
    int maxiter = 500 * node_len;
    while (maxiter > 0)
        {
            int offending_len = 0;
            if (offenders != ((void *)0)) {
                ;
                offenders = ((void *)0);
            }
            score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, &offenders, &offending_len);
            if (score == 0 || offending_len == 0)
                break;
            int rand_idx = rand() % offending_len;
            clusterManagerNode *first = offenders[rand_idx], *second = ((void *)0);
            clusterManagerNode **other_replicas = zcalloc((node_len - 1) * sizeof (*other_replicas));
            int other_replicas_count = 0;
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (n != first && n->replicate != ((void *)0))
                        other_replicas[other_replicas_count++] = n;
                }
            if (other_replicas_count == 0) {
                ;
                break;
            }
            rand_idx = rand() % other_replicas_count;
            second = other_replicas[rand_idx];
            char *first_master = first->replicate, *second_master = second->replicate;
            first->replicate = second_master , first->dirty = 1;
            second->replicate = first_master , second->dirty = 1;
            int new_score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
            if (new_score > score) {
                first->replicate = first_master;
                second->replicate = second_master;
            }
            ;
            maxiter--;
        }
    score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, ((void *)0), ((void *)0));
    char *msg;
    int perfect = (score == 0);
    int log_level = (perfect ? 4 : 2);
  cleanup:
    ;
}
static hisds clusterManagerNodeFlagString (clusterManagerNode *node){
    hisds flags = hi_sdsempty();
    if (!node->flags_str)
        return flags;
    int empty = 1;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            hisds flag = ln->value;
            if (strcmp(flag, "myself") == 0)
                continue;
            if (!empty)
                flags = hi_sdscat(flags, ",");
            flags = hi_sdscatfmt(flags, "%S", flag);
            empty = 0;
        }
    return flags;
}
static hisds clusterManagerNodeSlotsString (clusterManagerNode *node){
    hisds slots = hi_sdsempty();
    int first_range_idx = -1, last_slot_idx = -1, i;
    for (i = 0; i < 16384; i++) {
        int has_slot = node->slots[i];
        if (has_slot) {
            if (first_range_idx == -1) {
                if (hi_sdslen(slots))
                    slots = hi_sdscat(slots, ",");
                first_range_idx = i;
                slots = hi_sdscatfmt(slots, "[%u", i);
            }
            last_slot_idx = i;
        } else {
            if (last_slot_idx >= 0) {
                if (first_range_idx == last_slot_idx) {
                    slots = hi_sdscat(slots, "]");
                } else
                    slots = hi_sdscatfmt(slots, "-%u]", last_slot_idx);
            }
            last_slot_idx = -1;
            first_range_idx = -1;
        }
    }
    if (last_slot_idx >= 0) {
        if (first_range_idx == last_slot_idx) {
            slots = hi_sdscat(slots, "]");
        } else
            slots = hi_sdscatfmt(slots, "-%u]", last_slot_idx);
    }
    return slots;
}
static hisds clusterManagerNodeGetJSON (clusterManagerNode *node, unsigned long error_count){
    hisds json = hi_sdsempty();
    hisds replicate = hi_sdsempty();
    if (node->replicate) {
        replicate = hi_sdscatprintf(replicate, "\"%s\"", node->replicate);
    } else
        replicate = hi_sdscat(replicate, "null");
    hisds slots = clusterManagerNodeSlotsString(node);
    hisds flags = clusterManagerNodeFlagString(node);
    char *p = slots;
    while ((p = strchr(p, '-')) != ((void *)0))
        *(p++) = ',';
    json = hi_sdscatprintf(json, "  {\n    \"name\": \"%s\",\n    \"host\": \"%s\",\n    \"port\": %d,\n    \"replicate\": %s,\n    \"slots\": [%s],\n    \"slots_count\": %d,\n    \"flags\": \"%s\",\n    \"current_epoch\": %llu", node->name, node->ip, node->port, replicate, slots, node->slots_count, flags, (unsigned long long)node->current_epoch);
    if (error_count > 0) {
        json = hi_sdscatprintf(json, ",\n    \"cluster_errors\": %lu", error_count);
    }
    if (node->migrating_count > 0 && node->migrating != ((void *)0)) {
        int i = 0;
        hisds migrating = hi_sdsempty();
        for (; i < node->migrating_count; i += 2) {
            hisds slot = node->migrating[i];
            hisds dest = node->migrating[i + 1];
            if (slot && dest) {
                if (hi_sdslen(migrating) > 0)
                    migrating = hi_sdscat(migrating, ",");
                migrating = hi_sdscatfmt(migrating, "\"%S\": \"%S\"", slot, dest);
            }
        }
        if (hi_sdslen(migrating) > 0)
            json = hi_sdscatfmt(json, ",\n    \"migrating\": {%S}", migrating);
    }
    if (node->importing_count > 0 && node->importing != ((void *)0)) {
        int i = 0;
        hisds importing = hi_sdsempty();
        for (; i < node->importing_count; i += 2) {
            hisds slot = node->importing[i];
            hisds from = node->importing[i + 1];
            if (slot && from) {
                if (hi_sdslen(importing) > 0)
                    importing = hi_sdscat(importing, ",");
                importing = hi_sdscatfmt(importing, "\"%S\": \"%S\"", slot, from);
            }
        }
        if (hi_sdslen(importing) > 0)
            json = hi_sdscatfmt(json, ",\n    \"importing\": {%S}", importing);
    }
    json = hi_sdscat(json, "\n  }");
    return json;
}
static unsigned int clusterManagerKeyHashSlot (char *key, int keylen){
    int s, e;
    for (s = 0; s < keylen; s++)
        if (key[s] == '{')
            break;
    if (s == keylen)
        return crc16(key, keylen) & 16383;
    for (e = s + 1; e < keylen; e++)
        if (key[e] == '}')
            break;
    if (e == keylen || e == s + 1)
        return crc16(key, keylen) & 16383;
    return crc16(key + s + 1, e - s - 1) & 16383;
}
static hisds clusterManagerNodeInfo (clusterManagerNode *node, int indent){
    hisds info = hi_sdsempty();
    hisds spaces = hi_sdsempty();
    int i;
    for (i = 0; i < indent; i++)
        spaces = hi_sdscat(spaces, " ");
    if (indent)
        info = hi_sdscat(info, spaces);
    int is_master = !(node->flags & 1 << 1);
    char *role = (is_master ? "M" : "S");
    hisds slots = ((void *)0);
    if (node->dirty && node->replicate != ((void *)0)) {
        info = hi_sdscatfmt(info, "S: %S %s:%u", node->name, node->ip, node->port);
    } else {
        slots = clusterManagerNodeSlotsString(node);
        hisds flags = clusterManagerNodeFlagString(node);
        info = hi_sdscatfmt(info, "%s: %S %s:%u\n%s   slots:%S (%u slots) %S", role, node->name, node->ip, node->port, spaces, slots, node->slots_count, flags);
    }
    if (node->replicate != ((void *)0)) {
        info = hi_sdscatfmt(info, "\n%s   replicates %S", spaces, node->replicate);
    } else if (node->replicas_count)
        info = hi_sdscatfmt(info, "\n%s   %U additional replica(s)", spaces, node->replicas_count);
    return info;
}
static void clusterManagerShowNodes (){
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *node = ln->value;
            hisds info = clusterManagerNodeInfo(node, 0);
        }
}
static int clusterManagerAddSlots (clusterManagerNode *node, char **err){
    redisReply *reply = ((void *)0);
    void *_reply = ((void *)0);
    int success = 1;
    int argc = node->slots_count + 2;
    hisds *argv = zmalloc(argc * sizeof (*argv));
    size_t *argvlen = zmalloc(argc * sizeof (*argvlen));
    argv[0] = "CLUSTER";
    argv[1] = "ADDSLOTS";
    argvlen[0] = 7;
    argvlen[1] = 8;
    *err = ((void *)0);
    int i, argv_idx = 2;
    for (i = 0; i < 16384; i++) {
        if (argv_idx >= argc)
            break;
        if (node->slots[i]) {
            argv[argv_idx] = hi_sdsfromlonglong((long long)i);
            argvlen[argv_idx] = hi_sdslen(argv[argv_idx]);
            argv_idx++;
        }
    }
    if (argv_idx == 2) {
        success = 0;
        goto cleanup;
    }
    ;
    if (redisGetReply(node->context, &_reply) != 0) {
        success = 0;
        goto cleanup;
    }
    reply = (redisReply *)_reply;
    success = clusterManagerCheckRedisReply(node, reply, err);
  cleanup:
    ;
    return success;
}
static clusterManagerNode * clusterManagerGetSlotOwner (clusterManagerNode *n, int slot, char **err){
    ((void)sizeof ((slot >= 0 && slot < 16384) ? 1 : 0) , __extension__ ({
        if (slot >= 0 && slot < 16384)
            ;
        else
            __assert_fail("slot >= 0 && slot < CLUSTER_MANAGER_SLOTS", "redis-cli_InstSlice.c", 4226, __extension__ __PRETTY_FUNCTION__);
    }));
    clusterManagerNode *owner = ((void *)0);
    redisReply *reply = (redisCommand((n)->context, "CLUSTER SLOTS"));
    if (clusterManagerCheckRedisReply(n, reply, err)) {
        ((void)sizeof ((reply->type == 2) ? 1 : 0) , __extension__ ({
            if (reply->type == 2)
                ;
            else
                __assert_fail("reply->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 4230, __extension__ __PRETTY_FUNCTION__);
        }));
        size_t i;
        for (i = 0; i < reply->elements; i++) {
            redisReply *r = reply->element[i];
            ((void)sizeof ((r->type == 2 && r->elements >= 3) ? 1 : 0) , __extension__ ({
                if (r->type == 2 && r->elements >= 3)
                    ;
                else
                    __assert_fail("r->type == REDIS_REPLY_ARRAY && r->elements >= 3", "redis-cli_InstSlice.c", 4234, __extension__ __PRETTY_FUNCTION__);
            }));
            int from, to;
            from = r->element[0]->integer;
            to = r->element[1]->integer;
            if (slot < from || slot > to)
                continue;
            redisReply *nr = r->element[2];
            ((void)sizeof ((nr->type == 2 && nr->elements >= 2) ? 1 : 0) , __extension__ ({
                if (nr->type == 2 && nr->elements >= 2)
                    ;
                else
                    __assert_fail("nr->type == REDIS_REPLY_ARRAY && nr->elements >= 2", "redis-cli_InstSlice.c", 4241, __extension__ __PRETTY_FUNCTION__);
            }));
            char *name = ((void *)0);
            if (nr->elements >= 3)
                name = nr->element[2]->str;
            if (name != ((void *)0)) {
                owner = clusterManagerNodeByName(name);
            } else {
                char *ip = nr->element[0]->str;
                ((void)sizeof ((ip != ((void *)0)) ? 1 : 0) , __extension__ ({
                    if (ip != ((void *)0))
                        ;
                    else
                        __assert_fail("ip != NULL", "redis-cli_InstSlice.c", 4249, __extension__ __PRETTY_FUNCTION__);
                }));
                int port = (int)nr->element[1]->integer;
                listIter li;
                listNode *ln;
                while ((ln = listNext(&li)) != ((void *)0))
                    {
                        clusterManagerNode *nd = ln->value;
                        if (strcmp(nd->ip, ip) == 0 && port == nd->port) {
                            owner = nd;
                            break;
                        }
                    }
            }
            if (owner)
                break;
        }
    }
    ;
    return owner;
}
static int clusterManagerSetSlot (clusterManagerNode *node1, clusterManagerNode *node2, int slot, const char *status, char **err){
    redisReply *reply = (redisCommand((node1)->context, "CLUSTER SETSLOT %d %s %s", slot, status, (char *)node2->name));
    if (err != ((void *)0))
        *err = ((void *)0);
    if (!reply) {
        if (err)
            *err = zstrdup("CLUSTER SETSLOT failed to run");
        return 0;
    }
    int success = 1;
    if (reply->type == 6) {
        success = 0;
        if (err != ((void *)0)) {
            *err = zmalloc((reply->len + 1) * sizeof(char));
            redis_strlcpy(*err, reply->str, (reply->len + 1));
        } else
            clusterManagerLog(3, "Node %s:%d replied with error:\n%s\n", (node1)->ip, (node1)->port, (reply->str));
        goto cleanup;
    }
  cleanup:
    ;
    return success;
}
static int clusterManagerClearSlotStatus (clusterManagerNode *node, int slot){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER SETSLOT %d %s", slot, "STABLE"));
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    return success;
}
static int clusterManagerDelSlot (clusterManagerNode *node, int slot, int ignore_unassigned_err){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER DELSLOTS %d", slot));
    char *err = ((void *)0);
    int success = clusterManagerCheckRedisReply(node, reply, &err);
    if (!success && reply && reply->type == 6 && ignore_unassigned_err) {
        char *get_owner_err = ((void *)0);
        clusterManagerNode *assigned_to = clusterManagerGetSlotOwner(node, slot, &get_owner_err);
        if (!assigned_to) {
            if (get_owner_err == ((void *)0)) {
                success = 1;
            } else {
                ;
            }
        }
    }
    ;
    return success;
}
static int clusterManagerAddSlot (clusterManagerNode *node, int slot){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER ADDSLOTS %d", slot));
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    return success;
}
static int clusterManagerCountKeysInSlot (clusterManagerNode *node, int slot){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER COUNTKEYSINSLOT %d", slot));
    int count = -1;
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    if (success && reply->type == 3)
        count = reply->integer;
    return count;
}
static int clusterManagerBumpEpoch (clusterManagerNode *node){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER BUMPEPOCH"));
    int success = clusterManagerCheckRedisReply(node, reply, ((void *)0));
    return success;
}
static int clusterManagerOnSetOwnerErr (redisReply *reply, clusterManagerNode *n, int bulk_idx){
    ;
    return (bulk_idx != 1);
}
static int clusterManagerSetSlotOwner (clusterManagerNode *owner, int slot, int do_clear){
    int success = clusterManagerStartTransaction(owner);
    if (!success)
        return 0;
    clusterManagerDelSlot(owner, slot, 1);
    clusterManagerAddSlot(owner, slot);
    if (do_clear)
        clusterManagerClearSlotStatus(owner, slot);
    clusterManagerBumpEpoch(owner);
    success = clusterManagerExecTransaction(owner, clusterManagerOnSetOwnerErr);
    return success;
}
static int clusterManagerCompareKeysValues (clusterManagerNode *n1, clusterManagerNode *n2, redisReply *keys_reply, list *diffs){
    size_t i, argc = keys_reply->elements + 2;
    static const char *hash_zero = "0000000000000000000000000000000000000000";
    char **argv = zcalloc(argc * sizeof(char *));
    size_t *argv_len = zcalloc(argc * sizeof(size_t));
    argv[0] = "DEBUG";
    argv_len[0] = 5;
    argv[1] = "DIGEST-VALUE";
    argv_len[1] = 12;
    for (i = 0; i < keys_reply->elements; i++) {
        redisReply *entry = keys_reply->element[i];
        int idx = i + 2;
        argv[idx] = entry->str;
        argv_len[idx] = entry->len;
    }
    int success = 0;
    void *_reply1 = ((void *)0), *_reply2 = ((void *)0);
    redisReply *r1 = ((void *)0), *r2 = ((void *)0);
    success = (redisGetReply(n1->context, &_reply1) == 0);
    if (!success)
        goto cleanup;
    r1 = (redisReply *)_reply1;
    success = (redisGetReply(n2->context, &_reply2) == 0);
    if (!success)
        goto cleanup;
    r2 = (redisReply *)_reply2;
    success = (r1->type != 6 && r2->type != 6);
    if (r1->type == 6) {
        ;
        success = 0;
    }
    if (r2->type == 6) {
        ;
        success = 0;
    }
    if (!success)
        goto cleanup;
    ((void)sizeof ((keys_reply->elements == r1->elements && keys_reply->elements == r2->elements) ? 1 : 0) , __extension__ ({
        if (keys_reply->elements == r1->elements && keys_reply->elements == r2->elements)
            ;
        else
            __assert_fail("keys_reply->elements == r1->elements && keys_reply->elements == r2->elements", "redis-cli_InstSlice.c", 4432, __extension__ __PRETTY_FUNCTION__);
    }));
    for (i = 0; i < keys_reply->elements; i++) {
        char *key = keys_reply->element[i]->str;
        char *hash1 = r1->element[i]->str;
        char *hash2 = r2->element[i]->str;
    }
  cleanup:
    ;
    return success;
}
static redisReply * clusterManagerMigrateKeysInReply (clusterManagerNode *source, clusterManagerNode *target, redisReply *reply, int replace, int timeout, char *dots){
    redisReply *migrate_reply = ((void *)0);
    char **argv = ((void *)0);
    size_t *argv_len = ((void *)0);
    int c = (replace ? 8 : 7);
    if (config.conn_info.auth)
        c += 2;
    if (config.conn_info.user)
        c += 1;
    size_t argc = c + reply->elements;
    size_t i, offset = 6;
    argv = zcalloc(argc * sizeof(char *));
    argv_len = zcalloc(argc * sizeof(size_t));
    char portstr[255];
    char timeoutstr[255];
    argv[0] = "MIGRATE";
    argv_len[0] = 7;
    argv[1] = target->ip;
    argv_len[1] = strlen(target->ip);
    argv[2] = portstr;
    argv_len[2] = strlen(portstr);
    argv[3] = "";
    argv_len[3] = 0;
    argv[4] = "0";
    argv_len[4] = 1;
    argv[5] = timeoutstr;
    argv_len[5] = strlen(timeoutstr);
    if (replace) {
        argv[offset] = "REPLACE";
        argv_len[offset] = 7;
        offset++;
    }
    if (config.conn_info.auth) {
        if (config.conn_info.user) {
            argv[offset] = "AUTH2";
            argv_len[offset] = 5;
            offset++;
            argv[offset] = config.conn_info.user;
            argv_len[offset] = strlen(config.conn_info.user);
            offset++;
            argv[offset] = config.conn_info.auth;
            argv_len[offset] = strlen(config.conn_info.auth);
            offset++;
        } else {
            argv[offset] = "AUTH";
            argv_len[offset] = 4;
            offset++;
            argv[offset] = config.conn_info.auth;
            argv_len[offset] = strlen(config.conn_info.auth);
            offset++;
        }
    }
    argv[offset] = "KEYS";
    argv_len[offset] = 4;
    offset++;
    for (i = 0; i < reply->elements; i++) {
        redisReply *entry = reply->element[i];
        size_t idx = i + offset;
        ((void)sizeof ((entry->type == 1) ? 1 : 0) , __extension__ ({
            if (entry->type == 1)
                ;
            else
                __assert_fail("entry->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 4515, __extension__ __PRETTY_FUNCTION__);
        }));
        argv[idx] = (char *)hi_sdsnewlen(entry->str, entry->len);
        argv_len[idx] = entry->len;
        if (dots)
            dots[i] = '.';
    }
    if (dots)
        dots[reply->elements] = '\x00';
    void *_reply = ((void *)0);
    int success = (redisGetReply(source->context, &_reply) == 0);
    if (!success)
        goto cleanup;
    migrate_reply = (redisReply *)_reply;
  cleanup:
    ;
    return migrate_reply;
}
static int clusterManagerMigrateKeysInSlot (clusterManagerNode *source, clusterManagerNode *target, int slot, int timeout, int pipeline, int verbose, char **err){
    int success = 1;
    int do_fix = config.cluster_manager_command.flags & 1 << 0;
    int do_replace = config.cluster_manager_command.flags & 1 << 6;
    while (1)
        {
            char *dots = ((void *)0);
            redisReply *reply = ((void *)0), *migrate_reply = ((void *)0);
            reply = (redisCommand((source)->context, "CLUSTER GETKEYSINSLOT %d %d", slot, pipeline));
            success = (reply != ((void *)0));
            if (!success)
                return 0;
            if (reply->type == 6) {
                success = 0;
                if (err != ((void *)0)) {
                    *err = zmalloc((reply->len + 1) * sizeof(char));
                }
                goto next;
            }
            ((void)sizeof ((reply->type == 2) ? 1 : 0) , __extension__ ({
                if (reply->type == 2)
                    ;
                else
                    __assert_fail("reply->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 4563, __extension__ __PRETTY_FUNCTION__);
            }));
            size_t count = reply->elements;
            if (count == 0) {
                ;
                break;
            }
            if (verbose)
                dots = zmalloc((count + 1) * sizeof(char));
            migrate_reply = clusterManagerMigrateKeysInReply(source, target, reply, 0, timeout, dots);
            if (migrate_reply == ((void *)0))
                goto next;
            if (migrate_reply->type == 6) {
                int is_busy = strstr(migrate_reply->str, "BUSYKEY") != ((void *)0);
                int not_served = 0;
                if (!is_busy) {
                    char *get_owner_err = ((void *)0);
                    clusterManagerNode *served_by = clusterManagerGetSlotOwner(source, slot, &get_owner_err);
                    if (!served_by) {
                        if (get_owner_err == ((void *)0)) {
                            not_served = 1;
                        } else {
                            ;
                        }
                    }
                }
                if (is_busy || not_served) {
                    if (do_fix && not_served) {
                        ;
                        clusterManagerSetSlot(source, target, slot, "node", ((void *)0));
                    }
                    if (is_busy) {
                        ;
                        if (!do_replace) {
                            ;
                            list *diffs = listCreate();
                            success = clusterManagerCompareKeysValues(source, target, reply, diffs);
                            if (!success) {
                                ;
                                goto next;
                            }
                            if (((diffs)->len) > 0) {
                                success = 0;
                                listIter dli;
                                listNode *dln;
                                while ((dln = listNext(&dli)) != ((void *)0))
                                    {
                                        char *k = dln->value;
                                    }
                                ;
                                goto next;
                            }
                            ;
                        }
                        ;
                    }
                    ;
                    migrate_reply = clusterManagerMigrateKeysInReply(source, target, reply, is_busy, timeout, ((void *)0));
                    success = (migrate_reply != ((void *)0) && migrate_reply->type != 6);
                } else
                    success = 0;
                if (!success) {
                    if (migrate_reply != ((void *)0)) {
                        if (err) {
                            *err = zmalloc((migrate_reply->len + 1) * sizeof(char));
                        }
                        ;
                    }
                    goto next;
                }
            }
          next:
            ;
            if (!success)
                break;
        }
    return success;
}
static int clusterManagerMoveSlot (clusterManagerNode *source, clusterManagerNode *target, int slot, int opts, char **err){
    if (err != ((void *)0))
        *err = ((void *)0);
    int pipeline = config.cluster_manager_command.pipeline, timeout = config.cluster_manager_command.timeout, print_dots = (opts & 1 << 7), option_cold = (opts & 1 << 1), success = 1;
    if (!option_cold) {
        success = clusterManagerSetSlot(target, source, slot, "importing", err);
        if (!success)
            return 0;
        success = clusterManagerSetSlot(source, target, slot, "migrating", err);
        if (!success)
            return 0;
    }
    success = clusterManagerMigrateKeysInSlot(source, target, slot, timeout, pipeline, print_dots, err);
    if (!success)
        return 0;
    if (!option_cold) {
        success = clusterManagerSetSlot(target, target, slot, "node", err);
        if (!success)
            return 0;
        success = clusterManagerSetSlot(source, target, slot, "node", err);
        const char *acceptable = "ERR Please use SETSLOT only with masters.";
        if (!success && err && !strncmp(*err, acceptable, strlen(acceptable))) {
            ;
            *err = ((void *)0);
        } else if (!success && err) {
            return 0;
        }
        listIter li;
        listNode *ln;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                if (n == target || n == source)
                    continue;
                if (n->flags & 1 << 1)
                    continue;
                success = clusterManagerSetSlot(n, target, slot, "node", err);
                if (!success)
                    return 0;
            }
    }
    if (opts & 1 << 2) {
        source->slots[slot] = 0;
        target->slots[slot] = 1;
    }
    return 1;
}
static int clusterManagerFlushNodeConfig (clusterManagerNode *node, char **err){
    if (!node->dirty)
        return 0;
    redisReply *reply = ((void *)0);
    int is_err = 0, success = 1;
    if (err != ((void *)0))
        *err = ((void *)0);
    if (node->replicate != ((void *)0)) {
        reply = (redisCommand((node)->context, "CLUSTER REPLICATE %s", node->replicate));
        if (reply == ((void *)0) || (is_err = (reply->type == 6))) {
            if (is_err && err != ((void *)0)) {
                *err = zmalloc((reply->len + 1) * sizeof(char));
            }
            success = 0;
            goto cleanup;
        }
    } else {
        int added = clusterManagerAddSlots(node, err);
        if (!added || *err != ((void *)0))
            success = 0;
    }
    node->dirty = 0;
  cleanup:
    ;
    return success;
}
static void clusterManagerWaitForClusterJoin (){
    ;
    int counter = 0, check_after = 20 + (int)(((cluster_manager.nodes)->len) * 0.150000006F);
    while (!clusterManagerIsConfigConsistent())
        {
            ;
            if (++counter > check_after) {
                dict *status = clusterManagerGetLinkStatus();
                if (status != ((void *)0) && ((status)->ht_used[0] + (status)->ht_used[1]) > 0) {
                    ;
                    dictIterator iter;
                    dictEntry *entry;
                    while ((entry = dictNext(&iter)) != ((void *)0))
                        {
                            hisds nodeaddr = (hisds)dictGetKey(entry);
                            char *node_ip = ((void *)0);
                            int node_port = 0, node_bus_port = 0;
                            list *from = (list *)dictGetVal(entry);
                            if (parseClusterNodeAddress(nodeaddr, &node_ip, &node_port, &node_bus_port) && node_bus_port) {
                                ;
                            } else {
                                ;
                            }
                            listIter li;
                            listNode *ln;
                            while ((ln = listNext(&li)) != ((void *)0))
                                {
                                    hisds from_addr = ln->value;
                                }
                            ;
                        }
                    ;
                }
                ;
                counter = 0;
            }
        }
    ;
}
static int clusterManagerNodeLoadInfo (clusterManagerNode *node, int opts, char **err){
    redisReply *reply = (redisCommand((node)->context, "CLUSTER NODES"));
    int success = 1;
    *err = ((void *)0);
    if (!clusterManagerCheckRedisReply(node, reply, err)) {
        success = 0;
        goto cleanup;
    }
    int getfriends = (opts & 1 << 0);
    char *lines = reply->str, *p, *line;
    while ((p = strstr(lines, "\n")) != ((void *)0))
        {
            *p = '\x00';
            line = lines;
            lines = p + 1;
            char *name = ((void *)0), *addr = ((void *)0), *flags = ((void *)0), *master_id = ((void *)0), *ping_sent = ((void *)0), *ping_recv = ((void *)0), *config_epoch = ((void *)0), *link_status = ((void *)0);
            int i = 0;
            while ((p = strchr(line, ' ')) != ((void *)0))
                {
                    *p = '\x00';
                    char *token = line;
                    line = p + 1;
                    switch (i++) {
                      case 0:
                        name = token;
                        break;
                      case 1:
                        addr = token;
                        break;
                      case 2:
                        flags = token;
                        break;
                      case 3:
                        master_id = token;
                        break;
                      case 4:
                        ping_sent = token;
                        break;
                      case 5:
                        ping_recv = token;
                        break;
                      case 6:
                        config_epoch = token;
                        break;
                      case 7:
                        link_status = token;
                        break;
                    }
                    if (i == 8)
                        break;
                }
            if (!flags) {
                success = 0;
                goto cleanup;
            }
            char *ip = ((void *)0);
            int port = 0, bus_port = 0;
            if (addr == ((void *)0) || !parseClusterNodeAddress(addr, &ip, &port, &bus_port)) {
                ;
                success = 0;
                goto cleanup;
            }
            int myself = (strstr(flags, "myself") != ((void *)0));
            clusterManagerNode *currentNode = ((void *)0);
            if (myself) {
                node->bus_port = bus_port;
                node->flags |= 1 << 0;
                currentNode = node;
                clusterManagerNodeResetSlots(node);
                if (i == 8) {
                    int remaining = strlen(line);
                    while (remaining > 0)
                        {
                            p = strchr(line, ' ');
                            if (p == ((void *)0))
                                p = line + remaining;
                            remaining -= (p - line);
                            char *slotsdef = line;
                            *p = '\x00';
                            if (remaining) {
                                line = p + 1;
                                remaining--;
                            } else
                                line = p;
                            char *dash = ((void *)0);
                            if (slotsdef[0] == '[') {
                                slotsdef++;
                                if ((p = strstr(slotsdef, "->-"))) {
                                    *p = '\x00';
                                    p += 3;
                                    char *closing_bracket = strchr(p, ']');
                                    if (closing_bracket)
                                        *closing_bracket = '\x00';
                                    hisds slot = hi_sdsnew(slotsdef);
                                    hisds dst = hi_sdsnew(p);
                                    node->migrating_count += 2;
                                    node->migrating = zrealloc(node->migrating, (node->migrating_count * sizeof(hisds)));
                                    node->migrating[node->migrating_count - 2] = slot;
                                    node->migrating[node->migrating_count - 1] = dst;
                                } else if ((p = strstr(slotsdef, "-<-"))) {
                                    *p = '\x00';
                                    p += 3;
                                    char *closing_bracket = strchr(p, ']');
                                    if (closing_bracket)
                                        *closing_bracket = '\x00';
                                    hisds slot = hi_sdsnew(slotsdef);
                                    hisds src = hi_sdsnew(p);
                                    node->importing_count += 2;
                                    node->importing = zrealloc(node->importing, (node->importing_count * sizeof(hisds)));
                                    node->importing[node->importing_count - 2] = slot;
                                    node->importing[node->importing_count - 1] = src;
                                }
                            } else if ((dash = strchr(slotsdef, '-')) != ((void *)0)) {
                                p = dash;
                                int start, stop;
                                *p = '\x00';
                                start = atoi(slotsdef);
                                stop = atoi(p + 1);
                                node->slots_count += (stop - (start - 1));
                                while (start <= stop)
                                    node->slots[start++] = 1;
                            } else if (p > slotsdef) {
                                node->slots[atoi(slotsdef)] = 1;
                                node->slots_count++;
                            }
                        }
                }
                node->dirty = 0;
            } else if (!getfriends) {
                if (!(node->flags & 1 << 0)) {
                    continue;
                } else {
                    ;
                }
                ;
            } else {
                currentNode = clusterManagerNewNode(hi_sdsnew(ip), port, bus_port);
                currentNode->flags |= 1 << 2;
                if (node->friends == ((void *)0))
                    node->friends = listCreate();
            }
            if (name != ((void *)0)) {
                ;
                currentNode->name = hi_sdsnew(name);
            }
            ;
            currentNode->flags_str = listCreate();
            int flag_len;
            while ((flag_len = strlen(flags)) > 0)
                {
                    hisds flag = ((void *)0);
                    char *fp = strchr(flags, ',');
                    if (fp) {
                        *fp = '\x00';
                        flag = hi_sdsnew(flags);
                        flags = fp + 1;
                    } else {
                        flag = hi_sdsnew(flags);
                        flags += flag_len;
                    }
                    if (strcmp(flag, "noaddr") == 0) {
                        currentNode->flags |= 1 << 3;
                    } else if (strcmp(flag, "disconnected") == 0) {
                        currentNode->flags |= 1 << 4;
                    } else if (strcmp(flag, "fail") == 0) {
                        currentNode->flags |= 1 << 5;
                    } else if (strcmp(flag, "slave") == 0) {
                        currentNode->flags |= 1 << 1;
                        if (master_id != ((void *)0)) {
                            ;
                            currentNode->replicate = hi_sdsnew(master_id);
                        }
                    }
                    ;
                }
            if (config_epoch != ((void *)0))
                currentNode->current_epoch = atoll(config_epoch);
            if (ping_sent != ((void *)0))
                currentNode->ping_sent = atoll(ping_sent);
            if (ping_recv != ((void *)0))
                currentNode->ping_recv = atoll(ping_recv);
            if (!getfriends && myself)
                break;
        }
  cleanup:
    ;
    return success;
}
static int clusterManagerLoadInfoFromNode (clusterManagerNode *node){
    if (node->context == ((void *)0) && !clusterManagerNodeConnect(node)) {
        freeClusterManagerNode(node);
        return 0;
    }
    char *e = ((void *)0);
    if (!clusterManagerNodeIsCluster(node, &e)) {
        ;
        freeClusterManagerNode(node);
        return 0;
    }
    e = ((void *)0);
    if (!clusterManagerNodeLoadInfo(node, 1 << 0, &e)) {
        freeClusterManagerNode(node);
        return 0;
    }
    listIter li;
    listNode *ln;
    if (cluster_manager.nodes != ((void *)0)) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            freeClusterManagerNode((clusterManagerNode *)ln->value);
    }
    cluster_manager.nodes = listCreate();
    if (node->friends != ((void *)0)) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *friend = ln->value;
                if (!friend->ip || !friend->port)
                    goto invalid_friend;
                if (!friend->context && !clusterManagerNodeConnect(friend))
                    goto invalid_friend;
                e = ((void *)0);
                if (clusterManagerNodeLoadInfo(friend, 0, &e)) {
                    if (friend->flags & (1 << 3 | 1 << 4 | 1 << 5)) {
                        goto invalid_friend;
                    }
                    ;
                } else {
                    ;
                }
                continue;
              invalid_friend:
                if (!(friend->flags & 1 << 1))
                    cluster_manager.unreachable_masters++;
                freeClusterManagerNode(friend);
            }
        ;
        node->friends = ((void *)0);
    }
    ;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->replicate != ((void *)0)) {
                clusterManagerNode *master = clusterManagerNodeByName(n->replicate);
                if (master == ((void *)0)) {
                    ;
                } else
                    master->replicas_count++;
            }
        }
    return 1;
}
static hisds clusterManagerGetConfigSignature (clusterManagerNode *node){
    hisds signature = ((void *)0);
    int node_count = 0, i = 0, name_len = 0;
    char **node_configs = ((void *)0);
    redisReply *reply = (redisCommand((node)->context, "CLUSTER NODES"));
    if (reply == ((void *)0) || reply->type == 6)
        goto cleanup;
    char *lines = reply->str, *p, *line;
    while ((p = strstr(lines, "\n")) != ((void *)0))
        {
            i = 0;
            *p = '\x00';
            line = lines;
            lines = p + 1;
            char *nodename = ((void *)0);
            int tot_size = 0;
            while ((p = strchr(line, ' ')) != ((void *)0))
                {
                    *p = '\x00';
                    char *token = line;
                    line = p + 1;
                    if (i == 0) {
                        nodename = token;
                        tot_size = (p - token);
                        name_len = tot_size++;
                    }
                    if (++i == 8)
                        break;
                }
            if (i != 8)
                continue;
            if (nodename == ((void *)0))
                continue;
            int remaining = strlen(line);
            if (remaining == 0)
                continue;
            char **slots = ((void *)0);
            int c = 0;
            while (remaining > 0)
                {
                    p = strchr(line, ' ');
                    if (p == ((void *)0))
                        p = line + remaining;
                    int size = (p - line);
                    remaining -= size;
                    tot_size += size;
                    char *slotsdef = line;
                    *p = '\x00';
                    if (remaining) {
                        line = p + 1;
                        remaining--;
                    } else
                        line = p;
                    if (slotsdef[0] != '[') {
                        c++;
                        slots = zrealloc(slots, (c * sizeof(char *)));
                        slots[c - 1] = slotsdef;
                    }
                }
            if (c > 0) {
                ;
                node_count++;
                node_configs = zrealloc(node_configs, (node_count * sizeof(char *)));
                tot_size += (sizeof(char) * (c - 1));
                char *cfg = zmalloc((sizeof(char) * tot_size) + 1);
                char *sp = cfg + name_len;
                *(sp++) = ':';
                for (i = 0; i < c; i++) {
                    if (i > 0)
                        *(sp++) = ',';
                    int slen = strlen(slots[i]);
                    sp += slen;
                }
                *(sp++) = '\x00';
                node_configs[node_count - 1] = cfg;
            }
            ;
        }
    if (node_count > 0) {
        signature = hi_sdsempty();
        for (i = 0; i < node_count; i++) {
            if (i > 0)
                signature = hi_sdscatprintf(signature, "%c", '|');
            signature = hi_sdscatfmt(signature, "%s", node_configs[i]);
        }
    }
  cleanup:
    ;
    return signature;
}
static int clusterManagerIsConfigConsistent (){
    if (cluster_manager.nodes == ((void *)0))
        return 0;
    int consistent = (((cluster_manager.nodes)->len) <= 1);
    if (consistent)
        return 1;
    hisds first_cfg = ((void *)0);
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *node = ln->value;
            hisds cfg = clusterManagerGetConfigSignature(node);
            if (cfg == ((void *)0)) {
                consistent = 0;
                break;
            }
            if (first_cfg == ((void *)0)) {
                first_cfg = cfg;
            } else {
                consistent = !hi_sdscmp(first_cfg, cfg);
                if (!consistent)
                    break;
            }
        }
    ;
    return consistent;
}
static list * clusterManagerGetDisconnectedLinks (clusterManagerNode *node){
    list *links = ((void *)0);
    redisReply *reply = (redisCommand((node)->context, "CLUSTER NODES"));
    if (!clusterManagerCheckRedisReply(node, reply, ((void *)0)))
        goto cleanup;
    links = listCreate();
    char *lines = reply->str, *p, *line;
    while ((p = strstr(lines, "\n")) != ((void *)0))
        {
            int i = 0;
            *p = '\x00';
            line = lines;
            lines = p + 1;
            char *nodename = ((void *)0), *addr = ((void *)0), *flags = ((void *)0), *link_status = ((void *)0);
            while ((p = strchr(line, ' ')) != ((void *)0))
                {
                    *p = '\x00';
                    char *token = line;
                    line = p + 1;
                    if (i == 0) {
                        nodename = token;
                    } else if (i == 1) {
                        addr = token;
                    } else if (i == 2) {
                        flags = token;
                    } else if (i == 7) {
                        link_status = token;
                    } else if (i == 8)
                        break;
                    i++;
                }
            if (i == 7)
                link_status = line;
            if (nodename == ((void *)0) || addr == ((void *)0) || flags == ((void *)0) || link_status == ((void *)0))
                continue;
            if (strstr(flags, "myself") != ((void *)0))
                continue;
            int disconnected = ((strstr(flags, "disconnected") != ((void *)0)) || (strstr(link_status, "disconnected")));
            int handshaking = (strstr(flags, "handshake") != ((void *)0));
            if (disconnected || handshaking) {
                clusterManagerLink *link = zmalloc(sizeof (*link));
                link->node_name = hi_sdsnew(nodename);
                link->node_addr = hi_sdsnew(addr);
                link->connected = 0;
                link->handshaking = handshaking;
            }
        }
  cleanup:
    ;
    return links;
}
static dict * clusterManagerGetLinkStatus (){
    if (cluster_manager.nodes == ((void *)0))
        return ((void *)0);
    dict *status = dictCreate(&clusterManagerLinkDictType);
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *node = ln->value;
            list *links = clusterManagerGetDisconnectedLinks(node);
            if (links) {
                listIter lli;
                listNode *lln;
                while ((lln = listNext(&lli)) != ((void *)0))
                    {
                        clusterManagerLink *link = lln->value;
                        list *from = ((void *)0);
                        dictEntry *entry = dictFind(status, link->node_addr);
                        if (entry) {
                            from = dictGetVal(entry);
                        } else {
                            from = listCreate();
                        }
                        hisds myaddr = hi_sdsempty();
                        myaddr = hi_sdscatfmt(myaddr, "%s:%u", node->ip, node->port);
                    }
                ;
            }
        }
    return status;
}
static void clusterManagerOnError (hisds err){
    if (cluster_manager.errors == ((void *)0))
        cluster_manager.errors = listCreate();
}
static int clusterManagerGetCoveredSlots (char *all_slots){
    if (cluster_manager.nodes == ((void *)0))
        return 0;
    listIter li;
    listNode *ln;
    int totslots = 0, i;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *node = ln->value;
            for (i = 0; i < 16384; i++) {
                if (node->slots[i] && !all_slots[i]) {
                    all_slots[i] = 1;
                    totslots++;
                }
            }
        }
    return totslots;
}
static void clusterManagerPrintSlotsList (list *slots){
    clusterManagerNode n = {0};
    listIter li;
    listNode *ln;
    hisds nodeslist = clusterManagerNodeSlotsString(&n);
}
static clusterManagerNode * clusterManagerGetNodeWithMostKeysInSlot (list *nodes, int slot, char **err){
    clusterManagerNode *node = ((void *)0);
    int numkeys = 0;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1 || n->replicate)
                continue;
            redisReply *r = (redisCommand((n)->context, "CLUSTER COUNTKEYSINSLOT %d", slot));
            int success = clusterManagerCheckRedisReply(n, r, err);
            if (success) {
                if (r->integer > numkeys || node == ((void *)0)) {
                    numkeys = r->integer;
                    node = n;
                }
            }
            ;
            if (!success) {
                ;
                node = ((void *)0);
                break;
            }
        }
    return node;
}
static clusterManagerNode * clusterManagerNodeWithLeastReplicas (){
    clusterManagerNode *node = ((void *)0);
    int lowest_count = 0;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1)
                continue;
            if (node == ((void *)0) || n->replicas_count < lowest_count) {
                node = n;
                lowest_count = n->replicas_count;
            }
        }
    return node;
}
static clusterManagerNode * clusterManagerNodeMasterRandom (){
    int master_count = 0;
    int idx;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1)
                continue;
            master_count++;
        }
    ((void)sizeof ((master_count > 0) ? 1 : 0) , __extension__ ({
        if (master_count > 0)
            ;
        else
            __assert_fail("master_count > 0", "redis-cli_InstSlice.c", 5400, __extension__ __PRETTY_FUNCTION__);
    }));
    idx = rand() % master_count;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1)
                continue;
            if (!idx--) {
                return n;
            }
        }
    ;
    return ((void *)0);
}
static int clusterManagerFixSlotsCoverage (char *all_slots){
    int force_fix = config.cluster_manager_command.flags & 1 << 10;
    if (cluster_manager.unreachable_masters > 0 && !force_fix) {
        ;
        exit(1);
    }
    int i, fixed = 0;
    list *none = ((void *)0), *single = ((void *)0), *multi = ((void *)0);
    for (i = 0; i < 16384; i++) {
        int covered = all_slots[i];
        if (!covered) {
            hisds slot = hi_sdsfromlonglong((long long)i);
            list *slot_nodes = listCreate();
            hisds slot_nodes_str = hi_sdsempty();
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (n->flags & 1 << 1 || n->replicate)
                        continue;
                    redisReply *reply = (redisCommand((n)->context, "CLUSTER GETKEYSINSLOT %d %d", i, 1));
                    if (!clusterManagerCheckRedisReply(n, reply, ((void *)0))) {
                        fixed = -1;
                        goto cleanup;
                    }
                    ((void)sizeof ((reply->type == 2) ? 1 : 0) , __extension__ ({
                        if (reply->type == 2)
                            ;
                        else
                            __assert_fail("reply->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 5450, __extension__ __PRETTY_FUNCTION__);
                    }));
                    if (reply->elements > 0) {
                        ;
                        if (((slot_nodes)->len) > 1)
                            slot_nodes_str = hi_sdscat(slot_nodes_str, ", ");
                        slot_nodes_str = hi_sdscatfmt(slot_nodes_str, "%s:%u", n->ip, n->port);
                    }
                    ;
                }
            ;
        }
    }
    none = listCreate();
    single = listCreate();
    multi = listCreate();
    dictIterator iter;
    dictEntry *entry;
    while ((entry = dictNext(&iter)) != ((void *)0))
        {
            hisds slot = (hisds)dictGetKey(entry);
            list *nodes = (list *)dictGetVal(entry);
        }
    ;
    int ignore_force = 1;
    if (((none)->len) > 0) {
        ;
        clusterManagerPrintSlotsList(none);
        if (confirmWithYes("Fix these slots by covering with a random node?", ignore_force)) {
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    hisds slot = ln->value;
                    int s = atoi(slot);
                    clusterManagerNode *n = clusterManagerNodeMasterRandom();
                    if (!clusterManagerSetSlotOwner(n, s, 0)) {
                        fixed = -1;
                        goto cleanup;
                    }
                    n->slots[s] = 1;
                    fixed++;
                }
        }
    }
    if (((single)->len) > 0) {
        ;
        clusterManagerPrintSlotsList(single);
        if (confirmWithYes("Fix these slots by covering with those nodes?", ignore_force)) {
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    hisds slot = ln->value;
                    int s = atoi(slot);
                    dictEntry *entry = dictFind(clusterManagerUncoveredSlots, slot);
                    ((void)sizeof ((entry != ((void *)0)) ? 1 : 0) , __extension__ ({
                        if (entry != ((void *)0))
                            ;
                        else
                            __assert_fail("entry != NULL", "redis-cli_InstSlice.c", 5522, __extension__ __PRETTY_FUNCTION__);
                    }));
                    list *nodes = (list *)dictGetVal(entry);
                    listNode *fn = ((nodes)->head);
                    ((void)sizeof ((fn != ((void *)0)) ? 1 : 0) , __extension__ ({
                        if (fn != ((void *)0))
                            ;
                        else
                            __assert_fail("fn != NULL", "redis-cli_InstSlice.c", 5525, __extension__ __PRETTY_FUNCTION__);
                    }));
                    clusterManagerNode *n = fn->value;
                    if (!clusterManagerSetSlotOwner(n, s, 0)) {
                        fixed = -1;
                        goto cleanup;
                    }
                    n->slots[atoi(slot)] = 1;
                    fixed++;
                }
        }
    }
    if (((multi)->len) > 0) {
        ;
        clusterManagerPrintSlotsList(multi);
        if (confirmWithYes("Fix these slots by moving keys into a single node?", ignore_force)) {
            listIter li;
            listNode *ln;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    hisds slot = ln->value;
                    dictEntry *entry = dictFind(clusterManagerUncoveredSlots, slot);
                    ((void)sizeof ((entry != ((void *)0)) ? 1 : 0) , __extension__ ({
                        if (entry != ((void *)0))
                            ;
                        else
                            __assert_fail("entry != NULL", "redis-cli_InstSlice.c", 5551, __extension__ __PRETTY_FUNCTION__);
                    }));
                    list *nodes = (list *)dictGetVal(entry);
                    int s = atoi(slot);
                    clusterManagerNode *target = clusterManagerGetNodeWithMostKeysInSlot(nodes, s, ((void *)0));
                    if (target == ((void *)0)) {
                        fixed = -1;
                        goto cleanup;
                    }
                    ;
                    if (!clusterManagerSetSlotOwner(target, s, 1)) {
                        fixed = -1;
                        goto cleanup;
                    }
                    target->slots[atoi(slot)] = 1;
                    listIter nli;
                    listNode *nln;
                    while ((nln = listNext(&nli)) != ((void *)0))
                        {
                            clusterManagerNode *src = nln->value;
                            if (src == target)
                                continue;
                            if (!clusterManagerSetSlot(src, target, s, "NODE", ((void *)0)))
                                fixed = -1;
                            if (fixed < 0)
                                goto cleanup;
                            if (!clusterManagerSetSlot(src, target, s, "IMPORTING", ((void *)0)))
                                fixed = -1;
                            if (fixed < 0)
                                goto cleanup;
                            int opts = 1 << 7 | 1 << 1;
                            if (!clusterManagerMoveSlot(src, target, s, opts, ((void *)0))) {
                                fixed = -1;
                                goto cleanup;
                            }
                            if (!clusterManagerClearSlotStatus(src, s))
                                fixed = -1;
                            if (fixed < 0)
                                goto cleanup;
                        }
                    fixed++;
                }
        }
    }
  cleanup:
    ;
    return fixed;
}
static int clusterManagerFixOpenSlot (int slot){
    int force_fix = config.cluster_manager_command.flags & 1 << 10;
    if (cluster_manager.unreachable_masters > 0 && !force_fix) {
        ;
        exit(1);
    }
    ;
    int success = 1;
    list *owners = listCreate();
    list *migrating = listCreate();
    list *importing = listCreate();
    hisds migrating_str = hi_sdsempty();
    hisds importing_str = hi_sdsempty();
    clusterManagerNode *owner = ((void *)0);
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1)
                continue;
            if (n->slots[slot]) {
                ;
            } else {
                redisReply *r = (redisCommand((n)->context, "CLUSTER COUNTKEYSINSLOT %d", slot));
                success = clusterManagerCheckRedisReply(n, r, ((void *)0));
                if (!success)
                    goto cleanup;
            }
        }
    if (((owners)->len) == 1)
        owner = ((owners)->head)->value;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1)
                continue;
            int is_migrating = 0, is_importing = 0;
            if (n->migrating) {
                for (int i = 0; i < n->migrating_count; i += 2) {
                    hisds migrating_slot = n->migrating[i];
                    if (atoi(migrating_slot) == slot) {
                        char *sep = (((migrating)->len) == 0 ? "" : ",");
                        migrating_str = hi_sdscatfmt(migrating_str, "%s%s:%u", sep, n->ip, n->port);
                        is_migrating = 1;
                        break;
                    }
                }
            }
            if (!is_migrating && n->importing) {
                for (int i = 0; i < n->importing_count; i += 2) {
                    hisds importing_slot = n->importing[i];
                    if (atoi(importing_slot) == slot) {
                        char *sep = (((importing)->len) == 0 ? "" : ",");
                        importing_str = hi_sdscatfmt(importing_str, "%s%s:%u", sep, n->ip, n->port);
                        is_importing = 1;
                        break;
                    }
                }
            }
            if (!is_migrating && !is_importing && n != owner) {
                redisReply *r = (redisCommand((n)->context, "CLUSTER COUNTKEYSINSLOT %d", slot));
                success = clusterManagerCheckRedisReply(n, r, ((void *)0));
                if (success && r->integer > 0) {
                    ;
                    char *sep = (((importing)->len) == 0 ? "" : ",");
                    importing_str = hi_sdscatfmt(importing_str, "%s%s:%u", sep, n->ip, n->port);
                }
                ;
                if (!success)
                    goto cleanup;
            }
        }
    if (hi_sdslen(migrating_str) > 0) {
    }
    ;
    if (hi_sdslen(importing_str) > 0) {
    }
    ;
    if (owner == ((void *)0)) {
        ;
        owner = clusterManagerGetNodeWithMostKeysInSlot(cluster_manager.nodes, slot, ((void *)0));
        if (owner == ((void *)0)) {
            ;
            success = 0;
            goto cleanup;
        }
        ;
        success = clusterManagerClearSlotStatus(owner, slot);
        if (!success)
            goto cleanup;
        success = clusterManagerSetSlotOwner(owner, slot, 0);
        if (!success)
            goto cleanup;
        owner->slots[slot] = 1;
    }
    if (((owners)->len) > 1) {
        ((void)sizeof ((owner != ((void *)0)) ? 1 : 0) , __extension__ ({
            if (owner != ((void *)0))
                ;
            else
                __assert_fail("owner != NULL", "redis-cli_InstSlice.c", 5757, __extension__ __PRETTY_FUNCTION__);
        }));
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                if (n == owner)
                    continue;
                success = clusterManagerDelSlot(n, slot, 1);
                if (!success)
                    goto cleanup;
                n->slots[slot] = 0;
                success = clusterManagerSetSlot(n, owner, slot, "node", ((void *)0));
                if (!success)
                    goto cleanup;
                success = clusterManagerSetSlot(n, owner, slot, "importing", ((void *)0));
                if (!success)
                    goto cleanup;
            }
    }
    int move_opts = 1 << 7;
    if (((migrating)->len) == 1 && ((importing)->len) == 1) {
        clusterManagerNode *src = ((migrating)->head)->value;
        clusterManagerNode *dst = ((importing)->head)->value;
        move_opts |= 1 << 2;
        success = clusterManagerMoveSlot(src, dst, slot, move_opts, ((void *)0));
    } else if (((migrating)->len) == 0 && ((importing)->len) > 0) {
        ;
        move_opts |= 1 << 1;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                if (n == owner)
                    continue;
                success = clusterManagerMoveSlot(n, owner, slot, move_opts, ((void *)0));
                if (!success)
                    goto cleanup;
                success = clusterManagerClearSlotStatus(n, slot);
                if (!success)
                    goto cleanup;
            }
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                if (n == owner)
                    continue;
                if (n->flags & 1 << 1)
                    continue;
                success = clusterManagerSetSlot(n, owner, slot, "NODE", ((void *)0));
                if (!success)
                    goto cleanup;
            }
    } else if (((migrating)->len) == 1 && ((importing)->len) > 1) {
        int try_to_fix = 1;
        clusterManagerNode *src = ((migrating)->head)->value;
        clusterManagerNode *dst = ((void *)0);
        hisds target_id = ((void *)0);
        for (int i = 0; i < src->migrating_count; i += 2) {
            hisds migrating_slot = src->migrating[i];
            if (atoi(migrating_slot) == slot) {
                target_id = src->migrating[i + 1];
                break;
            }
        }
        ((void)sizeof ((target_id != ((void *)0)) ? 1 : 0) , __extension__ ({
            if (target_id != ((void *)0))
                ;
            else
                __assert_fail("target_id != NULL", "redis-cli_InstSlice.c", 5849, __extension__ __PRETTY_FUNCTION__);
        }));
        listIter li;
        listNode *ln;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                int count = clusterManagerCountKeysInSlot(n, slot);
                if (count > 0) {
                    try_to_fix = 0;
                    break;
                }
                if (strcmp(n->name, target_id) == 0)
                    dst = n;
            }
        if (!try_to_fix)
            goto unhandled_case;
        if (dst != ((void *)0)) {
            ;
            success = clusterManagerMoveSlot(src, dst, slot, move_opts, ((void *)0));
            if (!success)
                goto cleanup;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (dst == n)
                        continue;
                    success = clusterManagerClearSlotStatus(n, slot);
                    if (!success)
                        goto cleanup;
                }
        } else {
            ;
            success = clusterManagerClearSlotStatus(src, slot);
            if (!success)
                goto cleanup;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    success = clusterManagerClearSlotStatus(n, slot);
                    if (!success)
                        goto cleanup;
                }
        }
    } else {
        int try_to_close_slot = (((importing)->len) == 0 && ((migrating)->len) == 1);
        if (try_to_close_slot) {
            clusterManagerNode *n = ((migrating)->head)->value;
            if (!owner || owner != n) {
                redisReply *r = (redisCommand((n)->context, "CLUSTER GETKEYSINSLOT %d %d", slot, 10));
                success = clusterManagerCheckRedisReply(n, r, ((void *)0));
                if (r) {
                    if (success)
                        try_to_close_slot = (r->elements == 0);
                }
                if (!success)
                    goto cleanup;
            }
        }
        if (try_to_close_slot) {
            clusterManagerNode *n = ((migrating)->head)->value;
            redisReply *r = (redisCommand((n)->context, "CLUSTER SETSLOT %d %s", slot, "STABLE"));
            success = clusterManagerCheckRedisReply(n, r, ((void *)0));
        } else {
          unhandled_case:
            success = 0;
        }
    }
  cleanup:
    ;
    return success;
}
static int clusterManagerFixMultipleSlotOwners (int slot, list *owners){
    ;
    int success = 0;
    ((void)sizeof ((((owners)->len) > 1) ? 1 : 0) , __extension__ ({
        if (((owners)->len) > 1)
            ;
        else
            __assert_fail("listLength(owners) > 1", "redis-cli_InstSlice.c", 5942, __extension__ __PRETTY_FUNCTION__);
    }));
    clusterManagerNode *owner = clusterManagerGetNodeWithMostKeysInSlot(owners, slot, ((void *)0));
    if (!owner)
        owner = ((owners)->head)->value;
    if (!clusterManagerSetSlotOwner(owner, slot, 0))
        return 0;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n == owner)
                continue;
            if (n->flags & 1 << 1)
                continue;
            int count = clusterManagerCountKeysInSlot(n, slot);
            success = (count >= 0);
            if (!success)
                break;
            clusterManagerDelSlot(n, slot, 1);
            if (!clusterManagerSetSlot(n, owner, slot, "node", ((void *)0)))
                return 0;
            if (count > 0) {
                int opts = 1 << 7 | 1 << 1;
                success = clusterManagerMoveSlot(n, owner, slot, opts, ((void *)0));
                if (!success)
                    break;
            }
        }
    return success;
}
static int clusterManagerCheckCluster (int quiet){
    listNode *ln = ((cluster_manager.nodes)->head);
    if (!ln)
        return 0;
    clusterManagerNode *node = ln->value;
    int result = 1, consistent = 0;
    int do_fix = config.cluster_manager_command.flags & 1 << 0;
    if (!quiet)
        clusterManagerShowNodes();
    consistent = clusterManagerIsConfigConsistent();
    if (!consistent) {
        hisds err = hi_sdsnew("[ERR] Nodes don't agree about configuration!");
        clusterManagerOnError(err);
        result = 0;
    } else {
        ;
    }
    ;
    listIter li;
    int i;
    dict *open_slots = ((void *)0);
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->migrating != ((void *)0)) {
                if (open_slots == ((void *)0))
                    open_slots = dictCreate(&clusterManagerDictType);
                hisds errstr = hi_sdsempty();
                errstr = hi_sdscatprintf(errstr, "[WARNING] Node %s:%d has slots in migrating state ", n->ip, n->port);
                for (i = 0; i < n->migrating_count; i += 2) {
                    hisds slot = n->migrating[i];
                    char *fmt = (i > 0 ? ",%S" : "%S");
                    errstr = hi_sdscatfmt(errstr, fmt, slot);
                }
                errstr = hi_sdscat(errstr, ".");
                clusterManagerOnError(errstr);
            }
            if (n->importing != ((void *)0)) {
                if (open_slots == ((void *)0))
                    open_slots = dictCreate(&clusterManagerDictType);
                hisds errstr = hi_sdsempty();
                errstr = hi_sdscatprintf(errstr, "[WARNING] Node %s:%d has slots in importing state ", n->ip, n->port);
                for (i = 0; i < n->importing_count; i += 2) {
                    hisds slot = n->importing[i];
                    char *fmt = (i > 0 ? ",%S" : "%S");
                    errstr = hi_sdscatfmt(errstr, fmt, slot);
                }
                errstr = hi_sdscat(errstr, ".");
                clusterManagerOnError(errstr);
            }
        }
    if (open_slots != ((void *)0)) {
        result = 0;
        dictIterator iter;
        dictEntry *entry;
        hisds errstr = hi_sdsnew("[WARNING] The following slots are open: ");
        i = 0;
        while ((entry = dictNext(&iter)) != ((void *)0))
            {
                hisds slot = (hisds)dictGetKey(entry);
                char *fmt = (i++ > 0 ? ",%S" : "%S");
                errstr = hi_sdscatfmt(errstr, fmt, slot);
            }
        ;
        if (do_fix) {
            ;
            while ((entry = dictNext(&iter)) != ((void *)0))
                {
                    hisds slot = (hisds)dictGetKey(entry);
                    result = clusterManagerFixOpenSlot(atoi(slot));
                    if (!result)
                        break;
                }
            ;
        }
        ;
    }
    ;
    char slots[16384];
    memset(slots, 0, 16384);
    int coverage = clusterManagerGetCoveredSlots(slots);
    if (coverage == 16384) {
        ;
    } else {
        hisds err = hi_sdsempty();
        err = hi_sdscatprintf(err, "[ERR] Not all %d slots are covered by nodes.\n", 16384);
        clusterManagerOnError(err);
        result = 0;
        if (do_fix) {
            dictType dtype = clusterManagerDictType;
            dtype.keyDestructor = dictSdsDestructor;
            dtype.valDestructor = dictListDestructor;
            clusterManagerUncoveredSlots = dictCreate(&dtype);
            int fixed = clusterManagerFixSlotsCoverage(slots);
            if (fixed > 0)
                result = 1;
        }
    }
    int search_multiple_owners = config.cluster_manager_command.flags & 1 << 9;
    if (search_multiple_owners) {
        ;
        int slot = 0, slots_with_multiple_owners = 0;
        for (; slot < 16384; slot++) {
            listIter li;
            listNode *ln;
            list *owners = listCreate();
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (n->flags & 1 << 1)
                        continue;
                    if (n->slots[slot]) {
                        listAddNodeTail(owners, n);
                    } else {
                        int count = clusterManagerCountKeysInSlot(n, slot);
                    }
                }
            if (((owners)->len) > 1) {
                result = 0;
                while ((ln = listNext(&li)) != ((void *)0))
                    {
                        clusterManagerNode *n = ln->value;
                    }
                slots_with_multiple_owners++;
                if (do_fix) {
                    result = clusterManagerFixMultipleSlotOwners(slot, owners);
                    if (!result) {
                        ;
                        break;
                    } else
                        slots_with_multiple_owners--;
                }
            }
            ;
        }
        ;
    }
    return result;
}
static clusterManagerNode * clusterNodeForResharding (char *id, clusterManagerNode *target, int *raise_err){
    clusterManagerNode *node = ((void *)0);
    const char *invalid_node_msg = "*** The specified node (%s) is not known or not a master, please retry.\n";
    node = clusterManagerNodeByName(id);
    *raise_err = 0;
    if (!node || node->flags & 1 << 1) {
        ;
        *raise_err = 1;
        return ((void *)0);
    } else if (target != ((void *)0)) {
        if (!strcmp(node->name, target->name)) {
            ;
            return ((void *)0);
        }
    }
    return node;
}
static list * clusterManagerComputeReshardTable (list *sources, int numslots){
    list *moved = listCreate();
    int src_count = ((sources)->len), i = 0, tot_slots = 0, j;
    clusterManagerNode **sorted = zmalloc(src_count * sizeof (*sorted));
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *node = ln->value;
            tot_slots += node->slots_count;
            sorted[i++] = node;
        }
    ;
    for (i = 0; i < src_count; i++) {
        clusterManagerNode *node = sorted[i];
        float n = ((float)numslots / tot_slots * node->slots_count);
        if (i == 0) {
            n = ceil(n);
        } else
            n = floor(n);
        int max = (int)n, count = 0;
        for (j = 0; j < 16384; j++) {
            int slot = node->slots[j];
            if (!slot)
                continue;
            if (count >= max || (int)((moved)->len) >= numslots)
                break;
            clusterManagerReshardTableItem *item = zmalloc(sizeof (*item));
            item->source = node;
            item->slot = j;
            count++;
        }
    }
    ;
    return moved;
}
static void clusterManagerNodeArrayInit (clusterManagerNodeArray *array, int alloc_len){
    array->nodes = zcalloc(alloc_len * sizeof(clusterManagerNode *));
    array->alloc = array->nodes;
    array->len = alloc_len;
    array->count = 0;
}
static void clusterManagerNodeArrayReset (clusterManagerNodeArray *array){
    if (array->nodes > array->alloc) {
        array->len = array->nodes - array->alloc;
        array->nodes = array->alloc;
        array->count = 0;
        int i = 0;
        for (; i < array->len; i++) {
            if (array->nodes[i] != ((void *)0))
                array->count++;
        }
    }
}
static void clusterManagerNodeArrayShift (clusterManagerNodeArray *array, clusterManagerNode **nodeptr){
    ((void)sizeof ((array->len > 0) ? 1 : 0) , __extension__ ({
        if (array->len > 0)
            ;
        else
            __assert_fail("array->len > 0", "redis-cli_InstSlice.c", 6219, __extension__ __PRETTY_FUNCTION__);
    }));
    if (*array->nodes != ((void *)0))
        array->count--;
    *nodeptr = *array->nodes;
    array->nodes++;
    array->len--;
}
static void clusterManagerNodeArrayAdd (clusterManagerNodeArray *array, clusterManagerNode *node){
    ((void)sizeof ((array->len > 0) ? 1 : 0) , __extension__ ({
        if (array->len > 0)
            ;
        else
            __assert_fail("array->len > 0", "redis-cli_InstSlice.c", 6232, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((node != ((void *)0)) ? 1 : 0) , __extension__ ({
        if (node != ((void *)0))
            ;
        else
            __assert_fail("node != NULL", "redis-cli_InstSlice.c", 6233, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((array->count < array->len) ? 1 : 0) , __extension__ ({
        if (array->count < array->len)
            ;
        else
            __assert_fail("array->count < array->len", "redis-cli_InstSlice.c", 6234, __extension__ __PRETTY_FUNCTION__);
    }));
    array->nodes[array->count++] = node;
}
static void clusterManagerMode (clusterManagerCommandProc *proc){
    int argc = config.cluster_manager_command.argc;
    char **argv = config.cluster_manager_command.argv;
    cluster_manager.nodes = ((void *)0);
    int success = proc(argc, argv);
    freeClusterManager();
    exit(success ? 0 : 1);
}
static int clusterManagerCommandCreate (int argc, char **argv){
    int i, j, success = 1;
    cluster_manager.nodes = listCreate();
    for (i = 0; i < argc; i++) {
        char *addr = argv[i];
        char *ip = ((void *)0);
        int port = 0;
        if (!parseClusterNodeAddress(addr, &ip, &port, ((void *)0))) {
            ;
            return 0;
        }
        clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
        if (!clusterManagerNodeConnect(node)) {
            freeClusterManagerNode(node);
            return 0;
        }
        char *err = ((void *)0);
        if (!clusterManagerNodeIsCluster(node, &err)) {
            ;
            freeClusterManagerNode(node);
            return 0;
        }
        err = ((void *)0);
        if (!clusterManagerNodeLoadInfo(node, 0, &err)) {
            freeClusterManagerNode(node);
            return 0;
        }
        err = ((void *)0);
        if (!clusterManagerNodeIsEmpty(node, &err)) {
            ;
            freeClusterManagerNode(node);
            return 0;
        }
        ;
    }
    int node_len = cluster_manager.nodes->len;
    int replicas = config.cluster_manager_command.replicas;
    int masters_count = ((node_len) / ((replicas) + 1));
    if (masters_count < 3) {
        ;
        return 0;
    }
    ;
    int interleaved_len = 0, ip_count = 0;
    clusterManagerNode **interleaved = zcalloc(node_len * sizeof (**interleaved));
    char **ips = zcalloc(node_len * sizeof(char *));
    clusterManagerNodeArray *ip_nodes = zcalloc(node_len * sizeof (*ip_nodes));
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            int found = 0;
            for (i = 0; i < ip_count; i++) {
                char *ip = ips[i];
                if (!strcmp(ip, n->ip)) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                ips[ip_count++] = n->ip;
            }
            clusterManagerNodeArray *node_array = &(ip_nodes[i]);
            if (node_array->nodes == ((void *)0))
                clusterManagerNodeArrayInit(node_array, node_len);
            clusterManagerNodeArrayAdd(node_array, n);
        }
    while (interleaved_len < node_len)
        {
            for (i = 0; i < ip_count; i++) {
                clusterManagerNodeArray *node_array = &(ip_nodes[i]);
                if (node_array->count > 0) {
                    clusterManagerNode *n = ((void *)0);
                    clusterManagerNodeArrayShift(node_array, &n);
                    interleaved[interleaved_len++] = n;
                }
            }
        }
    clusterManagerNode **masters = interleaved;
    interleaved += masters_count;
    interleaved_len -= masters_count;
    float slots_per_node = 16384 / (float)masters_count;
    long first = 0;
    float cursor = 0.F;
    for (i = 0; i < masters_count; i++) {
        clusterManagerNode *master = masters[i];
        long last = lround(cursor + slots_per_node - 1);
        if (last > 16384 || i == (masters_count - 1))
            last = 16384 - 1;
        if (last < first)
            last = first;
        master->slots_count = 0;
        for (j = first; j <= last; j++) {
            master->slots[j] = 1;
            master->slots_count++;
        }
        master->dirty = 1;
        first = last + 1;
        cursor += slots_per_node;
    }
    clusterManagerNode *first_node = interleaved[0];
    for (i = 0; i < (interleaved_len - 1); i++)
        interleaved[i] = interleaved[i + 1];
    interleaved[interleaved_len - 1] = first_node;
    int assign_unused = 0, available_count = interleaved_len;
  assign_replicas:
    for (i = 0; i < masters_count; i++) {
        clusterManagerNode *master = masters[i];
        int assigned_replicas = 0;
        while (assigned_replicas < replicas)
            {
                if (available_count == 0)
                    break;
                clusterManagerNode *found = ((void *)0), *slave = ((void *)0);
                int firstNodeIdx = -1;
                for (j = 0; j < interleaved_len; j++) {
                    clusterManagerNode *n = interleaved[j];
                    if (n == ((void *)0))
                        continue;
                    if (strcmp(n->ip, master->ip)) {
                        found = n;
                        interleaved[j] = ((void *)0);
                        break;
                    }
                    if (firstNodeIdx < 0)
                        firstNodeIdx = j;
                }
                if (found) {
                    slave = found;
                } else if (firstNodeIdx >= 0) {
                    slave = interleaved[firstNodeIdx];
                    interleaved_len -= (firstNodeIdx + 1);
                    interleaved += (firstNodeIdx + 1);
                }
                if (slave != ((void *)0)) {
                    assigned_replicas++;
                    available_count--;
                    slave->replicate = hi_sdsnew(master->name);
                    slave->dirty = 1;
                } else {
                    ;
                }
                ;
                if (assign_unused)
                    break;
            }
    }
    if (!assign_unused && available_count > 0) {
        assign_unused = 1;
        goto assign_replicas;
    }
    for (i = 0; i < ip_count; i++) {
        clusterManagerNodeArray *node_array = ip_nodes + i;
        clusterManagerNodeArrayReset(node_array);
    }
    clusterManagerOptimizeAntiAffinity(ip_nodes, ip_count);
    clusterManagerShowNodes();
    int ignore_force = 0;
    if (confirmWithYes("Can I set the above configuration?", ignore_force)) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *node = ln->value;
                char *err = ((void *)0);
                int flushed = clusterManagerFlushNodeConfig(node, &err);
                if (!flushed && node->dirty && !node->replicate) {
                    success = 0;
                    goto cleanup;
                } else {
                    ;
                }
            }
        ;
        int config_epoch = 1;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *node = ln->value;
                redisReply *reply = ((void *)0);
                reply = (redisCommand((node)->context, "cluster set-config-epoch %d", config_epoch++));
            }
        ;
        clusterManagerNode *first = ((void *)0);
        char first_ip[46];
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *node = ln->value;
                if (first == ((void *)0)) {
                    first = node;
                    int anet_flags = 0;
                    if (config.prefer_ipv4)
                        anet_flags |= (1 << 1);
                    if (config.prefer_ipv6)
                        anet_flags |= (1 << 2);
                    if (anetResolve(((void *)0), first->ip, first_ip, sizeof (first_ip), anet_flags) == -1) {
                        ;
                        success = 0;
                        goto cleanup;
                    }
                    continue;
                }
                redisReply *reply = ((void *)0);
                if (first->bus_port == 0 || (first->bus_port == first->port + 10000)) {
                    reply = (redisCommand((node)->context, "cluster meet %s %d", first_ip, first->port));
                } else {
                    reply = (redisCommand((node)->context, "cluster meet %s %d %d", first_ip, first->port, first->bus_port));
                }
                int is_err = 0;
                if (reply != ((void *)0)) {
                    if ((is_err = reply->type == 6))
                        clusterManagerLog(3, "Node %s:%d replied with error:\n%s\n", (node)->ip, (node)->port, (reply->str));
                } else {
                    is_err = 1;
                }
                if (is_err) {
                    success = 0;
                    goto cleanup;
                }
            }
        ;
        clusterManagerWaitForClusterJoin();
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *node = ln->value;
                if (!node->dirty)
                    continue;
                char *err = ((void *)0);
                int flushed = clusterManagerFlushNodeConfig(node, &err);
                if (!flushed && !node->replicate) {
                    success = 0;
                    goto cleanup;
                } else {
                    ;
                }
            }
        ;
        clusterManagerNode *first_node = ((void *)0);
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *node = ln->value;
                if (!first_node) {
                    first_node = node;
                } else
                    freeClusterManagerNode(node);
            }
        ;
        if (!clusterManagerLoadInfoFromNode(first_node)) {
            success = 0;
            goto cleanup;
        }
        clusterManagerCheckCluster(0);
    }
  cleanup:
    ;
    for (i = 0; i < node_len; i++) {
        clusterManagerNodeArray *node_array = ip_nodes + i;
    }
    ;
    return success;
}
static int clusterManagerCommandAddNode (int argc, char **argv){
    int success = 1;
    redisReply *reply = ((void *)0);
    redisReply *function_restore_reply = ((void *)0);
    redisReply *function_list_reply = ((void *)0);
    char *ref_ip = ((void *)0), *ip = ((void *)0);
    int ref_port = 0, port = 0;
    if (!getClusterHostFromCmdArgs(argc - 1, argv + 1, &ref_ip, &ref_port))
        goto invalid_args;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *refnode = clusterManagerNewNode(ref_ip, ref_port, 0);
    if (!clusterManagerLoadInfoFromNode(refnode))
        return 0;
    if (!clusterManagerCheckCluster(0))
        return 0;
    clusterManagerNode *master_node = ((void *)0);
    if (config.cluster_manager_command.flags & 1 << 1) {
        char *master_id = config.cluster_manager_command.master_id;
        if (master_id != ((void *)0)) {
            master_node = clusterManagerNodeByName(master_id);
            if (master_node == ((void *)0)) {
                ;
                return 0;
            }
        } else {
            master_node = clusterManagerNodeWithLeastReplicas();
            ((void)sizeof ((master_node != ((void *)0)) ? 1 : 0) , __extension__ ({
                if (master_node != ((void *)0))
                    ;
                else
                    __assert_fail("master_node != NULL", "redis-cli_InstSlice.c", 6574, __extension__ __PRETTY_FUNCTION__);
            }));
        }
    }
    clusterManagerNode *new_node = clusterManagerNewNode(ip, port, 0);
    int added = 0;
    if (!clusterManagerNodeConnect(new_node)) {
        ;
        success = 0;
        goto cleanup;
    }
    char *err = ((void *)0);
    if (!(success = clusterManagerNodeIsCluster(new_node, &err))) {
        ;
        goto cleanup;
    }
    if (!clusterManagerNodeLoadInfo(new_node, 0, &err)) {
        success = 0;
        goto cleanup;
    }
    if (!(success = clusterManagerNodeIsEmpty(new_node, &err))) {
        ;
        goto cleanup;
    }
    clusterManagerNode *first = ((cluster_manager.nodes)->head)->value;
    added = 1;
    if (!master_node) {
        ;
        reply = (redisCommand((refnode)->context, "FUNCTION DUMP"));
        if (!clusterManagerCheckRedisReply(refnode, reply, &err)) {
            ;
        } else {
            ((void)sizeof ((reply->type == 1) ? 1 : 0) , __extension__ ({
                if (reply->type == 1)
                    ;
                else
                    __assert_fail("reply->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 6615, __extension__ __PRETTY_FUNCTION__);
            }));
            function_list_reply = (redisCommand((new_node)->context, "FUNCTION LIST"));
            if (!clusterManagerCheckRedisReply(new_node, function_list_reply, &err)) {
                ;
                success = 0;
                goto cleanup;
            }
            ((void)sizeof ((function_list_reply->type == 2) ? 1 : 0) , __extension__ ({
                if (function_list_reply->type == 2)
                    ;
                else
                    __assert_fail("function_list_reply->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 6624, __extension__ __PRETTY_FUNCTION__);
            }));
            if (function_list_reply->elements > 0) {
                ;
                success = 0;
                goto cleanup;
            }
            ;
            function_restore_reply = (redisCommand((new_node)->context, "FUNCTION RESTORE %b", reply->str, reply->len));
            if (!clusterManagerCheckRedisReply(new_node, function_restore_reply, &err)) {
                ;
                success = 0;
                goto cleanup;
            }
        }
    }
    ;
    char first_ip[46];
    int anet_flags = 0;
    if (config.prefer_ipv4)
        anet_flags |= (1 << 1);
    if (config.prefer_ipv6)
        anet_flags |= (1 << 2);
    if (anetResolve(((void *)0), first->ip, first_ip, sizeof (first_ip), anet_flags) == -1) {
        ;
        success = 0;
        goto cleanup;
    }
    if (first->bus_port == 0 || (first->bus_port == first->port + 10000)) {
        reply = (redisCommand((new_node)->context, "CLUSTER MEET %s %d", first_ip, first->port));
    } else {
        reply = (redisCommand((new_node)->context, "CLUSTER MEET %s %d %d", first_ip, first->port, first->bus_port));
    }
    if (!(success = clusterManagerCheckRedisReply(new_node, reply, ((void *)0))))
        goto cleanup;
    if (master_node) {
        ;
        clusterManagerWaitForClusterJoin();
        reply = (redisCommand((new_node)->context, "CLUSTER REPLICATE %s", master_node->name));
        if (!(success = clusterManagerCheckRedisReply(new_node, reply, ((void *)0))))
            goto cleanup;
    }
    ;
  cleanup:
    if (!added && new_node)
        freeClusterManagerNode(new_node);
    return success;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandDeleteNode (int argc, char **argv){
    ;
    int success = 1;
    int port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    char *node_id = argv[1];
    clusterManagerNode *ref_node = clusterManagerNewNode(ip, port, 0);
    clusterManagerNode *node = ((void *)0);
    if (!clusterManagerLoadInfoFromNode(ref_node))
        return 0;
    node = clusterManagerNodeByName(node_id);
    if (node == ((void *)0)) {
        ;
        return 0;
    }
    if (node->slots_count != 0) {
        ;
        return 0;
    }
    ;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n == node)
                continue;
            if (n->replicate && !strcasecmp(n->replicate, node_id)) {
                clusterManagerNode *master = clusterManagerNodeWithLeastReplicas();
                ((void)sizeof ((master != ((void *)0)) ? 1 : 0) , __extension__ ({
                    if (master != ((void *)0))
                        ;
                    else
                        __assert_fail("master != NULL", "redis-cli_InstSlice.c", 6731, __extension__ __PRETTY_FUNCTION__);
                }));
                redisReply *r = (redisCommand((n)->context, "CLUSTER REPLICATE %s", master->name));
                success = clusterManagerCheckRedisReply(n, r, ((void *)0));
                if (!success)
                    return 0;
            }
            redisReply *r = (redisCommand((n)->context, "CLUSTER FORGET %s", node_id));
            success = clusterManagerCheckRedisReply(n, r, ((void *)0));
            if (!success)
                return 0;
        }
    ;
    redisReply *r = redisCommand(node->context, "CLUSTER RESET %s", "SOFT");
    success = clusterManagerCheckRedisReply(node, r, ((void *)0));
    return success;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandInfo (int argc, char **argv){
    int port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(node))
        return 0;
    return 1;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandCheck (int argc, char **argv){
    int port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(node))
        return 0;
    return clusterManagerCheckCluster(0);
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandFix (int argc, char **argv){
    config.cluster_manager_command.flags |= 1 << 0;
    return clusterManagerCommandCheck(argc, argv);
}
static int clusterManagerCommandReshard (int argc, char **argv){
    int port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(node))
        return 0;
    clusterManagerCheckCluster(0);
    if (cluster_manager.errors && ((cluster_manager.errors)->len) > 0) {
        ;
        return 0;
    }
    int slots = config.cluster_manager_command.slots;
    if (!slots) {
        while (slots <= 0 || slots > 16384)
            {
                ;
                char buf[6];
                int nread = read(fileno(stdin), buf, 6);
                if (nread <= 0)
                    continue;
                int last_idx = nread - 1;
                if (buf[last_idx] != '\n') {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != (-1))
                        {
                        }
                }
                buf[last_idx] = '\x00';
                slots = atoi(buf);
            }
    }
    char buf[255];
    char *to = config.cluster_manager_command.to, *from = config.cluster_manager_command.from;
    while (to == ((void *)0))
        {
            ;
            int nread = read(fileno(stdin), buf, 255);
            if (nread <= 0)
                continue;
            int last_idx = nread - 1;
            if (buf[last_idx] != '\n') {
                int ch;
                while ((ch = getchar()) != '\n' && ch != (-1))
                    {
                    }
            }
            buf[last_idx] = '\x00';
            if (strlen(buf) > 0)
                to = buf;
        }
    int raise_err = 0;
    clusterManagerNode *target = clusterNodeForResharding(to, ((void *)0), &raise_err);
    if (target == ((void *)0))
        return 0;
    list *sources = listCreate();
    list *table = ((void *)0);
    int all = 0, result = 1;
    if (from == ((void *)0)) {
        ;
        while (1)
            {
                ;
                int nread = read(fileno(stdin), buf, 255);
                int last_idx = nread - 1;
                if (buf[last_idx] != '\n') {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != (-1))
                        {
                        }
                }
                buf[last_idx] = '\x00';
                if (!strcmp(buf, "done")) {
                    break;
                } else if (!strcmp(buf, "all")) {
                    all = 1;
                    break;
                } else {
                    clusterManagerNode *src = clusterNodeForResharding(buf, target, &raise_err);
                    if (src != ((void *)0)) {
                        listAddNodeTail(sources, src);
                    } else if (raise_err) {
                        result = 0;
                        goto cleanup;
                    }
                }
            }
    } else {
        char *p;
        while ((p = strchr(from, ',')) != ((void *)0))
            {
                *p = '\x00';
                if (!strcmp(from, "all")) {
                    all = 1;
                    break;
                } else {
                    clusterManagerNode *src = clusterNodeForResharding(from, target, &raise_err);
                    if (src != ((void *)0)) {
                        listAddNodeTail(sources, src);
                    } else if (raise_err) {
                        result = 0;
                        goto cleanup;
                    }
                }
                from = p + 1;
            }
        if (!all && strlen(from) > 0) {
            if (!strcmp(from, "all"))
                all = 1;
            if (!all) {
                clusterManagerNode *src = clusterNodeForResharding(from, target, &raise_err);
                if (src != ((void *)0)) {
                    listAddNodeTail(sources, src);
                } else if (raise_err) {
                    result = 0;
                    goto cleanup;
                }
            }
        }
    }
    listIter li;
    listNode *ln;
    if (all) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
            }
    }
    if (((sources)->len) == 0) {
        ;
        result = 0;
        goto cleanup;
    }
    ;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *src = ln->value;
            hisds info = clusterManagerNodeInfo(src, 4);
        }
    ;
    hisds info = clusterManagerNodeInfo(target, 4);
    table = clusterManagerComputeReshardTable(sources, slots);
    if (!(config.cluster_manager_command.flags & 1 << 2)) {
        ;
        char buf[4];
        int nread = read(fileno(stdin), buf, 4);
        buf[3] = '\x00';
        if (nread <= 0 || strcmp("yes", buf) != 0) {
            result = 0;
            goto cleanup;
        }
    }
    int opts = 1 << 7;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerReshardTableItem *item = ln->value;
            char *err = ((void *)0);
            result = clusterManagerMoveSlot(item->source, target, item->slot, opts, &err);
            if (!result) {
                goto cleanup;
            }
        }
  cleanup:
    ;
    return result;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandRebalance (int argc, char **argv){
    int port = 0;
    char *ip = ((void *)0);
    clusterManagerNode **weightedNodes = ((void *)0);
    list *involved = ((void *)0);
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(node))
        return 0;
    int result = 1, i;
    if (config.cluster_manager_command.weight != ((void *)0)) {
        for (i = 0; i < config.cluster_manager_command.weight_argc; i++) {
            char *name = config.cluster_manager_command.weight[i];
            char *p = strchr(name, '=');
            if (p == ((void *)0)) {
                ;
                result = 0;
                goto cleanup;
            }
            *p = '\x00';
            float w = atof(++p);
            clusterManagerNode *n = clusterManagerNodeByAbbreviatedName(name);
            if (n == ((void *)0)) {
                ;
                result = 0;
                goto cleanup;
            }
            n->weight = w;
        }
    }
    float total_weight = 0;
    int nodes_involved = 0;
    int use_empty = config.cluster_manager_command.flags & 1 << 4;
    involved = listCreate();
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if (n->flags & 1 << 1 || n->replicate)
                continue;
            if (!use_empty && n->slots_count == 0) {
                n->weight = 0;
                continue;
            }
            total_weight += n->weight;
            nodes_involved++;
        }
    weightedNodes = zmalloc(nodes_involved * sizeof(clusterManagerNode *));
    if (weightedNodes == ((void *)0))
        goto cleanup;
    clusterManagerCheckCluster(1);
    if (cluster_manager.errors && ((cluster_manager.errors)->len) > 0) {
        ;
        result = 0;
        goto cleanup;
    }
    int threshold_reached = 0, total_balance = 0;
    float threshold = config.cluster_manager_command.threshold;
    i = 0;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            weightedNodes[i++] = n;
            int expected = (int)(((float)16384 / total_weight) * n->weight);
            n->balance = n->slots_count - expected;
            total_balance += n->balance;
            int over_threshold = 0;
            if (threshold > 0) {
                if (n->slots_count > 0) {
                    float err_perc = fabs((100 - (100. * expected / n->slots_count)));
                    if (err_perc > threshold)
                        over_threshold = 1;
                } else if (expected > 1) {
                    over_threshold = 1;
                }
            }
            if (over_threshold)
                threshold_reached = 1;
        }
    if (!threshold_reached) {
        ;
        goto cleanup;
    }
    while (total_balance > 0)
        {
            ;
            while ((ln = listNext(&li)) != ((void *)0))
                {
                    clusterManagerNode *n = ln->value;
                    if (n->balance <= 0 && total_balance > 0) {
                        n->balance--;
                        total_balance--;
                    }
                }
        }
    ;
    if (config.verbose) {
        for (i = 0; i < nodes_involved; i++) {
            clusterManagerNode *n = weightedNodes[i];
        }
    }
    int dst_idx = 0;
    int src_idx = nodes_involved - 1;
    int simulate = config.cluster_manager_command.flags & 1 << 5;
    while (dst_idx < src_idx)
        {
            clusterManagerNode *dst = weightedNodes[dst_idx];
            clusterManagerNode *src = weightedNodes[src_idx];
            int db = abs(dst->balance);
            int sb = abs(src->balance);
            int numslots = (db < sb ? db : sb);
            if (numslots > 0) {
                ;
                list *lsrc = listCreate(), *table = ((void *)0);
                table = clusterManagerComputeReshardTable(lsrc, numslots);
                int table_len = (int)((table)->len);
                if (!table || table_len != numslots) {
                    ;
                    result = 0;
                    goto end_move;
                }
                if (simulate) {
                    for (i = 0; i < table_len; i++)
                        printf("#");
                } else {
                    int opts = 1 << 6 | 1 << 2;
                    while ((ln = listNext(&li)) != ((void *)0))
                        {
                            clusterManagerReshardTableItem *item = ln->value;
                            char *err;
                            result = clusterManagerMoveSlot(item->source, dst, item->slot, opts, &err);
                            if (!result) {
                                ;
                                goto end_move;
                            }
                            ;
                        }
                }
                ;
              end_move:
                ;
                if (!result)
                    goto cleanup;
            }
            dst->balance += numslots;
            src->balance -= numslots;
            if (dst->balance == 0)
                dst_idx++;
            if (src->balance == 0)
                src_idx--;
        }
  cleanup:
    ;
    return result;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandSetTimeout (int argc, char **argv){
    ;
    int port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    int timeout = atoi(argv[1]);
    if (timeout < 100) {
        ;
        return 0;
    }
    clusterManagerNode *node = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(node))
        return 0;
    int ok_count = 0, err_count = 0;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            char *err = ((void *)0);
            redisReply *reply = (redisCommand((n)->context, "CONFIG %s %s %d", "SET", "cluster-node-timeout", timeout));
            if (reply == ((void *)0))
                goto reply_err;
            int ok = clusterManagerCheckRedisReply(n, reply, &err);
            if (!ok)
                goto reply_err;
            reply = (redisCommand((n)->context, "CONFIG %s", "REWRITE"));
            if (reply == ((void *)0))
                goto reply_err;
            ok = clusterManagerCheckRedisReply(n, reply, &err);
            if (!ok)
                goto reply_err;
            ok_count++;
          reply_err:
            int need_free = 0;
            if (err == ((void *)0)) {
                err = "";
            } else
                need_free = 1;
            err_count++;
        }
    ;
    return 1;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandImport (int argc, char **argv){
    int success = 1;
    int port = 0, src_port = 0;
    char *ip = ((void *)0), *src_ip = ((void *)0);
    char *invalid_args_msg = ((void *)0);
    hisds cmdfmt = ((void *)0);
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port)) {
        ;
        goto invalid_args;
    }
    if (config.cluster_manager_command.from == ((void *)0)) {
        ;
        goto invalid_args;
    }
    char *src_host[] = {config.cluster_manager_command.from};
    if (!getClusterHostFromCmdArgs(1, src_host, &src_ip, &src_port)) {
        ;
        goto invalid_args;
    }
    ;
    clusterManagerNode *refnode = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(refnode))
        return 0;
    if (!clusterManagerCheckCluster(0))
        return 0;
    char *reply_err = ((void *)0);
    redisReply *src_reply = ((void *)0);
    redisContext *src_ctx = redisConnectWrapper(src_ip, src_port, config.connect_timeout);
    if (src_ctx->err) {
        success = 0;
        goto cleanup;
    }
    char *from_user = config.cluster_manager_command.from_user;
    char *from_pass = config.cluster_manager_command.from_pass;
    if (cliAuth(src_ctx, from_user, from_pass) == -1) {
        success = 0;
        goto cleanup;
    }
    src_reply = reconnectingRedisCommand(src_ctx, "INFO");
    if (!src_reply || src_reply->type == 6) {
        ;
        success = 0;
        goto cleanup;
    }
    if (getLongInfoField(src_reply->str, "cluster_enabled")) {
        ;
        success = 0;
        goto cleanup;
    }
    ;
    src_reply = reconnectingRedisCommand(src_ctx, "DBSIZE");
    if (!src_reply || src_reply->type == 6) {
        ;
        success = 0;
        goto cleanup;
    }
    int size = src_reply->integer, i;
    clusterManagerNode *slots_map[16384];
    memset(slots_map, 0, sizeof (slots_map));
    listIter li;
    listNode *ln;
    for (i = 0; i < 16384; i++) {
        ;
        while ((ln = listNext(&li)) != ((void *)0))
            {
                clusterManagerNode *n = ln->value;
                if (n->flags & 1 << 1)
                    continue;
                if (n->slots_count == 0)
                    continue;
                if (n->slots[i]) {
                    slots_map[i] = n;
                    break;
                }
            }
    }
    cmdfmt = hi_sdsnew("MIGRATE %s %d %s %d %d");
    if (config.conn_info.auth) {
        if (config.conn_info.user) {
            cmdfmt = hi_sdscatfmt(cmdfmt, " AUTH2 %s %s", config.conn_info.user, config.conn_info.auth);
        } else {
            cmdfmt = hi_sdscatfmt(cmdfmt, " AUTH %s", config.conn_info.auth);
        }
    }
    if (config.cluster_manager_command.flags & 1 << 7)
        cmdfmt = hi_sdscat(cmdfmt, " COPY");
    if (config.cluster_manager_command.flags & 1 << 6)
        cmdfmt = hi_sdscat(cmdfmt, " REPLACE");
    int cursor = -999, timeout = config.cluster_manager_command.timeout;
    while (cursor != 0)
        {
            if (cursor < 0)
                cursor = 0;
            src_reply = reconnectingRedisCommand(src_ctx, "SCAN %d COUNT %d", cursor, 1000);
            if (!src_reply || src_reply->type == 6) {
                ;
                success = 0;
                goto cleanup;
            }
            ((void)sizeof ((src_reply->type == 2) ? 1 : 0) , __extension__ ({
                if (src_reply->type == 2)
                    ;
                else
                    __assert_fail("src_reply->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 7324, __extension__ __PRETTY_FUNCTION__);
            }));
            ((void)sizeof ((src_reply->elements >= 2) ? 1 : 0) , __extension__ ({
                if (src_reply->elements >= 2)
                    ;
                else
                    __assert_fail("src_reply->elements >= 2", "redis-cli_InstSlice.c", 7325, __extension__ __PRETTY_FUNCTION__);
            }));
            ((void)sizeof ((src_reply->element[1]->type == 2) ? 1 : 0) , __extension__ ({
                if (src_reply->element[1]->type == 2)
                    ;
                else
                    __assert_fail("src_reply->element[1]->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 7326, __extension__ __PRETTY_FUNCTION__);
            }));
            if (src_reply->element[0]->type == 1) {
                cursor = atoi(src_reply->element[0]->str);
            } else if (src_reply->element[0]->type == 3)
                cursor = src_reply->element[0]->integer;
            int keycount = src_reply->element[1]->elements;
            for (i = 0; i < keycount; i++) {
                redisReply *kr = src_reply->element[1]->element[i];
                ((void)sizeof ((kr->type == 1) ? 1 : 0) , __extension__ ({
                    if (kr->type == 1)
                        ;
                    else
                        __assert_fail("kr->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 7334, __extension__ __PRETTY_FUNCTION__);
                }));
                char *key = kr->str;
                uint16_t slot = clusterManagerKeyHashSlot(key, kr->len);
                clusterManagerNode *target = slots_map[slot];
                redisReply *r = reconnectingRedisCommand(src_ctx, cmdfmt, target->ip, target->port, key, 0, timeout);
                if (!r || r->type == 6) {
                    success = 0;
                }
                ;
                if (!success)
                    goto cleanup;
            }
        }
  cleanup:
    ;
    return success;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandCall (int argc, char **argv){
    int port = 0, i;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *refnode = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(refnode))
        return 0;
    argc--;
    argv++;
    size_t *argvlen = zmalloc(argc * sizeof(size_t));
    for (i = 0; i < argc; i++) {
        argvlen[i] = strlen(argv[i]);
    }
    ;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            clusterManagerNode *n = ln->value;
            if ((config.cluster_manager_command.flags & 1 << 11) && (n->replicate != ((void *)0)))
                continue;
            if ((config.cluster_manager_command.flags & 1 << 12) && (n->replicate == ((void *)0)))
                continue;
            if (!n->context && !clusterManagerNodeConnect(n))
                continue;
            redisReply *reply = ((void *)0);
            int status = redisGetReply(n->context, (void **)(&reply));
            if (status != 0 || reply == ((void *)0)) {
                ;
            } else {
                hisds formatted_reply = cliFormatReplyRaw(reply);
            }
            ;
        }
    ;
    return 1;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandBackup (int argc, char **argv){
    ;
    int success = 1, port = 0;
    char *ip = ((void *)0);
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    clusterManagerNode *refnode = clusterManagerNewNode(ip, port, 0);
    if (!clusterManagerLoadInfoFromNode(refnode))
        return 0;
    int no_issues = clusterManagerCheckCluster(0);
    int cluster_errors_count = (no_issues ? 0 : ((cluster_manager.errors)->len));
    config.cluster_manager_command.backup_dir = argv[1];
    hisds json = hi_sdsnew("[\n");
    int first_node = 0;
    listIter li;
    listNode *ln;
    while ((ln = listNext(&li)) != ((void *)0))
        {
            if (!first_node) {
                first_node = 1;
            } else
                json = hi_sdscat(json, ",\n");
            clusterManagerNode *node = ln->value;
            hisds node_json = clusterManagerNodeGetJSON(node, cluster_errors_count);
            json = hi_sdscat(json, node_json);
            if (node->replicate)
                continue;
            getRDB(node);
        }
    json = hi_sdscat(json, "\n]");
    hisds jsonpath = hi_sdsnew(config.cluster_manager_command.backup_dir);
    if (jsonpath[hi_sdslen(jsonpath) - 1] != '/')
        jsonpath = hi_sdscat(jsonpath, "/");
    jsonpath = hi_sdscat(jsonpath, "nodes.json");
    FILE *out = fopen(jsonpath, "w+");
    if (!out) {
        ;
        success = 0;
        goto cleanup;
    }
    ;
  cleanup:
    ;
    return success;
  invalid_args:
    ;
    return 0;
}
static int clusterManagerCommandHelp (int argc, char **argv){
    ;
    int commands_count;
    int i, j;
    int padding;
    int options_count;
    return 0;
}
static void latencyMode (){
    redisReply *reply;
    long long start, latency, min, max, tot, count;
    long long history_interval = config.interval ? config.interval / 1000 : 15000;
    double avg;
    long long history_start = mstime();
    if (config.interval == 0) {
        config.interval = 1000;
    } else {
        config.interval /= 1000;
    }
    if (!context)
        exit(1);
    while (1)
        {
            start = mstime();
            reply = reconnectingRedisCommand(context, "PING");
            if (reply == ((void *)0)) {
                ;
            }
            latency = mstime() - start;
            if (config.output == 0) {
                ;
            } else {
                if (config.latency_history) {
                    ;
                } else if (mstime() - history_start > config.interval) {
                    ;
                    exit(0);
                }
            }
            if (config.latency_history && mstime() - history_start > history_interval) {
                printf(" -- %.2f seconds range\n", (float)(mstime() - history_start) / 1000);
                history_start = mstime();
            }
            ;
        }
}
static void latencyDistMode (){
    redisReply *reply;
    long long start, latency, count = 0;
    long long history_interval = config.interval ? config.interval / 1000 : 1000;
    long long history_start = ustime();
    int j, outputs;
    struct distsamples samples[] = {{10, 0, '.'}, {125, 0, '-'}, {250, 0, '*'}, {500, 0, '#'}, {1000, 0, '1'}, {2000, 0, '2'}, {3000, 0, '3'}, {4000, 0, '4'}, {5000, 0, '5'}, {6000, 0, '6'}, {7000, 0, '7'}, {8000, 0, '8'}, {9000, 0, '9'}, {10000, 0, 'A'}, {20000, 0, 'B'}, {30000, 0, 'C'}, {40000, 0, 'D'}, {50000, 0, 'E'}, {100000, 0, 'F'}, {200000, 0, 'G'}, {300000, 0, 'H'}, {400000, 0, 'I'}, {500000, 0, 'J'}, {1000000, 0, 'K'}, {2000000, 0, 'L'}, {4000000, 0, 'M'}, {8000000, 0, 'N'}, {16000000, 0, 'O'}, {30000000, 0, 'P'}, {60000000, 0, 'Q'}, {0, 0, '?'}};
    if (!context)
        exit(1);
    while (1)
        {
            start = ustime();
            reply = reconnectingRedisCommand(context, "PING");
            if (reply == ((void *)0)) {
                ;
            }
            latency = ustime() - start;
            count++;
            if (count && (ustime() - history_start) / 1000 > history_interval) {
                ;
                history_start = ustime();
                count = 0;
            }
            ;
        }
}
extern int sendReplconf (const char *arg1, const char *arg2){
    int res = 1;
    redisReply *reply = redisCommand(context, "REPLCONF %s %s", arg1, arg2);
    if (reply == ((void *)0)) {
        ;
    } else if (reply->type == 6) {
        ;
        res = 0;
    }
    ;
    return res;
}
extern void sendCapa (){
    sendReplconf("capa", "eof");
}
extern void sendRdbOnly (){
    sendReplconf("rdb-only", "1");
}
static ssize_t readConn (redisContext *c, char *buf, size_t len){
    return c->funcs->read(c, buf, len);
}
extern unsigned long long sendSync (redisContext *c, int send_sync, char *out_eof, int *out_full_mode){
    char buf[4096], *p;
    ssize_t nread;
    if (out_full_mode)
        *out_full_mode = 1;
    if (send_sync) {
        if (cliWriteConn(c, "SYNC\r\n", 6) != 6) {
            ;
        }
    } else {
        if (cliWriteConn(c, "", 0) != 0) {
            ;
        }
    }
    p = buf;
    while (1)
        {
            nread = readConn(c, p, 1);
            if (nread <= 0) {
                ;
            }
            if (*p == '\n' && p != buf)
                break;
            if (*p != '\n')
                p++;
            if (p >= buf + sizeof (buf) - 1)
                break;
        }
    *p = '\x00';
    if (buf[0] == '-') {
        ;
    }
    if (!strncmp(buf, "+FULLRESYNC", 11) || !strncmp(buf, "+CONTINUE", 9)) {
        int sync_partial = !strncmp(buf, "+CONTINUE", 9);
        p = buf;
        while (1)
            {
                nread = readConn(c, p, 1);
                if (nread <= 0) {
                    ;
                }
                if (*p == '\n' && p != buf)
                    break;
                if (*p != '\n')
                    p++;
                if (p >= buf + sizeof (buf) - 1)
                    break;
            }
        *p = '\x00';
        if (sync_partial) {
            if (out_full_mode)
                *out_full_mode = 0;
            return 0;
        }
    }
    if (strncmp(buf + 1, "EOF:", 4) == 0 && strlen(buf + 5) >= 40) {
        memcpy(out_eof, buf + 5, 40);
        return 0;
    }
    return strtoull(buf + 1, ((void *)0), 10);
}
static void slaveMode (int send_sync){
    static char eofmark[40];
    static char lastbytes[40];
    static int usemark;
    static int out_full_mode;
    unsigned long long payload = sendSync(context, send_sync, eofmark, &out_full_mode);
    char buf[1024];
    int original_output = config.output;
    char *info;
    if (out_full_mode == 1 && payload == 0) {
        payload = (9223372036854775807LL * 2ULL + 1ULL);
        memset(lastbytes, 0, 40);
        usemark = 1;
    } else {
        ;
    }
    while (payload)
        {
            ssize_t nread;
            nread = readConn(context, buf, (payload > sizeof (buf)) ? sizeof (buf) : payload);
            if (nread <= 0) {
                ;
            }
            payload -= nread;
            if (usemark) {
                if (nread >= 40) {
                    memcpy(lastbytes, buf + nread - 40, 40);
                } else {
                    int rem = 40 - nread;
                    memmove(lastbytes, lastbytes + nread, rem);
                    memcpy(lastbytes + rem, buf, nread);
                }
                if (memcmp(lastbytes, eofmark, 40) == 0)
                    break;
            }
        }
    if (usemark) {
        unsigned long long offset;
        sendReplconf("ACK", "0");
    } else {
        ;
    }
    config.output = 2;
    while (cliReadReply(0) == 0)
        ;
    config.output = original_output;
}
static void getRDB (clusterManagerNode *node){
    int fd;
    redisContext *s;
    char *filename;
    if (node != ((void *)0)) {
        ((void)sizeof ((node->context) ? 1 : 0) , __extension__ ({
            if (node->context)
                ;
            else
                __assert_fail("node->context", "redis-cli_InstSlice.c", 7807, __extension__ __PRETTY_FUNCTION__);
        }));
        s = node->context;
        filename = clusterManagerGetNodeRDBFilename(node);
    } else {
        s = context;
        filename = config.rdb_filename;
    }
    static char eofmark[40];
    static char lastbytes[40];
    static int usemark;
    unsigned long long payload = sendSync(s, 1, eofmark, ((void *)0));
    char buf[4096];
    if (payload == 0) {
        payload = (9223372036854775807LL * 2ULL + 1ULL);
        memset(lastbytes, 0, 40);
        usemark = 1;
    } else {
        ;
    }
    int write_to_stdout = !strcmp(filename, "-");
    if (write_to_stdout) {
        fd = 1;
    } else {
        fd = open(filename, 64 | 1, 420);
        if (fd == -1) {
            ;
        }
    }
    while (payload)
        {
            ssize_t nread, nwritten;
            nread = readConn(s, buf, (payload > sizeof (buf)) ? sizeof (buf) : payload);
            if (nread <= 0) {
                ;
            }
            nwritten = write(fd, buf, nread);
            if (nwritten != nread) {
                ;
            }
            payload -= nread;
            if (usemark) {
                if (nread >= 40) {
                    memcpy(lastbytes, buf + nread - 40, 40);
                } else {
                    int rem = 40 - nread;
                    memmove(lastbytes, lastbytes + nread, rem);
                    memcpy(lastbytes + rem, buf, nread);
                }
                if (memcmp(lastbytes, eofmark, 40) == 0)
                    break;
            }
        }
    ;
    if (node)
        node->context = ((void *)0);
    if (!write_to_stdout && fsync(fd) == -1) {
        ;
    }
    ;
    if (node) {
        ;
        return;
    }
    ;
}
static redisReply * sendScan (unsigned long long *it){
    redisReply *reply;
    if (config.pattern) {
        reply = redisCommand(context, "SCAN %llu MATCH %b COUNT %d", *it, config.pattern, hi_sdslen(config.pattern), config.count);
    } else
        reply = redisCommand(context, "SCAN %llu COUNT %d", *it, config.count);
    if (reply == ((void *)0)) {
        ;
    } else if (reply->type == 6) {
        ;
    } else if (reply->type != 2) {
        ;
    } else if (reply->elements != 2) {
        ;
    }
    ((void)sizeof ((reply->element[0]->type == 1) ? 1 : 0) , __extension__ ({
        if (reply->element[0]->type == 1)
            ;
        else
            __assert_fail("reply->element[0]->type == REDIS_REPLY_STRING", "redis-cli_InstSlice.c", 7919, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((reply->element[1]->type == 2) ? 1 : 0) , __extension__ ({
        if (reply->element[1]->type == 2)
            ;
        else
            __assert_fail("reply->element[1]->type == REDIS_REPLY_ARRAY", "redis-cli_InstSlice.c", 7920, __extension__ __PRETTY_FUNCTION__);
    }));
    *it = strtoull(reply->element[0]->str, ((void *)0), 10);
    return reply;
}
static int getDbSize (){
    redisReply *reply;
    int size;
    reply = redisCommand(context, "DBSIZE");
    if (reply == ((void *)0)) {
        ;
    } else if (reply->type == 6) {
        ;
    } else if (reply->type != 3) {
        ;
    }
    size = reply->integer;
    return size;
}
static int getDatabases (){
    redisReply *reply;
    int dbnum;
    reply = redisCommand(context, "CONFIG GET databases");
    if (reply == ((void *)0)) {
        ;
    } else if (reply->type == 6) {
        dbnum = 16;
    } else {
        ((void)sizeof ((reply->type == (config.current_resp3 ? 9 : 2)) ? 1 : 0) , __extension__ ({
            if (reply->type == (config.current_resp3 ? 9 : 2))
                ;
            else
                __assert_fail("reply->type == (config.current_resp3 ? REDIS_REPLY_MAP : REDIS_REPLY_ARRAY)", "redis-cli_InstSlice.c", 7965, __extension__ __PRETTY_FUNCTION__);
        }));
        ((void)sizeof ((reply->elements == 2) ? 1 : 0) , __extension__ ({
            if (reply->elements == 2)
                ;
            else
                __assert_fail("reply->elements == 2", "redis-cli_InstSlice.c", 7966, __extension__ __PRETTY_FUNCTION__);
        }));
        dbnum = atoi(reply->element[1]->str);
    }
    ;
    return dbnum;
}
static typeinfo * typeinfo_add (dict *types, char *name, typeinfo *type_template){
    typeinfo *info = zmalloc(sizeof(typeinfo));
    info->name = hi_sdsnew(name);
    return info;
}
static void getKeyTypes (dict *types_dict, redisReply *keys, typeinfo **types){
    redisReply *reply;
    unsigned int i;
    for (i = 0; i < keys->elements; i++) {
        const char *argv[] = {"TYPE", keys->element[i]->str};
        size_t lens[] = {4, keys->element[i]->len};
    }
    for (i = 0; i < keys->elements; i++) {
        if (redisGetReply(context, (void **)&reply) != 0) {
            ;
        } else if (reply->type != 5) {
            ;
        }
        hisds typereply = hi_sdsnew(reply->str);
        dictEntry *de = dictFind(types_dict, typereply);
        typeinfo *type = ((void *)0);
        if (de) {
            type = dictGetVal(de);
        } else if (strcmp(reply->str, "none"))
            type = typeinfo_add(types_dict, reply->str, &type_other);
        types[i] = type;
    }
}
static void getKeySizes (redisReply *keys, typeinfo **types, unsigned long long *sizes, int memkeys, long long memkeys_samples){
    redisReply *reply;
    unsigned int i;
    for (i = 0; i < keys->elements; i++) {
        if (!types[i] || (!types[i]->sizecmd && !memkeys))
            continue;
        if (!memkeys) {
            const char *argv[] = {types[i]->sizecmd, keys->element[i]->str};
            size_t lens[] = {strlen(types[i]->sizecmd), keys->element[i]->len};
        } else if (memkeys_samples == -1) {
            const char *argv[] = {"MEMORY", "USAGE", keys->element[i]->str};
            size_t lens[] = {6, 5, keys->element[i]->len};
        } else {
            hisds samplesstr = hi_sdsfromlonglong(memkeys_samples);
            const char *argv[] = {"MEMORY", "USAGE", keys->element[i]->str, "SAMPLES", samplesstr};
            size_t lens[] = {6, 5, keys->element[i]->len, 7, hi_sdslen(samplesstr)};
        }
    }
    for (i = 0; i < keys->elements; i++) {
        if (!types[i] || (!types[i]->sizecmd && !memkeys)) {
            sizes[i] = 0;
            continue;
        }
        if (redisGetReply(context, (void **)&reply) != 0) {
            ;
        } else if (reply->type != 3) {
            ;
            sizes[i] = 0;
        } else {
            sizes[i] = reply->integer;
        }
        ;
    }
}
static void sendReadOnly (){
    redisReply *read_reply;
    read_reply = redisCommand(context, "READONLY");
    if (read_reply == ((void *)0)) {
        ;
    } else if (read_reply->type == 6 && strcmp(read_reply->str, "ERR This instance has cluster support disabled") != 0 && strncmp(read_reply->str, "ERR unknown command", 19) != 0) {
        ;
    }
    ;
}
static void findBigKeys (int memkeys, long long memkeys_samples){
    unsigned long long sampled = 0, total_keys, totlen = 0, *sizes = ((void *)0), it = 0, scan_loops = 0;
    redisReply *reply, *keys;
    unsigned int arrsize = 0, i;
    dictIterator di;
    dictEntry *de;
    typeinfo **types = ((void *)0);
    double pct;
    long long refresh_time = mstime();
    dict *types_dict = dictCreate(&typeinfoDictType);
    typeinfo_add(types_dict, "string", &type_string);
    typeinfo_add(types_dict, "list", &type_list);
    typeinfo_add(types_dict, "set", &type_set);
    typeinfo_add(types_dict, "hash", &type_hash);
    typeinfo_add(types_dict, "zset", &type_zset);
    typeinfo_add(types_dict, "stream", &type_stream);
    total_keys = getDbSize();
    sendReadOnly();
    do {
        pct = 100 * (double)sampled / total_keys;
        reply = sendScan(&it);
        scan_loops++;
        keys = reply->element[1];
        if (keys->elements > arrsize) {
            types = zrealloc(types, sizeof(typeinfo *) * keys->elements);
            sizes = zrealloc(sizes, sizeof(unsigned long long) * keys->elements);
            if (!types || !sizes) {
                ;
            }
            arrsize = keys->elements;
        }
        getKeyTypes(types_dict, keys, types);
        getKeySizes(keys, types, sizes, memkeys, memkeys_samples);
        for (i = 0; i < keys->elements; i++) {
            typeinfo *type = types[i];
            if (!type)
                continue;
            type->totalsize += sizes[i];
            type->count++;
            totlen += keys->element[i]->len;
            sampled++;
            if (type->biggest < sizes[i]) {
                ;
                type->biggest_key = hi_sdscatrepr(hi_sdsempty(), keys->element[i]->str, keys->element[i]->len);
                if (!type->biggest_key) {
                    ;
                }
                type->biggest = sizes[i];
            }
            if (mstime() > refresh_time + 300 && (isatty(1) || getenv("FAKETTY"))) {
                int line_count = 0;
                refresh_time = mstime();
                line_count = displayKeyStatsProgressbar(sampled, total_keys);
                line_count += cleanPrintfln("");
                while ((de = dictNext(&di)))
                    {
                        typeinfo *current_type = dictGetVal(de);
                        if (current_type->biggest > 0) {
                            line_count += cleanPrintfln("Biggest %-9s found so far %s with %llu %s", current_type->name, current_type->biggest_key, current_type->biggest, !memkeys ? current_type->sizeunit : "bytes");
                        }
                    }
                ;
            }
        }
        ;
    } while (force_cancel_loop == 0 && it != 0);
    if ((isatty(1) || getenv("FAKETTY"))) {
        displayKeyStatsProgressbar(sampled, total_keys);
        int line_count = 0;
        while ((de = dictNext(&di)))
            line_count += cleanPrintfln("");
    }
    ;
}
static void getKeyFreqs (redisReply *keys, unsigned long long *freqs){
    redisReply *reply;
    unsigned int i;
    for (i = 0; i < keys->elements; i++) {
        const char *argv[] = {"OBJECT", "FREQ", keys->element[i]->str};
        size_t lens[] = {6, 4, keys->element[i]->len};
    }
    for (i = 0; i < keys->elements; i++) {
        if (redisGetReply(context, (void **)&reply) != 0) {
            hisds keyname = hi_sdscatrepr(hi_sdsempty(), keys->element[i]->str, keys->element[i]->len);
        } else if (reply->type != 3) {
            if (reply->type == 6) {
                ;
            } else {
                hisds keyname = hi_sdscatrepr(hi_sdsempty(), keys->element[i]->str, keys->element[i]->len);
                freqs[i] = 0;
            }
        } else {
            freqs[i] = reply->integer;
        }
        ;
    }
}
static void findHotKeys (){
    redisReply *keys, *reply;
    unsigned long long counters[16] = {0};
    hisds hotkeys[16] = {((void *)0)};
    unsigned long long sampled = 0, total_keys, *freqs = ((void *)0), it = 0, scan_loops = 0;
    unsigned int arrsize = 0, i;
    int k;
    double pct;
    long long refresh_time = mstime();
    total_keys = getDbSize();
    sendReadOnly();
    do {
        pct = 100 * (double)sampled / total_keys;
        reply = sendScan(&it);
        scan_loops++;
        keys = reply->element[1];
        if (keys->elements > arrsize) {
            freqs = zrealloc(freqs, sizeof(unsigned long long) * keys->elements);
            if (!freqs) {
                ;
            }
            arrsize = keys->elements;
        }
        getKeyFreqs(keys, freqs);
        for (i = 0; i < keys->elements; i++) {
            sampled++;
            k = 0;
            while (k < 16 && freqs[i] > counters[k])
                k++;
            if (k == 0)
                continue;
            k--;
            if (k == 0 || counters[k] == 0) {
                ;
            } else {
                ;
                memmove(counters, counters + 1, sizeof (counters[0]) * k);
                memmove(hotkeys, hotkeys + 1, sizeof (hotkeys[0]) * k);
            }
            counters[k] = freqs[i];
            hotkeys[k] = hi_sdscatrepr(hi_sdsempty(), keys->element[i]->str, keys->element[i]->len);
        }
        if (mstime() > refresh_time + 300 && (isatty(1) || getenv("FAKETTY"))) {
            int line_count = 0;
            refresh_time = mstime();
            line_count = displayKeyStatsProgressbar(sampled, total_keys);
            line_count += cleanPrintfln("");
            for (k = 16 - 1; k >= 0; k--) {
                if (counters[k] > 0) {
                    line_count += cleanPrintfln("hot key found with counter: %llu\tkeyname: %s", counters[k], hotkeys[k]);
                }
            }
            ;
        }
        ;
    } while (force_cancel_loop == 0 && it != 0);
    if ((isatty(1) || getenv("FAKETTY"))) {
        displayKeyStatsProgressbar(sampled, total_keys);
        int line_count = 0;
        for (k = 0; k <= 16; k++)
            line_count += cleanPrintfln("");
    }
    ;
}
static char * getInfoField (char *info, char *field){
    char *p = strstr(info, field);
    char *n1, *n2;
    char *result;
    if (!p)
        return ((void *)0);
    p += strlen(field) + 1;
    n1 = strchr(p, '\r');
    n2 = strchr(p, ',');
    if (n2 && n2 < n1)
        n1 = n2;
    result = zmalloc(sizeof(char) * (n1 - p) + 1);
    result[n1 - p] = '\x00';
    return result;
}
static long getLongInfoField (char *info, char *field){
    char *value = getInfoField(info, field);
    long l;
    if (!value)
        return (-9223372036854775807L - 1L);
    l = strtol(value, ((void *)0), 10);
    return l;
}
extern char * bytesToHuman (char *s, size_t size, long long n){
    double d;
    char *r = s;
    if (n < 0) {
        *s = '-';
    }
    return r;
}
static void statMode (){
    redisReply *reply;
    long aux, requests = 0;
    int dbnum = getDatabases();
    int i = 0;
    while (1)
        {
            char buf[64];
            int j;
            reply = reconnectingRedisCommand(context, "INFO");
            if (reply == ((void *)0)) {
                ;
            } else if (reply->type == 6) {
                ;
            }
            if ((i++ % 20) == 0) {
                ;
            }
            aux = 0;
            for (j = 0; j < dbnum; j++) {
                long k;
                k = getLongInfoField(reply->str, buf);
                if (k == (-9223372036854775807L - 1L))
                    continue;
                aux += k;
            }
            ;
            aux = getLongInfoField(reply->str, "used_memory");
            bytesToHuman(buf, sizeof (buf), aux);
            aux = getLongInfoField(reply->str, "connected_clients");
            aux = getLongInfoField(reply->str, "blocked_clients");
            aux = getLongInfoField(reply->str, "total_commands_processed");
            requests = aux;
            aux = getLongInfoField(reply->str, "total_connections_received");
            aux = getLongInfoField(reply->str, "bgsave_in_progress");
            aux |= getLongInfoField(reply->str, "aof_rewrite_in_progress") << 1;
            aux |= getLongInfoField(reply->str, "loading") << 2;
        }
}
static void scanMode (){
    redisReply *reply;
    unsigned long long cur = 0;
    do {
        reply = sendScan(&cur);
    } while (force_cancel_loop == 0 && cur != 0);
}
static void LRUTestMode (){
    redisReply *reply;
    char key[128];
    long long start_cycle;
    int j;
    while (1)
        {
            start_cycle = mstime();
            long long hits = 0, misses = 0;
            while (mstime() - start_cycle < 1000)
                {
                    for (j = 0; j < 250; j++) {
                        char val[6];
                        val[5] = '\x00';
                        for (int i = 0; i < 5; i++)
                            val[i] = 'A' + rand() % ('z' - 'A');
                    }
                    ;
                    for (j = 0; j < 250; j++) {
                        if (redisGetReply(context, (void **)&reply) == 0) {
                            switch (reply->type) {
                              case 6:
                                ;
                                break;
                              case 4:
                                misses++;
                                break;
                              default:
                                hits++;
                                break;
                            }
                        }
                    }
                    if (context->err) {
                        ;
                    }
                }
            ;
        }
    ;
}
static void intrinsicLatencyMode (){
    long long test_end, run_time, max_latency = 0, runs = 0;
    run_time = (long long)config.intrinsic_latency_duration * 1000000;
    test_end = ustime() + run_time;
    while (1)
        {
            long long start, end, latency;
            start = ustime();
            end = ustime();
            double avg_us;
            double avg_ns;
            if (force_cancel_loop || end > test_end) {
                ;
            }
        }
}
static hisds askPassword (const char *msg){
    ;
    hisds auth = linenoise(msg);
    return auth;
}
extern void testHint (const char *input){
    cliInitHelp();
    hisds hint = getHintForInput(input);
    exit(0);
}
extern hisds readHintSuiteLine (char buf[], size_t size, FILE *fp){
    while (fgets(buf, size, fp) != ((void *)0))
        {
            if (buf[0] != '#') {
                hisds input = hi_sdsnew(buf);
                input = hi_sdstrim(input, "\n");
                return input;
            }
        }
    return ((void *)0);
}
extern void testHintSuite (char *filename){
    FILE *fp;
    char buf[256];
    hisds line, input, expected, hint;
    int pass = 0, fail = 0;
    int argc;
    char **argv;
    fp = fopen(filename, "r");
    if (!fp) {
        ;
    }
    cliInitHelp();
    while (1)
        {
            line = readHintSuiteLine(buf, sizeof (buf), fp);
            if (line == ((void *)0))
                break;
            argv = hi_sdssplitargs(line, &argc);
            if (argc == 0) {
                ;
                continue;
            }
            if (argc == 1) {
                ;
            }
            input = argv[0];
            expected = argv[1];
            hint = getHintForInput(input);
            while (hint != ((void *)0) && hi_sdslen(hint) > 0 && hint[hi_sdslen(hint) - 1] == ' ')
                {
                    hi_sdssetlen(hint, hi_sdslen(hint) - 1);
                    hint[hi_sdslen(hint)] = '\x00';
                }
            if (hint == ((void *)0) || strcmp(hint, expected) != 0) {
                ;
                ++fail;
            } else {
                ++pass;
            }
            ;
        }
    ;
}
static void sizeDistInit (size_dist *dist, size_dist_entry *distribution){
    dist->max_size = 0;
    dist->total_count = 0;
    dist->total_size = 0;
    dist->size_dist = distribution;
}
static void addSizeDist (size_dist *dist, unsigned long long size){
    dist->total_count++;
    dist->total_size += size;
    if (size > dist->max_size)
        dist->max_size = size;
    int j;
    for (j = 0; dist->size_dist[j].size && size > dist->size_dist[j].size; j++)
        ;
    dist->size_dist[j].count++;
}
static int displayKeyStatsLengthDist (size_dist *dist){
    int line_count = 0;
    unsigned long long total_keys = 0, size;
    char buf[2][256];
    line_count += cleanPrintfln("Key name length Percentile Total keys");
    line_count += cleanPrintfln("--------------- ---------- -----------");
    for (int i = 0; dist->size_dist[i].size; i++) {
        if (dist->size_dist[i].count) {
            if (dist->max_size < dist->size_dist[i].size) {
                size = dist->max_size;
            } else {
                size = dist->size_dist[i].size;
            }
            total_keys += dist->size_dist[i].count;
            line_count += cleanPrintfln("%15s %9.4f%% %11llu", bytesToHuman(buf[1], sizeof (buf[1]), size), (double)100 * total_keys / dist->total_count, total_keys);
        }
    }
    if (total_keys < dist->total_count) {
        line_count += cleanPrintfln("           inf %9.4f%% %11llu", 100., dist->total_count);
    }
    line_count += cleanPrintfln("Total key length is %s (%s avg)", bytesToHuman(buf[0], sizeof (buf[0]), dist->total_size), dist->total_count ? bytesToHuman(buf[1], sizeof (buf[1]), dist->total_size / dist->total_count) : "0");
    return line_count;
}
static int displayKeyStatsProgressbar (unsigned long long sampled, unsigned long long total_keys){
    int line_count = 0;
    char progressbar[512];
    char buf[2][128];
    double completion_pct = total_keys ? sampled < total_keys ? (double)sampled / total_keys : 1 : 0;
    line_count += cleanPrintfln("%6.2f%% %s", completion_pct * 100, progressbar);
    line_count += cleanPrintfln("Keys sampled: %llu", sampled);
    return line_count;
}
static int displayKeyStatsSizeType (dict *memkeys_types_dict){
    dictIterator di;
    dictEntry *de;
    int line_count = 0;
    char buf[256];
    line_count += cleanPrintfln("--- Top size per type ---");
    while ((de = dictNext(&di)))
        {
            typeinfo *type = dictGetVal(de);
            if (type->biggest_key) {
                line_count += cleanPrintfln("%-10s %s is %s", type->name, type->biggest_key, bytesToHuman(buf, sizeof (buf), type->biggest));
            }
        }
    ;
    return line_count;
}
static int displayKeyStatsLengthType (dict *bigkeys_types_dict){
    dictIterator di;
    dictEntry *de;
    int line_count = 0;
    char buf[256];
    line_count += cleanPrintfln("--- Top length and cardinality per type ---");
    while ((de = dictNext(&di)))
        {
            typeinfo *type = dictGetVal(de);
            if (type->biggest_key) {
                if (!strcmp(type->sizeunit, "bytes")) {
                    bytesToHuman(buf, sizeof (buf), type->biggest);
                } else {
                    ;
                }
                line_count += cleanPrintfln("%-10s %s has %s", type->name, type->biggest_key, buf);
            }
        }
    ;
    return line_count;
}
static int displayKeyStatsSizeDist (struct hdr_histogram *keysize_histogram){
    int line_count = 0;
    double percentile;
    char size[32], mean[32], stddev[32];
    struct hdr_iter iter;
    int64_t last_displayed_cumulative_count = 0;
    line_count += cleanPrintfln("Key size Percentile Total keys");
    line_count += cleanPrintfln("-------- ---------- -----------");
    while (hdr_iter_next(&iter))
        {
            if (iter.cumulative_count != last_displayed_cumulative_count) {
                if (iter.cumulative_count == iter.h->total_count) {
                    percentile = 100;
                } else {
                    percentile = iter.specifics.percentiles.percentile;
                }
                line_count += cleanPrintfln("%8s %9.4f%% %11lld", bytesToHuman(size, sizeof (size), iter.highest_equivalent_value), percentile, iter.cumulative_count);
                last_displayed_cumulative_count = iter.cumulative_count;
            }
        }
    bytesToHuman(mean, sizeof (mean), hdr_mean(keysize_histogram));
    bytesToHuman(stddev, sizeof (stddev), hdr_stddev(keysize_histogram));
    line_count += cleanPrintfln("Note: 0.01%% size precision, Mean: %s, StdDeviation: %s", mean, stddev);
    return line_count;
}
static int displayKeyStatsType (unsigned long long sampled, dict *memkeys_types_dict, dict *bigkeys_types_dict){
    dictIterator di;
    dictEntry *de;
    int line_count = 0;
    char total_size[64], size_avg[64], total_length[64], length_avg[64];
    line_count += cleanPrintfln("Type        Total keys  Keys %% Tot size Avg size  Total length/card Avg ln/card");
    line_count += cleanPrintfln("--------- ------------ ------- -------- -------- ------------------ -----------");
    while ((de = dictNext(&di)))
        {
            typeinfo *memkey_type = dictGetVal(de);
            if (memkey_type->count) {
                bytesToHuman(total_size, sizeof (total_size), memkey_type->totalsize);
                bytesToHuman(size_avg, sizeof (size_avg), memkey_type->totalsize / memkey_type->count);
                strncpy(total_length, " - ", sizeof (total_length));
                strncpy(length_avg, " - ", sizeof (length_avg));
                dictEntry *bk_de = dictFind(bigkeys_types_dict, memkey_type->name);
                if (bk_de) {
                    typeinfo *bigkey_type = dictGetVal(bk_de);
                    if (bigkey_type->sizecmd && bigkey_type->count) {
                        double avg = (double)bigkey_type->totalsize / bigkey_type->count;
                        if (!strcmp(bigkey_type->sizeunit, "bytes")) {
                            bytesToHuman(total_length, sizeof (total_length), bigkey_type->totalsize);
                            bytesToHuman(length_avg, sizeof (length_avg), (long long)round(avg));
                        } else {
                            ;
                        }
                    }
                }
                line_count += cleanPrintfln("%-10s %11llu %6.2f%% %8s %8s %18s %11s", memkey_type->name, memkey_type->count, sampled ? 100 * (double)memkey_type->count / sampled : 0, total_size, size_avg, total_length, length_avg);
            }
        }
    ;
    return line_count;
}
static int displayKeyStatsTopSizes (list *top_key_sizes, unsigned long top_sizes_limit){
    int line_count = 0, i = 0;
    line_count += cleanPrintfln("--- Top %llu key sizes ---", top_sizes_limit);
    char buffer[32];
    listIter iter;
    listNode *node;
    while ((node = listNext(&iter)) != ((void *)0))
        {
            key_info *key = (key_info *)((node)->value);
            line_count += cleanPrintfln("%3d %8s %-10s %s", ++i, bytesToHuman(buffer, sizeof (buffer), key->size), key->type_name, key->key_name);
        }
    return line_count;
}
static key_info * createKeySizeInfo (char *key_name, size_t key_name_len, char *key_type, unsigned long long size){
    key_info *key = zmalloc(sizeof(key_info));
    key->size = size;
    key->key_name = hi_sdscatrepr(hi_sdsempty(), key_name, key_name_len);
    return key;
}
static int updateTopSizes (char *key_name, size_t key_name_len, unsigned long long key_size, char *type_name, list *topkeys, unsigned long top_sizes_limit){
    listNode *node;
    listIter iter;
    key_info *new_node;
    if (top_sizes_limit != 0 && topkeys->len == top_sizes_limit && key_size <= ((key_info *)topkeys->tail->value)->size) {
        return 0;
    }
    ;
    new_node = createKeySizeInfo(key_name, key_name_len, type_name, key_size);
    return 1;
}
static void displayKeyStats (unsigned long long sampled, unsigned long long total_keys, unsigned long long total_size, dict *memkeys_types_dict, dict *bigkeys_types_dict, list *top_key_sizes, unsigned long top_sizes_limit, int move_cursor_up){
    int line_count;
    char buf[256];
    line_count += displayKeyStatsProgressbar(sampled, total_keys);
    line_count += cleanPrintfln("Keys size:    %s", bytesToHuman(buf, sizeof (buf), total_size));
    line_count += cleanPrintfln("");
    line_count += displayKeyStatsTopSizes(top_key_sizes, top_sizes_limit);
    line_count += cleanPrintfln("");
    line_count += displayKeyStatsSizeType(memkeys_types_dict);
    line_count += cleanPrintfln("");
    line_count += displayKeyStatsLengthType(bigkeys_types_dict);
}
static void updateKeyType (redisReply *element, unsigned long long size, typeinfo *type){
    type->totalsize += size;
    type->count++;
    if (type->biggest < size) {
        ;
        type->biggest_key = hi_sdsnewlen(element->str, element->len);
        if (!type->biggest_key) {
            ;
        }
        type->biggest = size;
    }
}
static void keyStats (long long memkeys_samples, unsigned long long cursor, unsigned long top_sizes_limit){
    unsigned long long sampled = 0, total_keys, total_size = 0, it = 0, scan_loops = 0;
    unsigned long long *memkeys_sizes = ((void *)0), *bigkeys_sizes = ((void *)0);
    redisReply *reply, *keys;
    unsigned int array_size = 0, i;
    typeinfo **memkeys_types = ((void *)0), **bigkeys_types = ((void *)0);
    list *top_sizes;
    long long refresh_time = mstime();
    if ((top_sizes = listCreate()) == ((void *)0)) {
        ;
    }
    top_sizes->free = zfree;
    dict *memkeys_types_dict = dictCreate(&typeinfoDictType);
    typeinfo_add(memkeys_types_dict, "string", &type_string);
    typeinfo_add(memkeys_types_dict, "list", &type_list);
    typeinfo_add(memkeys_types_dict, "set", &type_set);
    typeinfo_add(memkeys_types_dict, "hash", &type_hash);
    typeinfo_add(memkeys_types_dict, "zset", &type_zset);
    typeinfo_add(memkeys_types_dict, "stream", &type_stream);
    dict *bigkeys_types_dict = dictCreate(&typeinfoDictType);
    typeinfo_add(bigkeys_types_dict, "string", &type_string);
    typeinfo_add(bigkeys_types_dict, "list", &type_list);
    typeinfo_add(bigkeys_types_dict, "set", &type_set);
    typeinfo_add(bigkeys_types_dict, "hash", &type_hash);
    typeinfo_add(bigkeys_types_dict, "zset", &type_zset);
    typeinfo_add(bigkeys_types_dict, "stream", &type_stream);
    size_dist key_length_dist;
    size_dist_entry distribution[] = {{1 << 5, 0}, {1 << 8, 0}, {1 << 16, 0}, {1024 * 1024, 0}, {16 * 1024 * 1024, 0}, {128 * 1024 * 1024, 0}, {512 * 1024 * 1024, 0}, {0, 0}};
    sizeDistInit(&key_length_dist, distribution);
    struct hdr_histogram *keysize_histogram;
    if (hdr_init(1, 1ULL * 1024 * 1024 * 1024 * 1024, 4, &keysize_histogram)) {
        ;
    }
    ;
    total_keys = getDbSize();
    sendReadOnly();
    do {
        reply = sendScan(&it);
        scan_loops++;
        keys = reply->element[1];
        if (keys->elements > array_size) {
            memkeys_types = zrealloc(memkeys_types, sizeof(typeinfo *) * keys->elements);
            memkeys_sizes = zrealloc(memkeys_sizes, sizeof(unsigned long long) * keys->elements);
            bigkeys_types = zrealloc(bigkeys_types, sizeof(typeinfo *) * keys->elements);
            bigkeys_sizes = zrealloc(bigkeys_sizes, sizeof(unsigned long long) * keys->elements);
            if (!memkeys_types || !memkeys_sizes || !bigkeys_types || !bigkeys_sizes) {
                ;
            }
            array_size = keys->elements;
        }
        getKeyTypes(memkeys_types_dict, keys, memkeys_types);
        getKeySizes(keys, memkeys_types, memkeys_sizes, 1, memkeys_samples);
        getKeyTypes(bigkeys_types_dict, keys, bigkeys_types);
        getKeySizes(keys, bigkeys_types, bigkeys_sizes, 0, memkeys_samples);
        for (i = 0; i < keys->elements; i++) {
            if (!memkeys_types[i] || !bigkeys_types[i]) {
                continue;
            }
            total_size += memkeys_sizes[i];
            sampled++;
            updateTopSizes(keys->element[i]->str, keys->element[i]->len, memkeys_sizes[i], memkeys_types[i]->name, top_sizes, top_sizes_limit);
            updateKeyType(keys->element[i], memkeys_sizes[i], memkeys_types[i]);
            updateKeyType(keys->element[i], bigkeys_sizes[i], bigkeys_types[i]);
            addSizeDist(&key_length_dist, keys->element[i]->len);
        }
        if (mstime() > refresh_time + 300 && (isatty(1) || getenv("FAKETTY"))) {
            displayKeyStats(sampled, total_keys, total_size, memkeys_types_dict, bigkeys_types_dict, top_sizes, top_sizes_limit, 1);
            refresh_time = mstime();
        }
        ;
    } while (force_cancel_loop == 0 && it != 0);
    displayKeyStats(sampled, total_keys, total_size, memkeys_types_dict, bigkeys_types_dict, top_sizes, top_sizes_limit, 0);
    cleanPrintfln("");
    displayKeyStatsSizeDist(keysize_histogram);
    cleanPrintfln("");
    displayKeyStatsLengthDist(&key_length_dist);
    cleanPrintfln("");
    displayKeyStatsType(sampled, memkeys_types_dict, bigkeys_types_dict);
    if (it != 0) {
        ;
    }
    ;
    listIter iter;
    listNode *node;
}
extern int main (int argc, char **argv){
    int firstarg;
    struct timeval tv;
    memset(&config.sslconfig, 0, sizeof (config.sslconfig));
    config.conn_info.hostip = hi_sdsnew("127.0.0.1");
    config.conn_info.hostport = 6379;
    config.connect_timeout.tv_sec = 0;
    config.connect_timeout.tv_usec = 0;
    config.hostsocket = ((void *)0);
    config.repeat = 1;
    config.interval = 0;
    config.dbnum = 0;
    config.conn_info.input_dbnum = 0;
    config.interactive = 0;
    config.shutdown = 0;
    config.monitor_mode = 0;
    config.pubsub_mode = 0;
    config.blocking_state_aborted = 0;
    config.latency_mode = 0;
    config.latency_dist_mode = 0;
    config.latency_history = 0;
    config.lru_test_mode = 0;
    config.lru_test_sample_size = 0;
    config.cluster_mode = 0;
    config.cluster_send_asking = 0;
    config.slave_mode = 0;
    config.getrdb_mode = 0;
    config.get_functions_rdb_mode = 0;
    config.stat_mode = 0;
    config.scan_mode = 0;
    config.count = 10;
    config.intrinsic_latency_mode = 0;
    config.pattern = ((void *)0);
    config.rdb_filename = ((void *)0);
    config.pipe_mode = 0;
    config.pipe_timeout = 30;
    config.bigkeys = 0;
    config.memkeys = 0;
    config.keystats = 0;
    config.cursor = 0;
    config.top_sizes_limit = 10;
    config.hotkeys = 0;
    config.stdin_lastarg = 0;
    config.stdin_tag_arg = 0;
    config.stdin_tag_name = ((void *)0);
    config.conn_info.auth = ((void *)0);
    config.askpass = 0;
    config.conn_info.user = ((void *)0);
    config.eval = ((void *)0);
    config.eval_ldb = 0;
    config.eval_ldb_end = 0;
    config.eval_ldb_sync = 0;
    config.enable_ldb_on_eval = 0;
    config.last_cmd_type = -1;
    config.last_reply = ((void *)0);
    config.verbose = 0;
    config.set_errcode = 0;
    config.no_auth_warning = 0;
    config.in_multi = 0;
    config.server_version = ((void *)0);
    config.prefer_ipv4 = 0;
    config.prefer_ipv6 = 0;
    config.cluster_manager_command.name = ((void *)0);
    config.cluster_manager_command.argc = 0;
    config.cluster_manager_command.argv = ((void *)0);
    config.cluster_manager_command.stdin_arg = ((void *)0);
    config.cluster_manager_command.flags = 0;
    config.cluster_manager_command.replicas = 0;
    config.cluster_manager_command.from = ((void *)0);
    config.cluster_manager_command.to = ((void *)0);
    config.cluster_manager_command.from_user = ((void *)0);
    config.cluster_manager_command.from_pass = ((void *)0);
    config.cluster_manager_command.from_askpass = 0;
    config.cluster_manager_command.weight = ((void *)0);
    config.cluster_manager_command.weight_argc = 0;
    config.cluster_manager_command.slots = 0;
    config.cluster_manager_command.timeout = 60000;
    config.cluster_manager_command.pipeline = 10;
    config.cluster_manager_command.threshold = 2;
    config.cluster_manager_command.backup_dir = ((void *)0);
    pref.hints = 1;
    spectrum_palette = spectrum_palette_color;
    spectrum_palette_size = spectrum_palette_color_size;
    if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == ((void *)0))) {
        config.output = 1;
        config.push_output = 0;
    } else {
        config.output = 0;
        config.push_output = 1;
    }
    config.mb_delim = hi_sdsnew("\n");
    config.cmd_delim = hi_sdsnew("\n");
    firstarg = parseOptions(argc, argv);
    argc -= firstarg;
    argv += firstarg;
    parseEnv();
    if (config.askpass) {
        config.conn_info.auth = askPassword("Please input password: ");
    }
    if (config.cluster_manager_command.from_askpass) {
        config.cluster_manager_command.from_pass = askPassword("Please input import source node password: ");
    }
    ;
    if ((config.cluster_manager_command.name != ((void *)0))) {
        clusterManagerCommandProc *proc = validateClusterManagerCommand();
        if (!proc) {
            ;
        }
        clusterManagerMode(proc);
    }
    if (config.latency_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        latencyMode();
    }
    if (config.latency_dist_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        latencyDistMode();
    }
    if (config.slave_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        sendCapa();
        sendReplconf("rdb-filter-only", "");
        slaveMode(1);
    }
    if (config.getrdb_mode || config.get_functions_rdb_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        sendCapa();
        sendRdbOnly();
        if (config.get_functions_rdb_mode && !sendReplconf("rdb-filter-only", "functions")) {
            ;
        }
        getRDB(((void *)0));
    }
    if (config.pipe_mode) {
        if (cliConnect(0) == -1)
            exit(1);
    }
    if (config.bigkeys) {
        if (cliConnect(0) == -1)
            exit(1);
        findBigKeys(0, 0);
    }
    if (config.memkeys) {
        if (cliConnect(0) == -1)
            exit(1);
        findBigKeys(1, config.memkeys_samples);
    }
    if (config.keystats) {
        if (cliConnect(0) == -1)
            exit(1);
        keyStats(config.memkeys_samples, config.cursor, config.top_sizes_limit);
    }
    if (config.hotkeys) {
        if (cliConnect(0) == -1)
            exit(1);
        findHotKeys();
    }
    if (config.stat_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        if (config.interval == 0)
            config.interval = 1000000;
        statMode();
    }
    if (config.scan_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        scanMode();
    }
    if (config.lru_test_mode) {
        if (cliConnect(0) == -1)
            exit(1);
        LRUTestMode();
    }
    if (config.intrinsic_latency_mode)
        intrinsicLatencyMode();
    if (config.test_hint) {
        testHint(config.test_hint);
    }
    if (config.test_hint_file) {
        testHintSuite(config.test_hint_file);
    }
    if (argc == 0 && !config.eval) {
        ;
        cliConnect(0);
        repl();
    }
    if (config.eval) {
        if (cliConnect(0) != 0)
            exit(1);
        return evalMode(argc, argv);
    } else {
        cliConnect((1 << 1));
        return noninteractive(argc, argv);
    }
}

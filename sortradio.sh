find /media/RADIO/Radio /tmp/play3abn/cache/download* /tmp/play3abn/cache/Radio* -follow -name '*.ogg' | egrep -v "/FullBreak|/AfflBreak|/3ABN_TODAY|/1-SECOND|/NEWSBREAK|/Network_ID|/One_Second_Time_Fill|/TDY|/The_Latest|/TODAY" | sort -f

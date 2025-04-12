#!/bin/bash
nohup ./workers/cpu_worker.out >/dev/null 2>&1 & 
nohup ./workers/worker.out >/dev/null 2>&1 &
nohup ./workers/memory_worker.out >/dev/null 2>&1 &
/usr/sbin/sshd -D

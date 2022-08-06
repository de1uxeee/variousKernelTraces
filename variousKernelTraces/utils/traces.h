#pragma once
#include <ntifs.h>
#include "../src/Driver.h"

void outputPiDDBCache();
void outputMmUnloadedDrv();
void outputKernelHashBucketList();
void outputPEProcessHashBucketList();
void loopCiValidationList();
void loopCiEaCacheList();
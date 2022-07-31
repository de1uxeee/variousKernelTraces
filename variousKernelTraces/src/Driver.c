#include "../utils/traces.h"

void checkThread()
{
	outputPiDDBCache();
	outputKernelHashBucketList();
	outputPEProcessHashBucketList();
	loopCiValidationList();
	loopCiEaCacheList();
}

NTSTATUS DriverEntry(PVOID driver, PUNICODE_STRING path)
{
	UNREFERENCED_PARAMETER(driver);
	UNREFERENCED_PARAMETER(path);

	HANDLE thrHandle = { NULL };

	if (!NT_SUCCESS(PsCreateSystemThread(&thrHandle, THREAD_ALL_ACCESS, NULL, NULL, NULL, (PKSTART_ROUTINE)checkThread, NULL)))
		return STATUS_UNSUCCESSFUL;

	ZwClose(thrHandle);

	return STATUS_SUCCESS;
}
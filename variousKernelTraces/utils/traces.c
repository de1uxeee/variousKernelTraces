#include "traces.h"

void outputPiDDBCache()
{
	PRTL_AVL_TABLE PiDDBCacheTable = (PRTL_AVL_TABLE)0xfffff8070635bd50; //find this address by yourself

	PiDDBCacheEntry* firstEntry = (PiDDBCacheEntry*)PiDDBCacheTable->BalancedRoot.RightChild;
	*(UINT_PTR*)(&firstEntry) += sizeof(RTL_BALANCED_LINKS);

	PiDDBCacheEntry* currEntry = (PiDDBCacheEntry*)firstEntry->List.Flink;

	while (TRUE)
	{
		if (currEntry == firstEntry)
			break;

		DebugLog("name: %wZ, timestamp: 0x%lx\n", &currEntry->DriverName, currEntry->TimeDateStamp);

		currEntry = (PiDDBCacheEntry*)currEntry->List.Flink;
	}
}

void outputKernelHashBucketList()
{
	PRTL_AVL_TABLE list = (PRTL_AVL_TABLE)0xfffff80706b5c080; //find by yourself
	HashBucketEntry* currentEntry = (HashBucketEntry*)list->BalancedRoot.Parent;

	while (TRUE)
	{
		if (currentEntry == NULL)
			break;
	
		DebugLog("name: %wZ, hash: %lx%lx%lx%lx%lx\n", &currentEntry->DriverName, currentEntry->hash[0], currentEntry->hash[1], currentEntry->hash[2], currentEntry->hash[3], currentEntry->hash[4]);
	
		currentEntry = currentEntry->Next;
	}
}

void outputMmUnloadedDrv()
{
	PVOID mMUnloadedDrvPtr = *(PVOID*)0xfffff8057a23d790;
	PMM_UNLOADED_DRIVER mMUnloadedDrv = (PMM_UNLOADED_DRIVER)mMUnloadedDrvPtr;

	for (SIZE_T i = 0; i < 50; i++)
	{
		PMM_UNLOADED_DRIVER currDrv = &mMUnloadedDrv[i];
		if (currDrv->drvName.Length > 0)
			DebugLog("driver name: %wZ, unload time: %llx\n", &currDrv->drvName, currDrv->unloadTime);
	}
}

void outputPEProcessHashBucketList()
{
	PRTL_AVL_TABLE listPEHash = (PRTL_AVL_TABLE)0xfffff80706b5c070; //find by yourself
	PEProcessHashBucketList* currChild = (PEProcessHashBucketList*)listPEHash->BalancedRoot.RightChild;

	while (TRUE)
	{
		if (currChild == NULL)
			break;

		DebugLog("PE name: %wZ\n", &currChild->DriverName);

		currChild = currChild->Next;
	}
}

void loopCiValidationList()
{
	PAGED_LOOKASIDE_LIST* listCiValidationHashTable = (PAGED_LOOKASIDE_LIST*)0xfffff80706ad1500; //find by yourself

	PGENERAL_LOOKASIDE listCiValidationHashTableEntry = (PGENERAL_LOOKASIDE)listCiValidationHashTable->L.ListEntry.Flink;
	PLIST_ENTRY listCiValidationHashTableCurrEntry = (PLIST_ENTRY)listCiValidationHashTableEntry;

	while (TRUE)
	{
		PGENERAL_LOOKASIDE entryList = (PGENERAL_LOOKASIDE)((UINT_PTR)listCiValidationHashTableCurrEntry - 0x40);

		char tag[5] = { NULL };
		memcpy(tag, &entryList->Tag, 0x4);

		DebugLog("type %lx, tag: %s\n", entryList->Type, tag);

		listCiValidationHashTableCurrEntry = listCiValidationHashTableCurrEntry->Flink;

		if ((PLIST_ENTRY)listCiValidationHashTableEntry == listCiValidationHashTableCurrEntry)
			break;
	}
}

void loopCiEaCacheList()
{
	PAGED_LOOKASIDE_LIST* listCiEaHashTable = (PAGED_LOOKASIDE_LIST*)0xfffff80706ad1480; //find by yourself

	PGENERAL_LOOKASIDE listCiEaHashTableEntry = (PGENERAL_LOOKASIDE)listCiEaHashTable->L.ListEntry.Flink;
	PLIST_ENTRY listCiEaHashTableCurrEntry = (PLIST_ENTRY)listCiEaHashTableEntry;

	while (TRUE)
	{
		PGENERAL_LOOKASIDE entryList = (PGENERAL_LOOKASIDE)((UINT_PTR)listCiEaHashTableCurrEntry - 0x40);

		char tag[5] = { NULL };
		memcpy(tag, &entryList->Tag, 0x4);

		DebugLog("type %lx, tag: %s\n", entryList->Type, tag);

		listCiEaHashTableCurrEntry = listCiEaHashTableCurrEntry->Flink;

		if ((PLIST_ENTRY)listCiEaHashTableEntry == listCiEaHashTableCurrEntry)
			break;
	}
}
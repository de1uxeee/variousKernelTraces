#include <ntifs.h>

#define DebugLog(...) DbgPrintEx(0,0, __VA_ARGS__) 

typedef struct _PiDDBCacheEntry
{
	LIST_ENTRY               List;
	UNICODE_STRING			 DriverName;
	ULONG                    TimeDateStamp;
} PiDDBCacheEntry, * NPiDDBCacheEntry;

typedef struct _HashBucketEntry
{
	struct _HashBucketEntry* Next;
	UNICODE_STRING DriverName;
	ULONG hash[5];
} HashBucketEntry, * PHashBucketEntry;

typedef struct _PEProcessHashBucketList
{
	struct _PEProcessHashBucketList* Next;
	UNICODE_STRING DriverName;
} PEProcessHashBucketList, * PPEProcessHashBucketList;
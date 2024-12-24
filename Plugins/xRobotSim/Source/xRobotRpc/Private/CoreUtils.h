#pragma once
#include "StructTypeContainer.h"

namespace xRobotRpc
{
	FORCEINLINE bool UEObjectIsPendingKill(const UObject* Test)
	{
#if ENGINE_MAJOR_VERSION > 4
		return !IsValid(Test) || Test->IsUnreachable();
#else
		return Test->IsPendingKillOrUnreachable();
#endif
	}
	
	template <typename T>
	T* FindAnyType(const TCHAR* InShortName)
	{
#if (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1) || ENGINE_MAJOR_VERSION > 5
		return FindFirstObject<T>(
			InShortName, EFindFirstObjectOptions::EnsureIfAmbiguous | EFindFirstObjectOptions::NativeFirst, ELogVerbosity::Error);
#else
		return FindObject<T>(ANY_PACKAGE, InShortName);
#endif
	}

	template <typename T>
	T* FindAnyType(const FString& InShortName)
	{
		return FindAnyType<T>(*InShortName);
	}

	class FCoreUtils
	{
	public:
		static FStructTypeContainer* LoadUEType(const FString& TypeName);

		static FStructTypeContainer* GetUEType(const FString& TypeName);

	private:
		static TMap<UField*, FStructTypeContainer*> ClassTypeContainerCache;
	};
}
